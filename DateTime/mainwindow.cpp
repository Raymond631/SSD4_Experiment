#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
    setTimeNow();//设置数组时钟
    ui->frame_4->installEventFilter(this);//绘制时钟，注册事件过滤器

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setTime()));//刷新数字时钟
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));//刷新窗口，自动调用时钟重绘函数
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTimeNow()
{
    QTime current_time=QTime::currentTime();
    int hour=current_time.hour();
    int minute=current_time.minute();
    int second=current_time.second();
    if(hour==0)
    {
        ampm=0;
        ui->radioButton->setChecked(true);
        ui->spinBox->setValue(12);
    }
    else if(hour==12)
    {
        ampm=1;
        ui->radioButton_2->setChecked(true);
        ui->spinBox->setValue(12);
    }
    else if(hour>12)
    {
        ampm=1;
        ui->radioButton_2->setChecked(true);
        ui->spinBox->setValue(hour-12);
    }
    else
    {
        ampm=0;
        ui->radioButton->setChecked(true);
        ui->spinBox->setValue(hour);
    }
    ui->spinBox_2->setValue(minute);
    ui->spinBox_3->setValue(second);
}

void MainWindow::on_spinBox_valueChanged(int arg1)//时
{
    if((h==11&&arg1==12)||(h==12&&arg1==11))
    {
        switch (ampm)
        {
        case 0:
            ampm=1;
            ui->radioButton_2->setChecked(true);
            break;
        case 1:
            ampm=0;
            ui->radioButton->setChecked(true);
            break;
        }
    }
    h=arg1;
}
void MainWindow::on_spinBox_2_valueChanged(int arg1)//分
{
    if(m==59&&arg1==0)
    {
        if(h==12)
            ui->spinBox->setValue(1);
        else
            ui->spinBox->setValue(h+1);
    }
    else if(m==0&&arg1==59)
    {
        if(h==1)
            ui->spinBox->setValue(12);
        else
            ui->spinBox->setValue(h-1);
    }
    m=arg1;
}
void MainWindow::on_spinBox_3_valueChanged(int arg1)//秒
{
    if(s==59&&arg1==0)
    {
        ui->spinBox_2->setValue(m+1);
    }
    else if(s==0&&arg1==59)
    {
        ui->spinBox_2->setValue(m-1);
    }
    s=arg1;
}
void MainWindow::on_radioButton_clicked()//上午
{
    ampm=0;//上午
}
void MainWindow::on_radioButton_2_clicked()//下午
{
    ampm=1;//下午
}
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)//时区
{
    ui->label_4->setText(arg1);
}

QString MainWindow::getMessage(int x)
{
    int year=ui->calendarWidget->selectedDate().year();
    int month=ui->calendarWidget->selectedDate().month();
    int day=ui->calendarWidget->selectedDate().day();
    int hour=-1;
    if(ampm==0)
    {
        if(h==12)
            hour=0;
        else
            hour=h;
    }
    else if(ampm==1)
    {
        if(h==12)
            hour=12;
        else
            hour=h+12;
    }
    int minute=m;
    int second=s;
    QString timeZone=ui->comboBox->currentText();
    bool daylight=ui->checkBox->isChecked();

    QString text="";
    switch (x)
    {
    case 1:
        text=QString("OK...\n====================\nYear=%1\nMonth=%2\nDay=%3\nHour=%4\nMinute=%5\nSecond=%6\nTimeZone=%7\nAuto Daylight=%8\n====================\n(Time saved)")
                .arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second).arg(timeZone).arg(daylight?"true":"false");
        break;
    case 2:
        text=QString("Cancelled...\n====================\nYear=%1\nMonth=%2\nDay=%3\nHour=%4\nMinute=%5\nSecond=%6\nTimeZone=%7\nAuto Daylight=%8\n====================\n(Time not saved)")
                .arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second).arg(timeZone).arg(daylight?"true":"false");
        break;
    case 3:
        text=QString("Applied...\n====================\nYear=%1\nMonth=%2\nDay=%3\nHour=%4\nMinute=%5\nSecond=%6\nTimeZone=%7\nAuto Daylight=%8\n====================\n(Time saved)")
                .arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second).arg(timeZone).arg(daylight?"true":"false");
        break;
    }
    return text;
}
void MainWindow::on_pushButton_clicked()
{
    QMessageBox::information(NULL, "Date_and_Time",getMessage(1));
    QApplication::exit();
}
void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(NULL, "Date_and_Time",getMessage(2));
    QApplication::exit();
}
void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::information(NULL, "Date_and_Time",getMessage(3));
}


void MainWindow::setTime()
{
    if(s==59)
    {
        ui->spinBox_3->setValue(0);
    }
    else
    {
        ui->spinBox_3->setValue(s+1);
    }
}
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->frame_4 && event->type() == QEvent::Paint)
    {
        showPaint(); //响应函数
    }
    return QWidget::eventFilter(watched,event);
}
void MainWindow::showPaint()
{
    //刻画时针、分针、秒针、长刻度、短刻度
    static const QPoint hourHand[3]={
        QPoint(7,14),
        QPoint(-7,14),
        QPoint(0,-50)
    };
    static const QPoint minuteHand[3]={
        QPoint(5,14),
        QPoint(-5,14),
        QPoint(0,-65)
    };
    static const QPoint secondHand[3]={
        QPoint(3,14),
        QPoint(-3,14),
        QPoint(0,-80)
    };
    static const QPoint line_long[2]={
        QPoint(0,100),
        QPoint(0,85)
    };
    static const QPoint line_short[2]={
        QPoint(0,100),
        QPoint(0,95)
    };
    int side=qMin(ui->frame_4->width(),ui->frame_4->height());//绘制的范围
    QPainter painter(ui->frame_4);//声明用来绘图的painter

    painter.setRenderHint(QPainter::Antialiasing);//反走样、抗锯齿
    painter.translate(ui->frame_4->width()/2,ui->frame_4->height()/2);//将坐标原点移动到画布中央
    painter.scale(side/250.0,side/250.0);//设定边界，图形大小适应画布
    painter.setPen(Qt::black);//描边色
    painter.setBrush(Qt::black);//填充色

    //长刻度（小时）
    painter.save();
    painter.setPen(Qt::black);
    for(int i=0;i<12;++i)
    {
        painter.drawLine(line_long[0],line_long[1]);
        if(i==0)
            painter.drawText(-20,-82,40,40,Qt::AlignHCenter|Qt::AlignTop,QString::number(12));
        else
            painter.drawText(-20,-82,40,40,Qt::AlignHCenter|Qt::AlignTop,QString::number(i));
        painter.rotate(30.0);//旋转，每格360/12=30度
    }
    painter.restore();

    //短刻度（分钟）
    painter.save();
    painter.setPen(Qt::blue);//描边色
    for(int j=0;j<60;++j)
    {
        if((j%5)!=0)
            painter.drawLine(line_short[0],line_short[1]);
        painter.rotate(6.0);
    }
    painter.restore();

    //绘制时针
    painter.save();
    painter.setBrush(Qt::red);
    painter.rotate(30.0*(h+m/60.0+s/3600));
    painter.drawConvexPolygon(hourHand,3);
    painter.restore();

    //绘制分针
    painter.save();
    painter.setBrush(Qt::yellow);
    painter.rotate(6.0*(m+s/60.0));
    painter.drawConvexPolygon(minuteHand,3);
    painter.restore();

    //绘制秒针
    painter.save();
    painter.setBrush(Qt::green);
    painter.rotate(6.0*s);
    painter.drawConvexPolygon(secondHand,3);
    painter.restore();
}
