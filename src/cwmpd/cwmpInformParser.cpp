#include "cwmpDeviceIDParser.h"
#include "cwmpEvent.h"
#include "cwmpEventParser.h"
#include "cwmpInformParser.h"
#include "cwmpParameterList.h"
#include "cwmpParameterListParser.h"

CWMPInformParser::CWMPInformParser() {
    qDebug("%s, %d: Constructing NULL CWMPInformParser", __FUNCTION__, __LINE__);
}

CWMPInformParser::CWMPInformParser(const QDomNode &informNode) {
    qDebug("%s, %d: Constructing filled CWMPInformParser", __FUNCTION__, __LINE__);
    QDomNode node = informNode.firstChild();

    while(!node.isNull()) {
        if(QString("DeviceId") == node.localName()) {
            CWMPDeviceIDParser deviceIDParser = CWMPDeviceIDParser(node);
            // TODO: Get rid of redundant copy. Make CWMPDeviceIDParser write
            // to _inform::_deviceID.
            _inform.setDeviceID(deviceIDParser.deviceID());
        } else if(QString("Event") == node.localName()) {
            CWMPEventParser eventParser(node);
            // TODO: Same as ebove
            _inform.setEvent(eventParser.event());
        } else if(QString("MaxEnvelopes") == node.localName()) {
            _inform.setMaxEnvelopes(node.firstChild().toText().data().toUInt());
        } else if(QString("CurrentTime") == node.localName()) {
            _inform.setCurrentTime(node.firstChild().toText().data());
        } else if(QString("RetryCount") == node.localName()) {
            _inform.setRetryCount(node.firstChild().toText().data().toUInt());
        } else if(QString("ParameterList") == node.localName()) {
            CWMPParameterListParser parameterListParser =
                    CWMPParameterListParser(node);
            _inform.setParameterList(parameterListParser.parameters());
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

    qDebug("\nEvents:");
    for(int i = 0; i < _inform.event().events().count(); ++i)
        qDebug("[%d]=%s", i,
               _inform.event().events()[i].eventCode().toAscii().constData());

    qDebug(" ");
    for(int i = 0; i < _inform.parameterList().parameters().count(); ++i)
        qDebug("[%d]: name=%s, value=%s", i,
               _inform.parameterList().parameters()[i].name().toAscii().constData(),
               _inform.parameterList().parameters()[i].value().toString().toAscii().constData());
    qDebug("It's a good place to use D-Bus for announcing an Inform");
}

CWMPInformParser::~CWMPInformParser() {
    qDebug("%s, %d: Destructing CWMPInformParser", __FUNCTION__, __LINE__);
}

