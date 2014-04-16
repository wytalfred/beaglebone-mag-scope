#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <QWSServer> //used by setCursorVisible()
#include <QPainter>
#include <QPointF>
#include <math.h>

#define PERI 20

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //hide title bar
    QWSServer::setCursorVisible(false); //hide cursor

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->start(PERI);
    this->num=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
     QPainter painter(this);
     QPen pen;

     pen.setColor(Qt::darkRed);
     painter.setPen(pen);

    this->path.lineTo(num,-dir/3);
    painter.translate(300-num,180);
    painter.drawPath(this->path);


/*     painter.translate(200,160); //set (0,0)
     painter.rotate(dir);
     static const QPointF points[4] = {QPointF(-50, 0), QPointF(50, 10), QPointF(50, -10),QPointF(-50, 0)};
     painter.drawPolyline(points, 4);
*/
}

void MainWindow::timerUpDate()
{
    int fd;
    char buf[MAX_BUF];
    char ch[10];
    int x,y,z;

    QString tmp="";

    snprintf(buf,sizeof(buf),SYSFS_MAG"/in_magn_x_raw");
    fd = open(buf, O_RDONLY);
    read(fd,ch,10);
    x=atoi(ch);
    tmp.sprintf("%d",x);
    ui->horizontalSlider->setValue(atoi(ch));
    ui->lineEdit->setText(tmp);
    ::close(fd);

    snprintf(buf,sizeof(buf),SYSFS_MAG"/in_magn_y_raw");
    fd = open(buf, O_RDONLY);
    read(fd,ch,10);
    y=atoi(ch);
    tmp.sprintf("%d",y);
    ui->horizontalSlider_2->setValue(atoi(ch));
    ui->lineEdit_2->setText(tmp);
    ::close(fd);

    snprintf(buf,sizeof(buf),SYSFS_MAG"/in_magn_z_raw");
    fd = open(buf, O_RDONLY);
    read(fd,ch,10);
    z=atoi(ch);
    tmp.sprintf("%d",z);
    ui->horizontalSlider_3->setValue(atoi(ch));
    ui->lineEdit_3->setText(tmp);
    ::close(fd);

    dir=(int)(atan((double)z/(double)x)*180/3.14);
    if(x>0)dir+=180;

    this->num++;
    tmp.sprintf("%d",dir);
    ui->lineEdit_4->setText(tmp);

    update();
}

void MainWindow::on_pushButton_clicked()
{
    QApplication* app;
    app->quit();
}
