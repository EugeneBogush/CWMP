#ifndef _CWMP_CTX_H_
#define _CWMP_CTX_H_

#include <QByteArray>
#include <QList>
#include <QMutex>
#include <QString>

//! Identifies specific CPE
/*! Used to indentify specific CPE by their serial numbers. This class also
 * holds other informations send in \<DeviceId\>...\</DeviceId\> Inform element,
 * like Manufacturer, OUI, and ProductClass. Each time Serial number is set,
 * there's also unique Id generated. Id is a SHA-256 of a serial number. It
 * may later be used as e. g. HTTP cookie to mark specific CPE's HTTP session.
 */
class ClientID {
    public:
        //! Constructor
        /*! Default constructor leaves all \<DeviceId\> information blank. Since
         * Serial Number is blank after calling default constructor, Id is
         * empty as well.
         */
        ClientID();

        //! Constructor
        /*!
         * \param serialNo CPE's serial number
         *
         *  this overloaded constructor allows to set serial number at
         * instance creation time. Id is also generated automatically.
         */
        ClientID(const QString &serialNo);

        //! Returns CPE's Id
        /*!
         * Returns CPE's unique Id, which is SHA-256 of serial number. Id is
         * generated each time serial number is set.
         * \see void setSerialNo(const QString &serialNo);
         */
        const QString &id() const { return _id; }

        const QString &soapHdrId() const { return _soapHdrId; }
        QByteArray soapHdrIdToByteArray() const { return _soapHdrId.toLatin1(); }
        void setSoapHdrId(const QString &soapHdrId) { _soapHdrId = soapHdrId; }

        //! Returns CPE's Id
        /*!
         * Returns CPE's unique Id, which is SHA-256 of serial number. Id is
         * generated each time serial number is set.
         * \see void setSerialNo(const QString &serialNo);
         */
        QByteArray idToByteArray() const { return _id.toLatin1(); }

        //! Returns CPE's Manufacturer
        /*! Returns a Manufacturer field of \<DeviceId\>...\</DeviceId\> of an
         * Inform method
         */
        const QString &manufacturer() const { return _manufacturer; }

        //! Returns CPE's Manufacturer
        /*! Returns a Manufacturer field of \<DeviceId\>...\</DeviceId\> of an
         * Inform method
         */
        QByteArray manufacturerToByteArray() const { return _manufacturer.toLatin1(); }

        //! Sets CPE's Manufacturer
        /*! Sets CPE's Manufacturer as sent in \<DeviceId\>...\</DeviceId\> of an
         * Inform method
         *
         *  \param manufacturer a reference to new Manufacturer string
         */
        void setManufacturer(const QString &manufacturer) { _manufacturer = manufacturer; }

        //! Returns CPE's OUI string
        /*! Returns CPE's OUI string as sent in \<DeviceId\>...\</DeviceId\> of an
         * Inform method
         */
        const QString &oui() const { return _oui; }

        //! Returns CPE's OUI string
        /*! Returns CPE's OUI string as sent in \<DeviceId\>...\</DeviceId\> of an
         * Inform method
         */
        QByteArray ouiToByteArray() const { return _oui.toLatin1(); }

        //! Sets CPE's OUI string
        /*! Sets CPE's OUI string
         * \param oui CPE's OUI as sent in \<DeviceId\>...\</DeviceId\> of an
         *        Inform method
         */
        void setOui(const QString &oui) { _oui = oui; }

        //! Returns CPE's ProductClass
        /*! Returns CPE's ProductClass as sent in \<DeviceId\>...\</DeviceId\> of an
         * Inform method
         */
        const QString &productClass() const { return _productClass; }

        //! Returns CPE's ProductClass
        /*! Returns CPE's ProductClass as sent in \<DeviceId\>...\</DeviceId\> of an
         *  Inform method
         */
        QByteArray productClassToByteArray() const { return _productClass.toLatin1(); }

        //! Sets CPE's ProductClass
        /*! Sets CPE's ProductClass
         * \param productClass ProductClass as sent in \<DeviceId\>...\</DeviceId\> of an
         *        Inform method
         */
        void setProductClass(const QString &productClass) { _productClass = productClass; }

        //! Returns CPE's SerialNumber
        /*! Returns CPE's SerialNumber as sent in \<DeviceId\>...\</DeviceId\> of an
         *        Inform method
         */
        const QString &serialNo() const { return _serialNo; }

        //! Returns CPE's SerialNumber
        /*! Returns CPE's SerialNumber as sent in \<DeviceId\>...\</DeviceId\> of an
         *        Inform method
         */
        QByteArray serialNoToByteArray() const { return _serialNo.toLatin1(); }

        //! Sets serial number
        /*!
         * Sets serial number of a CPE. When this function is called, Id is also
         * automatically generated.
         */
        void setSerialNo(const QString &serialNo);

        //! Compares 2 ClientIDs instances.
        /*! Compares 2 ClientIDs instances. They're be considered equal when
         * serial numbers will be the same. Other elements of ClientID (like
         * Manufacturer, OUI etc.) are NOT considered.
         */
        bool operator ==(const ClientID &rhs) const { return (_serialNo == rhs._serialNo); }

    private:
        void generateId();
        
        QString _id;
        QString _soapHdrId;
        QString _manufacturer;
        QString _oui;
        QString _productClass;
        QString _serialNo;
};

//! CWMP context
/*! This class holds all ongoing CWMP sessions contexts. Since CWMP sessions
 * are really HTTP sessions, we have to keep track of all sessions
 * independently from TCP sessions. All information and sessions progresses
 * are stored in this classes instance.
 */
class CWMPCtx {
        //! Default constructor
        /*! Singleton pattern, thus constructor is private
         */
        CWMPCtx();

        //! Default destructor
        /*! Singleton pattern, thus destructor is private
         */
        ~CWMPCtx();

        //! Copy constructor
        /*! Singleton pattern, thus copy constructor is private
         */
        CWMPCtx(const CWMPCtx &);

        //! Assignment operator
        /*! Singleton pattern, thus assignment operator is private
         */
        CWMPCtx operator =(const CWMPCtx &);

        template <class MatchClass>
        const ClientID *cID(const MatchClass &match);

        QList<ClientID> cwmpSessions;

        static CWMPCtx *_instance;
        static QMutex _instanceMutex;
        QMutex sessMutex;

    public:
        //! Returns CWMPCtx's instance
        /*! CWMPCtx is a sigleton class. It's instance may be retrieved by this
         * function.
         */
        static CWMPCtx &instance();

        //! Adds new session to the context
        /*! Check if a session for specified ClientID already exists. If not,
         * new session context is created and stored in CWMPCtx's instance
         *
         * \param clientID CPE's client for which new session is about to be
         *        added
         */
        void addSession(const ClientID &clientID);

        //! Looks up for a client is sessions list based on SerialNumber
        /*! Looks up a CWMP session based on SerialNumber
         *
         * \param serialNo SerialNumber
         * \returns Pointer to ClientID if found. NULL otherwise.
         */
        const ClientID *clientID(const QString &serialNo);

        //! Looks up for a client is sessions list based by ClientID
        /*! Looks up a CWMP session by ClientID
         *
         * \param clientID ClientID based on which lookup is performed
         * \returns Pointer to ClientID if found. NULL otherwise.
         */
        const ClientID *clientID(const ClientID &clientID);

};
#endif // _CWMP_CTX_H_
