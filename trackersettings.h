#ifndef TRACKERSETTINGS_H
#define TRACKERSETTINGS_H

#include <QString>

class TrackerSettings
{
public:
    TrackerSettings();
    static void read();
    static QString getUsername();
    static QString getPassword();
    static QList<int>* getSuppressedMessages();
};

#endif // TRACKERSETTINGS_H
