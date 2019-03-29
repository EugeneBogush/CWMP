/* 
 * File:   CWMPAutoCompleteTransferResponseMethod.cpp
 * Author: eug
 * 
 * Created on 4 листопада 2018, 23:44
 */
#include <QDomDocument>
#include "cwmpAutoCompleteTransferResponseMethod.h"

CWMPAutoCompleteTransferResponseMethod::CWMPAutoCompleteTransferResponseMethod(
const CWMPAutoCompleteTransferResponse &) {
}

CWMPAutoCompleteTransferResponseMethod::~CWMPAutoCompleteTransferResponseMethod() {
}

QByteArray CWMPAutoCompleteTransferResponseMethod::methodContent(QDomDocument &document,
                                                   QDomElement &body) const {
    QDomElement AutoResp = document.createElement("cwmp:AutonomousTransferCompleteResponse");
    body.appendChild(AutoResp);

    QDomElement maxEnvelopes = document.createElement("MaxEnvelopes");
    AutoResp.appendChild(maxEnvelopes);

    QDomText maxEnvValue = document.createTextNode("1");
    maxEnvelopes.appendChild(maxEnvValue);

    return document.toString().toLatin1();
}