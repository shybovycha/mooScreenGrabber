#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "saveScreenShot.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    fileIndex = 0;

    dp = XOpenDisplay(NULL);

    shootTimer = new QTimer();
    shootTimer->setInterval(10);
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
}

void MainWidget::shoot()
{
    /*int screenCnt = ScrenCount(dp);

    for (int i = 0; i < screenCnt; i++)
    {
        int width = DisplayWidth(dp, i), height = DisplayHeight(dp, i);
    }*/

    int width = DisplayWidth(dp, 0), height = DisplayHeight(dp, 0);

    Window rootWindow = DefaultRootWindow(dp);
    XImage *x11image = XGetImage(dp, rootWindow, 0, 0, width, height, AllPlanes, ZPixmap);
    XFixesCursorImage *xfixescursor = XFixesGetCursorImage(dp);

    saveScreenShot(dp, x11image, xfixescursor, QString("screen_%1.png").arg(fileIndex++), "PNG");
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_clicked()
{
    fileIndex = 0;

    if (shootTimer->isActive())
    {
        shootTimer->stop();
        ui->pushButton->setText(QString("start shooting"));
    } else
    {
        shootTimer->start();
        ui->pushButton->setText(QString("stop shooting"));
    }
}
