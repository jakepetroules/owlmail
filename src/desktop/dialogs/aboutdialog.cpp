#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "licensedialog.h"
#include <petroules-utilities.h>

/*!
    \class AboutDialog

    The AboutDialog class provides a dialog that displays general application information.
 */

/*!
    Constructs a new AboutDialog.

    \param parent The parent widget of the dialog.
 */
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    this->ui->setupUi(this);

    // Set window title to "About ApplicationName"
    this->setWindowTitle(this->windowTitle().arg(qiApp->applicationName()));

    // Set the application and organization names on the labels
    this->ui->labelApplication->setText(this->ui->labelApplication->text()
        .arg(qiApp->applicationName())
        .arg(qiApp->applicationVersion()));
    this->ui->labelInfo->setText(this->ui->labelInfo->text()
        .arg(qiApp->copyrightLink())
        .arg(qiApp->trademarks())
        .arg(qiApp->applicationName()));
}

/*!
    Destroys the dialog.
 */
AboutDialog::~AboutDialog()
{
    delete this->ui;
}

/*!
    Displays the license dialog.
 */
void AboutDialog::displayLicenseDialog()
{
    LicenseDialog dialog(this);
    dialog.exec();
}

/*!
    Displays the build information dialog.
 */
void AboutDialog::displayBuildInformationDialog()
{
    QString qtType = QString::number(PlatformInformation::wordSize());
#if defined(Q_OS_MAC) && defined(Q_WS_MAC)
    #ifdef QT_MAC_USE_COCOA
        qtType = "Cocoa, " + qtType;
    #else
        qtType = "Carbon, " + qtType;
    #endif
#endif

    QString osString = PlatformInformation::osString();
#ifdef Q_WS_X11
    osString += "/X11";
#elif defined(Q_WS_WAYLAND)
    osString += "/Wayland";
#endif

    QString buildInfo = QString("<p>Compiled against Qt %1 (%2-bit) using %3 and linked against:</p>"
                                "<ul>"
                                "<li>Qt %4</li>"
                                "<li>Qt Solutions %5</li>"
                                "<li>Petroules Utilities %6</li>"
                                "</ul>"
                                "<p>Running on %7 with a %8 processor.</p>")
        .arg(QT_VERSION_STR)
        .arg(qtType)
        .arg(PlatformInformation::compilerString())
        .arg(qVersion())
        .arg("2.6")
        .arg(PETROULESUTILITIES_VERSION_STR)
        .arg(osString)
        .arg(PlatformInformation::byteOrder());

    NativeDialogs::information(this, tr("Build Information"), buildInfo);
}
