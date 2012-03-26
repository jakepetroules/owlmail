#ifndef TRACKERPREFERENCES_H
#define TRACKERPREFERENCES_H

#include <QtCore>
#include "linuxsysteminfo.h"

class MailMessageInfo;

class TrackerPreferences
{
public:
    ~TrackerPreferences();
    static TrackerPreferences& instance();
    static const TrackerPreferences& defaults();
    static void destroy();
    void load();
    void save();
    void restoreDefaults();

    QString username() const;
    void setUsername(QString username);
    QString password() const;
    void setPassword(QString password);
    QList<MailMessageInfo*>* suppressedMessages();
    bool containsMessageWithId(int id);
    void removeMessageWithId(int id);

    static bool runAtStartupSupported();
    bool runAtStartup() const;
    void setRunAtStartup(bool run);

    bool updateOnStartup() const;
    void setUpdateOnStartup(bool update);

    QString updateInstallerPath() const;
    void setUpdateInstallerPath(const QString &path);

private:
    TrackerPreferences();
    static TrackerPreferences *m_instance;
    static TrackerPreferences *m_defaults;
    QString m_username;
    QString m_password;
    QList<MailMessageInfo*> *m_suppressedMessages;
    bool m_updateOnStartup;
    QString m_updateInstallerPath;

#ifdef Q_WS_WIN
    static QString applicationPathForRegistry();
#elif defined(Q_WS_MAC)
    static QString macLoginItemsFile();
#elif defined(Q_OS_LINUX)
    static QString startupFile();
    static QString startupFileFor(LinuxSystemInfo::DesktopEnvironment desktopEnvironment);
#endif
};

#endif // TRACKERPREFERENCES_H
