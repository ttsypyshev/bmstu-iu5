/****************************************************************************
** Meta object code from reading C++ file 'onb1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bd___qt/onb1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'onb1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_onb1_t {
    QByteArrayData data[11];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_onb1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_onb1_t qt_meta_stringdata_onb1 = {
    {
QT_MOC_LITERAL(0, 0, 4), // "onb1"
QT_MOC_LITERAL(1, 5, 9), // "selectAll"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 18), // "on_btnExit_clicked"
QT_MOC_LITERAL(4, 35, 3), // "add"
QT_MOC_LITERAL(5, 39, 6), // "remove"
QT_MOC_LITERAL(6, 46, 5), // "clean"
QT_MOC_LITERAL(7, 52, 4), // "edit"
QT_MOC_LITERAL(8, 57, 26), // "on_tw_itemSelectionChanged"
QT_MOC_LITERAL(9, 84, 6), // "search"
QT_MOC_LITERAL(10, 91, 21) // "generateReportRequest"

    },
    "onb1\0selectAll\0\0on_btnExit_clicked\0"
    "add\0remove\0clean\0edit\0on_tw_itemSelectionChanged\0"
    "search\0generateReportRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_onb1[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

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

       0        // eod
};

void onb1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<onb1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectAll(); break;
        case 1: _t->on_btnExit_clicked(); break;
        case 2: _t->add(); break;
        case 3: _t->remove(); break;
        case 4: _t->clean(); break;
        case 5: _t->edit(); break;
        case 6: _t->on_tw_itemSelectionChanged(); break;
        case 7: _t->search(); break;
        case 8: _t->generateReportRequest(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject onb1::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_onb1.data,
    qt_meta_data_onb1,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *onb1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *onb1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_onb1.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int onb1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
