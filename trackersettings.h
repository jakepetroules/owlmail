#ifndef TRACKERSETTINGS_H
#define TRACKERSETTINGS_H

#include "mailmessageinfo.h"
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
    QList<MailMessageInfo*>* getSuppressedMessages();
    bool containsMessageWithId(int id);
    void removeMessageWithId(int id);

private:
    QString username;
    QString password;
    QList<MailMessageInfo*>* suppressedMessages;
};

#endif // TRACKERSETTINGS_H
