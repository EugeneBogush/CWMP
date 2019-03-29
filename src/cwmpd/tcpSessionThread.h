#ifndef _CWMP_SESSION_THREAD_H_
#define _CWMP_SESSION_THREAD_H_

#include <QDomNode>
#include <QTcpSocket>
#include <QThread>

class CWMPDAdapter;

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
            GET_HEADERS,               //!< Initial state -- need to parse HTTP headers
            GET_CONTENT,               //!< Headers already parsed, need to read HTTP content
            PARSE_SOAP,                //!< Content read, need to parse SOAP envelope
            SEND_INFORM_RESPONSE,      //!< Need to send InformResponse back to CPE
            SEND_GET_PARAMETER_VALUES, //!< Need to send GetParameterValues to CPE
            CHECK_SCHEDULE_QUEUE,      //!< Check if more tasks are scheduled for this CPE
            SEND_EMPTY_RESPONSE,       //!< Need to send empty HTTP response
            FINISHED,                   //!< Free to exit state machine
            SEND_SET_PARAMETER_VALUES
        };

        //! Constructor of TCP session thread
        /*! Constructs separate thread for TCP connection pointed by
         * socketDescriptor.
         */
        TCPSessionThread(QTcpSocket *socket, QObject *parent = NULL);

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
        void changeState(State newState);
        void handleGetContentState();
        void sendEmptyResponse();

    private:
        template<class CWMPMethod, class CWMPMethodContent>
        void sendMethod(const CWMPMethodContent &content);
        void handleParseSoapState();
        void handleGetHeadersState();

        QTcpSocket *_socket;
        State _state;
        int _contentLen;
        QString _cookie;
        int _contentRead;
        QByteArray _content;
        //Inform *_inform;
        CWMPDAdapter *_pDbusAdapter;
};

#endif // _CWMP_SESSION_THREAD_H_
