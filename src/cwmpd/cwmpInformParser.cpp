#include "cwmpInformParser.h"

CWMPInformParser::CWMPInformParser() {
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
            _inform.setMaxEnvelopes(node.firstChild().toText().data().toUInt());
        } else if(QString("CurrentTime") == node.localName()) {
            _inform.setCurrentTime(node.firstChild().toText().data());
        } else if(QString("RetryCount") == node.localName()) {
            _inform.setRetryCount(node.firstChild().toText().data().toUInt());
        } else if(QString("ParameterList") == node.localName()) {
            _parameterListParser = CWMPParameterListParser(node);
        }

        node = node.nextSibling();
    }

    qDebug("It's a good place to use D-Bus for announcing an Inform");
}

CWMPInformParser::~CWMPInformParser() {
    qDebug("%s, %d: Destructing CWMPInformParser", __FUNCTION__, __LINE__);
}

