#include "cwmpInform.h"

CWMPInform::CWMPInform()
: _maxEnvelopes(0), _retryCount(0) {
}

CWMPInform::~CWMPInform() {
}

QDBusArgument &operator <<(QDBusArgument &arg, const CWMPInform &rhs) {
    arg.beginStructure();

    // Version
    arg << QString("1.0");

    arg << rhs.maxEnvelopes() << rhs.retryCount() << rhs.currentTime();
    arg << rhs.deviceID();
    arg << rhs.event();
    arg << rhs.parameterList();

    arg.endStructure();

    return arg;
}

const QDBusArgument &operator >>(const QDBusArgument &arg, CWMPInform &rhs) {
    QString version;
    QString str;
    unsigned u;
    CWMPDeviceID devID;
    CWMPEvent event;
    CWMPParameterList paramList;

    arg.beginStructure();
    arg >> version;

    arg >> u;
    rhs.setMaxEnvelopes(u);

    arg >> u;
    rhs.setRetryCount(u);

    arg >> str;
    rhs.setCurrentTime(str);

    arg >> devID;
    rhs.setDeviceID(devID);

    arg >> event;
    rhs.setEvent(event);

    arg >> paramList;
    rhs.setParameterList(paramList);

    arg.endStructure();

    return arg;
}
