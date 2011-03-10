#include "cwmpDeviceIDParser.h"
#include "cwmpEvent.h"
#include "cwmpEventParser.h"
#include "cwmpInformParser.h"
#include "cwmpParameterValueStruct.h"
#include "cwmpParameterValueStructParser.h"

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
            CWMPParameterValueStructParser parameterValueStructParser =
                    CWMPParameterValueStructParser(node);
            _inform.setParameterList(
                    parameterValueStructParser.parameters());
        }

        node = node.nextSibling();
    }
}

CWMPInformParser::~CWMPInformParser() {
    qDebug("%s, %d: Destructing CWMPInformParser", __FUNCTION__, __LINE__);
}

