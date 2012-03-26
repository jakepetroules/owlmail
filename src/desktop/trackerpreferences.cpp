#include "trackerpreferences.h"
#include "trackerpreferences_keys.h"
#include "mailmessageinfo.h"
#include <QDesktopServices>
#ifdef Q_WS_MAC
#include "mac/macloginitemsmanager.h"
#endif

TrackerPreferences* TrackerPreferences::m_instance = NULL;
TrackerPreferences* TrackerPreferences::m_defaults = NULL;

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
    this->load();
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
    Gets a reference to the TrackerPreferences instance, constructing one if it has not yet been
    created.
 */
TrackerPreferences& TrackerPreferences::instance()
{
    if (!TrackerPreferences::m_instance)
    {
        TrackerPreferences::m_instance = new TrackerPreferences();
    }

    return *TrackerPreferences::m_instance;
}

/*!
    Returns an immutable instance of TrackerPreferences with all values set to default.
 */
const TrackerPreferences& TrackerPreferences::defaults()
{
    if (!TrackerPreferences::m_defaults)
    {
        TrackerPreferences::m_defaults = new TrackerPreferences();

        // Set the default values; now once we return it, it's locked into this state
        TrackerPreferences::m_defaults->restoreDefaults();
    }

    return *TrackerPreferences::m_defaults;
}

/*!
    Destroys the preferences instance, first saving all the settings.
 */
void TrackerPreferences::destroy()
{
    if (TrackerPreferences::m_instance)
    {
        TrackerPreferences::m_instance->save();

        delete TrackerPreferences::m_instance;
        TrackerPreferences::m_instance = NULL;
    }

    if (TrackerPreferences::m_defaults)
    {
        delete TrackerPreferences::m_defaults;
        TrackerPreferences::m_defaults = NULL;
    }
}

/*!
    Loads all preferences from persistent storage.
 */
void TrackerPreferences::load()
{
    // Restoring the defaults allows us to determine the default values when
    // reading settings without duplicating them - all default values should
    // appear in the restoreDefaults() method; nowhere else
    this->restoreDefaults();

    QSettings settings;
    this->setUsername(settings.value(KEY_USERNAME, this->m_username).toString());
    this->setPassword(settings.value(KEY_PASSWORD, this->m_password).toString());

    int suppressesMessagesCount = settings.beginReadArray(KEY_SUPPRESSED_MESSAGES);
    this->suppressedMessages()->clear();
    for (int i = 0; i < suppressesMessagesCount; i++)
    {
        settings.setArrayIndex(i);
        MailMessageInfo* info = new MailMessageInfo(
           settings.value(KEY_SUPPRESSED_MESSAGES_ID).toInt(),
           settings.value(KEY_SUPPRESSED_MESSAGES_SENDER).toString(),
           settings.value(KEY_SUPPRESSED_MESSAGES_SUBJECT).toString(),
           settings.value(KEY_SUPPRESSED_MESSAGES_RECEIVED).toDateTime());
        this->suppressedMessages()->append(info);
    }

    settings.endArray();

    this->setUpdateOnStartup(settings.value(KEY_UPDATE_ON_STARTUP, this->m_updateOnStartup).toBool());
    this->setUpdateInstallerPath(settings.value(KEY_UPDATE_INSTALLER_PATH, this->m_updateInstallerPath).toString());
}

/*!
    Saves all preferences to persistent storage.

    \note Regarding implementation: this method does not modify the class but is not marked const as
    this would allow the instance returned by \a defaults() to persist the settings, which should
    not be allowed.
 */
