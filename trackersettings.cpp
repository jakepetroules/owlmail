#include "trackersettings.h"
#include <QList>
#include <QString>

TrackerSettings::TrackerSettings()
{
}

void TrackerSettings::read()
{

}

QString TrackerSettings::getUsername()
{
    return "jpetroules";
}

QString TrackerSettings::getPassword()
{
    return "rafflez0rz13";
}

QList<int>* TrackerSettings::getSuppressedMessages()
{
    return new QList<int>();
}
