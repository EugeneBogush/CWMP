#include "cwmpSetParameterValues.h"

CWMPSetParameterValues::CWMPSetParameterValues()
{
}

CWMPSetParameterValues::~CWMPSetParameterValues()
{
}

void CWMPSetParameterValues::addParameterName(const QString &name) {
    _parameterNames.append(name);
}

void CWMPSetParameterValues::removeParameterName(const QString &name) {
    _parameterNames.removeAll(name);
}

void CWMPSetParameterValues::addParameterValue(const QString &value) {
    _parameterValues.append(value);
}

void CWMPSetParameterValues::removeParameterValue(const QString &value) {
    _parameterValues.removeAll(value);
}

void CWMPSetParameterValues::addParameterKey(const QString &key) {
    _parameterKey.append(key);
}

void CWMPSetParameterValues::removeParameterKey(const QString &key) {
    _parameterKey.removeAll(key);
}


