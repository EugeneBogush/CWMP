#include <QString>

#include "cwmpMethodResponse.h"

CWMPMethodResponse::CWMPMethodResponse() {
}

CWMPMethodResponse::~CWMPMethodResponse() {
}

QByteArray CWMPMethodResponse::content() const {
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

QByteArray CWMPMethodResponse::line(QByteArray l) const {
    l += 0x0d;
    l += 0x0a;

    return l;
}

