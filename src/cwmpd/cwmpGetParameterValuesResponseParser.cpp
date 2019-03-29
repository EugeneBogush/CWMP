#include "cwmpGetParameterValuesResponseParser.h"
#include "cwmpParameterValueStructParser.h"

CWMPGetParameterValuesResponseParser::CWMPGetParameterValuesResponseParser(
        const QDomNode &gPVResponseNode) {
    qDebug("%d | %s: Constructing filled "
           "CWMPGetParameterValuesResponseParser", __LINE__, __FUNCTION__ );
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
