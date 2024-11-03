#include "errorwindow.h"
#include "ui_errorwindow.h"

#include <QScreen>

ErrorWindow::ErrorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
    setWindowTitle("Error");

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    this->resize(screenWidth * 0.4, screenHeight * 0.4);
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

//OK
void ErrorWindow::on_pushButton_clicked()
{
    close();
}


//resize
void ErrorWindow::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    QFont font("宋体", x*0.015);

    ui->label->setGeometry(x*0.2, y*0.2, x*0.7, y*0.1);
    ui->label_2->setGeometry(x*0.2, y*0.4, x*0.7, y*0.1);
    ui->label->setFont(font);
    ui->label_2->setFont(font);

    ui->pushButton->setGeometry(x*0.4, y*0.7, x*0.2, y*0.1);
}
