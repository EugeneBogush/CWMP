#include <QDomNode>

#include "cwmpDeviceIDParser.h"

CWMPDeviceIDParser::CWMPDeviceIDParser() {
    qDebug("%s, %d: Constructing NULL CWMPDeviceIDParser", __FUNCTION__, __LINE__);
}

CWMPDeviceIDParser::CWMPDeviceIDParser(const QDomNode &deviceIDNode) {
    qDebug("%s, %d: Constructing filled CWMPDeviceIDParser", __FUNCTION__, __LINE__);
    QDomNode node = deviceIDNode.firstChild();
    QByteArray dbgA;

    while(!node.isNull()) {
        QByteArray dbgA = node.localName().toLatin1();
        qDebug("%s, %d: Current node is: %s", __FUNCTION__, __LINE__, dbgA.constData());
        dbgA = node.firstChild().toText().data().toLatin1();
        if(QString("Manufacturer") == node.localName()) {
            qDebug("%s, %d: Manufacturer=<%s>", __FUNCTION__, __LINE__, dbgA.constData());
            _manufacturer = node.firstChild().toText().data();
        } else if(QString("OUI") == node.localName()) {
            qDebug("%s, %d: OUI=<%s>", __FUNCTION__, __LINE__, dbgA.constData());
            _oui = node.firstChild().toText().data();
        } else if(QString("ProductClass") == node.localName()) {
            qDebug("%s, %d: ProductClass=%s", __FUNCTION__, __LINE__, dbgA.constData());
            _productClass = node.firstChild().toText().data();
        } else if(QString("SerialNumber") == node.localName()) {
            qDebug("%s, %d: SerialNumber=%s", __FUNCTION__, __LINE__, dbgA.constData());
            _serialNumber = node.firstChild().toText().data();
        }

        node = node.nextSibling();
    }
}

CWMPDeviceIDParser::~CWMPDeviceIDParser() {
    //qDebug("%s, %d: Destructing CWMPDeviceIDParser", __FUNCTION__, __LINE__);
}

