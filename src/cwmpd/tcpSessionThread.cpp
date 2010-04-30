#include <iostream>

#include <QDomDocument>
#include <QTimer>

#include <QtCrypto>

#include "cwmpCtx.h"
#include "tcpSessionThread.h"

TCPSessionThread::TCPSessionThread(int socketDescriptor, QObject *parent)
: QThread(parent), _state(GET_HEADERS), _contentLen(0), _contentRead(0), _socketDescriptor(socketDescriptor) {
}

TCPSessionThread::~TCPSessionThread() {
}

void TCPSessionThread::run() {
    stateMachine();
}

void TCPSessionThread::stateMachine() {
    qDebug("%s, Hello...", __FUNCTION__);
    if(_state == GET_HEADERS) {
        handleGetHeadersState();
    } else if(_state == GET_CONTENT) {
        handleGetContentState();
    } else if(_state == PARSE_SOAP) {
        handleParseSoapState();
    }
}

void TCPSessionThread::handleGetContentState() {
    qDebug("%s, Hello...", __FUNCTION__);
    while(!_socket.bytesAvailable()) {
        qDebug("%s, %d: Nothing yet available to read", __FUNCTION__, __LINE__);
        QTimer::singleShot(10, this, SLOT(handleGetContentState()));
        qDebug("%s, %d: Nothing yet available to read", __FUNCTION__, __LINE__);
        return;
    }

    _contentRead += _socket.read(_content.data() + _contentRead, _contentLen - _contentRead);
    qDebug("%s, %d: _contentRead=%d, _contentLen=%d", __FUNCTION__, __LINE__, _contentRead, _contentLen);
    if(_contentRead < _contentLen) {
        qDebug("%s, %d: _contentRead=%d, _contentLen=%d", __FUNCTION__, __LINE__, _contentRead, _contentLen);
        QTimer::singleShot(10, this, SLOT(handleGetContentState()));
        qDebug("%s, %d: _contentRead=%d, _contentLen=%d", __FUNCTION__, __LINE__, _contentRead, _contentLen);
        return;
    }

    _state = PARSE_SOAP;
    QTimer::singleShot(0, this, SLOT(stateMachine()));
}

void TCPSessionThread::handleGetHeadersState()  {
    if (!_socket.setSocketDescriptor(_socketDescriptor)) {
        return;
    }
    /*
       QCA::SecureArray serial("00135839d6b5");
       QCA::Hash hasher("md5");
       QByteArray hash = hasher.hashToString(serial).toLatin1();

       qDebug("serial=<%s>, sha1=<%s>", serial.constData(), hash.constData());
       */

    _socket.waitForReadyRead();

    getHeaders();
}

void TCPSessionThread::handleParseSoapState() {
    QDomDocument soapMessage;
    QString errorMsg;
    int lineNo = 0;
    int colNo = 0;
    QByteArray name;

    soapMessage.setContent(_content, true, &errorMsg, &lineNo, &colNo);
    name = soapMessage.nodeName().toLatin1();
    qDebug("Document's node name is <%s>", name.constData());
    QDomElement docElem = soapMessage.documentElement();
    qDebug("errorMsg=<%s>, lineNo=%d, colNo=%d", errorMsg.toLatin1().constData(), lineNo, colNo);
    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        // Looking for soap:Envelope's children (soap:Header and soap:Body)
        name = n.nodeName().toLatin1();
        qDebug("%s, %d: n.nodeName()=%s", __FUNCTION__, __LINE__, name.constData());

        if(QString("soap:Body") == n.nodeName()) {
            qDebug("It's soap:Body, parsing it...");
            // It's the body. Now we're expecting soap:Inform
            QDomNode informNode = n.firstChild();
            name = informNode.nodeName().toLatin1();
            qDebug("%s, %d: informNode.nodeName()=<%s>", __FUNCTION__, __LINE__, name.constData());
            if(QString("cwmp:Inform") == informNode.nodeName()) {
                // it's Inform, gotta parse it
                qDebug("About to parse Inform");
                parseInform(informNode);
            }

            informNode = informNode.nextSibling();
        }

        n = n.nextSibling();
    }
    qDebug("%s, %d", __FUNCTION__, __LINE__);
}

void TCPSessionThread::getHeaders() {
    QByteArray message;
    QByteArray emptyLine;
    int cLen;

    emptyLine += 0x0d;
    emptyLine += 0x0a;

    while(!_socket.canReadLine()) {
        qDebug("CAN'T READ LINE YET");
        QTimer::singleShot(10, this, SLOT(getHeaders()));
        return;
    }

    message = _socket.readLine();
    qDebug("%s: Got line <%s>", __FUNCTION__, message.constData());

    if(0 <= (cLen = contentLenHdr(message))) {
        _contentLen = cLen;
        _content.resize(_contentLen);
        _state = GET_CONTENT;
        qDebug("This is content length <%s>. Length is %d ", message.constData(), _contentLen);
    } else if(emptyLine == message) {
        _state = GET_CONTENT;
        QTimer::singleShot(0, this, SLOT(stateMachine()));
        return;
    }
    
    QTimer::singleShot(10, this, SLOT(getHeaders()));
}

int TCPSessionThread::contentLenHdr(const QByteArray &line) {
    QString lineStr(line);
    qDebug("Checking line <%s>", line.constData());
    const QString CONT_LEN("Content-Length: ");
    if(lineStr.left(CONT_LEN.size()) != CONT_LEN)
        return -1;

    return lineStr.right(lineStr.size() - CONT_LEN.size()).toInt();
}

void TCPSessionThread::parseInform(const QDomNode &informNode) {
    QDomNode node = informNode.firstChild();
    QByteArray name;
    while(!node.isNull()) {
        name = node.nodeName().toLatin1();
        QString nodeName = node.nodeName();
        qDebug("Name is <%s>", name.constData());

        if(QString("DeviceId") == nodeName) {
            parseDeviceId(node);
        } else if(QString("Event") == nodeName) {
        } else if(QString("MaxEnvelopes") == nodeName) {
        }

        node = node.nextSibling();
    }
}

void TCPSessionThread::parseDeviceId(const QDomNode &deviceIdNode) {
    QDomNode node = deviceIdNode.firstChild();
    QByteArray name;
    ClientID clientId;
    QDomElement element;
    while(!node.isNull()) {
        name = node.nodeName().toLatin1();
        element = node.toElement();
        if(QString("Manufacturer") == node.nodeName()) {
            clientId.setManufacturer(element.text());
        } else if(QString("OUI") == node.nodeName()) {
            clientId.setOui(element.text());
        } else if(QString("ProductClass") == node.nodeName()) {
            clientId.setProductClass(element.text());
        } else if(QString("SerialNumber") == node.nodeName()) {
            clientId.setSerialNo(element.text());
        }

        node = node.nextSibling();
    }
    qDebug("manufacturer=<%s>", clientId.manufacturerToByteArray().constData());
    qDebug("oui=<%s>", clientId.ouiToByteArray().constData());
    qDebug("productClass=<%s>", clientId.productClassToByteArray().constData());
    qDebug("serialNo=<%s>", clientId.serialNoToByteArray().constData());
    qDebug("id=<%s>", clientId.idToByteArray().constData());
}

