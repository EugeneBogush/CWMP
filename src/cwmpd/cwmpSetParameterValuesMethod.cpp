#include <QDomDocument>

#include "cwmpSetParameterValuesMethod.h"

CWMPSetParameterValuesMethod::CWMPSetParameterValuesMethod(
        const CWMPSetParameterValues &setParameterValues)
: _setParameter(setParameterValues) {
}

CWMPSetParameterValuesMethod::~CWMPSetParameterValuesMethod() {
}

QByteArray CWMPSetParameterValuesMethod::methodContent(
        QDomDocument &document,
        QDomElement &body) const {

    QDomElement setParameterValues = document.createElement(
            "cwmp:SetParameterValues");
    body.appendChild(setParameterValues);

    int size = _setParameter.parameterNames().size() / 2; // name, value need all param devide 2

    QDomElement ParameterList = document.createElement(
            "ParameterList");
    QString strList = QString("cwmp:ParameterValueStruct[%1]").arg(size);
    ParameterList.setAttribute("soap:arrayType", strList);
    setParameterValues.appendChild(ParameterList);

    QDomElement ParameterValueStruct = document.createElement(
            "ParameterValueStruct");
    ParameterList.appendChild(ParameterValueStruct);

    QDomElement Name = document.createElement(
            "Name");
    ParameterValueStruct.appendChild(Name);
    QDomText name = document.createTextNode(
            _setParameter.parameterNames()[0]);
    Name.appendChild(name);
    QDomElement Value = document.createElement(
            "Value");
    Value.setAttribute("xsi:type", "xsd:boolean");

    QDomText value = document.createTextNode(
            _setParameter.parameterValues()[0]);
    Value.appendChild(value);

    ParameterValueStruct.appendChild(Value);

    QDomElement ParameterKey = document.createElement(
            "ParameterKey");
    QDomText Key = document.createTextNode(
            _setParameter.parameterKey()[0]);
    ParameterKey.appendChild(Key);
    setParameterValues.appendChild(ParameterKey);

    //    for(int i = 0; i < size; ++i) {
    //        QDomElement strElement = document.createElement("string");
    //        ParameterList.appendChild(strElement);
    //        QDomText name = document.createTextNode(
    //                _setParameterValues.parameterNames()[i]);
    //        strElement.appendChild(name);
    //    }
    return document.toString().toLatin1();
}
