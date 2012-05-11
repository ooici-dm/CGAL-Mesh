/****************************************************************************
** Meta object code from reading C++ file 'GraphicsItem.h'
**
** Created: Thu May 10 10:35:35 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../include/CGAL/Qt/GraphicsItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphicsItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CGAL__Qt__GraphicsItem[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CGAL__Qt__GraphicsItem[] = {
    "CGAL::Qt::GraphicsItem\0\0modelChanged()\0"
};

const QMetaObject CGAL::Qt::GraphicsItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CGAL__Qt__GraphicsItem,
      qt_meta_data_CGAL__Qt__GraphicsItem, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CGAL::Qt::GraphicsItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CGAL::Qt::GraphicsItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CGAL::Qt::GraphicsItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGAL__Qt__GraphicsItem))
        return static_cast<void*>(const_cast< GraphicsItem*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< GraphicsItem*>(this));
    if (!strcmp(_clname, "com.trolltech.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< GraphicsItem*>(this));
    return QObject::qt_metacast(_clname);
}

int CGAL::Qt::GraphicsItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: modelChanged(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
