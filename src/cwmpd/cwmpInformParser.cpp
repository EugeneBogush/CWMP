#include "cwmpInformParser.h"

CWMPInformParser::CWMPInformParser()
: _retryCount(0) {
    qDebug("%s, %d: Constructing NULL CWMPInformParser", __FUNCTION__, __LINE__);
}

CWMPInformParser::CWMPInformParser(const QDomNode &informNode) {
    qDebug("%s, %d: Constructing filled CWMPInformParser", __FUNCTION__, __LINE__);
    QDomNode node = informNode.firstChild();

    while(!node.isNull()) {
        if(QString("DeviceId") == node.localName()) {
            _deviceIDParser = CWMPDeviceIDParser(node);
        } else if(QString("Event") == node.localName()) {
            _eventParser = CWMPEventParser(node);
        } else if(QString("MaxEnvelopes") == node.localName()) {
            _maxEnvelopes = node.firstChild().toText().data();
            QByteArray dbgA = _maxEnvelopes.toLatin1();
            qDebug("%s, %d: maxEnvelopes=%s", __FUNCTION__, __LINE__, _maxEnvelopes. constData());
        } else if(QString("RetryCount") == node.localName()) {
            _retryCount = node.firstChild().toText().data().toInt();
            qDebug("%s, %d: RetryCount=%d", __FUNCTION__, __LINE__, _retryCount);
        }

        node = node.nextSibling();
    }
}

CWMPInformParser::~CWMPInformParser() {
    qDebug("%s, %d: Destructing CWMPInformParser", __FUNCTION__, __LINE__);
}

