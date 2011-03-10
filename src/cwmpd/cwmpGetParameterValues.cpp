#include "cwmpGetParameterValues.h"

CWMPGetParameterValues::CWMPGetParameterValues()
{
}

CWMPGetParameterValues::~CWMPGetParameterValues()
{
}

void CWMPGetParameterValues::addParameterName(const QString &name) {
    _parameterNames.append(name);
}

void CWMPGetParameterValues::removeParameterName(const QString &name) {
    _parameterNames.removeAll(name);
}
