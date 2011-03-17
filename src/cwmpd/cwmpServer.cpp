#include <QTcpSocket>

#include "cwmpServer.h"
#include "tcpSessionThread.h"

CWMPServer::CWMPServer(QObject *parent)
: QTcpServer(parent) {
    qDebug("Creating CWMPServer...");
    connect(this, SIGNAL(newConnection()), this, SLOT(handleIncomingConnection()));
}

CWMPServer::~CWMPServer() {
}

void CWMPServer::handleIncomingConnection() {
    qDebug("New connection.");
    TCPSessionThread *thread = new TCPSessionThread(nextPendingConnection(), this);
    thread->run();
}

