#include <QDomDocument>

#include "cwmpInformResponseMethod.h"
#include "soap.h"

CWMPInformResponseMethod::CWMPInformResponseMethod() {
}

CWMPInformResponseMethod::~CWMPInformResponseMethod() {
}

QByteArray CWMPInformResponseMethod::soapContent() const {
    QDomDocument informResponseDoc;

    QDomElement envelope = informResponseDoc.createElementNS(SOAP_NS, "soap:Envelope");
    informResponseDoc.appendChild(envelope);

    QDomElement body = informResponseDoc.createElement("soap:Body");
    envelope.appendChild(body);

    QDomElement informResp = informResponseDoc.createElementNS(CWMP_NS, "cwmp:InformResponse");
    body.appendChild(informResp);

    QDomElement maxEnvelopes = informResponseDoc.createElement("MaxEnvelopes");
    informResp.appendChild(maxEnvelopes);

    QDomText maxEnvValue = informResponseDoc.createTextNode("1");
    maxEnvelopes.appendChild(maxEnvValue);

    return informResponseDoc.toString().toLatin1();
}

