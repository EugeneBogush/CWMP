#ifndef _CWMP_INFORM_RESPONSE_H_
#define _CWMP_INFORM_RESPONSE_H_

#include "cwmpMethod.h"

class CWMPInformResponseMethod : public CWMPMethod {
    public:
        CWMPInformResponseMethod();
        virtual ~CWMPInformResponseMethod();

    protected:
        virtual QByteArray soapContent() const;
};

#endif // _CWMP_INFORM_RESPONSE_H_
