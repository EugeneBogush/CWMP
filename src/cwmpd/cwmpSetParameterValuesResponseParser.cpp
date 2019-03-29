#include <qt5/QtCore/qdebug.h>
#include <qt5/QtCore/qstring.h>

#include "cwmpSetParameterValuesResponseParser.h"
#include "cwmpParameterValueStructParser.h"

CWMPSetParameterValuesResponseParser::CWMPSetParameterValuesResponseParser(
        const QDomNode &gPVResponseNode) {
    qDebug("%s, %d: Constructing filled "
            "CWMPSetParameterValuesResponseParser", __FUNCTION__, __LINE__);
    QDomNode node = gPVResponseNode.firstChild();

    while (!node.isNull()) {
        if (QString("Status") == node.localName()) {
            qDebug(">>>> Status");
            _getParameterValuesResponse.setParameterList(
                    node.toElement().text().toLatin1().toInt());
        } else if (QString("faultcode") == node.localName()) {
            qDebug(">>>> faultcode: %s", node.toElement().text().toLatin1().data());
        } else if (QString("faultstring") == node.localName()) {
            qDebug(">>>> faultstring: %s", node.toElement().text().toLatin1().data());
        } else if (QString("detail") == node.localName()) {
            QDomElement node2 = node.toElement();

            while (!node2.isNull()) {
                if (QString("FaultCode") == node2.localName()) {
                    qDebug(">>>> FaultCode: %s", node2.toElement().text().toLatin1().data());

                } else if (QString("FaultString") == node2.localName()) {
                    qDebug(">>>> FaultString: %s", node2.toElement().text().toLatin1().data());

                } else if (QString("SetParameterValuesFault") == node2.localName()) {
                    qDebug(">>>> SetParameterValuesFault: %s", node2.toElement().text().toLatin1().data());

                }

                //node2 = node2.nextSibling();
                break;
            }
            QString a;
            node2.firstChildElement(a);
            qDebug(">>>> detail: %s", (char*)a.data());
        } else
            qDebug(">>>> Unknown data:  %s", node.localName().toLatin1().data());
        node = node.nextSibling();
    }
}

CWMPSetParameterValuesResponseParser::~CWMPSetParameterValuesResponseParser() {
}