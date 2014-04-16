#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> //define O_WRONLY and O_RDONLY

#define SYSFS_GYRO "/sys/bus/i2c/devices/1-0069/iio:device1"
#define SYSFS_MAG "/sys/bus/i2c/devices/1-001e/iio:device2"
#define MAX_BUF 64

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void timerUpDate();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    int num;
    int dir;
    QPainterPath path;

};





#endif // MAINWINDOW_H
