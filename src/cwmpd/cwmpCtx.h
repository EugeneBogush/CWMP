#ifndef _CWMP_CTX_H_
#define _CWMP_CTX_H_

#include <QByteArray>
#include <QList>
#include <QMutex>
#include <QString>

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

        static CWMPCtx *_instance;
        static QMutex _instanceMutex;
        QMutex sessMutex;

    public:
        //! Returns CWMPCtx's instance
        /*! CWMPCtx is a sigleton class. It's instance may be retrieved by this
         * function.
         */
        static CWMPCtx &instance();
};
#endif // _CWMP_CTX_H_