void TrackerPreferences::save()
{
    QSettings settings;
    settings.setValue(KEY_USERNAME, this->m_username);
    settings.setValue(KEY_PASSWORD, this->m_password);

    settings.beginWriteArray(KEY_SUPPRESSED_MESSAGES);
    for (int i = 0; i < this->suppressedMessages()->size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue(KEY_SUPPRESSED_MESSAGES_ID, this->suppressedMessages()->at(i)->id());
        settings.setValue(KEY_SUPPRESSED_MESSAGES_SENDER, this->suppressedMessages()->at(i)->sender());
        settings.setValue(KEY_SUPPRESSED_MESSAGES_SUBJECT, this->suppressedMessages()->at(i)->subject());
        settings.setValue(KEY_SUPPRESSED_MESSAGES_RECEIVED, this->suppressedMessages()->at(i)->received());
    }

    settings.endArray();

    settings.setValue(KEY_UPDATE_ON_STARTUP, this->m_updateOnStartup);
    settings.setValue(KEY_UPDATE_INSTALLER_PATH, this->m_updateInstallerPath);
}

/*!
    Restores all preferences to their original values.

    \note The recent file list will NOT be affected by this method; that can be cleared with the
    \a clearRecentFiles() method.

    \note File associations will NOT be affected by this method; those settings can be adjusted by
    \a isFileAssociationSet and \a setFileAssociationActive.
 */
void TrackerPreferences::restoreDefaults()
{
    this->setUsername(QString());
    this->setPassword(QString());
    this->suppressedMessages()->clear();
    this->setUpdateOnStartup(true);
    this->setUpdateInstallerPath(QString());
}

/*!
    Gets the login username for CampusCruiser.
 */
QString TrackerPreferences::username() const
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
QString TrackerPreferences::password() const
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
QList<MailMessageInfo*>* TrackerPreferences::suppressedMessages()
{
    return this->m_suppressedMessages;
}

/*!
    Determines whether the settings contain a blocked message with the specified ID.
 */
