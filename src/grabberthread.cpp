#include "grabberthread.h"

GrabberThread::GrabberThread(Display *_display, XImage *_screenshot, XFixesCursorImage *_cursor, char _keystates[32], int _screenWidth, int _screenHeight, QString _fileName, QString _fileFormat)
{
    memcpy(keystates, _keystates, sizeof(char) * 32);

    display = _display;
    fileName = _fileName;
    fileFormat = _fileFormat;
    x11image = _screenshot;
    xfixescursor = _cursor;
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    mutex = new QMutex();
}

void GrabberThread::run()
{
    QImage screenshot((uchar*) x11image->data, x11image->width, x11image->height, QImage::Format_ARGB32_Premultiplied);

    //Annoyingly, xfixes specifies the data to be 32bit, but places it in an unsigned long *
    //which can be 64 bit.  So we need to iterate over a 64bit structure to put it in a 32bit
    //structure. This hack is gratefully taken from KSnapshot.
    QVarLengthArray<quint32> pixels(xfixescursor->width * xfixescursor->height);

    for (int i = 0; i < xfixescursor->width * xfixescursor->height; ++i)
        pixels[i] = xfixescursor->pixels[i] & 0xffffffff;

    QImage cursor((uchar *) pixels.data(), xfixescursor->width, xfixescursor->height, QImage::Format_ARGB32_Premultiplied);

    int shortcutWidth = (int) ((float) (screenWidth) * 0.6f), shortcutHeight = 250;
    QImage *shortcut = getKeyboardShortcutImage(shortcutWidth, shortcutHeight);

    QPainter painter(&screenshot);

    painter.drawImage(QRectF(xfixescursor->x - xfixescursor->xhot, xfixescursor->y - xfixescursor->yhot, xfixescursor->width, xfixescursor->height), cursor);

    if (shortcut)
    {
        painter.drawImage((screenWidth / 2) - (shortcut->width() / 2), (screenHeight / 2) - (shortcut->height() / 2), *shortcut, 0, 0, shortcutWidth, shortcutHeight, Qt::DiffuseDither | Qt::DiffuseAlphaDither);
    }

    painter.end();

    screenshot.save(fileName, fileFormat.toStdString().c_str());
}

bool GrabberThread::isKeyDown(int keysym)
{
    int keycode = (int) XKeysymToKeycode(display, keysym);

    return (bool) (keystates[keycode / 8] & (1 << (keycode % 8)));
}

QImage* GrabberThread::getKeyboardShortcutImage(int width, int height)
{
    TKeyMap keymap = getKeyLabelMap();

    QList<int> modKeys;

    modKeys.push_back(XK_Alt_L);
    modKeys.push_back(XK_Alt_R);
    modKeys.push_back(XK_Control_L);
    modKeys.push_back(XK_Control_R);

    bool fl = false;

    for (int i = 0; i < modKeys.size(); i++)
    {
        if (isKeyDown(modKeys[i]))
        {
            fl = true;
            break;
        }
    }

    if (!fl)
    {
        return 0;
    }

    QStringList shortcutKeys;
    QString shortcut;

    for (int i = 0; i < keymap.keys().size(); i++)
    {
        QString key = keymap.keys().at(i);

        for (int t = 0; t < keymap[key].size(); t++)
        {
            if (isKeyDown(keymap[key][t]))
            {
                shortcutKeys.push_back(key);
            }
        }
    }

    if (shortcutKeys.size() < 1)
    {
        return 0;
    }

    shortcut = shortcutKeys.join(" + ");

    QImage *img = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);

    QPainter painter(img);

    QBrush originalBrush = painter.brush();

    painter.setCompositionMode(QPainter::CompositionMode_Source);

    painter.fillRect(QRectF(0, 0, width, height), QBrush(QColor(0, 0, 0, 0), Qt::SolidPattern));

    // QRadialGradient gradient(50, 50, 50, 50, 50);
    QLinearGradient gradient(QPointF(width / 2, 5), QPointF(width / 2, height - 5));
    gradient.setColorAt(0, QColor(110, 110, 110, 255));
    gradient.setColorAt(1, QColor(110, 110, 110, 100));

    painter.setBrush(*(new QBrush(gradient))); // *(new QBrush(QColor(110, 110, 110, 255), Qt::SolidPattern)));
    painter.drawRoundedRect(QRectF(10, 10, width - 20, height - 20), 40, 40);

    painter.setFont(QFont("Arial", 36, QFont::SansSerif));

    painter.setPen(*(new QPen(QColor(189, 189, 189, 255))));
    painter.drawText(QRectF(30, 30, width - 60, height - 60), Qt::AlignCenter, shortcut);

    painter.setBrush(originalBrush);

    painter.end();

    return img;
}

TKeyMap GrabberThread::getKeyLabelMap()
{
    TKeyMap keymap;

    {
        TIntList codes;

        codes.push_back(XK_Alt_L);
        codes.push_back(XK_Alt_R);

        keymap["Alt"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Control_L);
        codes.push_back(XK_Control_R);

        keymap["Ctrl"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Shift_L);
        codes.push_back(XK_Shift_R);

        keymap["Shift"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Tab);

        keymap["Tab"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Escape);

        keymap["Esc"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_BackSpace);

        keymap["Bckspc"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Caps_Lock);

        keymap["CapsLock"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Page_Up);

        keymap["PgUp"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Page_Down);

        keymap["PgDn"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Home);

        keymap["Home"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_End);

        keymap["End"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Insert);

        keymap["Ins"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Delete);

        keymap["Del"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_comma);

        keymap[","] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_semicolon);

        keymap[";"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_Return);

        keymap["Return"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_slash);

        keymap["\\"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_backslash);

        keymap["/"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_1);

        keymap["1"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_2);

        keymap["2"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_3);

        keymap["3"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_4);

        keymap["4"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_5);

        keymap["5"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_6);

        keymap["6"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_7);

        keymap["7"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_8);

        keymap["8"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_9);

        keymap["9"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_0);

        keymap["0"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_a);

        keymap["a"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_b);

        keymap["b"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_c);

        keymap["c"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_d);

        keymap["d"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_e);

        keymap["e"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_f);

        keymap["f"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_g);

        keymap["g"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_h);

        keymap["h"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_i);

        keymap["i"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_j);

        keymap["j"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_k);

        keymap["k"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_l);

        keymap["l"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_m);

        keymap["m"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_n);

        keymap["n"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_o);

        keymap["o"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_p);

        keymap["p"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_q);

        keymap["q"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_r);

        keymap["r"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_s);

        keymap["s"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_t);

        keymap["t"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_u);

        keymap["u"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_v);

        keymap["v"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_w);

        keymap["w"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_x);

        keymap["x"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_y);

        keymap["y"] = codes;
    }

    {
        TIntList codes;

        codes.push_back(XK_z);

        keymap["z"] = codes;
    }

    return keymap;
}
