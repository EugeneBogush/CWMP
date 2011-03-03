#include "cwmpParameterList.h"

CWMPParameterList::ParameterValueStruct::ParameterValueStruct(
        const QString &name, const QVariant &value)
: _name(name), _value(value) {
}

CWMPParameterList::ParameterValueStruct::~ParameterValueStruct() {
}

CWMPParameterList::CWMPParameterList() {
}
