/* 
 * File:   cwmpSetParameterValuesMethod.h
 * Author: yevhen
 *
 * Created on 17 січня 2018, 14:21
 */

#ifndef CWMPSETPARAMETERVALUESMETHOD_H
#define CWMPSETPARAMETERVALUESMETHOD_H

#include "cwmpSetParameterValues.h"
#include "cwmpMethod.h"

class CWMPSetParameterValuesMethod : public CWMPMethod
{
public:
    CWMPSetParameterValuesMethod(const CWMPSetParameterValues &);
    virtual ~CWMPSetParameterValuesMethod();

protected:
    virtual QByteArray methodContent(QDomDocument &document,
                                     QDomElement &body) const;

private:
    CWMPSetParameterValues _setParameter;
};


#endif /* CWMPSETPARAMETERVALUESMETHOD_H */

