#ifndef TRACKERPREFERENCES_H
#define TRACKERPREFERENCES_H

#include <QtCore>

class MailMessageInfo;

class TrackerPreferences
{
public:
    TrackerPreferences();
    ~TrackerPreferences();
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

#endif // TRACKERPREFERENCES_H
