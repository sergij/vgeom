/****************************************************************************
** Meta object code from reading C++ file 'generator.h'
**
** Created: Sun Jul 22 11:02:33 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "generator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'generator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Generator[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   81,   10,   10, 0x0a,
     118,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Generator[] = {
    "Generator\0\0num,vert,multi,full\0"
    "generatePointsGeneratorSignal(int,bool,bool,bool)\0"
    "num\0generatePointsGeneratorSlot(int)\0"
    "generateGeneratorSlot()\0"
};

const QMetaObject Generator::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Generator,
      qt_meta_data_Generator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Generator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Generator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Generator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Generator))
        return static_cast<void*>(const_cast< Generator*>(this));
    return QDialog::qt_metacast(_clname);
}

int Generator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: generatePointsGeneratorSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: generatePointsGeneratorSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: generateGeneratorSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Generator::generatePointsGeneratorSignal(int _t1, bool _t2, bool _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
