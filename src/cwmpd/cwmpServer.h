#ifndef _CWMP_SERVER_H_
#define _CWMP_SERVER_H_

#include <QObject>
#include <QTcpServer>

/*!
 * \brief Main CWMP's server class
 *
 * This class handles all incoming connection. For each connection
 * separate thread is started
 */
class CWMPServer : public QTcpServer {
    Q_OBJECT
    public:
        //! Server's constructor
        /*!
         * \param parent If specified, points to parent object
         */
        CWMPServer(QObject *parent = NULL);

        //! Destructor
        ~CWMPServer();

    protected:
        //! Handles incoming connection
        /*! Reimplemented from QTcpServer. Handles incoming connections
         *
         * \param socketDescriptor raw socket's descriptor. Internally
         * QTcpSocket.setSocketDescriptor() is called to attach to the
         * connection
         */
        void incomingConnection(int socketDescriptor);
};

#endif // _CWMP_SERVER_H_
