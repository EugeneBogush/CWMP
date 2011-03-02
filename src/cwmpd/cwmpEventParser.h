#ifndef _CWMP_EVENT_PARSER_H_
#define _CWMP_EVENT_PARSER_H_

#include <QDomNode>
#include <QList>

class CWMPEventParser {
    public:
        class CWMPEvent  {
            public:
                CWMPEvent(const QString &event, const QString &cmdKey);
                ~CWMPEvent();

                const QString &eventCode() const { return _eventCode; }
                const QString &cmdKey() const { return _cmdKey; }

            private:
                QString _eventCode, _cmdKey;
        };

        typedef QList<CWMPEvent> EventList;

        CWMPEventParser();
        CWMPEventParser(const QDomNode &eventNode);
        ~CWMPEventParser();

        void addEvent(const QDomNode &event);

        const EventList &event() const { return _events; }

    private:
        EventList _events;
};

#endif // _CWMP_EVENT_PARSER_H_
