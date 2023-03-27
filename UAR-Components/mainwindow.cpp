#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();//光标定位
    ui->pushButton_3->setShortcut(tr("ESC"));
    QShortcut *shortcut= new QShortcut(QKeySequence(tr("ctrl+f")), this);
    connect(shortcut, SIGNAL(activated()), this,SLOT(search()));
    QShortcut *shortcut2= new QShortcut(QKeySequence(tr("ctrl+d")), this);
    connect(shortcut2, SIGNAL(activated()), this,SLOT(display()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int num=ui->lineEdit->text().toInt();
    ui->lineEdit_2->setFocus();//光标定位
    switch (num)
    {
    case 1:
        ui->textBrowser->setText(s1);
        break;
    case 2:
        ui->textBrowser->setText(s2);
        break;
    case 3:
        ui->textBrowser->setText(s3);
        break;
    case 4:
        ui->textBrowser->setText(s4);
        break;
    case 5:
        ui->textBrowser->setText(s5);
        break;
    case 6:
        ui->textBrowser->setText(s6);
        break;
    case 7:
        ui->textBrowser->setText(s7);
        break;
    default:
        QMessageBox::warning(NULL,"ERROR","Please enter values between 1 and 7!");
        ui->lineEdit->setFocus();
        ui->lineEdit->selectAll();
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    QString sentence=ui->textBrowser->toPlainText();
    if(sentence.isEmpty())
    {
        QMessageBox::warning(NULL,"ERROR","Please select text!");
        ui->lineEdit->setFocus();
        ui->lineEdit->selectAll();
        return;
    }

    QString keyword=ui->lineEdit_2->text();
    if(keyword.isEmpty())
    {
        QMessageBox::warning(NULL,"ERROR","Please enter a search string!");
        ui->lineEdit_2->setFocus();
        return;
    }

    int times=sentence.count(keyword,Qt::CaseInsensitive);
    if(times==0)
    {
        QString m=QString("String '%1' not found \n search same text again?").arg(keyword);
        QMessageBox::StandardButton result=QMessageBox::warning(NULL,"Search String",m,QMessageBox::Yes|QMessageBox::No);
        if(result==QMessageBox::Yes)
        {
            ui->lineEdit_2->setFocus();
            ui->lineEdit_2->selectAll();
        }
        else
        {
            ui->textBrowser->clear();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->label_13->clear();
            ui->label_14->clear();
            ui->lineEdit->setFocus();
        }
        return;
    }

    int first=sentence.indexOf(keyword,0,Qt::CaseInsensitive)+1;
    int last=sentence.lastIndexOf(keyword,-1,Qt::CaseInsensitive)+1;

    QString message1=QString("Occurrence 1: Position: %1").arg(first);
    QString message2=QString("Occurrence %1: Fosition: %2").arg(times).arg(last);
    ui->label_13->setText(message1);
    ui->label_14->setText(message2);

    QString message3=QString("The number of occurences of '%1' is: %2 \n Search same text?").arg(keyword).arg(times);
    QMessageBox::StandardButton result=QMessageBox::question(NULL,"Search String",message3);
    if(result==QMessageBox::Yes)
    {
        ui->lineEdit_2->setFocus();
        ui->lineEdit_2->selectAll();
    }
    else
    {
        ui->textBrowser->clear();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->label_13->clear();
        ui->label_14->clear();
        ui->lineEdit->setFocus();
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    QApplication::exit();
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->textBrowser->clear();
    ui->lineEdit_2->clear();
    ui->label_13->clear();
    ui->label_14->clear();
}
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->label_13->clear();
    ui->label_14->clear();
}

//快捷键
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if(ui->lineEdit->hasFocus())
        {
            emit ui->pushButton->click();
        }
        else if(ui->lineEdit_2->hasFocus())
        {
            emit ui->pushButton_2->click();
        }
    }
}
void MainWindow::search()
{
    ui->lineEdit_2->setFocus();
    ui->lineEdit_2->selectAll();
}
void MainWindow::display()
{
    ui->lineEdit->setFocus();
    ui->lineEdit->selectAll();
}
