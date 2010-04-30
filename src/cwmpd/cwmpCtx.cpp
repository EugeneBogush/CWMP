#include <QtCrypto>

#include "cwmpCtx.h"

CWMPCtx CWMPCtx::_instance;

ClientID::ClientID() {
}

ClientID::ClientID(const QString &serialNo) {
    setSerialNo(serialNo);
}

void ClientID::setSerialNo(const QString &serialNo) {
    _serialNo = serialNo;
    generateId();
}

void ClientID::generateId() {
    qDebug("%s, %d: Hello...", __FUNCTION__, __LINE__);
    QCA::Initializer init;
    QCA::SecureArray serial(_serialNo.toLatin1());
    QCA::Hash hasher("sha256");
    QByteArray hash = hasher.hashToString(serial).toLatin1();
    _id = hash;

    qDebug("serial=<%s>, sha256=<%s>", serial.constData(), hash.constData());
}

CWMPCtx &CWMPCtx::instance() {
    return _instance;
}

