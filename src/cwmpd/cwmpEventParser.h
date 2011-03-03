#ifndef _CWMP_EVENT_PARSER_H_
#define _CWMP_EVENT_PARSER_H_

#include "cwmpEvent.h"

#include <QDomNode>

class CWMPEventParser {
    public:
        CWMPEventParser();
        CWMPEventParser(const QDomNode &eventNode);
        ~CWMPEventParser();

        void addEvent(const QDomNode &event);

        const CWMPEvent &event() const { return _event; }

    private:
        CWMPEvent _event;
};

#endif // _CWMP_EVENT_PARSER_H_
