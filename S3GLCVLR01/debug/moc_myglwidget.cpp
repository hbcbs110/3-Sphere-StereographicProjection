/****************************************************************************
** Meta object code from reading C++ file 'myglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../S3GLCV01/myglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_s3s_t {
    QByteArrayData data[9];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_s3s_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_s3s_t qt_meta_stringdata_s3s = {
    {
QT_MOC_LITERAL(0, 0, 3), // "s3s"
QT_MOC_LITERAL(1, 4, 11), // "setthetitle"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 5), // "char*"
QT_MOC_LITERAL(4, 23, 12), // "callkeypress"
QT_MOC_LITERAL(5, 36, 10), // "QKeyEvent*"
QT_MOC_LITERAL(6, 47, 2), // "ev"
QT_MOC_LITERAL(7, 50, 9), // "callkeyup"
QT_MOC_LITERAL(8, 60, 5) // "letgo"

    },
    "s3s\0setthetitle\0\0char*\0callkeypress\0"
    "QKeyEvent*\0ev\0callkeyup\0letgo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_s3s[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       7,    1,   40,    2, 0x0a /* Public */,
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void s3s::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        s3s *_t = static_cast<s3s *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->setthetitle((*reinterpret_cast< char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->callkeypress((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->callkeyup((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->letgo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (s3s::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&s3s::setthetitle)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject s3s::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_s3s.data,
      qt_meta_data_s3s,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *s3s::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *s3s::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_s3s.stringdata0))
        return static_cast<void*>(const_cast< s3s*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< s3s*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int s3s::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
int s3s::setthetitle(char * _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
