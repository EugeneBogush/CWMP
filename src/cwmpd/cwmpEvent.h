#ifndef CWMPEVENT_H
#define CWMPEVENT_H

#include <QList>
#include <QString>

class CWMPEvent
{
public:
    class Event  {
        public:
            Event(const QString &event, const QString &cmdKey);
            ~Event();

            const QString &eventCode() const { return _eventCode; }
            const QString &cmdKey() const { return _cmdKey; }

        private:
            QString _eventCode, _cmdKey;
    };

    typedef QList<Event> EventList;

    CWMPEvent();

    EventList &events() { return _events; }

private:
    EventList _events;
};

#endif // CWMPEVENT_H
