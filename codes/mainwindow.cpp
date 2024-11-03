#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>
#include <QtMath>
#include "errorwindow.h"
#include "aboutmewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Base Converter");

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    this->resize(screenWidth * 0.4, screenHeight * 0.6);

    //insert items into comboboxes
    QStringList items;
    items << "2(binary)" << "3" << "4" << "5" << "6" << "7" << "8(octal)"
          << "9" << "10(decimal)" << "11" << "12" << "13" << "14" << "15" << "16(hex)";
    ui->comboBox_1->addItems(items);
    ui->comboBox_2->addItems(items);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//resize
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    QFont font_Header("黑体", x*0.02);
    QFont font_Text("黑体", x*0.01);

    ui->labelHeader->setFont(font_Header);
    ui->labelHeader->setGeometry(x*0.1, y*0.05, x*0.8, y*0.1);

    ui->label_Enter->setFont(font_Text);
    ui->label_Enter->setGeometry(x*0.2, y*0.15, x*0.6, y*0.05);
    ui->lineEditNum->setGeometry(x*0.2, y*0.2, x*0.6, y*0.07);

    ui->label_firstBase->setFont(font_Text);
    ui->label_firstBase->setGeometry(x*0.2, y*0.27, x*0.6, y*0.05);
    ui->comboBox_1->setGeometry(x*0.2, y*0.32, x*0.6, y*0.07);

    ui->label_secBase->setFont(font_Text);
    ui->label_secBase->setGeometry(x*0.2, y*0.39, x*0.6, y*0.05);
    ui->comboBox_2->setGeometry(x*0.2, y*0.44, x*0.6, y*0.07);

    ui->pushButtonConvert->setGeometry(x*0.4, y*0.53, x*0.2, y*0.08);

    ui->label_Result->setFont(font_Text);
    ui->label_Result->setGeometry(x*0.2, y*0.61, x*0.6, y*0.05);
    ui->textBrowserResult->setGeometry(x*0.2, y*0.66, x*0.6, y*0.07);

    ui->pushButtonExit->setGeometry(x*0.4, y*0.78, x*0.2, y*0.08);

    ui->pushButton->setGeometry(x*0.8, y*0.8, x*0.1, y*0.08);
}

//exit
void MainWindow::on_pushButtonExit_clicked()
{
    close();
}

//convert
//step1: check if the input number is valid (like if the 1st base is 8(octal)
// then the number should be 0-7) -> if not, call error window
//step2: so now as we going to this step, the number is confirmed to be valid.
// we will have 3 separated situations:
// 1: first base = second base -> result = input;
// 2: first base is 10(decimal) but second base is not; (10->x)
// 3: second base is 10(decimal) but first base is not; (x->10)
// 4: both of the starting and ending bases are not 10(decimal).
//  in this case we will have to turn the number into 10(decimal) as a bridge
//  and then convert it into the final result.
void MainWindow::on_pushButtonConvert_clicked()
{
    int firstBase; //first base
    if (ui->comboBox_1->currentText() == "2(binary)") firstBase = 2;
    else if (ui->comboBox_1->currentText() == "8(octal)") firstBase = 8;
    else if (ui->comboBox_1->currentText() == "10(decimal)") firstBase = 10;
    else if (ui->comboBox_1->currentText() == "16(hex)") firstBase = 16;
    else firstBase = ui->comboBox_1->currentText().toInt();

    QString inputNum = ui->lineEditNum->text();

    //step1: valid or not?
    bool valid = true;  //defalut = true
    for (auto digit : inputNum)  //travel through digits and check if its valid
    {
        //need to be 0-9 or A-F or a-f
        if (!((digit >= 48 && digit <=57) || (digit >= 65 && digit <= 70) || (digit >= 97 && digit <= 102)))
        {
            valid = false;
            break;
        }

        int currentDigit; //current digit in int form
        if (digit >= 97) currentDigit = digit.unicode() - 87;
        else if (digit >= 65) currentDigit = digit.unicode() - 55;
        else currentDigit = digit.unicode() - 48;

        //need to be < base
        if (currentDigit >= firstBase)
        {
            valid = false;
            break;
        }
    }

    if (!valid)
    {
        ErrorWindow errorWindow(this);
        errorWindow.exec();
    }
    else
    {
        //step2: calculate
        int secondBase; //second base
        if (ui->comboBox_2->currentText() == "2(binary)") secondBase = 2;
        else if (ui->comboBox_2->currentText() == "8(octal)") secondBase = 8;
        else if (ui->comboBox_2->currentText() == "10(decimal)") secondBase = 10;
        else if (ui->comboBox_2->currentText() == "16(hex)") secondBase = 16;
        else secondBase = ui->comboBox_2->currentText().toInt();

        if (firstBase == secondBase) //situation 1
        {
            ui->textBrowserResult->setText(inputNum);
        }
        else if (firstBase == 10) //situation 2
        {
            int input = inputNum.toInt();
            QString result = "";
            while (input > 0)
            {
                int bit = input - (input / secondBase) * secondBase;
                input /= secondBase;
                if (bit <= 9) result.insert(0, QChar(bit + 48));
                else result.insert(0, QChar(bit + 55));
            }
            ui->textBrowserResult->setText(result);
        }
        else if (secondBase == 10) //situation 3
        {
            int result = 0;
            for (int i = 0; i < inputNum.size(); i++)
            {
                int currentDigit;
                QChar digit = inputNum[inputNum.size()-1-i];
                if (digit >= 97) currentDigit = digit.unicode() - 87;
                else if (digit >= 65) currentDigit = digit.unicode() - 55;
                else currentDigit = digit.unicode() - 48;

                result += (currentDigit * pow(firstBase, i));
            }
            ui->textBrowserResult->setText(QString::number(result));
        }
        else //situation 4
        {
            int decimalBridge = 0;
            for (int i = 0; i < inputNum.size(); i++)
            {
                int currentDigit;
                QChar digit = inputNum[inputNum.size()-1-i];
                if (digit >= 97) currentDigit = digit.unicode() - 87;
                else if (digit >= 65) currentDigit = digit.unicode() - 55;
                else currentDigit = digit.unicode() - 48;

                decimalBridge += (currentDigit * pow(firstBase, i));
            }

            QString result = "";
            while (decimalBridge > 0)
            {
                int bit = decimalBridge - (decimalBridge / secondBase) * secondBase;
                decimalBridge /= secondBase;
                if (bit <= 9) result.insert(0, QChar(bit + 48));
                else result.insert(0, QChar(bit + 55));
            }

            ui->textBrowserResult->setText(result);
        }
    }
}

//About me
void MainWindow::on_pushButton_clicked()
{
    AboutMeWindow aboutmeWindow(this);
    aboutmeWindow.exec();
}
