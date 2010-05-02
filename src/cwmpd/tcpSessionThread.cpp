#include <iostream>

#include <QDomDocument>
#include <QTimer>

#include <QtCrypto>

#include "cwmpCtx.h"
#include "cwmpInform.h"
#include "tcpSessionThread.h"

TCPSessionThread::TCPSessionThread(int socketDescriptor, QObject *parent)
: QThread(parent), _state(GET_HEADERS), _contentLen(0), _contentRead(0), _socketDescriptor(socketDescriptor),
_inform(NULL) {
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
                //parseInform(informNode);
                _inform = new Inform(informNode);
            }

            informNode = informNode.nextSibling();
        }

        n = n.nextSibling();
    }

    qDebug("%s, %d", __FUNCTION__, __LINE__);
}

void TCPSessionThread::getHeaders() {
    QByteArray line;
    QByteArray emptyLine;
    int cLen;
    const QString CONT_LEN("Content-Length: ");
    const QString COOKIE("Cookie:");

    emptyLine += 0x0d;
    emptyLine += 0x0a;

    while(!_socket.canReadLine()) {
        qDebug("CAN'T READ LINE YET");
        QTimer::singleShot(10, this, SLOT(getHeaders()));
        return;
    }

    line = _socket.readLine();
    qDebug("%s: Got line <%s>", __FUNCTION__, line.constData());

    if(CONT_LEN == line.left(CONT_LEN.size())) {
        QString contLenHdr(line);
        _contentLen = contLenHdr.right(contLenHdr.size() - CONT_LEN.size()).toInt();
        _content.resize(_contentLen);
        qDebug("This is content length <%s>. Length is %d ", line.constData(), _contentLen);
    } else if(COOKIE == line.left(COOKIE.size())) {
        QString cookieHdr(line);
        _cookie = cookieHdr.right(cookieHdr.size() - COOKIE.size());
    } else if(emptyLine == line) {
        // The end of headers
        _state = GET_CONTENT;
        QTimer::singleShot(0, this, SLOT(stateMachine()));
        return;
    }
    
    QTimer::singleShot(10, this, SLOT(getHeaders()));
}

