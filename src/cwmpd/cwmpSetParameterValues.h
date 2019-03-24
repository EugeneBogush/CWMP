/* 
 * File:   cwmpSetParameterValues.h
 * Author: yevhen
 *
 * Created on 17 січня 2018, 14:16
 */

#ifndef CWMPSETPARAMETERVALUES_H
#define CWMPSETPARAMETERVALUES_H

#include <QStringList>

class CWMPSetParameterValues {
public:
    CWMPSetParameterValues();
    ~CWMPSetParameterValues();

    const QStringList &parameterNames() const {
        return _parameterNames;
    }
    void setParameterNames(const QStringList &parameterNames) {
        _parameterNames = parameterNames;
    }
    void addParameterName(const QString &name);
    void removeParameterName(const QString &name);

    const QStringList &parameterValues() const {
        return _parameterValues;
    }
    void setParameterValue(const QStringList &parameterValue) {
        _parameterValues = parameterValue;
    }
    void addParameterValue(const QString &value);
    void removeParameterValue(const QString &value);

    const QStringList &parameterKey() const {
        return _parameterKey;
    }
    void setParameterKey(const QStringList &parameterKey) {
        _parameterKey = parameterKey;
    }
    void addParameterKey(const QString &key);
    void removeParameterKey(const QString &key);
private:
    QStringList _parameterNames;
    QStringList _parameterValues;
    QStringList _parameterKey;
};

#endif /* CWMPSETPARAMETERVALUES_H */

