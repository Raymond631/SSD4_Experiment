#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTimeNow();
    QString getMessage(int x);

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void showPaint();

    bool eventFilter(QObject *watched, QEvent *event);

    void setTime();

private:
    Ui::MainWindow *ui;
    int h=12;
    int m=0;
    int s=0;
    int ampm=0;
};
#endif // MAINWINDOW_H
