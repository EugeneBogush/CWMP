#include <QDomDocument>

#include "cwmpInformResponseMethod.h"

CWMPInformResponseMethod::CWMPInformResponseMethod(
        const CWMPInformResponse &) {
}

CWMPInformResponseMethod::~CWMPInformResponseMethod() {
}

QByteArray CWMPInformResponseMethod::methodContent(QDomDocument &document,
                                                   QDomElement &body) const {
    QDomElement informResp = document.createElement("cwmp:InformResponse");
    body.appendChild(informResp);

    QDomElement maxEnvelopes = document.createElement("MaxEnvelopes");
    informResp.appendChild(maxEnvelopes);

    QDomText maxEnvValue = document.createTextNode("1");
    maxEnvelopes.appendChild(maxEnvValue);

    return document.toString().toLatin1();
}

