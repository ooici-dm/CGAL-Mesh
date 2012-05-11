/****************************************************************************
** Meta object code from reading C++ file 'GraphicsViewInput.h'
**
** Created: Thu May 10 10:35:35 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../include/CGAL/Qt/GraphicsViewInput.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphicsViewInput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CGAL__Qt__GraphicsViewInput[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   29,   28,   28, 0x05,
      54,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CGAL__Qt__GraphicsViewInput[] = {
    "CGAL::Qt::GraphicsViewInput\0\0o\0"
    "generate(CGAL::Object)\0modelChanged()\0"
    "processInput(CGAL::Object)\0"
};

const QMetaObject CGAL::Qt::GraphicsViewInput::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CGAL__Qt__GraphicsViewInput,
      qt_meta_data_CGAL__Qt__GraphicsViewInput, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CGAL::Qt::GraphicsViewInput::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CGAL::Qt::GraphicsViewInput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CGAL::Qt::GraphicsViewInput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGAL__Qt__GraphicsViewInput))
        return static_cast<void*>(const_cast< GraphicsViewInput*>(this));
    return QObject::qt_metacast(_clname);
}

int CGAL::Qt::GraphicsViewInput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: generate((*reinterpret_cast< CGAL::Object(*)>(_a[1]))); break;
        case 1: modelChanged(); break;
        case 2: processInput((*reinterpret_cast< CGAL::Object(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CGAL::Qt::GraphicsViewInput::generate(CGAL::Object _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CGAL::Qt::GraphicsViewInput::modelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
