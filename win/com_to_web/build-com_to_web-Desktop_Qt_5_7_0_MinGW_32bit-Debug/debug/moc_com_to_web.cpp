/****************************************************************************
** Meta object code from reading C++ file 'com_to_web.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../com_to_web/com_to_web.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'com_to_web.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_com_to_web_t {
    QByteArrayData data[5];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_com_to_web_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_com_to_web_t qt_meta_stringdata_com_to_web = {
    {
QT_MOC_LITERAL(0, 0, 10), // "com_to_web"
QT_MOC_LITERAL(1, 11, 19), // "incommingConnection"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "readyRead"
QT_MOC_LITERAL(4, 42, 12) // "stateChanged"

    },
    "com_to_web\0incommingConnection\0\0"
    "readyRead\0stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_com_to_web[] = {

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
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void com_to_web::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        com_to_web *_t = static_cast<com_to_web *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->incommingConnection(); break;
        case 1: _t->readyRead(); break;
        case 2: _t->stateChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject com_to_web::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_com_to_web.data,
      qt_meta_data_com_to_web,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *com_to_web::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *com_to_web::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_com_to_web.stringdata0))
        return static_cast<void*>(const_cast< com_to_web*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int com_to_web::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
