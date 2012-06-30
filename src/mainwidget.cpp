#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "grabberthread.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    fileIndex = 0;

    dp = XOpenDisplay(NULL);

    shootTimer = new QTimer();
    shootTimer->setInterval(100);
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
}

void MainWidget::shoot()
{
    /*int screenCnt = ScrenCount(dp);

    for (int i = 0; i < screenCnt; i++)
    {
        int width = DisplayWidth(dp, i), height = DisplayHeight(dp, i);
    }*/

    int screenWidth = XDisplayWidth(dp, 0), screenHeight = XDisplayHeight(dp, 0);

    Window rootWindow = XDefaultRootWindow(dp);
    XImage *x11image = XGetImage(dp, rootWindow, 0, 0, screenWidth, screenHeight, AllPlanes, ZPixmap);
    XFixesCursorImage *xfixescursor = XFixesGetCursorImage(dp);

    char keystates[32];

    XQueryKeymap(dp, keystates);

    GrabberThread *thread = new GrabberThread(dp, x11image, xfixescursor, keystates, screenWidth, screenHeight, QString("screen_%1.png").arg(fileIndex++), "PNG");
    thread->start();
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
