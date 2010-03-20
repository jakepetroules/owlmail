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
    int id;
    QString sender;
    QString subject;
    QDateTime received;
};

#endif // MAILMESSAGEINFO_H
