/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Dec 15 12:30:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      46,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      88,   11,   11,   11, 0x08,
     113,   11,   11,   11, 0x08,
     139,   11,   11,   11, 0x08,
     154,   11,   11,   11, 0x08,
     172,   11,   11,   11, 0x08,
     191,   11,   11,   11, 0x08,
     213,   11,   11,   11, 0x08,
     237,   11,   11,   11, 0x08,
     273,   11,   11,   11, 0x08,
     294,   11,   11,   11, 0x08,
     320,   11,   11,   11, 0x08,
     340,   11,   11,   11, 0x08,
     348,   11,   11,   11, 0x08,
     374,   11,   11,   11, 0x08,
     396,   11,   11,   11, 0x08,
     419,   11,   11,   11, 0x08,
     442,   11,   11,   11, 0x08,
     464,   11,   11,   11, 0x08,
     490,   11,   11,   11, 0x08,
     501,   11,   11,   11, 0x08,
     518,   11,   11,   11, 0x08,
     533,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0addListSymbology()\0"
    "createEncode()\0createEncodeQR()\0"
    "on_ImageButton_clicked()\0"
    "on_VideoButton_clicked()\0"
    "on_CameraButton_clicked()\0ProcessFrame()\0"
    "showImageEncode()\0readFromFileText()\0"
    "on_btEncode_clicked()\0on_pushButton_clicked()\0"
    "on_cbListCode_currentIndexChanged()\0"
    "on_btnSave_clicked()\0on_pushButton_2_clicked()\0"
    "use_drawRectangle()\0snake()\0"
    "on_pushButton_3_clicked()\0"
    "on_radioURL_clicked()\0on_radioText_clicked()\0"
    "on_radioDial_clicked()\0on_radioSMS_clicked()\0"
    "on_radioContact_clicked()\0clearAll()\0"
    "disableBarcode()\0enableQRcode()\0"
    "on_btEncode_2_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->addListSymbology(); break;
        case 1: _t->createEncode(); break;
        case 2: _t->createEncodeQR(); break;
        case 3: _t->on_ImageButton_clicked(); break;
        case 4: _t->on_VideoButton_clicked(); break;
        case 5: _t->on_CameraButton_clicked(); break;
        case 6: _t->ProcessFrame(); break;
        case 7: _t->showImageEncode(); break;
        case 8: _t->readFromFileText(); break;
        case 9: _t->on_btEncode_clicked(); break;
        case 10: _t->on_pushButton_clicked(); break;
        case 11: _t->on_cbListCode_currentIndexChanged(); break;
        case 12: _t->on_btnSave_clicked(); break;
        case 13: _t->on_pushButton_2_clicked(); break;
        case 14: _t->use_drawRectangle(); break;
        case 15: _t->snake(); break;
        case 16: _t->on_pushButton_3_clicked(); break;
        case 17: _t->on_radioURL_clicked(); break;
        case 18: _t->on_radioText_clicked(); break;
        case 19: _t->on_radioDial_clicked(); break;
        case 20: _t->on_radioSMS_clicked(); break;
        case 21: _t->on_radioContact_clicked(); break;
        case 22: _t->clearAll(); break;
        case 23: _t->disableBarcode(); break;
        case 24: _t->enableQRcode(); break;
        case 25: _t->on_btEncode_2_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
