#ifndef _CWMP_METHOD_H_
#define _CWMP_METHOD_H_

#include <QByteArray>
#include <QDomDocument>
#include <QDomElement>

class CWMPMethod {
    public:
        CWMPMethod();
        virtual ~CWMPMethod();
        QByteArray content() const;

    protected:
        QByteArray line(QByteArray l) const;
        QByteArray soapContent() const;
        virtual QByteArray methodContent(QDomDocument &document,
                                         QDomElement &body) const = 0;
};

#endif // _CWMP_METHOD_H_
