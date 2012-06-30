#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "grabberthread.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->imageFormat->addItem("PNG");
    ui->imageFormat->addItem("JPG");
    ui->imageFormat->addItem("JPEG");
    ui->imageFormat->addItem("BMP");
    ui->imageFormat->addItem("TIFF");

    frameIndex = 0;

    dp = XOpenDisplay(NULL);

    shootTimer = new QTimer();
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("record-2.png"));
    trayIcon->setToolTip("mooScreenGrabber");

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIcon_activated(QSystemTrayIcon::ActivationReason)));

    trayIcon->show();
}

void MainWidget::shoot()
{
    /*int screenCnt = ScrenCount(dp);

    for (int i = 0; i < screenCnt; i++)
    {
        int width = DisplayWidth(dp, i), height = DisplayHeight(dp, i);
    }*/

    shootTimer->setInterval(1000 / ui->fps->text().toInt());

    int screenWidth = XDisplayWidth(dp, 0), screenHeight = XDisplayHeight(dp, 0);

    Window rootWindow = XDefaultRootWindow(dp);
    XImage *x11image = XGetImage(dp, rootWindow, 0, 0, screenWidth, screenHeight, AllPlanes, ZPixmap);
    XFixesCursorImage *xfixescursor = XFixesGetCursorImage(dp);

    char keystates[32];

    XQueryKeymap(dp, keystates);

    GrabberThread *thread = new GrabberThread(dp, x11image, xfixescursor, keystates, screenWidth, screenHeight,
        ui->outputDir->text() + "/" + QString(ui->fileNamePattern->text() + ".%2").arg(frameIndex++).arg(ui->imageFormat->currentText().toLower()),
        ui->imageFormat->currentText().toStdString().c_str());

    thread->start();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_chooseOutputDirectoryButton_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::DirectoryOnly);

    if (dialog.exec())
    {
        ui->outputDir->setText(dialog.directory().absolutePath());
    }

}

void MainWidget::on_togglingButton_clicked()
{
    frameIndex = 0;

    if (ui->fileNamePattern->text().isEmpty())
    {
        ui->fileNamePattern->setText("screen_%1");
    }

    if (ui->imageFormat->currentIndex() < 0)
    {
        ui->imageFormat->setCurrentIndex(0);
    }

    if (ui->outputDir->text().isEmpty())
    {
        ui->outputDir->setText(QApplication::applicationDirPath());
    }

    shootTimer->setInterval(1000 / ui->fps->text().toInt());

    if (shootTimer->isActive())
    {
        shootTimer->stop();
        ui->togglingButton->setText(QString("start shooting"));
        trayIcon->setIcon(QIcon("record-2.png"));
    } else
    {
        shootTimer->start();
        ui->togglingButton->setText(QString("stop shooting"));
        trayIcon->setIcon(QIcon("stop-1.png"));
    }
}

void MainWidget::trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
            this->on_togglingButton_clicked();
        break;

        case QSystemTrayIcon::Context:
            if (this->isVisible())
            {
                this->hide();
            } else
            {
                this->show();
            }
        break;

        default:
        break;
    }
}
