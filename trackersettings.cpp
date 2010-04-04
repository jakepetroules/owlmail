#include "trackersettings.h"
#include <QList>
#include <QString>
#include <QDesktopServices>
#include <QSettings>

/*!
    Initializes a new instance of the TrackerSettings class.
 */
TrackerSettings::TrackerSettings()
{
    this->suppressedMessages = new QList<int>();
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
         this->getSuppressedMessages()->append(settings.value("id").toInt());
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
        settings.setValue("id", this->getSuppressedMessages()->at(i));
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
QList<int>* TrackerSettings::getSuppressedMessages()
{
    return this->suppressedMessages;
}
