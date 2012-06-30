#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

// Here we can not include common.h because it shall cause ambigousity with X11 libs
#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <QPainter>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    
private:
    Ui::MainWidget *ui;

    QTimer *shootTimer;
    QString outputPath;

    Display *dp;

    int frameIndex;

    bool isKeyDown(Display *dp, int keysum);

private slots:
    void shoot();
    void on_chooseOutputDirectoryButton_clicked();
    void on_togglingButton_clicked();
};

#endif // MAINWIDGET_H
