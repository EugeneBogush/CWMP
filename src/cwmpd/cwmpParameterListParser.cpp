#include "cwmpParameterListParser.h"

CWMPParameterListParser::ParameterValueStruct::ParameterValueStruct(const QString &name, const QString &value)
: _name(name), _value(value) {
}

CWMPParameterListParser::ParameterValueStruct::~ParameterValueStruct() {
}

CWMPParameterListParser::CWMPParameterListParser() {
}

CWMPParameterListParser::CWMPParameterListParser(const QDomNode &parameterListNode) {
}

CWMPParameterListParser::~CWMPParameterListParser() {
}

