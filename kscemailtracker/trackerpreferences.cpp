#include "trackerpreferences.h"
#include "mailmessageinfo.h"

/*!
    \class TrackerPreferences

    Represents the KSC Email Tracker application settings.
 */

/*!
    Constructs a settings instance.
 */
TrackerPreferences::TrackerPreferences()
    : m_username(QString()), m_password(QString()), m_suppressedMessages(new QList<MailMessageInfo*>())
{
}

/*!
    Destroys the TrackerPreferences.
 */
TrackerPreferences::~TrackerPreferences()
{
    for (int i = 0; i < this->m_suppressedMessages->count(); i++)
    {
        delete this->m_suppressedMessages->at(i);
    }

    this->m_suppressedMessages->clear();
    delete this->m_suppressedMessages;
    this->m_suppressedMessages = NULL;
}

/*!
    Reads application settings from disk.
 */
void TrackerPreferences::read()
{
    QSettings settings;
    settings.beginGroup("user");
    this->setUsername(settings.value("username", "").toString());
    this->setPassword(settings.value("password", "").toString());
    int size = settings.beginReadArray("suppressed_messages");
    this->getSuppressedMessages()->clear();
    for (int i = 0; i < size; i++)
    {
         settings.setArrayIndex(i);
         MailMessageInfo* info = new MailMessageInfo(
            settings.value("id").toInt(),
            settings.value("sender").toString(),
            settings.value("subject").toString(),
            settings.value("received").toDateTime());
         this->getSuppressedMessages()->append(info);
    }

    settings.endArray();
    settings.endGroup();
}

/*!
    Writes application settings to disk.
 */
void TrackerPreferences::write()
{
    QSettings settings;
    settings.beginGroup("user");
    settings.setValue("username", this->getUsername());
    settings.setValue("password", this->getPassword());
    settings.beginWriteArray("suppressed_messages");
    for (int i = 0; i < this->getSuppressedMessages()->size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("id", this->getSuppressedMessages()->at(i)->id());
        settings.setValue("sender", this->getSuppressedMessages()->at(i)->sender());
        settings.setValue("subject", this->getSuppressedMessages()->at(i)->subject());
        settings.setValue("received", this->getSuppressedMessages()->at(i)->received());
    }

    settings.endArray();
    settings.endGroup();
}

/*!
    Gets the login username for CampusCruiser.
 */
QString TrackerPreferences::getUsername()
{
    return this->m_username;
}

/*!
    Sets the login username for CampusCruiser.
 */
void TrackerPreferences::setUsername(QString username)
{
    this->m_username = username;
}

/*!
    Gets the login password for CampusCruiser.
 */
QString TrackerPreferences::getPassword()
{
    return this->m_password;
}

/*!
    Sets the login password for CampusCruiser.
 */
void TrackerPreferences::setPassword(QString password)
{
    this->m_password = password;
}

/*!
    Gets the list of message IDs NOT to show alerts about.
 */
QList<MailMessageInfo*>* TrackerPreferences::getSuppressedMessages()
{
    return this->m_suppressedMessages;
}

/*!
    Determines whether the settings contain a blocked message with the specified ID.
 */
bool TrackerPreferences::containsMessageWithId(int id)
{
    for (int i = 0; i < this->getSuppressedMessages()->count(); i++)
    {
        if (this->getSuppressedMessages()->at(i)->id() == id)
        {
            return true;
        }
    }

    return false;
}

/*!
    Removes the message with the specified ID from the blocked message collection if it is contained within.
 */
void TrackerPreferences::removeMessageWithId(int id)
{
    for (int i = 0; i < this->getSuppressedMessages()->count(); i++)
    {
        if (this->getSuppressedMessages()->at(i)->id() == id)
        {
            this->getSuppressedMessages()->removeAt(i);
            break;
        }
    }
}