bool TrackerPreferences::containsMessageWithId(int id)
{
    for (int i = 0; i < this->suppressedMessages()->count(); i++)
    {
        if (this->suppressedMessages()->at(i)->id() == id)
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
    for (int i = 0; i < this->suppressedMessages()->count(); i++)
    {
        if (this->suppressedMessages()->at(i)->id() == id)
        {
            this->suppressedMessages()->removeAt(i);
            break;
        }
    }
}

/*!
    Gets a value indicating whether run-at-startup is supported on this platform and configuration.
 */
bool TrackerPreferences::runAtStartupSupported()
{
#if defined(Q_WS_WIN) || defined(Q_WS_MAC)
    return true;
#elif defined(Q_OS_LINUX)
    return !TrackerPreferences::startupFile().isEmpty();
#else
    return false;
#endif
}

bool TrackerPreferences::runAtStartup() const
{
    if (!TrackerPreferences::runAtStartupSupported())
    {
        qWarning() << "Run at startup is not supported on this platform and configuration.";
    }

#ifdef Q_WS_WIN
    QString path = this->applicationPathForRegistry();

    // If we're running on Windows, set the check box if the registry contains the correct key set to the running application's path
    QSettings reg(KEY_WIN_STARTUP_PATH, QSettings::NativeFormat);
    return reg.contains(KEY_WIN_STARTUP_NAME) && reg.value(KEY_WIN_STARTUP_NAME).toString().compare(path, Qt::CaseInsensitive) == 0;
#elif defined(Q_WS_MAC)
    MacLoginItemsManager manager;
    return manager.containsRunningApplication();
#elif defined(Q_OS_LINUX)
    return QFile::exists(TrackerPreferences::startupFile());
#else
    return false;
#endif
}

void TrackerPreferences::setRunAtStartup(bool run)
{
    if (!TrackerPreferences::runAtStartupSupported())
    {
        Q_UNUSED(run);
        qWarning() << "Run at startup is not supported on this platform and configuration.";
        return;
    }

#ifdef Q_WS_WIN
    QSettings settings(KEY_WIN_STARTUP_PATH, QSettings::NativeFormat);
    if (run)
    {
        settings.setValue(KEY_WIN_STARTUP_NAME, this->applicationPathForRegistry());
    }
    else
    {
        settings.remove(KEY_WIN_STARTUP_NAME);
    }
#elif defined(Q_WS_MAC)
    if (QFile::exists(TrackerPreferences::macLoginItemsFile()))
    {
        MacLoginItemsManager manager;

        if (run && !TrackerPreferences::runAtStartup())
        {
            manager.appendRunningApplication();
        }
        else if (!run && TrackerPreferences::runAtStartup())
        {
            manager.removeRunningApplication();
        }
    }
#elif defined(Q_OS_LINUX)
    switch (LinuxSystemInfo::desktopEnvironment())
    {
        case LinuxSystemInfo::GNOME:
        {
            if (run)
            {
                QFile file(TrackerPreferences::startupFile());
                if (file.open(QFile::WriteOnly | QFile::Truncate))
                {
                    file.setPermissions(file.permissions() | QFile::ExeOwner | QFile::ExeGroup);

                    QTextStream out(&file);
                    out << "[Desktop Entry]\n";
                    out << "Type=Application\n";
                    out << QString("Exec=%1.desktop\n").arg(QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
                    out << "Hidden=false\n";
                    out << "NoDisplay=false\n";
                    out << "X-GNOME-Autostart-enabled=true\n";
                    out << "Name=Silverlock\n";
                }
            }
            else
            {
                QFile::remove(TrackerPreferences::startupFile());
            }
        }

        case LinuxSystemInfo::KDE:
        {
            if (run)
            {
                QFile::link(QDir::toNativeSeparators(QCoreApplication::applicationFilePath()), TrackerPreferences::startupFile());
            }
            else
            {
                QFile::remove(TrackerPreferences::startupFile());
            }
        }

        default:
            return;
    }
#endif
}

bool TrackerPreferences::updateOnStartup() const
{
    return this->m_updateOnStartup;
}

void TrackerPreferences::setUpdateOnStartup(bool update)
{
    this->m_updateOnStartup = update;
}

/*!
    Returns the path of the downloaded update installer.

    This is stored so if the user cancels the installation they can restart
    it later without having to re-download the installation file.
 */
QString TrackerPreferences::updateInstallerPath() const
{
    return QDir(this->m_updateInstallerPath).canonicalPath();
}

void TrackerPreferences::setUpdateInstallerPath(const QString &path)
{
    this->m_updateInstallerPath = QDir(path).canonicalPath();
}

// Platform-specific methods...
#ifdef Q_WS_WIN

/*!
    Gets the path of the running application with native separators and enclosed in quotes, suitable
    for entry into the Windows registry.
 */
QString TrackerPreferences::applicationPathForRegistry()
{
    return QString("\"%1\"").arg(QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
}

#elif defined(Q_WS_MAC)

/*!
    Gets the property list file for login items on Mac OS X.
 */
QString TrackerPreferences::macLoginItemsFile()
{
    return QDesktopServices::storageLocation(QDesktopServices::HomeLocation) + "/Library/Preferences/loginwindow.plist";
}

#elif defined(Q_OS_LINUX)
/*!
    Gets the absolute path of the run-at-startup file for the current desktop environment.

    Returns an empty string if the desktop environment is not supported.
 */
QString TrackerPreferences::startupFile()
{
    return TrackerPreferences::startupFileFor(LinuxSystemInfo::desktopEnvironment());
}

/*!
    Gets the absolute path of the run-at-startup file for the specified desktop environment.

    Returns an empty string if the desktop environment is not supported.
 */
QString TrackerPreferences::startupFileFor(LinuxSystemInfo::DesktopEnvironment desktopEnvironment)
{
    switch (desktopEnvironment)
    {
        case LinuxSystemInfo::GNOME:
            return QString("%1/config/autostart/%2.desktop").arg(QDir::homePath()).arg(ApplicationInfo::unixName());
        case LinuxSystemInfo::KDE:
            return QString("%1/.kde/Autostart/%2").arg(QDir::homePath()).arg(ApplicationInfo::unixName());
        default:
            return QString();
    }
}
#endif
