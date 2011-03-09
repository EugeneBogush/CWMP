#include "cwmpParameterListParser.h"

CWMPParameterListParser::CWMPParameterListParser() {
}

CWMPParameterListParser::CWMPParameterListParser(const QDomNode &parameterListNode) {
    QDomNode node = parameterListNode.firstChild();
    while(!node.isNull()) {
        QByteArray dbgA = node.localName().toLatin1();
        qDebug("%s, %d: Node's name is %s", __FUNCTION__, __LINE__, dbgA.constData());

        addParameter(node);

        node = node.nextSibling();
    }
}

CWMPParameterListParser::~CWMPParameterListParser() {
}

void CWMPParameterListParser::addParameter(const QDomNode &parameter) {
    QDomNode node = parameter.firstChild();
    QString name;
    QVariant value;

    while(!node.isNull()) {
        if(QString("Name") == node.localName()) {
            name = node.firstChild().toText().data();
        } else if(QString("Value") == node.localName()) {
            QDomNamedNodeMap attributes = node.attributes();
            QDomAttr typeAttr = attributes.namedItem("type").toAttr();
            QString  type = typeAttr.value();
            if("xsd:string" == type ||
               "xsd:dateTime" == type ||
               "xsd:base64" == type ||
               "xsd:anySimpleType" == type) {
                value = node.firstChild().toText().data();
            } else if("xsd:int" == type) {
                value = node.firstChild().toText().data().toInt();
            } else if("xsd:unsignedInt" == type) {
                value = node.firstChild().toText().data().toUInt();
            } else if("xsd:boolean" == type) {
                if("0" == node.firstChild().toText().data() ||
                   "false" == node.firstChild().toText().data()) {
                    value  = true;
                } else {
                    value = false;
                }
            }
        }

        node = node.nextSibling();
    }

    _parameters.parameters().append(
            CWMPParameterList::ParameterValueStruct(name, value));
}
