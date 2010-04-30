#ifndef _CWMP_CTX_H_
#define _CWMP_CTX_H_

#include <QByteArray>

class ClientID {
    public:
        ClientID(const QString &serialNo);
        QByteArray id() const { return _id; }

        const QString &manufacturer() const { return _manufacturer; }
        void setManufacturer(const QString &manufacturer) { _manufacturer = manufacturer; }
        const QString &oui() const { return _oui; }
        void setOui(const QString &oui) { _oui = oui; }
        const QString &serialNo() const { return _serialNo; }
        void setSerialNo(const QString &serialNo);

    private:
        void generateId();
        
        QByteArray _id;
        QString _manufacturer;
        QString _oui;
        QString _serialNo;
};

class CWMPCtx {
        /// Singleton pattern, thus constructor is private
        CWMPCtx() {};
        ~CWMPCtx() {};
        CWMPCtx(const CWMPCtx &);
        CWMPCtx operator =(const CWMPCtx &);

        static CWMPCtx _instance;

    public:
        CWMPCtx &instance();

};
#endif // _CWMP_CTX_H_
