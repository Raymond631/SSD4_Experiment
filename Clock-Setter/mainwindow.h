#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool check();

private slots:
    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    const int min=0;
    const int max=23*3600+59*60+59;
};
#endif // MAINWINDOW_H
