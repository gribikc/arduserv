/****************************************************************************
** Meta object code from reading C++ file 'gr_serial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../com_to_web/gr_serial/gr_serial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gr_serial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gr_serial_t {
    QByteArrayData data[7];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gr_serial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gr_serial_t qt_meta_stringdata_gr_serial = {
    {
QT_MOC_LITERAL(0, 0, 9), // "gr_serial"
QT_MOC_LITERAL(1, 10, 11), // "serial_open"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "num"
QT_MOC_LITERAL(4, 27, 5), // "speed"
QT_MOC_LITERAL(5, 33, 11), // "serial_read"
QT_MOC_LITERAL(6, 45, 11) // "serial_list"

    },
    "gr_serial\0serial_open\0\0num\0speed\0"
    "serial_read\0serial_list"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gr_serial[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x08 /* Private */,
       5,    0,   34,    2, 0x08 /* Private */,
       6,    0,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void gr_serial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gr_serial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->serial_open((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->serial_read(); break;
        case 2: _t->serial_list(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gr_serial::staticMetaObject = { {
    &gr_data_source::staticMetaObject,
    qt_meta_stringdata_gr_serial.data,
    qt_meta_data_gr_serial,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gr_serial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gr_serial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gr_serial.stringdata0))
        return static_cast<void*>(this);
    return gr_data_source::qt_metacast(_clname);
}

int gr_serial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = gr_data_source::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
