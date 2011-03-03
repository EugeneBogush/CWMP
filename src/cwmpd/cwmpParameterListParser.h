#ifndef _CWMP_PARAMETER_LIST_PARSER_H_
#define _CWMP_PARAMETER_LIST_PARSER_H_

#include "cwmpParameterList.h"

#include <QDomNode>
#include <QString>

class CWMPParameterListParser {
    public:
        CWMPParameterListParser();
        CWMPParameterListParser(const QDomNode &parameterListNode);
        ~CWMPParameterListParser();
        void addParameter(const QDomNode &parameter);
        const CWMPParameterList &parameters() const { return _parameters; }

    private:
        CWMPParameterList _parameters;
};

#endif // _CWMP_PARAMETER_LIST_PARSER_H_
