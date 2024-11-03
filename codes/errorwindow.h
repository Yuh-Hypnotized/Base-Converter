#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = nullptr);
    ~ErrorWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ErrorWindow *ui;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // ERRORWINDOW_H
