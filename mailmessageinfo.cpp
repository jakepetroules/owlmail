#include "mailmessageinfo.h"
#include <QString>
#include <QDateTime>

MailMessageInfo::MailMessageInfo(int id, QString sender, QString subject, QDateTime received)
{
    this->id = id;
    this->sender = sender;
    this->subject = subject;
    this->received = received;
}

int MailMessageInfo::getId()
{
    return this->id;
}

QString MailMessageInfo::getSender()
{
    return this->sender;
}

QString MailMessageInfo::getSubject()
{
    return this->subject;
}

QDateTime MailMessageInfo::getReceived()
{
    return this->received;
}
