#include "cwmpEvent.h"

CWMPEvent::Event::Event(const QString &eventCode, const QString &cmdKey)
: _eventCode(eventCode), _cmdKey(cmdKey) {
}

CWMPEvent::Event::~Event() {
}

CWMPEvent::CWMPEvent()
{
}

QDBusArgument &operator <<(QDBusArgument &arg, const CWMPEvent &rhs) {
    int size = rhs.events().size();

    arg.beginStructure();

    // First push number of entries
    arg << size;

    // Now push the whole array
    for(int i = 0; i < size; ++i) {
        arg << rhs.events()[i].eventCode();
        arg << rhs.events()[i].cmdKey();
    }

    arg.endStructure();

    return arg;
}

const QDBusArgument &operator >>(const QDBusArgument &arg, CWMPEvent &rhs) {
    int size;
    QString eventCode, cmdKey;
    arg.beginStructure();

    // First get the size
    arg >> size;

    // And now get whole array
    for(int i = 0; i < size; ++i) {
        arg >> eventCode >> cmdKey;
        rhs.events().append(CWMPEvent::Event(eventCode, cmdKey));
    }

    arg.endStructure();

    return arg;
}
