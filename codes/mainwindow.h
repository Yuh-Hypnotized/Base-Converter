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

private:
    Ui::MainWindow *ui;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_pushButtonExit_clicked();
    void on_pushButtonConvert_clicked();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
