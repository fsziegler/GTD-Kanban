/****************************************************************************
** Meta object code from reading C++ file 'inbasketform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt_test001/inbasketform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inbasketform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InBasketForm_t {
    QByteArrayData data[14];
    char stringdata[359];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InBasketForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InBasketForm_t qt_meta_stringdata_InBasketForm = {
    {
QT_MOC_LITERAL(0, 0, 12), // "InBasketForm"
QT_MOC_LITERAL(1, 13, 31), // "on_inBasketTextEdit_textChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 32), // "on_reEditSelectionButton_clicked"
QT_MOC_LITERAL(4, 79, 29), // "on_somedayMaybeButton_clicked"
QT_MOC_LITERAL(5, 109, 26), // "on_referenceButton_clicked"
QT_MOC_LITERAL(6, 136, 22), // "on_trashButton_clicked"
QT_MOC_LITERAL(7, 159, 21), // "on_doItButton_clicked"
QT_MOC_LITERAL(8, 181, 33), // "on_waitingOnSomeoneButton_cli..."
QT_MOC_LITERAL(9, 215, 25), // "on_calendarButton_clicked"
QT_MOC_LITERAL(10, 241, 28), // "on_nextActionsButton_clicked"
QT_MOC_LITERAL(11, 270, 31), // "on_projectsToPlanButton_clicked"
QT_MOC_LITERAL(12, 302, 29), // "on_projectPlansButton_clicked"
QT_MOC_LITERAL(13, 332, 26) // "on_gtdMinMaxButton_clicked"

    },
    "InBasketForm\0on_inBasketTextEdit_textChanged\0"
    "\0on_reEditSelectionButton_clicked\0"
    "on_somedayMaybeButton_clicked\0"
    "on_referenceButton_clicked\0"
    "on_trashButton_clicked\0on_doItButton_clicked\0"
    "on_waitingOnSomeoneButton_clicked\0"
    "on_calendarButton_clicked\0"
    "on_nextActionsButton_clicked\0"
    "on_projectsToPlanButton_clicked\0"
    "on_projectPlansButton_clicked\0"
    "on_gtdMinMaxButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InBasketForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InBasketForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InBasketForm *_t = static_cast<InBasketForm *>(_o);
        switch (_id) {
        case 0: _t->on_inBasketTextEdit_textChanged(); break;
        case 1: _t->on_reEditSelectionButton_clicked(); break;
        case 2: _t->on_somedayMaybeButton_clicked(); break;
        case 3: _t->on_referenceButton_clicked(); break;
        case 4: _t->on_trashButton_clicked(); break;
        case 5: _t->on_doItButton_clicked(); break;
        case 6: _t->on_waitingOnSomeoneButton_clicked(); break;
        case 7: _t->on_calendarButton_clicked(); break;
        case 8: _t->on_nextActionsButton_clicked(); break;
        case 9: _t->on_projectsToPlanButton_clicked(); break;
        case 10: _t->on_projectPlansButton_clicked(); break;
        case 11: _t->on_gtdMinMaxButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject InBasketForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InBasketForm.data,
      qt_meta_data_InBasketForm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InBasketForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InBasketForm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InBasketForm.stringdata))
        return static_cast<void*>(const_cast< InBasketForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int InBasketForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
