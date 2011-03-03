#include <QDomNode>

#include "cwmpDeviceIDParser.h"

CWMPDeviceIDParser::CWMPDeviceIDParser() {
}

CWMPDeviceIDParser::CWMPDeviceIDParser(const QDomNode &deviceIDNode) {
    QDomNode node = deviceIDNode.firstChild();
    QByteArray dbgA;

    while(!node.isNull()) {
        QByteArray dbgA = node.localName().toLatin1();
        dbgA = node.firstChild().toText().data().toLatin1();
        if(QString("Manufacturer") == node.localName()) {
            _deviceID.setManufacturer(node.firstChild().toText().data());
        } else if(QString("OUI") == node.localName()) {
            _deviceID.setOui(node.firstChild().toText().data());
        } else if(QString("ProductClass") == node.localName()) {
            _deviceID.setProductClass(node.firstChild().toText().data());
        } else if(QString("SerialNumber") == node.localName()) {
            _deviceID.setSerialNumber(node.firstChild().toText().data());
        }

        node = node.nextSibling();
    }
}

CWMPDeviceIDParser::~CWMPDeviceIDParser() {
}

