/* 
 * File:   cwmpSetParameterValuesResponse.h
 * Author: yevhen
 *
 * Created on 18 січня 2018, 12:56
 */

#ifndef CWMPSETPARAMETERVALUESRESPONSE_H
#define CWMPSETPARAMETERVALUESRESPONSE_H

#include "cwmpParameterValueStruct.h"

#include <QtDBus/QDBusArgument>
#include <QString>

class CWMPSetParameterValuesResponse
{
public:
    CWMPSetParameterValuesResponse();
    ~CWMPSetParameterValuesResponse();
    const int &parameterList() const
        { return resCode; }
    void setParameterList(
        const int &parameterList)
        { resCode = parameterList; }

private:
    int resCode;
};

#endif /* CWMPSETPARAMETERVALUESRESPONSE_H */

