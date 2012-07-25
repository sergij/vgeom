/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Jul 24 23:05:32 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   12,   11,   11, 0x05,
      88,   83,   11,   11, 0x05,
     126,   83,   11,   11, 0x05,
     162,   83,   11,   11, 0x05,
     204,   11,   11,   11, 0x05,
     227,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     254,   12,   11,   11, 0x0a,
     303,   11,   11,   11, 0x0a,
     330,   11,   11,   11, 0x0a,
     351,   11,   11,   11, 0x0a,
     376,   11,   11,   11, 0x0a,
     406,   11,   11,   11, 0x0a,
     436,   11,   11,   11, 0x0a,
     465,   11,   11,   11, 0x0a,
     492,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0num,vert,multi,full\0"
    "generetePointsMainWindowSignal(int,bool,bool,bool)\0"
    "file\0loadFromFileMainWindowSignal(QString)\0"
    "saveToFileMainWindowSignal(QString)\0"
    "saveResultToFileMainWindowSignal(QString)\0"
    "drawMainWindowSignal()\0"
    "stopDrawMainWindowSignal()\0"
    "generetePointsMainWindowSlot(int,bool,bool,bool)\0"
    "generationMainWindowSlot()\0"
    "drawMainWindowSlot()\0stopDrawMainWindowSlot()\0"
    "enableToolsOnMainWindowSlot()\0"
    "enableToolsOfMainWindowSlot()\0"
    "loadFromFileMainWindowSlot()\0"
    "saveToFileMainWindowSlot()\0"
    "saveResultToFileMainWindowSlot()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->generetePointsMainWindowSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: _t->loadFromFileMainWindowSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->saveToFileMainWindowSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->saveResultToFileMainWindowSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->drawMainWindowSignal(); break;
        case 5: _t->stopDrawMainWindowSignal(); break;
        case 6: _t->generetePointsMainWindowSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 7: _t->generationMainWindowSlot(); break;
        case 8: _t->drawMainWindowSlot(); break;
        case 9: _t->stopDrawMainWindowSlot(); break;
        case 10: _t->enableToolsOnMainWindowSlot(); break;
        case 11: _t->enableToolsOfMainWindowSlot(); break;
        case 12: _t->loadFromFileMainWindowSlot(); break;
        case 13: _t->saveToFileMainWindowSlot(); break;
        case 14: _t->saveResultToFileMainWindowSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::generetePointsMainWindowSignal(int _t1, bool _t2, bool _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::loadFromFileMainWindowSignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::saveToFileMainWindowSignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::saveResultToFileMainWindowSignal(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::drawMainWindowSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MainWindow::stopDrawMainWindowSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
