#include <QDomDocument>

#include "cwmpGetParameterValuesMethod.h"
#include "soap.h"

CWMPGetParameterValuesMethod::CWMPGetParameterValuesMethod(
        const CWMPGetParameterValues &getParameterValues)
: _getParameterValues(getParameterValues) {
}

CWMPGetParameterValuesMethod::~CWMPGetParameterValuesMethod() {
}

QByteArray CWMPGetParameterValuesMethod::methodContent(
        QDomDocument &document,
        QDomElement &body) const {

    QDomElement getParameterValues = document.createElement(
            "cwmp:GetParameterValues");
    body.appendChild(getParameterValues);

    QDomElement parameterNames = document.createElement(
            "ParameterNames");

    int size =_getParameterValues.parameterNames().size();
    QString str = QString("xsd:string[%1]").arg(size);
    parameterNames.setAttribute("soap:arrayType", str);
    getParameterValues.appendChild(parameterNames);

    for(int i = 0; i < size; ++i) {
        QDomElement strElement = document.createElement("string");
        parameterNames.appendChild(strElement);
        QDomText name = document.createTextNode(
                _getParameterValues.parameterNames()[i]);
        strElement.appendChild(name);
    }
    return document.toString().toLatin1();
}
