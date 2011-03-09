#ifndef CWMPDADAPTER_H
#define CWMPDADAPTER_H

#include "cwmpInform.h"

#include <QtDBus/QDBusAbstractAdaptor>

class CWMPDAdapter : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.prezu_cwmp")
public:
    CWMPDAdapter(QObject *);
    ~CWMPDAdapter();

    void emitInform(const CWMPInform &);

public slots:
    void gimme(int a) { qDebug("got %d", a); }

signals:
    void inform(CWMPInform);
};

#endif // CWMPDADAPTER_H
