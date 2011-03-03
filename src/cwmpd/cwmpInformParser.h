#ifndef _CWMP_INFORM_PARSER_H
#define _CWMP_INFORM_PARSER_H

#include <QDomNode>
#include <QString>

#include "cwmpEventParser.h"
#include "cwmpInform.h"
#include "cwmpParameterListParser.h"

class CWMPInformParser {
    public:
        CWMPInformParser();
        CWMPInformParser(const QDomNode &informNode);
        ~CWMPInformParser();
        const CWMPInform &inform() const { return _inform; }
        const CWMPEventParser &event() const { return _eventParser; }

    private:
        CWMPInform _inform;

        CWMPEventParser _eventParser;
        CWMPParameterListParser _parameterListParser;
};

#endif // _CWMP_INFORM_PARSER_H
