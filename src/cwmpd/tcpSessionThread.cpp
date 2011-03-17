#include <iostream>

#include <QtDBus/QDBusMetaType>
#include <QtDBus/QDBusConnection>
#include <QDomDocument>
#include <QTimer>

#include <QtCrypto>

#include "cwmpCtx.h"
#include "cwmpGetParameterValuesMethod.h"
#include "cwmpGetParameterValuesResponseParser.h"
#include "cwmpInformParser.h"
#include "cwmpInformResponseMethod.h"
#include "cwmpSoap.h"
#include "tcpSessionThread.h"
#include "cwmpdAdapter.h"

TCPSessionThread::TCPSessionThread(QTcpSocket *socket, QObject *parent)
: QThread(parent), _socket(socket), _state(GET_HEADERS), _contentLen(0),
_contentRead(0) {
    qDebug("%s, %d: Constructor", __FUNCTION__, __LINE__);
    _pDbusAdapter = new CWMPDAdapter(this);
    qDBusRegisterMetaType<CWMPInform>();
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/CWMPd", this);
    connection.registerService("org.prezu_cwmp");

    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

TCPSessionThread::~TCPSessionThread() {
    qDebug("%s, %d: Destructor", __FUNCTION__, __LINE__);
}

void TCPSessionThread::run() {
    qDebug("%s, %d: Starting run()", __FUNCTION__, __LINE__);
    stateMachine();
    qDebug("%s, %d: Ending run()", __FUNCTION__, __LINE__);
}

void TCPSessionThread::stateMachine() {
    qDebug("%s, Hello...", __FUNCTION__);
    qDebug("%s, %d: _state=%d", __FUNCTION__, __LINE__, _state);
    if(GET_HEADERS == _state) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        handleGetHeadersState();
    } else if(GET_CONTENT == _state) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        handleGetContentState();
    } else if(PARSE_SOAP == _state) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        handleParseSoapState();
    } else if(SEND_INFORM_RESPONSE == _state) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        CWMPInformResponse resp;
        sendMethod<CWMPInformResponseMethod, CWMPInformResponse>(resp);
    } else if(SEND_GET_PARAMETER_VALUES == _state) {
        CWMPGetParameterValues getParams;
        getParams.addParameterName(
                "InternetGatewayDevice.DeviceInfo.Manufacturer");
                //"InternetGatewayDevice.");
        sendMethod<CWMPGetParameterValuesMethod, CWMPGetParameterValues>(
                getParams);
    } else if(CHECK_SCHEDULE_QUEUE == _state) {
        // TODO: Implement it
        changeState(FINISHED);
    } else if(SEND_EMPTY_RESPONSE == _state) {
        qDebug("%s, %d: Set _state=%d", __FUNCTION__, __LINE__, _state);
        sendEmptyResponse();
    }

    if(FINISHED != _state)
        QTimer::singleShot(0, this, SLOT(stateMachine()));
    else {
        qDebug("Finishing...");
    }
}

void TCPSessionThread::changeState(State newState) {
    _state = newState;
    if(GET_HEADERS == _state) {
        _contentLen = _contentRead = 0;
        _content.clear();
    }
}

void TCPSessionThread::handleGetContentState() {
    qDebug("%s, Hello...", __FUNCTION__);
    while(!_socket->bytesAvailable()) {
        qDebug("%s, %d: Nothing yet available to read. Sleeping...", __FUNCTION__, __LINE__);
        msleep(10);
        qDebug("Awoken");
        return;
    }

    _contentRead += _socket->read(_content.data() + _contentRead, _contentLen - _contentRead);
    qDebug("%s, %d: _contentRead=%d, _contentLen=%d", __FUNCTION__, __LINE__, _contentRead, _contentLen);
    if(_contentRead < _contentLen) {
        qDebug("%s, %d: _contentRead=%d, _contentLen=%d", __FUNCTION__, __LINE__, _contentRead, _contentLen);
        qDebug("Sleeping...");
        msleep(10);
        qDebug("Awoken");
        return;
    }

    if(_contentLen > 0) {
        changeState(PARSE_SOAP);
    }
}

void TCPSessionThread::sendEmptyResponse() {
    QByteArray emptyLn;
    emptyLn += 0x0d;
    emptyLn += 0x0a;

    QByteArray http("HTTP/1.1 204 No content");
    http += emptyLn + emptyLn;
    _socket->write(http);
    _socket->waitForBytesWritten();

    changeState(FINISHED);
}

template<class CWMPMethod, class CWMPMethodContent>
void TCPSessionThread::sendMethod(const CWMPMethodContent &content) {
    CWMPMethod method(content);
    _socket->write(method.content());
    if(_socket->waitForBytesWritten()) {
        changeState(GET_HEADERS);
    }
}

