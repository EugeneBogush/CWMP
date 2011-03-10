#ifndef CWMPGETPARAMETERVALUES_H
#define CWMPGETPARAMETERVALUES_H

#include <QStringList>

class CWMPGetParameterValues
{
public:
    CWMPGetParameterValues();
    ~CWMPGetParameterValues();

    const QStringList &parameterNames() const { return _parameterNames; }
    void setParameterNames(const QStringList &parameterNames)
        { _parameterNames = parameterNames; }
    void addParameterName(const QString &name);
    void removeParameterName(const QString &name);

private:
    QStringList _parameterNames;
};

#endif // CWMPGETPARAMETERVALUES_H
