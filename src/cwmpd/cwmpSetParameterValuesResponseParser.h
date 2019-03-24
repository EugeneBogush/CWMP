/* 
 * File:   cwmpSetParameterValuesResponseParser.h
 * Author: yevhen
 *
 * Created on 18 січня 2018, 12:57
 */

#ifndef CWMPSETPARAMETERVALUESRESPONSEPARSER_H
#define CWMPSETPARAMETERVALUESRESPONSEPARSER_H

#include "cwmpSetParameterValuesResponse.h"

#include <QDomNode>
#include <QString>

class CWMPSetParameterValuesResponseParser
{
public:
    CWMPSetParameterValuesResponseParser(
            const QDomNode &gPVResponseNode);
    ~CWMPSetParameterValuesResponseParser();

    const CWMPSetParameterValuesResponse &getParameterValuesResponse() const
        { return _getParameterValuesResponse; }
    void setParameterValuesResponse(
        const CWMPSetParameterValuesResponse &getParameterValuesResponse)
        { _getParameterValuesResponse = getParameterValuesResponse; }

private:
    CWMPSetParameterValuesResponse _getParameterValuesResponse;
};

#endif /* CWMPSETPARAMETERVALUESRESPONSEPARSER_H */

