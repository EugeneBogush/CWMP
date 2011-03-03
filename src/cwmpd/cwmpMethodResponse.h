#ifndef _CWMP_METHOD_RESPONSE_H_
#define _CWMP_METHOD_RESPONSE_H_

#include <QByteArray>

class CWMPMethodResponse {
    public:
        CWMPMethodResponse();
        ~CWMPMethodResponse();
        QByteArray content() const;

    protected:
        QByteArray line(QByteArray l) const;
        virtual QByteArray soapContent() const = 0;
};

#endif // _CWMP_METHOD_RESPONSE_H_
