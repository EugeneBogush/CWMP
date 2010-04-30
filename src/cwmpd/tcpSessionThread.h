#ifndef _CWMP_SESSION_THREAD_H_
#define _CWMP_SESSION_THREAD_H_

#include <QThread>

class TCPSessionThread : public QThread {
    public:
        TCPSessionThread(int socketDescriptor, QObject *parent = NULL);
        ~TCPSessionThread();

        void run();

    private:
        int socketDescriptor;
};

#endif // _CWMP_SESSION_THREAD_H_
