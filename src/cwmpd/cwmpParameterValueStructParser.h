#ifndef _CWMP_PARAMETER_LIST_PARSER_H_
#define _CWMP_PARAMETER_LIST_PARSER_H_

#include "cwmpParameterValueStruct.h"

#include <QDomNode>
#include <QString>

class CWMPParameterValueStructParser {
    public:
        CWMPParameterValueStructParser();
        CWMPParameterValueStructParser(const QDomNode &parameterListNode);
        ~CWMPParameterValueStructParser();
        void addParameter(const QDomNode &parameter);
        const CWMPParameterValueStruct &parameters() const { return _parameters; }

    private:
        CWMPParameterValueStruct _parameters;
};

#endif // _CWMP_PARAMETER_LIST_PARSER_H_
