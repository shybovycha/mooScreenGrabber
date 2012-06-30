#ifndef COMMON_H
#define COMMON_H

#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QVarLengthArray>
#include <QThread>
#include <QMutex>
#include <QFileDialog>
#include <QSystemTrayIcon>
#include <QMessageBox>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/Xfixes.h>

typedef QList<int> TIntList;
typedef QMap<QString, TIntList> TKeyMap;

#endif // COMMON_H
