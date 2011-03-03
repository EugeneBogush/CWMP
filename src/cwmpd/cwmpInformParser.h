#ifndef _CWMP_INFORM_PARSER_H
#define _CWMP_INFORM_PARSER_H

#include <QDomNode>
#include <QString>

#include "cwmpDeviceIDParser.h"
#include "cwmpEventParser.h"
#include "cwmpInform.h"
#include "cwmpParameterListParser.h"

class CWMPInformParser {
    public:
        CWMPInformParser();
        CWMPInformParser(const QDomNode &informNode);
        ~CWMPInformParser();
        const CWMPDeviceIDParser &deviceID() const { return _deviceIDParser; }
        const CWMPEventParser &event() const { return _eventParser; }

    private:
        CWMPInform _inform;

        CWMPDeviceIDParser _deviceIDParser;
        CWMPEventParser _eventParser;
        CWMPParameterListParser _parameterListParser;
};

#endif // _CWMP_INFORM_PARSER_H
