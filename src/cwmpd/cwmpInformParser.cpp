#include "cwmpDeviceIDParser.h"
#include "cwmpInformParser.h"

CWMPInformParser::CWMPInformParser() {
    qDebug("%s, %d: Constructing NULL CWMPInformParser", __FUNCTION__, __LINE__);
}

CWMPInformParser::CWMPInformParser(const QDomNode &informNode) {
    qDebug("%s, %d: Constructing filled CWMPInformParser", __FUNCTION__, __LINE__);
    QDomNode node = informNode.firstChild();

    while(!node.isNull()) {
        if(QString("DeviceId") == node.localName()) {
            CWMPDeviceIDParser deviceIDParser = CWMPDeviceIDParser(node);
            _inform.setDeviceID(deviceIDParser.deviceID());
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

    qDebug("MaxEnvelopes=%d", _inform.maxEnvelopes());
    qDebug("CurrentTime=%s", _inform.currentTime().toAscii().constData());
    qDebug("RetryCount=%d", _inform.retryCount());

    qDebug("Manufacturer=%s",
           _inform.deviceID().manufacturer().toAscii().constData());
    qDebug("OUI=%s", _inform.deviceID().oui().toAscii().constData());
    qDebug("ProductClass=%s",
           _inform.deviceID().productClass().toAscii().constData());
    qDebug("SerialNumber=%s",
           _inform.deviceID().serialNumber().toAscii().constData());
    qDebug("It's a good place to use D-Bus for announcing an Inform");
}

CWMPInformParser::~CWMPInformParser() {
    qDebug("%s, %d: Destructing CWMPInformParser", __FUNCTION__, __LINE__);
}

