#ifndef CWMPPARAMETERLIST_H
#define CWMPPARAMETERLIST_H

#include <QtDBus/QDBusArgument>
#include <QList>
#include <QString>
#include <QVariant>

class CWMPParameterValueStruct {
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

    CWMPParameterValueStruct();
    ~CWMPParameterValueStruct();

    ParameterList &parameters() { return _parameters; }
    const ParameterList &parameters() const { return _parameters; }

private:
    ParameterList _parameters;
};

QDBusArgument &operator <<(QDBusArgument &, const CWMPParameterValueStruct &);
const QDBusArgument &operator >>(const QDBusArgument &, CWMPParameterValueStruct &);

#endif // CWMPPARAMETERLIST_H
