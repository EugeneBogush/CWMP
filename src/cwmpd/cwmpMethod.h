#ifndef _CWMP_METHOD_H_
#define _CWMP_METHOD_H_

#include <QByteArray>

class CWMPMethod {
    public:
        CWMPMethod();
        ~CWMPMethod();
        QByteArray content() const;

    protected:
        QByteArray line(QByteArray l) const;
        virtual QByteArray soapContent() const = 0;
};

#endif // _CWMP_METHOD_H_
