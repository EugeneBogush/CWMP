#ifndef _CWMP_DEVICE_ID_PARSER_H_
#define _CWMP_DEVICE_ID_PARSER_H_

#include "cwmpDeviceID.h"

#include <QDomNode>
#include <QString>

class CWMPDeviceIDParser {
    public:
        CWMPDeviceIDParser();
        CWMPDeviceIDParser(const QDomNode &deviceIDNode);
        ~CWMPDeviceIDParser();
        
        const CWMPDeviceID &deviceID() const { return _deviceID; }

    private:
        CWMPDeviceID _deviceID;
};

#endif // _CWMP_DEVICE_ID_PARSER_H_
