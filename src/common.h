#ifndef COMMON_H
#define COMMON_H

#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <QPainter>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/Xfixes.h>

typedef QList<int> TIntList;
typedef QMap<QString, TIntList> TKeyMap;

bool isKeyDown(Display *dp, int keysym)
{
    char keystates[32];

    XQueryKeymap(dp, keystates);

    int keycode = (int) XKeysymToKeycode(dp, keysym);

    return (bool) (keystates[keycode / 8] & (1 << (keycode % 8)));
}

#endif // COMMON_H
