/****************************************************************************
** Meta object code from reading C++ file 'gtdtreewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_test001/gtdtreewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gtdtreewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GTDTreeWidget_t {
    QByteArrayData data[10];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GTDTreeWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GTDTreeWidget_t qt_meta_stringdata_GTDTreeWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GTDTreeWidget"
QT_MOC_LITERAL(1, 14, 28), // "onCustomContextMenuRequested"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 3), // "pos"
QT_MOC_LITERAL(4, 48, 12), // "onMenuAction"
QT_MOC_LITERAL(5, 61, 8), // "QAction*"
QT_MOC_LITERAL(6, 70, 6), // "action"
QT_MOC_LITERAL(7, 77, 8), // "EditItem"
QT_MOC_LITERAL(8, 86, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(9, 103, 4) // "item"

    },
    "GTDTreeWidget\0onCustomContextMenuRequested\0"
    "\0pos\0onMenuAction\0QAction*\0action\0"
    "EditItem\0QTreeWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GTDTreeWidget[] = {

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
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       7,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void GTDTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GTDTreeWidget *_t = static_cast<GTDTreeWidget *>(_o);
        switch (_id) {
        case 0: _t->onCustomContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->onMenuAction((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->EditItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GTDTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_GTDTreeWidget.data,
      qt_meta_data_GTDTreeWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GTDTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GTDTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GTDTreeWidget.stringdata))
        return static_cast<void*>(const_cast< GTDTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int GTDTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
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
