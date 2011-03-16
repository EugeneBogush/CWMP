#ifndef CWMPGETPARAMETERVALUESRESPONSE_H
#define CWMPGETPARAMETERVALUESRESPONSE_H

#include "cwmpParameterValueStruct.h"

#include <QtDBus/QDBusArgument>
#include <QString>

class CWMPGetParameterValuesResponse
{
public:
    CWMPGetParameterValuesResponse();
    ~CWMPGetParameterValuesResponse();
    const CWMPParameterValueStruct &parameterList() const
        { return _parameterList; }
    void setParameterList(
        const CWMPParameterValueStruct &parameterList)
        { _parameterList = parameterList; }

private:
    CWMPParameterValueStruct _parameterList;
};

#endif // CWMPGETPARAMETERVALUESRESPONSE_H
