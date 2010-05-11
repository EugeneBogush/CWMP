#include <QMutexLocker>

#include <QtCrypto>

#include "cwmpCtx.h"

CWMPCtx *CWMPCtx::_instance = NULL;
QMutex CWMPCtx::_instanceMutex;

CWMPCtx::CWMPCtx() {
    qDebug("Creating signleton CWMPCtx!!!!");
}

CWMPCtx::~CWMPCtx() {
    QMutexLocker locker(&_instanceMutex);
    delete _instance;
    _instance = NULL;
}

CWMPCtx &CWMPCtx::instance() {
    if(true) {
        QMutexLocker locker(&_instanceMutex);
        if(!_instance)
            _instance = new CWMPCtx;
    }

    return *_instance;
}

