#ifndef _CWMP_INFORM_H_
#define _CWMP_INFORM_H_

#include <QDomNode>

class ClientID;

class Inform {
    public:
        Inform(const QDomNode &informNode);
        ~Inform();

        const ClientID *clientID() const { return _clientID; }
        void parseInform(const QDomNode &informNode);
        void parseDeviceId(const QDomNode &deviceIdNode);

    private:
        const ClientID *_clientID;
};

#endif // _CWMP_INFORM_H_

