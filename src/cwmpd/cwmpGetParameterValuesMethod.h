#ifndef CWMPGETPARAMETERVALUESMETHOD_H
#define CWMPGETPARAMETERVALUESMETHOD_H

#include "cwmpGetParameterValues.h"
#include "cwmpMethod.h"

class CWMPGetParameterValuesMethod : public CWMPMethod
{
public:
    CWMPGetParameterValuesMethod(const CWMPGetParameterValues &);
    virtual ~CWMPGetParameterValuesMethod();

protected:
    virtual QByteArray methodContent(QDomDocument &document,
                                     QDomElement &body) const;

private:
    CWMPGetParameterValues _getParameterValues;
};

#endif // CWMPGETPARAMETERVALUESMETHOD_H
