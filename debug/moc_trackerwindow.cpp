/****************************************************************************
** Meta object code from reading C++ file 'trackerwindow.h'
**
** Created: Fri Jan 29 20:05:09 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../trackerwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackerwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrackerWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      22,   14,   14,   14, 0x09,
      37,   14,   14,   14, 0x09,
      53,   14,   14,   14, 0x09,
      63,   14,   14,   14, 0x09,
      81,   14,   14,   14, 0x09,
      89,   14,   14,   14, 0x09,
     108,  105,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_TrackerWindow[] = {
    "TrackerWindow\0\0exit()\0navigateHome()\0"
    "navigateInbox()\0options()\0checkForUpdates()\0"
    "about()\0browserReload()\0ok\0"
    "browserLoaded(bool)\0"
};

const QMetaObject TrackerWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TrackerWindow,
      qt_meta_data_TrackerWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrackerWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrackerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrackerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrackerWindow))
        return static_cast<void*>(const_cast< TrackerWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TrackerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: exit(); break;
        case 1: navigateHome(); break;
        case 2: navigateInbox(); break;
        case 3: options(); break;
        case 4: checkForUpdates(); break;
        case 5: about(); break;
        case 6: browserReload(); break;
        case 7: browserLoaded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
