#ifndef _CWMP_SESSION_THREAD_H_
#define _CWMP_SESSION_THREAD_H_

#include <QDomNode>
#include <QTcpSocket>
#include <QThread>

class Inform;

//! Representation of TCP session with specific CPE
/*! This class represents single TCP session (NOT CWMP session). Since CWMP
 * session is an HTTP session, other means of session control (like cookies)
 * must be implied. Single CWMP session may consists of several TCP sessions,
 * thus CWMPCtx must be used to lookup CWMP session, so TCPSessionThread may
 * properly handle CMWP transactions.
 */
class TCPSessionThread : public QThread {
    Q_OBJECT
    public:
        //! Represents all states of TCPSessionThread's state machine
        enum State {
            GET_HEADERS, //!< Initial state -- need to parse HTTP headers
            GET_CONTENT, //!< Headers already parsed, need to read HTTP content
            PARSE_SOAP  //!< Content read, need to parse SOAP envelope
        };

        //! Constructor of TCP session thread
        /*! Constructs separate thread for TCP connection pointed by
         * socketDescriptor.
         */
        TCPSessionThread(int socketDescriptor, QObject *parent = NULL);

        //! Default destructor
        ~TCPSessionThread();

        //! Main thread's flow function.
        /*!
         * This function is supposed to be called to handle TCP session. It calls
         * QTcpSocket.setSocketDescriptor(socketDescriptor) is called to
         * initiate connection. Afterwards content of HTTP request is read and
         * parsed.
         */
        void run();

    private slots:
        void stateMachine();
        void getHeaders();
        void handleGetContentState();

    private:
        void handleGetHeadersState();
        void handleParseSoapState();

        int _socketDescriptor;
        QTcpSocket _socket;
        State _state;
        int _contentLen;
        QString _cookie;
        int _contentRead;
        QByteArray _content;
        Inform *_inform;
};

#endif // _CWMP_SESSION_THREAD_H_
