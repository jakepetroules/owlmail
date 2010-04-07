#include "trackersettings.h"
#include "mailmessageinfo.h"
#include <QList>
#include <QString>
#include <QDesktopServices>
#include <QSettings>

/*!
    Initializes a new instance of the TrackerSettings class.
 */
TrackerSettings::TrackerSettings()
{
    this->suppressedMessages = new QList<MailMessageInfo*>();
}

/*!
    Reads application settings from disk.
 */
void TrackerSettings::read()
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
void TrackerSettings::write()
{
    QSettings settings;
    settings.beginGroup("user");
    settings.setValue("username", this->getUsername());
    settings.setValue("password", this->getPassword());
    settings.beginWriteArray("suppressed_messages");
    for (int i = 0; i < this->getSuppressedMessages()->size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("id", this->getSuppressedMessages()->at(i)->getId());
        settings.setValue("sender", this->getSuppressedMessages()->at(i)->getSender());
        settings.setValue("subject", this->getSuppressedMessages()->at(i)->getSubject());
        settings.setValue("received", this->getSuppressedMessages()->at(i)->getReceived());
    }

    settings.endArray();
    settings.endGroup();
}

/*!
    Gets the login username for CampusCruiser.
 */
QString TrackerSettings::getUsername()
{
    return this->username;
}

/*!
    Sets the login username for CampusCruiser.
 */
void TrackerSettings::setUsername(QString username)
{
    this->username = username;
}

/*!
    Gets the login password for CampusCruiser.
 */
QString TrackerSettings::getPassword()
{
    return this->password;
}

/*!
    Sets the login password for CampusCruiser.
 */
void TrackerSettings::setPassword(QString password)
{
    this->password = password;
}

/*!
    Gets the list of message IDs NOT to show alerts about.
 */
QList<MailMessageInfo*>* TrackerSettings::getSuppressedMessages()
{
    return this->suppressedMessages;
}

/*!
    Determines whether the settings contain a blocked message with the specified ID.
 */
bool TrackerSettings::containsMessageWithId(int id)
{
    for (int i = 0; i < this->getSuppressedMessages()->count(); i++)
    {
        if (this->getSuppressedMessages()->at(i)->getId() == id)
        {
            return true;
        }
    }

    return false;
}

/*!
    Removes the message with the specified ID from the blocked message collection if it is contained within.
 */
void TrackerSettings::removeMessageWithId(int id)
{
    for (int i = 0; i < this->getSuppressedMessages()->count(); i++)
    {
        if (this->getSuppressedMessages()->at(i)->getId() == id)
        {
            this->getSuppressedMessages()->removeAt(i);
            break;
        }
    }
}
