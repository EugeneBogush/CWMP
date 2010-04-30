#ifndef _CWMP_SERVER_H_
#define _CWMP_SERVER_H_

#include <QObject>
#include <QTcpServer>

class CWMPServer : public QTcpServer {
    Q_OBJECT
    public:
        CWMPServer(QObject *parnent = NULL);
        ~CWMPServer();

    protected:
        void incomingConnection(int socketDescriptor);
};

#endif // _CWMP_SERVER_H_
