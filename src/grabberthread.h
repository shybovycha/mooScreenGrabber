#ifndef GRABBERTHREAD_H
#define GRABBERTHREAD_H

#include "common.h"

class GrabberThread : public QThread
{
    Q_OBJECT

    public:
        GrabberThread(Display *_display, XImage *_screenshot, XFixesCursorImage *_cursor, char _keystates[32], int _screenWidth, int _screenHeight, QString _fileName, QString _fileFormat);

    private:
        QMutex *mutex;

        Display *display;
        XImage *x11image;
        XFixesCursorImage *xfixescursor;

        int screenWidth;
        int screenHeight;

        char keystates[32];

        QString fileName;
        QString fileFormat;

        void run();

        QImage* getKeyboardShortcutImage(int width, int height);
        bool isKeyDown(int keysym);
        TKeyMap getKeyLabelMap();
};

#endif // GRABBERTHREAD_H
