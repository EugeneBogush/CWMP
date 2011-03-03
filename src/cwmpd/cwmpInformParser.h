#ifndef _CWMP_INFORM_PARSER_H
#define _CWMP_INFORM_PARSER_H

#include <QDomNode>
#include <QString>

#include "cwmpEvent.h"
#include "cwmpInform.h"
#include "cwmpParameterListParser.h"

class CWMPInformParser {
    public:
        CWMPInformParser();
        CWMPInformParser(const QDomNode &informNode);
        ~CWMPInformParser();
        const CWMPInform &inform() const { return _inform; }
        const CWMPEvent &event() const { return _event; }

    private:
        CWMPInform _inform;
        CWMPEvent _event;

        CWMPParameterListParser _parameterListParser;
};

#endif // _CWMP_INFORM_PARSER_H
