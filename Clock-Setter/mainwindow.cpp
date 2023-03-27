#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //焦点回车响应
    ui->pushButton->setFocus();
    ui->pushButton->setDefault(true);
    //快捷键
    ui->pushButton_3->setShortcut(tr("CTRL+A"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check()
{
    int h=ui->spinBox->value();
    int m=ui->spinBox_2->value();
    int s=ui->spinBox_3->value();

    int seconds=h*3600+m*60+s;
    if(seconds>=min && seconds<=max)
        return true;
    else
        return false;
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)//秒
{
    if(arg1<0)
    {
        if(check())
        {
            int m=ui->spinBox_2->value();
            ui->spinBox_2->setValue(--m);
            ui->spinBox_3->setValue(59);
        }
        else
        {
            ui->spinBox_3->setValue(0);
        }
    }
    else if(arg1>59)
    {
        if(check())
        {
            int m=ui->spinBox_2->value();
            ui->spinBox_2->setValue(++m);
            ui->spinBox_3->setValue(0);
        }
        else
        {
            ui->spinBox_3->setValue(59);
        }
    }
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    if(arg1<0)
    {
        if(check())
        {
            int m=ui->spinBox->value();
            ui->spinBox->setValue(--m);
            ui->spinBox_2->setValue(59);
        }
        else
        {
            ui->spinBox_2->setValue(0);
        }
    }
    else if(arg1>59)
    {
        if(check())
        {
            int m=ui->spinBox->value();
            ui->spinBox->setValue(++m);
            ui->spinBox_2->setValue(0);
        }
        else
        {
            ui->spinBox_2->setValue(59);
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    QApplication::exit();
}


void MainWindow::on_pushButton_2_clicked()
{
    QApplication::exit();
}