void TCPSessionThread::handleParseSoapState() {
    QDomDocument soapMessage;
    QString errorMsg;
    int lineNo = 0;
    int colNo = 0;
    QByteArray name;
    bool gotMessageIsInform = false;
    bool gotMessageIsGetParameterValues = false;

    soapMessage.setContent(_content, true, &errorMsg, &lineNo, &colNo);
    name = soapMessage.nodeName().toLatin1();
    qDebug("%s, %d: Document's node name is <%s>", __FUNCTION__, __LINE__, name.constData());
    QDomElement docElem = soapMessage.documentElement();
    QDomNamedNodeMap attributes = docElem.attributes();
    //qDebug("%s, %d: errorMsg=<%s>, lineNo=%d, colNo=%d", __FUNCTION__, __LINE__, errorMsg.toLatin1().constData(), lineNo, colNo);
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
        for(unsigned i = 0; i < attributes.length(); ++i) {
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

        if(SOAP_NS == n.namespaceURI() && QString("Header") == n.localName()) {
            QDomNode idNode = n.firstChild();
            name = idNode.namespaceURI().toLatin1();
            qDebug("%s, %d: namespace=%s", __FUNCTION__, __LINE__, name.constData());
            name = idNode.localName().toLatin1();
            qDebug("%s, %d: localName=%s", __FUNCTION__, __LINE__, name.constData());
        } else if(SOAP_NS == n.namespaceURI() && QString("Body") == n.localName()) {
            qDebug("%s, %d: It's soap:Body, parsing it...", __FUNCTION__, __LINE__);
            // It's the body. Now we're expecting soap:<Method>
            QDomNode bodyNode = n.firstChild();
            // Is it Inform?
            if(CWMP_NS == bodyNode.namespaceURI() &&
               QString("Inform") == bodyNode.localName()) {
                gotMessageIsInform = true;
                CWMPInformParser informParser = CWMPInformParser(bodyNode);
                qDebug("MaxEnvelopes=%d",
                       informParser.inform().maxEnvelopes());
                qDebug("CurrentTime=%s",
                       informParser.inform().currentTime().toAscii().constData());
                qDebug("RetryCount=%d",
                       informParser.inform().retryCount());

                qDebug("Manufacturer=%s",
                       informParser.inform().deviceID().manufacturer().toAscii().constData());
                qDebug("OUI=%s", informParser.inform().deviceID().oui().toAscii().constData());
                qDebug("ProductClass=%s",
                       informParser.inform().deviceID().productClass().toAscii().constData());
                qDebug("SerialNumber=%s",
                       informParser.inform().deviceID().serialNumber().toAscii().constData());

                qDebug("\nEvents:");
                for(int i = 0; i < informParser.inform().event().events().count(); ++i)
                    qDebug("[%d]=%s", i,
                           informParser.inform().event().events()[i].eventCode().toAscii().constData());

                qDebug(" ");
                for(int i = 0; i < informParser.inform().parameterList().parameters().count(); ++i)
                    qDebug("[%d]: name=%s, value=%s", i,
                           informParser.inform().parameterList().parameters()[i].name().toAscii().constData(),
                           informParser.inform().parameterList().parameters()[i].value().toString().toAscii().constData());
                qDebug("It's a good place to use D-Bus for announcing an Inform");
                _pDbusAdapter->emitInform(informParser.inform());
                // Is it GetParameterValuesResponse?
            } else if(CWMP_NS == bodyNode.namespaceURI() &&
                      QString("GetParameterValuesResponse") ==
                      bodyNode.localName()) {
                gotMessageIsGetParameterValues = true;
                CWMPGetParameterValuesResponseParser gPVRespParser =
                        CWMPGetParameterValuesResponseParser(bodyNode);
                qDebug("GETPARAMETERVALUES!!!!!!!!!!!!!!!!!!!!!!!!!");
                int size = gPVRespParser.getParameterValuesResponse().parameterList().parameters().size();
                for(int i = 0; i < size; ++i) {
                    qDebug("Name=<%s>", gPVRespParser.getParameterValuesResponse().parameterList().parameters()[i].name().toAscii().constData());
                    qDebug("Value=<%s>\n", gPVRespParser.getParameterValuesResponse().parameterList().parameters()[i].value().toString().toAscii().constData());
                }
            }
        }

        n = n.nextSibling();
    }

    if(gotMessageIsInform) {
        changeState(SEND_INFORM_RESPONSE);
        qDebug("%s, %d: Set _state to %d, _state=%d", __FUNCTION__, __LINE__, SEND_INFORM_RESPONSE, _state);
    } else if(gotMessageIsGetParameterValues) {
        changeState(SEND_EMPTY_RESPONSE);
    }

    qDebug("%s, %d", __FUNCTION__, __LINE__);
}

void TCPSessionThread::handleGetHeadersState() {
    QByteArray line;
    QByteArray emptyLine;
    const QString CONT_LEN("Content-Length: ");
    const QString COOKIE("Cookie:");

    qDebug("%d, hello...", __LINE__);
    emptyLine += 0x0d;
    emptyLine += 0x0a;

    while(!_socket->canReadLine()) {
        qDebug("CAN'T READ LINE YET. Sleeping...");
        msleep(10);
        qDebug("Awoken");
        return;
    }

    line = _socket->readLine();
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
        if(0 != _contentLen) {
            changeState(GET_CONTENT);
        } else {
            // TODO: Remove this
            static bool once = true;
            if(once) {
                once = false;
                changeState(SEND_GET_PARAMETER_VALUES);
            } else {
                //changeState(CHECK_SCHEDULE_QUEUE);
                sendEmptyResponse();
                changeState(FINISHED);
            }
        }
    }
}

