#ifndef SAVESCREENSHOT_H
#define SAVESCREENSHOT_H

#include "common.h"
#include "getKeyLabelMap.h"

QImage* getKeyboardShortcutImage(Display *dp, int width, int height)
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
        if (isKeyDown(dp, modKeys[i]))
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
            if (isKeyDown(dp, keymap[key][t]))
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

    QImage *img = new QImage(width, height, QImage::Format_ARGB32);

    QPainter painter(img);

    QBrush originalBrush = painter.brush();

    QRadialGradient gradient(50, 50, 50, 50, 50);
    gradient.setColorAt(0, QColor(110, 110, 110, 255));
    gradient.setColorAt(1, QColor(110, 110, 110, 100));

    painter.setBrush(*(new QBrush(gradient))); // *(new QBrush(QColor(110, 110, 110, 255), Qt::SolidPattern)));
    painter.drawRoundedRect(QRectF(10, 10, width - 20, height - 20), 5, 5);

    painter.setFont(QFont("Arial", 36, QFont::SansSerif));

    painter.setPen(*(new QPen(QColor(189, 189, 189, 255))));
    painter.drawText(QRectF(30, 30, width - 60, height - 60), Qt::AlignCenter, shortcut);

    painter.setBrush(originalBrush);

    painter.end();

    return img;
}

void saveScreenShot(Display *dp, XImage *x11image, XFixesCursorImage *xfixescursor, QString filename, QString fileformat)
{
    QImage screenshot((const uchar*) x11image->data, x11image->width, x11image->height, QImage::Format_ARGB32);
    QImage cursor((const uchar*) xfixescursor->pixels, xfixescursor->width, xfixescursor->height, QImage::Format_ARGB32);

    int screenWidth = XDisplayWidth(dp, 0), screenHeight = XDisplayHeight(dp, 0);
    int shortcutWidth = (int) ((float) (screenWidth) * 0.6f), shortcutHeight = 250;
    QImage *shortcut = getKeyboardShortcutImage(dp, shortcutWidth, shortcutHeight);

    QPainter painter(&screenshot);

    painter.drawImage(xfixescursor->x, xfixescursor->y, cursor);

    if (shortcut)
    {
        painter.drawImage((screenWidth / 2) - (shortcut->width() / 2), (screenHeight / 2) - (shortcut->height() / 2), *shortcut);
    }

    painter.end();

    screenshot.save(filename, fileformat.toStdString().c_str());
}

#endif // SAVESCREENSHOT_H