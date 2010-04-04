#include "mailmessageinfo.h"
#include <QString>
#include <QDateTime>

/*!
    \class MailMessageInfo
    Encapsulates MyKSC email message details.
 */

/*!
    Initializes a new instance of the MailMessageInfo class.
 */
MailMessageInfo::MailMessageInfo(int id, QString sender, QString subject, QDateTime received)
{
    this->id = id;
    this->sender = sender;
    this->subject = subject;
    this->received = received;
}

/*!
   Gets the ID number of the message.
 */
int MailMessageInfo::getId()
{
    return this->id;
}

/*!
   Gets the sender of the message.
 */
QString MailMessageInfo::getSender()
{
    return this->sender;
}

/*!
   Gets the subject of the message.
 */
QString MailMessageInfo::getSubject()
{
    return this->subject;
}

/*!
   Gets the date and time on which the message was received.
 */
QDateTime MailMessageInfo::getReceived()
{
    return this->received;
}
