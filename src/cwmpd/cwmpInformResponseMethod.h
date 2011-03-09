#ifndef _CWMP_INFORM_RESPONSE_H_
#define _CWMP_INFORM_RESPONSE_H_

#include "cwmpMethodResponse.h"

class CWMPInformResponseMethod : public CWMPMethodResponse {
    public:
        CWMPInformResponseMethod();
        ~CWMPInformResponseMethod();

    protected:
        virtual QByteArray soapContent() const;
};

#endif // _CWMP_INFORM_RESPONSE_H_
