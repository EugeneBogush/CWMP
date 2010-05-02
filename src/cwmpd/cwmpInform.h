#ifndef _CWMP_INFORM_H_
#define _CWMP_INFORM_H_

#include <QDomNode>

class Inform {
    public:
        Inform(const QDomNode &informNode);
        ~Inform();

        void parseInform(const QDomNode &informNode);
        void parseDeviceId(const QDomNode &deviceIdNode);
};

#endif // _CWMP_INFORM_H_

