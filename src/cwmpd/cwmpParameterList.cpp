#include "cwmpParameterList.h"

CWMPParameterList::ParameterValueStruct::ParameterValueStruct(
        const QString &name, const QVariant &value)
: _name(name), _value(value) {
}

CWMPParameterList::ParameterValueStruct::~ParameterValueStruct() {
}

CWMPParameterList::CWMPParameterList() {
}

QDBusArgument &operator <<(QDBusArgument &arg, const CWMPParameterList &rhs) {
    int size = rhs.parameters().size();

    arg.beginStructure();

    // First push number of entries
    arg << size;

    // Now push the whole array
    for(int i = 0; i < size; ++i) {
        arg << rhs.parameters()[i].name();
        arg << QDBusVariant(rhs.parameters()[i].value());
    }

    arg.endStructure();

    return arg;
}

const QDBusArgument &operator >>(const QDBusArgument &arg, CWMPParameterList &rhs) {
    int size;

    arg.beginStructure();

    // First get the size
    arg >> size;

    // Now get whole parameter array
    for(int i = 0; i < size; ++i) {
        QString name;
        QDBusVariant value;

        arg >> name >> value;
        rhs.parameters().append(
                CWMPParameterList::ParameterValueStruct(name, value.variant()));
    }

    arg.endStructure();

    return arg;
}
