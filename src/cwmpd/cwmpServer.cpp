#include <QTcpSocket>

#include "cwmpServer.h"
#include "tcpSessionThread.h"

CWMPServer::CWMPServer(QObject *parent)
: QTcpServer(parent) {
    qDebug("Creating CWMPServer...");
}

CWMPServer::~CWMPServer() {
}

void CWMPServer::incomingConnection(int socketDescriptor) {
    qDebug("New connection. Descriptor is %d", socketDescriptor);
    TCPSessionThread *thread = new TCPSessionThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->run();
}

