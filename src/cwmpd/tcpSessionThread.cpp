#include <QTcpSocket>
#include "tcpSessionThread.h"

TCPSessionThread::TCPSessionThread(int socketDescriptor, QObject *parent)
: QThread(parent), socketDescriptor(socketDescriptor) {
}

TCPSessionThread::~TCPSessionThread() {
}

void TCPSessionThread::run() {
   QTcpSocket socket;
   if (!socket.setSocketDescriptor(socketDescriptor)) {
       return;
   }
   //QDataStream s(&socket);
   //s.setVersion(QDataStream::Qt_4_0);

   QByteArray message;

   forever{
       socket.waitForReadyRead();
       message = socket.readLine();
       while(!message.isEmpty()) {
           qDebug("<%s>", message.constData());
           message = socket.readLine();
       }
   }
}

