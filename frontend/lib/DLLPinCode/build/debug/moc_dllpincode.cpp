/****************************************************************************
** Meta object code from reading C++ file 'dllpincode.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../dllpincode.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dllpincode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_DLLPinCode_t {
    uint offsetsAndSizes[24];
    char stringdata0[11];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[18];
    char stringdata5[18];
    char stringdata6[17];
    char stringdata7[15];
    char stringdata8[16];
    char stringdata9[17];
    char stringdata10[12];
    char stringdata11[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_DLLPinCode_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_DLLPinCode_t qt_meta_stringdata_DLLPinCode = {
    {
        QT_MOC_LITERAL(0, 10),  // "DLLPinCode"
        QT_MOC_LITERAL(11, 12),  // "LoginSuccess"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 18),  // "numberClickHandler"
        QT_MOC_LITERAL(44, 17),  // "enterClickHandler"
        QT_MOC_LITERAL(62, 17),  // "clearClickHandler"
        QT_MOC_LITERAL(80, 16),  // "stopClickHandler"
        QT_MOC_LITERAL(97, 14),  // "accountFreezed"
        QT_MOC_LITERAL(112, 15),  // "getCardIDFromDb"
        QT_MOC_LITERAL(128, 16),  // "getWrongAttempts"
        QT_MOC_LITERAL(145, 11),  // "setLanguage"
        QT_MOC_LITERAL(157, 13)   // "emptyLineEdit"
    },
    "DLLPinCode",
    "LoginSuccess",
    "",
    "numberClickHandler",
    "enterClickHandler",
    "clearClickHandler",
    "stopClickHandler",
    "accountFreezed",
    "getCardIDFromDb",
    "getWrongAttempts",
    "setLanguage",
    "emptyLineEdit"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_DLLPinCode[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   74,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   79,    2, 0x08,    4 /* Private */,
       4,    0,   80,    2, 0x08,    5 /* Private */,
       5,    0,   81,    2, 0x08,    6 /* Private */,
       6,    0,   82,    2, 0x08,    7 /* Private */,
       7,    0,   83,    2, 0x08,    8 /* Private */,
       8,    0,   84,    2, 0x08,    9 /* Private */,
       9,    0,   85,    2, 0x08,   10 /* Private */,
      10,    0,   86,    2, 0x08,   11 /* Private */,
      11,    0,   87,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,

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

Q_CONSTINIT const QMetaObject DLLPinCode::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_DLLPinCode.offsetsAndSizes,
    qt_meta_data_DLLPinCode,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_DLLPinCode_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DLLPinCode, std::true_type>,
        // method 'LoginSuccess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'numberClickHandler'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enterClickHandler'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearClickHandler'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopClickHandler'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'accountFreezed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getCardIDFromDb'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getWrongAttempts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLanguage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'emptyLineEdit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void DLLPinCode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DLLPinCode *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->LoginSuccess((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->numberClickHandler(); break;
        case 2: _t->enterClickHandler(); break;
        case 3: _t->clearClickHandler(); break;
        case 4: _t->stopClickHandler(); break;
        case 5: _t->accountFreezed(); break;
        case 6: _t->getCardIDFromDb(); break;
        case 7: _t->getWrongAttempts(); break;
        case 8: _t->setLanguage(); break;
        case 9: _t->emptyLineEdit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DLLPinCode::*)(int , QString );
            if (_t _q_method = &DLLPinCode::LoginSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *DLLPinCode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DLLPinCode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DLLPinCode.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DLLPinCode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DLLPinCode::LoginSuccess(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
