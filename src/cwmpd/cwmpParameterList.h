#ifndef CWMPPARAMETERLIST_H
#define CWMPPARAMETERLIST_H

#include <QList>
#include <QString>
#include <QVariant>

class CWMPParameterList {
public:
    class ParameterValueStruct {
        public:
            ParameterValueStruct(const QString &name, const QVariant &value);
            ~ParameterValueStruct();

            const QString &name() const { return _name; }
            const QVariant &value() const { return _value; }

        private:
            QString _name;
            QVariant _value;
    };

    typedef QList<ParameterValueStruct> ParameterList;

    CWMPParameterList();

    ParameterList &parameters() { return _parameters; }
    const ParameterList &parameters() const { return _parameters; }

private:
    ParameterList _parameters;
};

#endif // CWMPPARAMETERLIST_H
