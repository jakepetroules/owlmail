#ifndef KSCEMAILTRACKERAPPLICATIONMAC_H
#define KSCEMAILTRACKERAPPLICATIONMAC_H

#include "kscemailtrackerapplication.h"

class NSEvent;
class objc_object;

class KSCEmailTrackerApplicationMac : public KSCEmailTrackerApplication
{
    Q_OBJECT

public:
    explicit KSCEmailTrackerApplicationMac(int &argc, char *argv[]);
    ~KSCEmailTrackerApplicationMac();
    // This method to be public due to lack of friend classes in Objective-C and
    // the lack inheritance of Objective-C classes from C++ ones.
    void dockIconClickEvent();

private slots:
    //void handleStateChange(State state) const;

private:
    static QList<QShortcut*> shortcuts(QWidget *parent);
    static QList<QShortcut*> activeShortcuts(const QKeySequence &seq, bool autorep, QWidget *parent = 0);
    NSEvent* cocoaEventFilter(NSEvent *incomingEvent);
private slots:
    void setupCocoaEventHandler();

private:
    QMenu m_dockMenu;

    objc_object *m_pool;
    objc_object *m_eventMonitor;
    objc_object *m_dockIconClickEventHandler;
};

#endif // KSCEMAILTRACKERAPPLICATIONMAC_H
