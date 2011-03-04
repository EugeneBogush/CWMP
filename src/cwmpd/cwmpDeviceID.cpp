#include "cwmpDeviceID.h"

CWMPDeviceID::CWMPDeviceID()
{
}

QDBusArgument &operator <<(QDBusArgument &arg, const CWMPDeviceID &rhs) {
    arg.beginStructure();
    arg << rhs.manufacturer() << rhs.oui() << rhs.productClass() <<
            rhs.serialNumber();
    arg.endStructure();

    return arg;
}

const QDBusArgument &operator >>(const QDBusArgument &arg, CWMPDeviceID &rhs) {
    QString str;
    arg.beginStructure();

    arg >> str;
    rhs.setManufacturer(str);

    arg >> str;
    rhs.setOui(str);

    arg >> str;
    rhs.setProductClass(str);

    arg >> str;
    rhs.setSerialNumber(str);

    arg.endStructure();

    return arg;
}
