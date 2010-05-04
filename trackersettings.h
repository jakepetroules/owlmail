#ifndef TRACKERSETTINGS_H
#define TRACKERSETTINGS_H

#include "mailmessageinfo.h"
#include <QString>

class TrackerSettings
{
public:
    TrackerSettings();
    ~TrackerSettings();
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
    QString m_username;
    QString m_password;
    QList<MailMessageInfo*>* m_suppressedMessages;
};

#endif // TRACKERSETTINGS_H
