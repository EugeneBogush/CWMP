#ifndef CWMPEVENT_H
#define CWMPEVENT_H

#include <QtDBus/QDBusArgument>
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
    const EventList &events() const { return _events; }

private:
    EventList _events;
};

QDBusArgument &operator <<(QDBusArgument &, const CWMPEvent &);
const QDBusArgument &operator >>(const QDBusArgument &, CWMPEvent &);

#endif // CWMPEVENT_H
