/****************************************************************************
** Meta object code from reading C++ file 'area.h'
**
** Created: Tue Jul 24 23:05:34 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "area.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'area.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Area[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,    5,    5,    5, 0x0a,
      55,    5,    5,    5, 0x0a,
      74,    5,    5,    5, 0x0a,
      97,    5,    5,    5, 0x0a,
     117,    5,    5,    5, 0x0a,
     140,    5,    5,    5, 0x0a,
     160,    5,    5,    5, 0x0a,
     184,    5,    5,    5, 0x0a,
     205,    5,    5,    5, 0x0a,
     221,    5,    5,    5, 0x0a,
     236,    5,    5,    5, 0x0a,
     253,    5,    5,    5, 0x0a,
     268,    5,    5,    5, 0x0a,
     287,    5,    5,    5, 0x0a,
     302,    5,    5,    5, 0x0a,
     322,  317,    5,    5, 0x0a,
     352,  317,    5,    5, 0x0a,
     380,  317,    5,    5, 0x0a,
     442,  414,    5,    5, 0x0a,
     485,    5,    5,    5, 0x0a,
     508,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Area[] = {
    "Area\0\0generationFailAreaSignal()\0"
    "forwardStepAreaSlot()\0backStepAreaSlot()\0"
    "qforwardStepAreaSlot()\0qbackStepAreaSlot()\0"
    "forwardStepsAreaSlot()\0backStepsAreaSlot()\0"
    "qforwardStepsAreaSlot()\0qbackStepsAreaSlot()\0"
    "pauseAreaSlot()\0stopAreaSlot()\0"
    "finishAreaSlot()\0drawAreaSlot()\0"
    "stopDrawAreaSlot()\0undoAreaSlot()\0"
    "redoAreaSlot()\0file\0loadFromFileAreaSlot(QString)\0"
    "saveToFileAreaSlot(QString)\0"
    "saveResultToFileAreaSlot(QString)\0"
    "numSegments,vert,multi,full\0"
    "generetePointsAreaSlot(int,bool,bool,bool)\0"
    "computeIntersections()\0cleanSegments()\0"
};

void Area::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Area *_t = static_cast<Area *>(_o);
        switch (_id) {
        case 0: _t->generationFailAreaSignal(); break;
        case 1: _t->forwardStepAreaSlot(); break;
        case 2: _t->backStepAreaSlot(); break;
        case 3: _t->qforwardStepAreaSlot(); break;
        case 4: _t->qbackStepAreaSlot(); break;
        case 5: _t->forwardStepsAreaSlot(); break;
        case 6: _t->backStepsAreaSlot(); break;
        case 7: _t->qforwardStepsAreaSlot(); break;
        case 8: _t->qbackStepsAreaSlot(); break;
        case 9: _t->pauseAreaSlot(); break;
        case 10: _t->stopAreaSlot(); break;
        case 11: _t->finishAreaSlot(); break;
        case 12: _t->drawAreaSlot(); break;
        case 13: _t->stopDrawAreaSlot(); break;
        case 14: _t->undoAreaSlot(); break;
        case 15: _t->redoAreaSlot(); break;
        case 16: _t->loadFromFileAreaSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->saveToFileAreaSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->saveResultToFileAreaSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->generetePointsAreaSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 20: _t->computeIntersections(); break;
        case 21: _t->cleanSegments(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Area::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Area::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Area,
      qt_meta_data_Area, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Area::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Area::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Area::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Area))
        return static_cast<void*>(const_cast< Area*>(this));
    return QWidget::qt_metacast(_clname);
}

int Area::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void Area::generationFailAreaSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
