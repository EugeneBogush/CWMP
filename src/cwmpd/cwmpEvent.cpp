#include "cwmpEvent.h"

CWMPEvent::Event::Event(const QString &eventCode, const QString &cmdKey)
: _eventCode(eventCode), _cmdKey(cmdKey) {
}

CWMPEvent::Event::~Event() {
}

CWMPEvent::CWMPEvent()
{
}
