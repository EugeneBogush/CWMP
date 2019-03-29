/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CWMPGetParameterNamesMethod.cpp
 * Author: eug
 * 
 * Created on 6 листопада 2018, 0:07
 */

#include "cwmpGetParameterNamesMethod.h"

CWMPGetParameterNamesMethod::CWMPGetParameterNamesMethod(
        const CWMPGetParameterNames &getParameterNames)
: _getParameterNames(getParameterNames) {
}

CWMPGetParameterNamesMethod::~CWMPGetParameterNamesMethod() {
}

QByteArray CWMPGetParameterNamesMethod::methodContent(QDomDocument &document,
                                                   QDomElement &body) const {
    QDomElement GetParameterNames = document.createElement("cwmp:CWMPGetParameterNames");
    body.appendChild(GetParameterNames);

    QDomElement ParameterPath = document.createElement("ParameterPath");
    GetParameterNames.appendChild(ParameterPath);

    QDomText ParameterPathValue = document.createTextNode("InternetGatewayDevice.");
    ParameterPath.appendChild(ParameterPathValue);

    return document.toString().toLatin1();
}