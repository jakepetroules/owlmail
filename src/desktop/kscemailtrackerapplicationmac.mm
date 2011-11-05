#include "kscemailtrackerapplicationmac.h"

extern void qt_mac_set_dock_menu(QMenu*);

@interface DockIconClickEventHandler : NSObject
{
@public
    KSCEmailTrackerApplicationMac* macApplication;
}
- (void)handleDockClickEvent:(NSAppleEventDescriptor*)event withReplyEvent:(NSAppleEventDescriptor*)replyEvent;
@end

@implementation DockIconClickEventHandler
- (void)handleDockClickEvent:(NSAppleEventDescriptor*)event withReplyEvent:(NSAppleEventDescriptor*)replyEvent {
    if (macApplication)
        macApplication->dockIconClickEvent();
}
@end

KSCEmailTrackerApplicationMac::KSCEmailTrackerApplicationMac(int &argc, char *argv[]) :
    KSCEmailTrackerApplication(argc, argv), m_pool([[NSAutoreleasePool alloc] init]),
    m_dockIconClickEventHandler([[DockIconClickEventHandler alloc] init])
{
    m_eventMonitor = [NSEvent addLocalMonitorForEventsMatchingMask:NSKeyDownMask handler:^(NSEvent *incomingEvent) {
        return cocoaEventFilter(incomingEvent);
    }];

    DockIconClickEventHandler* dockIconClickEventHandler = static_cast<DockIconClickEventHandler*>(m_dockIconClickEventHandler);
    dockIconClickEventHandler->macApplication = this;

    /*connect(this, SIGNAL(goToState(State)),
            this, SLOT(handleStateChange(State)));*/

    /*foreach (CharmWindow* window, m_windows)
        m_dockMenu.addAction(window->showHideAction());*/

    //qt_mac_set_dock_menu(&m_dockMenu);

    // OSX doesn't use icons in menus
    setWindowIcon(QIcon());
    /*foreach (CharmWindow* window, m_windows)
        window->setWindowIcon(QIcon());*/
    QCoreApplication::setAttribute(Qt::AA_DontShowIconsInMenus);

    // here temporarily
    QTimer::singleShot(1, this, SLOT(setupCocoaEventHandler()));
    //setupCocoaEventHandler();
}

KSCEmailTrackerApplicationMac::~KSCEmailTrackerApplicationMac()
{
    [NSEvent removeMonitor: m_eventMonitor];
    [m_pool drain];
}

/*void KSCEmailTrackerApplicationMac::handleStateChange(State state) const
{
    if (state == Configuring)
        setupCocoaEventHandler();
}*/

void KSCEmailTrackerApplicationMac::setupCocoaEventHandler()
{
    // TODO: This apparently uses a legacy API and we should be using the
    // applicationShouldHandleReopen:hasVisibleWindows: method on
    // NSApplicationDelegate but this isn't possible without nasty runtime
    // reflection hacks until Qt is fixed. If this breaks, shout at them :)
    [[NSAppleEventManager sharedAppleEventManager]
     setEventHandler: m_dockIconClickEventHandler
     andSelector: @selector(handleDockClickEvent:withReplyEvent:)
     forEventClass: kCoreEventClass
     andEventID: kAEReopenApplication];
}

void KSCEmailTrackerApplicationMac::dockIconClickEvent()
{
    this->showMainWindow();
}

NSEvent* KSCEmailTrackerApplicationMac::cocoaEventFilter(NSEvent* incomingEvent)
{
    NSUInteger modifierFlags = [incomingEvent modifierFlags];

    int shortcutFlags = [[incomingEvent charactersIgnoringModifiers] UTF8String][0];

    if (modifierFlags & NSShiftKeyMask)
        shortcutFlags |= Qt::ShiftModifier;
    if (modifierFlags & NSControlKeyMask)
        shortcutFlags |= Qt::MetaModifier;
    if (modifierFlags & NSCommandKeyMask)
        shortcutFlags |= Qt::ControlModifier;
    if (modifierFlags & NSAlternateKeyMask)
        shortcutFlags |= Qt::AltModifier;

    const QKeySequence keySequence(shortcutFlags);
    const bool autoRepeat = [incomingEvent isARepeat];

    const QList<QShortcut*> active = activeShortcuts(keySequence, autoRepeat);
    foreach (QShortcut* const shortcut, active)
    {
        QShortcutEvent event(keySequence, shortcut->id());
        QObject* const receiver = shortcut;
        receiver->event(&event);
    }

    if (!active.isEmpty())
        return nil;

    return incomingEvent;
}

QList<QShortcut*> KSCEmailTrackerApplicationMac::shortcuts(QWidget* parent)
{
    QList<QShortcut*> result;
    if (!parent)
    {
        const QWidgetList widgets = QApplication::topLevelWidgets();
        for (QWidgetList::const_iterator it = widgets.begin(); it != widgets.end(); ++it)
            result += shortcuts(*it);
    }
    else
    {
        const QList<QShortcut*> cuts = parent->findChildren<QShortcut*>();
        for (QList<QShortcut*>::const_iterator it = cuts.begin(); it != cuts.end(); ++it)
            if ((*it)->context() == Qt::ApplicationShortcut)
                result.push_back(*it);

        const QList<QWidget*> children = parent->findChildren<QWidget*>();
        for (QList<QWidget*>::const_iterator it = children.begin(); it != children.end(); ++it)
            result += shortcuts(*it);
    }

    return result;
}

QList<QShortcut*> KSCEmailTrackerApplicationMac::activeShortcuts(const QKeySequence &seq, bool autorep, QWidget* parent)
{
    const QList<QShortcut*> cuts = shortcuts(parent);
    QList<QShortcut*> result;
    for (QList<QShortcut*>::const_iterator it = cuts.begin(); it != cuts.end(); ++it)
        if ((*it)->context() == Qt::ApplicationShortcut && ((*it)->autoRepeat() == autorep || !autorep) && (*it)->isEnabled() && (*it)->key().matches(seq))
            result.push_back( *it );
    return result;
}
