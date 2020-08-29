/****************************************************************************
** Meta object code from reading C++ file 'com_to_web.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../com_to_web.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'com_to_web.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_com_to_web_t {
    QByteArrayData data[11];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_com_to_web_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_com_to_web_t qt_meta_stringdata_com_to_web = {
    {
QT_MOC_LITERAL(0, 0, 10), // "com_to_web"
QT_MOC_LITERAL(1, 11, 17), // "onNewWebs_connect"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "processTextMessage"
QT_MOC_LITERAL(4, 49, 7), // "message"
QT_MOC_LITERAL(5, 57, 20), // "processBinaryMessage"
QT_MOC_LITERAL(6, 78, 19), // "incommingConnection"
QT_MOC_LITERAL(7, 98, 22), // "client_requestComplete"
QT_MOC_LITERAL(8, 121, 15), // "GR_http_client*"
QT_MOC_LITERAL(9, 137, 11), // "http_client"
QT_MOC_LITERAL(10, 149, 21) // "on_pushButton_clicked"

    },
    "com_to_web\0onNewWebs_connect\0\0"
    "processTextMessage\0message\0"
    "processBinaryMessage\0incommingConnection\0"
    "client_requestComplete\0GR_http_client*\0"
    "http_client\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_com_to_web[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       6,    0,   51,    2, 0x0a /* Public */,
       7,    1,   52,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void com_to_web::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<com_to_web *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewWebs_connect(); break;
        case 1: _t->processTextMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->processBinaryMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->incommingConnection(); break;
        case 4: _t->client_requestComplete((*reinterpret_cast< GR_http_client*(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GR_http_client* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject com_to_web::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_com_to_web.data,
    qt_meta_data_com_to_web,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *com_to_web::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *com_to_web::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_com_to_web.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int com_to_web::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
