#include "cwmpCtx.h"

CWMPCtx CWMPCtx::_instance;

CWMPCtx &CWMPCtx::instance() {
    return _instance;
}

