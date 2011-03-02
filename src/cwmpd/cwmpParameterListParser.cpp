#include "cwmpParameterListParser.h"

CWMPParameterListParser::ParameterValueStruct::ParameterValueStruct(
        const QString &name, const QVariant &value)
: _name(name), _value(value) {
}

CWMPParameterListParser::ParameterValueStruct::~ParameterValueStruct() {
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

    _parameters.append(ParameterValueStruct(name, value));
}

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

