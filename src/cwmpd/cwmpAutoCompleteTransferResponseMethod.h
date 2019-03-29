/* 
 * File:   CWMPAutoCompleteTransferResponseMethod.h
 * Author: eug
 *
 * Created on 4 листопада 2018, 23:44
 */

#ifndef CWMPAUTOCOMPLETETRANSFERRESPONSEMETHOD_H
#define CWMPAUTOCOMPLETETRANSFERRESPONSEMETHOD_H
#include "cwmpMethod.h"
#include "cwmpAutoCompleteTransferResponse.h"
class CWMPAutoCompleteTransferResponseMethod : public CWMPMethod {
public:
    CWMPAutoCompleteTransferResponseMethod(const CWMPAutoCompleteTransferResponse &);
    virtual ~CWMPAutoCompleteTransferResponseMethod();
protected:
    virtual QByteArray methodContent(QDomDocument &document,
            QDomElement &body) const;

};

#endif /* CWMPAUTOCOMPLETETRANSFERRESPONSEMETHOD_H */

