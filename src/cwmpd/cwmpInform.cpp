#include "cwmpCtx.h"
#include "cwmpInform.h"

Inform::Inform(const QDomNode &informNode) {
    QDomNode node = informNode.firstChild();
    QByteArray name;
    while(!node.isNull()) {
        name = node.nodeName().toLatin1();
        QString nodeName = node.nodeName();
        qDebug("Name is <%s>", name.constData());

        if(QString("DeviceId") == nodeName) {
            parseDeviceId(node);
        } else if(QString("Event") == nodeName) {
        } else if(QString("MaxEnvelopes") == nodeName) {
        }

        node = node.nextSibling();
    }
}

Inform::~Inform() {
}

void Inform::parseDeviceId(const QDomNode &deviceIdNode) {
    QDomNode node = deviceIdNode.firstChild();
    QByteArray name;
    ClientID clientId;
    QDomElement element;
    while(!node.isNull()) {
        name = node.nodeName().toLatin1();
        element = node.toElement();
        if(QString("Manufacturer") == node.nodeName()) {
            clientId.setManufacturer(element.text());
        } else if(QString("OUI") == node.nodeName()) {
            clientId.setOui(element.text());
        } else if(QString("ProductClass") == node.nodeName()) {
            clientId.setProductClass(element.text());
        } else if(QString("SerialNumber") == node.nodeName()) {
            clientId.setSerialNo(element.text());
        }

        node = node.nextSibling();
    }
    qDebug("manufacturer=<%s>", clientId.manufacturerToByteArray().constData());
    qDebug("oui=<%s>", clientId.ouiToByteArray().constData());
    qDebug("productClass=<%s>", clientId.productClassToByteArray().constData());
    qDebug("serialNo=<%s>", clientId.serialNoToByteArray().constData());
    qDebug("id=<%s>", clientId.idToByteArray().constData());
}

