#include <QString>

#include "cwmpMethod.h"
#include "soap.h"

CWMPMethod::CWMPMethod() {
}

CWMPMethod::~CWMPMethod() {
}

QByteArray CWMPMethod::content() const {
    QByteArray msg;
    QByteArray cont = soapContent();

    msg += line("HTTP/1.1 200 OK");
    //msg += line("Server: FreeCWMP");
    msg += line("Content-Type: text/xml; charset=\"utf-8\"");
    msg += line(QString("Content-Length: %1").arg(cont.size()).toLatin1());
    msg += line("");
    msg += line(cont);
    return msg;
}

QByteArray CWMPMethod::line(QByteArray l) const {
    l += 0x0d;
    l += 0x0a;

    return l;
}

QByteArray CWMPMethod::soapContent() const {
    QDomDocument document;

    QDomElement envelope = document.createElement("soap:Envelope");
    envelope.setAttribute("xmlns:soap", QString(SOAP_ENV_NS));
    envelope.setAttribute("xmlns:soap-enc", QString(SOAP_ENC_NS));
    envelope.setAttribute("xmlns:cwmp", QString(CWMP_NS));
    envelope.setAttribute("xmlns:xsd", QString(XSD_NS));
    envelope.setAttribute("xmlns:xsi", QString(XSI_NS));
    document.appendChild(envelope);

    QDomElement header = document.createElement("soap:Header");
    envelope.appendChild(header);

    QDomElement body = document.createElement("soap:Body");
    envelope.appendChild(body);

    return methodContent(document, body);
}
