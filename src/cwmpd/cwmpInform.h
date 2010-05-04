#ifndef _CWMP_INFORM_H_
#define _CWMP_INFORM_H_

#include <QDomNode>

class ClientID;

//! Representation of Inform RPC method
/*! This class represents Inform method called by CPE. All information like
 * \<DeviceId\>, \<Events\> and so on are parsed and stored by this class.
 */
class Inform {
    public:
        //! Constructs Inform's instance
        /*! This constructor creats an instance based on informNode.
         * \param informNode This holds \<Inform\> node of SOAP message
         */
        Inform(const QDomNode &informNode, const ClientID &clientID);

        //! Default destructor
        ~Inform();

        //! Returns this instance's CWMP session context
        /*! This function returns context of CWMP session associated with
         * this Inform
         */
        const ClientID *clientID() const { return _clientID; }

    private:
        void parseInform(const QDomNode &informNode);
        void parseDeviceId(const QDomNode &deviceIdNode);

        const ClientID *_clientID;
};

#endif // _CWMP_INFORM_H_

