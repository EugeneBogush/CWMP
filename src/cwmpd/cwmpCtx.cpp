#include <QMutexLocker>

#include <QtCrypto>

#include "cwmpCtx.h"

CWMPCtx *CWMPCtx::_instance = NULL;
QMutex CWMPCtx::_instanceMutex;

ClientID::ClientID() {
}

ClientID::ClientID(const QString &serialNo) {
    setSerialNo(serialNo);
}

void ClientID::setSerialNo(const QString &serialNo) {
    _serialNo = serialNo;
    generateId();
}

CWMPCtx::CWMPCtx() {
    qDebug("Creating signleton CWMPCtx!!!!");
}

CWMPCtx::~CWMPCtx() {
    QMutexLocker locker(&_instanceMutex);
    delete _instance;
    _instance = NULL;
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

template <class MatchClass>
const ClientID *CWMPCtx::cID(const MatchClass &match) {
    const ClientID *c = NULL;
    if(cwmpSessions.contains(match)) {
        c = &(cwmpSessions.at(cwmpSessions.indexOf(match)));
    }
}

CWMPCtx &CWMPCtx::instance() {
    if(true) {
        QMutexLocker locker(&_instanceMutex);
        if(!_instance)
            _instance = new CWMPCtx;
    }

    return *_instance;
}

void CWMPCtx::addSession(const ClientID &clientID) {
    QMutexLocker locker(&sessMutex);
    if(!cwmpSessions.contains(clientID))
        cwmpSessions.append(clientID);
}

const ClientID *CWMPCtx::clientID(const QString &serialNo) {
    return cID(serialNo);
}

const ClientID *CWMPCtx::clientID(const ClientID &clientID) {
    return cID(clientID);
}

