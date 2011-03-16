#include "cwmpGetParameterValuesResponseParser.h"
#include "cwmpParameterValueStructParser.h"

CWMPGetParameterValuesResponseParser::CWMPGetParameterValuesResponseParser(
        const QDomNode &gPVResponseNode) {
    qDebug("%s, %d: Constructing filled "
           "CWMPGetParameterValuesResponseParser", __FUNCTION__, __LINE__);
    QDomNode node = gPVResponseNode.firstChild();

    while(!node.isNull()) {
        if(QString("ParameterList") == node.localName()) {
            CWMPParameterValueStructParser parameterValueStructParser =
                    CWMPParameterValueStructParser(node);
            _getParameterValuesResponse.setParameterList(
                        parameterValueStructParser.parameters());
        }

        node = node.nextSibling();
    }
}

CWMPGetParameterValuesResponseParser::~CWMPGetParameterValuesResponseParser() {
}
