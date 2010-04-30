#include <QCoreApplication>
#include "cwmpServer.h"

int main(int argc, char *argv[]) {
    qDebug("main()");
    QCoreApplication app(argc, argv);
    CWMPServer server;
    server.listen(QHostAddress::Any, 1111);

    app.exec();

    return 0;
}

