#ifndef CWMPGETPARAMETERVALUESRESPONSEPARSER_H
#define CWMPGETPARAMETERVALUESRESPONSEPARSER_H

#include "cwmpGetParameterValuesResponse.h"

#include <QDomNode>
#include <QString>

class CWMPGetParameterValuesResponseParser
{
public:
    CWMPGetParameterValuesResponseParser(
            const QDomNode &gPVResponseNode);
    ~CWMPGetParameterValuesResponseParser();

    const CWMPGetParameterValuesResponse &getParameterValuesResponse() const
        { return _getParameterValuesResponse; }
    void setParameterValuesResponse(
        const CWMPGetParameterValuesResponse &getParameterValuesResponse)
        { _getParameterValuesResponse = getParameterValuesResponse; }

private:
    CWMPGetParameterValuesResponse _getParameterValuesResponse;
};

#endif // CWMPGETPARAMETERVALUESRESPONSEPARSER_H
