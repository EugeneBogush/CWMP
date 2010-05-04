#include <iostream>

#include <QDomDocument>
#include <QTimer>

#include <QtCrypto>

#include "cwmpCtx.h"
#include "cwmpInform.h"
#include "tcpSessionThread.h"
#include "cwmpSoap.h"

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
    qDebug("%s, %d: _state=%d", __FUNCTION__, __LINE__, _state);
    if(_state == GET_HEADERS) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        handleGetHeadersState();
    } else if(_state == GET_CONTENT) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        handleGetContentState();
    } else if(_state == PARSE_SOAP) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        handleParseSoapState();
    } else if(_state == SEND_INFORM_RESPONSE){
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        sendInformResponse();
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

void TCPSessionThread::sendInformResponse() {
    QDomDocument informResponseDoc;
    QDomElement envelope = informResponseDoc.createElementNS("http://schemas.xmlsoap.org/soap/envelope/", "cwmp:Envelope");
    informResponseDoc.appendChild(envelope);

    QDomElement body = informResponseDoc.createElement("cwmp:Body");
    envelope.appendChild(body);

    QDomElement informResp = informResponseDoc.createElement("InformResponse");
    body.appendChild(informResp);
    QByteArray xmlStr = informResponseDoc.toString().toLatin1();
    qDebug("%s, %d: InformResponse=%s", __FUNCTION__, __LINE__, xmlStr.constData());
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
    bool gotMessageIsInform = FALSE;
    ClientID clientID;

    soapMessage.setContent(_content, true, &errorMsg, &lineNo, &colNo);
    name = soapMessage.nodeName().toLatin1();
    qDebug("%s, %d: Document's node name is <%s>", __FUNCTION__, __LINE__, name.constData());
    QDomElement docElem = soapMessage.documentElement();
    QDomNamedNodeMap attributes = docElem.attributes();
    qDebug("%s, %d: errorMsg=<%s>, lineNo=%d, colNo=%d", __FUNCTION__, __LINE__, errorMsg.toLatin1().constData(), lineNo, colNo);
    name = docElem.tagName().toLatin1();
    qDebug("%s, %d: docElem.tagName()=%s", __FUNCTION__, __LINE__, name.constData());
    name = docElem.prefix().toLatin1();
    qDebug("%s, %d: docElem.prefix()=%s", __FUNCTION__, __LINE__, name.constData());
    name = docElem.localName().toLatin1();
    qDebug("%s, %d: docElem.localName()=%s", __FUNCTION__, __LINE__, name.constData());
    qDebug("%s, %d: attributes.count()=%d", __FUNCTION__, __LINE__, attributes.count());

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        // Looking for soap:Envelope's children (soap:Header and soap:Body)

        QDomNamedNodeMap attributes = n.attributes();
        qDebug("%s, %d: There are %d attributes here", __FUNCTION__, __LINE__, attributes.length());
        for(int i = 0; i < attributes.length(); ++i) {
            QDomNode n = attributes.item(i);
            name = n.nodeName().toLatin1();
            qDebug("%s, %d: n.nodeName()=%s", __FUNCTION__, __LINE__, name.constData());
        }



        name = n.nodeName().toLatin1();
        qDebug("%s, %d: n.nodeName()=%s", __FUNCTION__, __LINE__, name.constData());
        name = n.namespaceURI().toLatin1();
        qDebug("%s, %d: namespace=%s", __FUNCTION__, __LINE__, name.constData());
        name = n.localName().toLatin1();
        qDebug("%s, %d: localName=%s", __FUNCTION__, __LINE__, name.constData());

        //if(QString("soap:Header") == n.nodeName()) {
        if(SOAP_NS == n.namespaceURI() && QString("Header") == n.localName()) {
            QDomNode idNode = n.firstChild();
            name = idNode.namespaceURI().toLatin1();
            qDebug("%s, %d: namespace=%s", __FUNCTION__, __LINE__, name.constData());
            name = idNode.localName().toLatin1();
            qDebug("%s, %d: localName=%s", __FUNCTION__, __LINE__, name.constData());
            if(CWMP_NS == idNode.namespaceURI() && QString("ID") == idNode.localName()) {
                qDebug("!!!!!!!!!!!!!!!!!!!!!!!!");
                clientID.setSoapHdrId(idNode.toElement().text());
            }
            qDebug("%s, %d: soapHdrId=<%s>", __FUNCTION__, __LINE__, clientID.soapHdrIdToByteArray().constData());
        } else if(SOAP_NS == n.namespaceURI() && QString("Body") == n.localName()) {
            qDebug("%s, %d: It's soap:Body, parsing it...", __FUNCTION__, __LINE__);
            // It's the body. Now we're expecting soap:Inform
            QDomNode informNode = n.firstChild();
            name = informNode.nodeName().toLatin1();
            qDebug("%s, %d: informNode.nodeName()=<%s>", __FUNCTION__, __LINE__, name.constData());
            if(QString("cwmp:Inform") == informNode.nodeName()) {
                // it's Inform, gotta parse it
                qDebug("%s, %d: About to parse Inform", __FUNCTION__, __LINE__);
                //parseInform(informNode);
                _inform = new Inform(informNode, clientID);
                const ClientID *clientID = _inform->clientID();
                if(clientID) {
                    qDebug("%s, %d: manufacturer=<%s>", __FUNCTION__, __LINE__, clientID->manufacturerToByteArray().constData());
                    qDebug("%s, %d: oui=<%s>", __FUNCTION__, __LINE__, clientID->ouiToByteArray().constData());
                    qDebug("%s, %d: productClass=<%s>", __FUNCTION__, __LINE__, clientID->productClassToByteArray().constData());
                    qDebug("%s, %d: serialNo=<%s>", __FUNCTION__, __LINE__, clientID->serialNoToByteArray().constData());
                    qDebug("%s, %d: id=<%s>", __FUNCTION__, __LINE__, clientID->idToByteArray().constData());
                    qDebug("%s, %d: soapHdrId=<%s>", __FUNCTION__, __LINE__, clientID->soapHdrIdToByteArray().constData());
                }

                gotMessageIsInform = true;
            }

            informNode = informNode.nextSibling();
        }

        n = n.nextSibling();
    }

    if(gotMessageIsInform) {
        _state = SEND_INFORM_RESPONSE;
        qDebug("%s, %d: Set _state to %d, _state=%d", __FUNCTION__, __LINE__, SEND_INFORM_RESPONSE, _state);
        QTimer::singleShot(0, this, SLOT(stateMachine()));
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

