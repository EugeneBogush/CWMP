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

    protected slots:
        //! Handles incoming connection
        /*! Reimplemented from QTcpServer. Handles incoming connections
         *
         */
        void handleIncomingConnection();
};

#endif // _CWMP_SERVER_H_
