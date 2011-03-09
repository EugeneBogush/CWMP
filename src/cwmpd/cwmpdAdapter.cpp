#include "cwmpdAdapter.h"

CWMPDAdapter::CWMPDAdapter(QObject *parent)
: QDBusAbstractAdaptor(parent){
}

CWMPDAdapter::~CWMPDAdapter() {
}

void CWMPDAdapter::emitInform(const CWMPInform &inf) {
    emit inform(inf);
}
