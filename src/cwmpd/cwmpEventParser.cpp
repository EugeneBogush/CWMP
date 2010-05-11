#include "cwmpEventParser.h"

CWMPEventParser::CWMPEvent::CWMPEvent(const QString &eventCode, const QString &cmdKey)
: _eventCode(eventCode), _cmdKey(cmdKey) {
}

CWMPEventParser::CWMPEvent::~CWMPEvent() {
}

CWMPEventParser::CWMPEventParser() {
}

CWMPEventParser::CWMPEventParser(const QDomNode &eventNode) {
    QDomNode node = eventNode.firstChild();
    while(!node.isNull()) {
        QByteArray dbgA = node.localName().toLatin1();
        qDebug("%s, %d: Node's name is %s", __FUNCTION__, __LINE__, dbgA.constData());
        addEvent(node);

        node = node.nextSibling();
    }
}

CWMPEventParser::~CWMPEventParser() {
}

void CWMPEventParser::addEvent(const QDomNode &event) {
    QDomNode node = event.firstChild();
    QString eventCode, cmdKey;

    while(!node.isNull()) {
        if(QString("EventCode") == node.localName()) {
            eventCode = node.firstChild().toText().data();
        } else if(QString("CommandKey") == node.localName()) {
            cmdKey = node.firstChild().toText().data();
        }

        node = node.nextSibling();
    }

    _events.append(CWMPEvent(eventCode, cmdKey));
}

