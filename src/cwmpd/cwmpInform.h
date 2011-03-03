#ifndef CWMPINFORM_H
#define CWMPINFORM_H

#include <QString>

class CWMPInform
{
public:
    CWMPInform();
    unsigned maxEnvelopes() const { return _maxEnvelopes; }
    void setMaxEnvelopes(int maxEnvelopes) { _maxEnvelopes = maxEnvelopes; }

    const QString &currentTime() const { return _currentTime; }
    void setCurrentTime(const QString &currentTime)
        { _currentTime = currentTime; }

    unsigned retryCount() const { return _retryCount; }
    void setRetryCount(unsigned retryCount) { _retryCount = retryCount; }

private:
    unsigned _maxEnvelopes;
    QString _currentTime;
    unsigned _retryCount;
};

#endif // CWMPINFORM_H
