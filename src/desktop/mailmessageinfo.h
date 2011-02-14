#ifndef MAILMESSAGEINFO_H
#define MAILMESSAGEINFO_H

#include <QtCore>

class MailMessageInfo
{
public:
    MailMessageInfo(int, QString, QString, QDateTime);
    int id();
    QString sender();
    QString subject();
    QDateTime received();

private:
    int m_id;
    QString m_sender;
    QString m_subject;
    QDateTime m_received;
};

#endif // MAILMESSAGEINFO_H
