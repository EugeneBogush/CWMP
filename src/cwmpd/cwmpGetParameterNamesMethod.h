/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CWMPGetParameterNamesMethod.h
 * Author: eug
 *
 * Created on 6 листопада 2018, 0:07
 */

#ifndef CWMPGETPARAMETERNAMESMETHOD_H
#define CWMPGETPARAMETERNAMESMETHOD_H
#include "cwmpMethod.h"
#include "cwmpGetParameterNames.h"
class CWMPGetParameterNamesMethod : public CWMPMethod {
public:
    CWMPGetParameterNamesMethod(const CWMPGetParameterNames &);
    virtual ~CWMPGetParameterNamesMethod();

protected:
    virtual QByteArray methodContent(QDomDocument &document,
            QDomElement &body) const;
private:
    CWMPGetParameterNames _getParameterNames;
};

#endif /* CWMPGETPARAMETERNAMESMETHOD_H */

