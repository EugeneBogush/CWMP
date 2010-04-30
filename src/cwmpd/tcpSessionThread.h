#ifndef _CWMP_SESSION_THREAD_H_
#define _CWMP_SESSION_THREAD_H_

#include <QDomNode>
#include <QTcpSocket>
#include <QThread>


class TCPSessionThread : public QThread {
    Q_OBJECT
    public:
        enum State {
            GET_HEADERS,
            GET_CONTENT,
            PARSE_SOAP};
        TCPSessionThread(int socketDescriptor, QObject *parent = NULL);
        ~TCPSessionThread();

        void run();

    private slots:
        void stateMachine();
        void getHeaders();
        void handleGetContentState();

    private:
        void handleGetHeadersState();
        void handleParseSoapState();
        int contentLenHdr(const QByteArray &line);
        void parseInform(const QDomNode &informNode);
        void parseDeviceId(const QDomNode &deviceIdNode);

        int _socketDescriptor;
        QTcpSocket _socket;
        State _state;
        int _contentLen;
        int _contentRead;
        QByteArray _content;
};

#endif // _CWMP_SESSION_THREAD_H_
