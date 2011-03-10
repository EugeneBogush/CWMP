#ifndef CWMPGETPARAMETERVALUESRESPONSEPARSER_H
#define CWMPGETPARAMETERVALUESRESPONSEPARSER_H

#include <QDomNode>
#include <QString>


class CWMPGetParameterValuesResponseParser
{
public:
    CWMPGetParameterValuesResponseParser(
            const QDomNode &gPVResponseNode);
    ~CWMPGetParameterValuesResponseParser();
};

#endif // CWMPGETPARAMETERVALUESRESPONSEPARSER_H
