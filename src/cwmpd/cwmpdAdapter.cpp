#include "cwmpdAdapter.h"

CWMPDAdapter::CWMPDAdapter(QObject *parent)
: QDBusAbstractAdaptor(parent){
}

void CWMPDAdapter::emitInform(const CWMPInform &inf) {
    emit inform(inf);
}
