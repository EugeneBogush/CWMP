#ifndef _CWMP_INFORM_PARSER_H
#define _CWMP_INFORM_PARSER_H

#include <QDomNode>
#include <QString>

#include "cwmpInform.h"

class CWMPInformParser {
    public:
        CWMPInformParser();
        CWMPInformParser(const QDomNode &informNode);
        ~CWMPInformParser();
        const CWMPInform &inform() const { return _inform; }

    private:
        CWMPInform _inform;
};

#endif // _CWMP_INFORM_PARSER_H
