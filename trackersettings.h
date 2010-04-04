#ifndef TRACKERSETTINGS_H
#define TRACKERSETTINGS_H

#include <QString>

class TrackerSettings
{
public:
    TrackerSettings();
    void read();
    void write();
    QString getUsername();
    void setUsername(QString username);
    QString getPassword();
    void setPassword(QString password);
    QList<int>* getSuppressedMessages();

private:
    QString username;
    QString password;
    QList<int>* suppressedMessages;
};

#endif // TRACKERSETTINGS_H
