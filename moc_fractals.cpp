/****************************************************************************
** Meta object code from reading C++ file 'fractals.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fractals.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fractals.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_fractals_t {
    QByteArrayData data[30];
    char stringdata[365];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fractals_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fractals_t qt_meta_stringdata_fractals = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 12),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 19),
QT_MOC_LITERAL(4, 43, 21),
QT_MOC_LITERAL(5, 65, 10),
QT_MOC_LITERAL(6, 76, 12),
QT_MOC_LITERAL(7, 89, 9),
QT_MOC_LITERAL(8, 99, 4),
QT_MOC_LITERAL(9, 104, 4),
QT_MOC_LITERAL(10, 109, 6),
QT_MOC_LITERAL(11, 116, 4),
QT_MOC_LITERAL(12, 121, 4),
QT_MOC_LITERAL(13, 126, 4),
QT_MOC_LITERAL(14, 131, 4),
QT_MOC_LITERAL(15, 136, 4),
QT_MOC_LITERAL(16, 141, 4),
QT_MOC_LITERAL(17, 146, 11),
QT_MOC_LITERAL(18, 158, 13),
QT_MOC_LITERAL(19, 172, 5),
QT_MOC_LITERAL(20, 178, 5),
QT_MOC_LITERAL(21, 184, 23),
QT_MOC_LITERAL(22, 208, 25),
QT_MOC_LITERAL(23, 234, 16),
QT_MOC_LITERAL(24, 251, 4),
QT_MOC_LITERAL(25, 256, 24),
QT_MOC_LITERAL(26, 281, 18),
QT_MOC_LITERAL(27, 300, 19),
QT_MOC_LITERAL(28, 320, 22),
QT_MOC_LITERAL(29, 343, 21)
    },
    "fractals\0updatePixmap\0\0on_abortBut_clicked\0"
    "on_drawButton_clicked\0timerEvent\0"
    "QTimerEvent*\0DrawJulia\0npix\0npiy\0"
    "kcolor\0pmin\0qmin\0xmin\0ymin\0xmax\0ymax\0"
    "resizeEvent\0QResizeEvent*\0event\0clear\0"
    "on_drawButton_2_clicked\0"
    "on_listWidget_itemClicked\0QListWidgetItem*\0"
    "item\0on_setMaximumRes_clicked\0"
    "on_zoomInB_clicked\0on_zoomOutB_clicked\0"
    "on_clearButton_clicked\0on_abortBut_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fractals[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       3,    0,   87,    2, 0x08 /* Private */,
       4,    0,   88,    2, 0x08 /* Private */,
       5,    1,   89,    2, 0x08 /* Private */,
       7,    9,   92,    2, 0x08 /* Private */,
      17,    1,  111,    2, 0x08 /* Private */,
      20,    0,  114,    2, 0x08 /* Private */,
      21,    0,  115,    2, 0x08 /* Private */,
      22,    1,  116,    2, 0x08 /* Private */,
      25,    0,  119,    2, 0x08 /* Private */,
      26,    0,  120,    2, 0x08 /* Private */,
      27,    0,  121,    2, 0x08 /* Private */,
      28,    0,  122,    2, 0x08 /* Private */,
      29,    0,  123,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    8,    9,   10,   11,   12,   13,   14,   15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void fractals::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fractals *_t = static_cast<fractals *>(_o);
        switch (_id) {
        case 0: _t->updatePixmap((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->on_abortBut_clicked(); break;
        case 2: _t->on_drawButton_clicked(); break;
        case 3: _t->timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 4: _t->DrawJulia((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8])),(*reinterpret_cast< double(*)>(_a[9]))); break;
        case 5: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 6: _t->clear(); break;
        case 7: _t->on_drawButton_2_clicked(); break;
        case 8: _t->on_listWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->on_setMaximumRes_clicked(); break;
        case 10: _t->on_zoomInB_clicked(); break;
        case 11: _t->on_zoomOutB_clicked(); break;
        case 12: _t->on_clearButton_clicked(); break;
        case 13: _t->on_abortBut_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject fractals::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_fractals.data,
      qt_meta_data_fractals,  qt_static_metacall, 0, 0}
};


const QMetaObject *fractals::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fractals::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fractals.stringdata))
        return static_cast<void*>(const_cast< fractals*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int fractals::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
struct qt_meta_stringdata_RenderThread_t {
    QByteArrayData data[4];
    char stringdata[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderThread_t qt_meta_stringdata_RenderThread = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 13),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 5)
    },
    "RenderThread\0renderedImage\0\0image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,

       0        // eod
};

void RenderThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderThread *_t = static_cast<RenderThread *>(_o);
        switch (_id) {
        case 0: _t->renderedImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RenderThread::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderThread::renderedImage)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject RenderThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_RenderThread.data,
      qt_meta_data_RenderThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *RenderThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderThread.stringdata))
        return static_cast<void*>(const_cast< RenderThread*>(this));
    return QThread::qt_metacast(_clname);
}

int RenderThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void RenderThread::renderedImage(const QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
