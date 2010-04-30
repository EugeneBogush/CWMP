#ifndef _CWMP_CTX_H_
#define _CWMP_CTX_H_

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
