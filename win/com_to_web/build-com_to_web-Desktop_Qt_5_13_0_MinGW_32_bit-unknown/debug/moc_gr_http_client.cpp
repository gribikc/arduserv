/****************************************************************************
** Meta object code from reading C++ file 'gr_http_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../com_to_web/gr_http_client/gr_http_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gr_http_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gr_http_client_t {
    QByteArrayData data[8];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gr_http_client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gr_http_client_t qt_meta_stringdata_gr_http_client = {
    {
QT_MOC_LITERAL(0, 0, 14), // "gr_http_client"
QT_MOC_LITERAL(1, 15, 15), // "requestComplete"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "gr_http_client*"
QT_MOC_LITERAL(4, 48, 12), // "dataComplete"
QT_MOC_LITERAL(5, 61, 9), // "readyRead"
QT_MOC_LITERAL(6, 71, 12), // "stateChanged"
QT_MOC_LITERAL(7, 84, 20) // "http_request_parsing"

    },
    "gr_http_client\0requestComplete\0\0"
    "gr_http_client*\0dataComplete\0readyRead\0"
    "stateChanged\0http_request_parsing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gr_http_client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   45,    2, 0x0a /* Public */,
       6,    0,   46,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    0,
    QMetaType::Void, 0x80000000 | 3,    0,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void gr_http_client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gr_http_client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestComplete((*reinterpret_cast< gr_http_client*(*)>(_a[1]))); break;
        case 1: _t->dataComplete((*reinterpret_cast< gr_http_client*(*)>(_a[1]))); break;
        case 2: _t->readyRead(); break;
        case 3: _t->stateChanged(); break;
        case 4: _t->http_request_parsing(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< gr_http_client* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< gr_http_client* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (gr_http_client::*)(gr_http_client * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gr_http_client::requestComplete)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (gr_http_client::*)(gr_http_client * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gr_http_client::dataComplete)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gr_http_client::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_gr_http_client.data,
    qt_meta_data_gr_http_client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *gr_http_client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gr_http_client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gr_http_client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int gr_http_client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void gr_http_client::requestComplete(gr_http_client * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void gr_http_client::dataComplete(gr_http_client * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
