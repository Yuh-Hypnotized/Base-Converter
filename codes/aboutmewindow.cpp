#include "aboutmewindow.h"
#include "ui_aboutmewindow.h"

#include <QScreen>

AboutMeWindow::AboutMeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMeWindow)
{
    ui->setupUi(this);
    setWindowTitle("About Me");

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    this->resize(screenWidth * 0.4, screenHeight * 0.4);
}

AboutMeWindow::~AboutMeWindow()
{
    delete ui;
}

//OK
void AboutMeWindow::on_pushButton_clicked()
{
    close();
}


//resize
void AboutMeWindow::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    QFont font("宋体", x*0.015);

    ui->label->setGeometry(x*0.1, y*0.2, x*0.8, y*0.1);
    ui->label_2->setGeometry(x*0.1, y*0.3, x*0.8, y*0.1);
    ui->label_3->setGeometry(x*0.3, y*0.37, x*0.6, y*0.1);
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);

    ui->pushButton->setGeometry(x*0.4, y*0.7, x*0.2, y*0.1);
}
