#ifndef TRACKERPREFERENCES_KEYS_H
#define TRACKERPREFERENCES_KEYS_H

// Main settings (loaded and saved automatically by the class)
#define KEY_USERNAME "Username"
#define KEY_PASSWORD "Password"
#define KEY_UPDATE_ON_STARTUP "UpdateOnStartup"
#define KEY_UPDATE_INSTALLER_PATH "UpdateInstallerPath"
#define KEY_SUPPRESSED_MESSAGES "SuppressedMessages"
#define KEY_SUPPRESSED_MESSAGES_ID "ID"
#define KEY_SUPPRESSED_MESSAGES_SENDER "Sender"
#define KEY_SUPPRESSED_MESSAGES_SUBJECT "Subject"
#define KEY_SUPPRESSED_MESSAGES_RECEIVED "Received"

// Miscellaneous settings (loaded and saved manually by the user)
#define KEY_WIN_STARTUP_PATH "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define KEY_WIN_STARTUP_NAME "KSC Email Tracker"

#endif // TRACKERPREFERENCES_KEYS_H
