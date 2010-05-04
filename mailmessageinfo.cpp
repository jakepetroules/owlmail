#include "mailmessageinfo.h"
#include <QDateTime>
#include <QString>

/*!
    \class MailMessageInfo
    Encapsulates MyKSC email message details.
 */

/*!
    Initializes a new instance of the MailMessageInfo class.
 */
MailMessageInfo::MailMessageInfo(int id, QString sender, QString subject, QDateTime received)
    : m_id(id), m_sender(sender), m_subject(subject), m_received(received)
{
}

/*!
   Gets the ID number of the message.
 */
int MailMessageInfo::getId()
{
    return this->m_id;
}

/*!
   Gets the sender of the message.
 */
QString MailMessageInfo::getSender()
{
    return this->m_sender;
}

/*!
   Gets the subject of the message.
 */
QString MailMessageInfo::getSubject()
{
    return this->m_subject;
}

/*!
   Gets the date and time on which the message was received.
 */
QDateTime MailMessageInfo::getReceived()
{
    return this->m_received;
}
