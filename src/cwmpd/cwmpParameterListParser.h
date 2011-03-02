#ifndef _CWMP_PARAMETER_LIST_PARSER_H_
#define _CWMP_PARAMETER_LIST_PARSER_H_

#include <QDomNode>
#include <QList>
#include <QString>

class CWMPParameterListParser {
    public:
        class ParameterValueStruct {
            public:
                ParameterValueStruct(const QString &name, const QString &value);
                ~ParameterValueStruct();

            private:
                QString _name, _value;
        };

        typedef QList<ParameterValueStruct> ParameterList;

        CWMPParameterListParser();
        CWMPParameterListParser(const QDomNode &parameterListNode);
        ~CWMPParameterListParser();

    private:
        ParameterList _parameters;
};

#endif // _CWMP_PARAMETER_LIST_PARSER_H_
