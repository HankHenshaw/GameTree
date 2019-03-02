/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[45];
    char stringdata0[878];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 25), // "on_previousButton_clicked"
QT_MOC_LITERAL(4, 60, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(5, 82, 21), // "on_nextButton_clicked"
QT_MOC_LITERAL(6, 104, 25), // "on_playlistButton_clicked"
QT_MOC_LITERAL(7, 130, 15), // "slotSetDuration"
QT_MOC_LITERAL(8, 146, 1), // "n"
QT_MOC_LITERAL(9, 148, 23), // "slotSetProgressPosotion"
QT_MOC_LITERAL(10, 172, 20), // "slotSetMediaPosition"
QT_MOC_LITERAL(11, 193, 3), // "pos"
QT_MOC_LITERAL(12, 197, 23), // "slotPlaylistFormClicked"
QT_MOC_LITERAL(13, 221, 26), // "on_actionRussian_triggered"
QT_MOC_LITERAL(14, 248, 26), // "on_actionEnglish_triggered"
QT_MOC_LITERAL(15, 275, 38), // "on_treeView_customContextMenu..."
QT_MOC_LITERAL(16, 314, 10), // "slotDelete"
QT_MOC_LITERAL(17, 325, 8), // "slotEdit"
QT_MOC_LITERAL(18, 334, 11), // "slotEditMod"
QT_MOC_LITERAL(19, 346, 9), // "slotStart"
QT_MOC_LITERAL(20, 356, 23), // "slotStartWithParameters"
QT_MOC_LITERAL(21, 380, 12), // "slotStartMod"
QT_MOC_LITERAL(22, 393, 26), // "slotStartModWithParameters"
QT_MOC_LITERAL(23, 420, 7), // "slotAdd"
QT_MOC_LITERAL(24, 428, 10), // "slotAddMod"
QT_MOC_LITERAL(25, 439, 22), // "on_buttonStart_clicked"
QT_MOC_LITERAL(26, 462, 21), // "on_buttonEdit_clicked"
QT_MOC_LITERAL(27, 484, 23), // "on_buttonRemove_clicked"
QT_MOC_LITERAL(28, 508, 19), // "slotButtonActivator"
QT_MOC_LITERAL(29, 528, 13), // "selectedIndex"
QT_MOC_LITERAL(30, 542, 12), // "slotShowHide"
QT_MOC_LITERAL(31, 555, 17), // "slotIconActivated"
QT_MOC_LITERAL(32, 573, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(33, 607, 6), // "reason"
QT_MOC_LITERAL(34, 614, 14), // "slotDblClicked"
QT_MOC_LITERAL(35, 629, 10), // "slotFilter"
QT_MOC_LITERAL(36, 640, 33), // "on_splitterVertical_splitterM..."
QT_MOC_LITERAL(37, 674, 5), // "index"
QT_MOC_LITERAL(38, 680, 35), // "on_splitterHorizontal_splitte..."
QT_MOC_LITERAL(39, 716, 39), // "on_splitterHorizontalInfo_spl..."
QT_MOC_LITERAL(40, 756, 37), // "on_splitterVerticalInfo_split..."
QT_MOC_LITERAL(41, 794, 24), // "slotCoversSlideshowStart"
QT_MOC_LITERAL(42, 819, 23), // "slotMediaSlideshowStart"
QT_MOC_LITERAL(43, 843, 28), // "on_volumeSlider_valueChanged"
QT_MOC_LITERAL(44, 872, 5) // "value"

    },
    "MainWindow\0on_playButton_clicked\0\0"
    "on_previousButton_clicked\0"
    "on_stopButton_clicked\0on_nextButton_clicked\0"
    "on_playlistButton_clicked\0slotSetDuration\0"
    "n\0slotSetProgressPosotion\0"
    "slotSetMediaPosition\0pos\0"
    "slotPlaylistFormClicked\0"
    "on_actionRussian_triggered\0"
    "on_actionEnglish_triggered\0"
    "on_treeView_customContextMenuRequested\0"
    "slotDelete\0slotEdit\0slotEditMod\0"
    "slotStart\0slotStartWithParameters\0"
    "slotStartMod\0slotStartModWithParameters\0"
    "slotAdd\0slotAddMod\0on_buttonStart_clicked\0"
    "on_buttonEdit_clicked\0on_buttonRemove_clicked\0"
    "slotButtonActivator\0selectedIndex\0"
    "slotShowHide\0slotIconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0slotDblClicked\0slotFilter\0"
    "on_splitterVertical_splitterMoved\0"
    "index\0on_splitterHorizontal_splitterMoved\0"
    "on_splitterHorizontalInfo_splitterMoved\0"
    "on_splitterVerticalInfo_splitterMoved\0"
    "slotCoversSlideshowStart\0"
    "slotMediaSlideshowStart\0"
    "on_volumeSlider_valueChanged\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  194,    2, 0x08 /* Private */,
       3,    0,  195,    2, 0x08 /* Private */,
       4,    0,  196,    2, 0x08 /* Private */,
       5,    0,  197,    2, 0x08 /* Private */,
       6,    0,  198,    2, 0x08 /* Private */,
       7,    1,  199,    2, 0x08 /* Private */,
       9,    1,  202,    2, 0x08 /* Private */,
      10,    1,  205,    2, 0x08 /* Private */,
      12,    0,  208,    2, 0x08 /* Private */,
      13,    0,  209,    2, 0x08 /* Private */,
      14,    0,  210,    2, 0x08 /* Private */,
      15,    1,  211,    2, 0x08 /* Private */,
      16,    0,  214,    2, 0x08 /* Private */,
      17,    0,  215,    2, 0x08 /* Private */,
      18,    0,  216,    2, 0x08 /* Private */,
      19,    0,  217,    2, 0x08 /* Private */,
      20,    0,  218,    2, 0x08 /* Private */,
      21,    0,  219,    2, 0x08 /* Private */,
      22,    0,  220,    2, 0x08 /* Private */,
      23,    0,  221,    2, 0x08 /* Private */,
      24,    0,  222,    2, 0x08 /* Private */,
      25,    0,  223,    2, 0x08 /* Private */,
      26,    0,  224,    2, 0x08 /* Private */,
      27,    0,  225,    2, 0x08 /* Private */,
      28,    1,  226,    2, 0x08 /* Private */,
      30,    0,  229,    2, 0x08 /* Private */,
      31,    1,  230,    2, 0x08 /* Private */,
      34,    0,  233,    2, 0x08 /* Private */,
      35,    0,  234,    2, 0x08 /* Private */,
      36,    2,  235,    2, 0x08 /* Private */,
      38,    2,  240,    2, 0x08 /* Private */,
      39,    2,  245,    2, 0x08 /* Private */,
      40,    2,  250,    2, 0x08 /* Private */,
      41,    0,  255,    2, 0x08 /* Private */,
      42,    0,  256,    2, 0x08 /* Private */,
      43,    1,  257,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void, QMetaType::QPoint,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   11,
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
    QMetaType::Void, QMetaType::QModelIndex,   29,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   37,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   37,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   37,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   44,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_playButton_clicked(); break;
        case 1: _t->on_previousButton_clicked(); break;
        case 2: _t->on_stopButton_clicked(); break;
        case 3: _t->on_nextButton_clicked(); break;
        case 4: _t->on_playlistButton_clicked(); break;
        case 5: _t->slotSetDuration((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->slotSetProgressPosotion((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->slotSetMediaPosition((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 8: _t->slotPlaylistFormClicked(); break;
        case 9: _t->on_actionRussian_triggered(); break;
        case 10: _t->on_actionEnglish_triggered(); break;
        case 11: _t->on_treeView_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: _t->slotDelete(); break;
        case 13: _t->slotEdit(); break;
        case 14: _t->slotEditMod(); break;
        case 15: _t->slotStart(); break;
        case 16: _t->slotStartWithParameters(); break;
        case 17: _t->slotStartMod(); break;
        case 18: _t->slotStartModWithParameters(); break;
        case 19: _t->slotAdd(); break;
        case 20: _t->slotAddMod(); break;
        case 21: _t->on_buttonStart_clicked(); break;
        case 22: _t->on_buttonEdit_clicked(); break;
        case 23: _t->on_buttonRemove_clicked(); break;
        case 24: _t->slotButtonActivator((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 25: _t->slotShowHide(); break;
        case 26: _t->slotIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 27: _t->slotDblClicked(); break;
        case 28: _t->slotFilter(); break;
        case 29: _t->on_splitterVertical_splitterMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 30: _t->on_splitterHorizontal_splitterMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 31: _t->on_splitterHorizontalInfo_splitterMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 32: _t->on_splitterVerticalInfo_splitterMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 33: _t->slotCoversSlideshowStart(); break;
        case 34: _t->slotMediaSlideshowStart(); break;
        case 35: _t->on_volumeSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 36;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
