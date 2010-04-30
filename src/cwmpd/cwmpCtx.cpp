#include <QtCrypto>

#include "cwmpCtx.h"

CWMPCtx CWMPCtx::_instance;

ClientID::ClientID(const QString &serialNo) {
    setSerialNo(serialNo);
}

void ClientID::setSerialNo(const QString &serialNo) {
    _serialNo = serialNo;
    generateId();
}

void ClientID::generateId() {
    // TODO: Implement this
}

CWMPCtx &CWMPCtx::instance() {
    return _instance;
}

