#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_Clear_clicked();

    void on_pushButton_mult_clicked();

    void on_pushButton_divide_clicked();

    void on_pushButton_5__clicked();

    void on_pushButton_7__clicked();

    void on_pushButton_8__clicked();

    void on_pushButton_9__clicked();

    void on_pushButton_4__clicked();

    void on_pushButton_6__clicked();

    void on_pushButton_1__clicked();

    void on_pushButton_2__clicked();

    void on_pushButton_3__clicked();

    void on_pushButton_0__clicked();

    void on_pushButton_perCent_clicked();

    void on_pushButton_point_clicked();

    void on_pushButton_sub_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_backSpace_clicked();

    void on_pushButton_equal_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
