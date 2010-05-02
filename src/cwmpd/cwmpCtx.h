#ifndef _CWMP_CTX_H_
#define _CWMP_CTX_H_

#include <QByteArray>
#include <QList>
#include <QMutex>
#include <QString>

class ClientID {
    public:
        ClientID();
        ClientID(const QString &serialNo);
        QString id() const { return _id; }
        QByteArray idToByteArray() const { return _id.toLatin1(); }

        const QString &manufacturer() const { return _manufacturer; }
        QByteArray manufacturerToByteArray() const { return _manufacturer.toLatin1(); }
        void setManufacturer(const QString &manufacturer) { _manufacturer = manufacturer; }
        const QString &oui() const { return _oui; }
        QByteArray ouiToByteArray() const { return _oui.toLatin1(); }
        void setOui(const QString &oui) { _oui = oui; }
        const QString &productClass() const { return _productClass; }
        QByteArray productClassToByteArray() const { return _productClass.toLatin1(); }
        void setProductClass(const QString &productClass) { _productClass = productClass; }
        const QString &serialNo() const { return _serialNo; }
        QByteArray serialNoToByteArray() const { return _serialNo.toLatin1(); }
        void setSerialNo(const QString &serialNo);

        bool operator ==(const ClientID &rhs) const { return (_serialNo == rhs._serialNo); }

    private:
        void generateId();
        
        QString _id;
        QString _manufacturer;
        QString _oui;
        QString _productClass;
        QString _serialNo;
};

class CWMPCtx {
        /// Singleton pattern, thus constructor is private
        CWMPCtx();
        ~CWMPCtx();
        CWMPCtx(const CWMPCtx &);
        CWMPCtx operator =(const CWMPCtx &);

        QList<ClientID> cwmpSessions;

        static CWMPCtx *_instance;
        static QMutex _instanceMutex;
        QMutex sessMutex;

    public:
        static CWMPCtx &instance();
        void addSession(const ClientID &clientID);

};
#endif // _CWMP_CTX_H_
