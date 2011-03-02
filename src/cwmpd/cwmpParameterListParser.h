#ifndef _CWMP_PARAMETER_LIST_PARSER_H_
#define _CWMP_PARAMETER_LIST_PARSER_H_

#include <QDomNode>
#include <QList>
#include <QString>
#include <QVariant>

class CWMPParameterListParser {
    public:
        class ParameterValueStruct {
            public:
                ParameterValueStruct(const QString &name, const QVariant &value);
                ~ParameterValueStruct();

            private:
                QString _name;
                QVariant _value;
        };

        typedef QList<ParameterValueStruct> ParameterList;

        CWMPParameterListParser();
        CWMPParameterListParser(const QDomNode &parameterListNode);
        ~CWMPParameterListParser();
        void addParameter(const QDomNode &parameter);

    private:
        ParameterList _parameters;
};

#endif // _CWMP_PARAMETER_LIST_PARSER_H_
