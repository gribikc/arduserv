/****************************************************************************
** Meta object code from reading C++ file 'gr_sock_srv.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../micro_web_srv/gr_sock_srv/gr_sock_srv.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gr_sock_srv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_gr_sock_srv_t {
    QByteArrayData data[7];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gr_sock_srv_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gr_sock_srv_t qt_meta_stringdata_gr_sock_srv = {
    {
QT_MOC_LITERAL(0, 0, 11), // "gr_sock_srv"
QT_MOC_LITERAL(1, 12, 19), // "incommingConnection"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9), // "readyRead"
QT_MOC_LITERAL(4, 43, 12), // "stateChanged"
QT_MOC_LITERAL(5, 56, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(6, 85, 4) // "stat"

    },
    "gr_sock_srv\0incommingConnection\0\0"
    "readyRead\0stateChanged\0"
    "QAbstractSocket::SocketState\0stat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gr_sock_srv[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void gr_sock_srv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gr_sock_srv *_t = static_cast<gr_sock_srv *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->incommingConnection(); break;
        case 1: _t->readyRead(); break;
        case 2: _t->stateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    }
}

const QMetaObject gr_sock_srv::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_gr_sock_srv.data,
      qt_meta_data_gr_sock_srv,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *gr_sock_srv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gr_sock_srv::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_gr_sock_srv.stringdata0))
        return static_cast<void*>(const_cast< gr_sock_srv*>(this));
    return QObject::qt_metacast(_clname);
}

int gr_sock_srv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
