#ifndef MAILMESSAGEINFO_H
#define MAILMESSAGEINFO_H

#include <QDateTime>

class MailMessageInfo
{
public:
    MailMessageInfo(int, QString, QString, QDateTime);
    int getId();
    QString getSender();
    QString getSubject();
    QDateTime getReceived();

private:
    int m_id;
    QString m_sender;
    QString m_subject;
    QDateTime m_received;
};

#endif // MAILMESSAGEINFO_H
