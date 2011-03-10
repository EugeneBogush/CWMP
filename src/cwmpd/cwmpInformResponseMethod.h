#ifndef _CWMP_INFORM_RESPONSE_H_
#define _CWMP_INFORM_RESPONSE_H_

#include "cwmpMethod.h"
#include "cwmpInformResponse.h"

class CWMPInformResponseMethod : public CWMPMethod {
    public:
        CWMPInformResponseMethod(const CWMPInformResponse &);
        virtual ~CWMPInformResponseMethod();

    protected:
        virtual QByteArray methodContent(QDomDocument &document,
                                         QDomElement &body) const;
};

#endif // _CWMP_INFORM_RESPONSE_H_
