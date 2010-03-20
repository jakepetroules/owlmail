#include <QtGui/QApplication>
#include "trackerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrackerWindow w;
    w.show();
    return a.exec();
}
