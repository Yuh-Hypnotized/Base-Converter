#ifndef ABOUTMEWINDOW_H
#define ABOUTMEWINDOW_H

#include <QDialog>

namespace Ui {
class AboutMeWindow;
}

class AboutMeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutMeWindow(QWidget *parent = nullptr);
    ~AboutMeWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AboutMeWindow *ui;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // ABOUTMEWINDOW_H
