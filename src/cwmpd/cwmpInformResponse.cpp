#include <QDomDocument>

#include "cwmpInformResponse.h"
#include "soap.h"

CWMPInformResponse::CWMPInformResponse() {
}

CWMPInformResponse::~CWMPInformResponse() {
}

QByteArray CWMPInformResponse::soapContent() const {
    QDomDocument informResponseDoc;
    /*
    QDomProcessingInstruction instr = informResponseDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" ");
    informResponseDoc.appendChild(instr);
    */

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

