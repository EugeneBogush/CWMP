#include "cwmpParameterListParser.h"

CWMPParameterListParser::ParameterValueStruct::ParameterValueStruct(const QString &name, const QString &value)
: _name(name), _value(value) {
}

CWMPParameterListParser::ParameterValueStruct::~ParameterValueStruct() {
}

void CWMPParameterListParser::addParameter(const QDomNode &parameter) {
    QDomNode node = parameter.firstChild();
    QString name, value;

    while(!node.isNull()) {
        if(QString("Name") == node.localName()) {
            name = node.firstChild().toText().data();
        } else if(QString("Value") == node.localName()) {
            value = node.firstChild().toText().data();
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

