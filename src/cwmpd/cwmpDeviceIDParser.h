#ifndef _CWMP_DEVICE_ID_PARSER_H_
#define _CWMP_DEVICE_ID_PARSER_H_

#include <QDomNode>
#include <QString>

class CWMPDeviceIDParser {
    public:
        CWMPDeviceIDParser();
        CWMPDeviceIDParser(const QDomNode &deviceIDNode);
        ~CWMPDeviceIDParser();
        
        QString manufacturer() const { return _manufacturer; }
        QString oui() const { return _oui; }
        QString productClass() const { return _productClass; }
        QString serialNumber() const { return _serialNumber; }

    private:
        QString _manufacturer;
        QString _oui;
        QString _productClass;
        QString _serialNumber;
};

#endif // _CWMP_DEVICE_ID_PARSER_H_
