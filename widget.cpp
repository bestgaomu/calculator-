#include "widget.h"
#include "ui_widget.h"
#include <QRegularExpression>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_Clear_clicked()
{
    ui->plainTextEdit->clear();
}


void Widget::on_pushButton_mult_clicked()
{
    ui->plainTextEdit->insertPlainText("*");
}


void Widget::on_pushButton_divide_clicked()
{
    ui->plainTextEdit->insertPlainText("/");
}


void Widget::on_pushButton_5__clicked()
{
    ui->plainTextEdit->insertPlainText("5");
}


void Widget::on_pushButton_7__clicked()
{
    ui->plainTextEdit->insertPlainText("7");
}


void Widget::on_pushButton_8__clicked()
{
    ui->plainTextEdit->insertPlainText("8");
}


void Widget::on_pushButton_9__clicked()
{
    ui->plainTextEdit->insertPlainText("9");
}


void Widget::on_pushButton_4__clicked()
{
    ui->plainTextEdit->insertPlainText("4");
}


void Widget::on_pushButton_6__clicked()
{
    ui->plainTextEdit->insertPlainText("6");
}


void Widget::on_pushButton_1__clicked()
{
    ui->plainTextEdit->insertPlainText("1");
}


void Widget::on_pushButton_2__clicked()
{
    ui->plainTextEdit->insertPlainText("2");
}


void Widget::on_pushButton_3__clicked()
{
    ui->plainTextEdit->insertPlainText("3");
}


void Widget::on_pushButton_0__clicked()
{
    ui->plainTextEdit->insertPlainText("0");
}


void Widget::on_pushButton_perCent_clicked()
{
    ui->plainTextEdit->insertPlainText("%");
}


void Widget::on_pushButton_point_clicked()
{
    QString currentText = ui->plainTextEdit->toPlainText();
    if(currentText.size()==0)
    {
        ui->plainTextEdit->insertPlainText("0.");
    }
    else{
        ui->plainTextEdit->insertPlainText(".");
    }
}


void Widget::on_pushButton_sub_clicked()
{
    ui->plainTextEdit->insertPlainText("-");
}


void Widget::on_pushButton_add_clicked()
{
    ui->plainTextEdit->insertPlainText("+");
}


void Widget::on_pushButton_backSpace_clicked()
{
    QString currentText = ui->plainTextEdit->toPlainText();
    // 检查文本是否为空
    if (!currentText.isEmpty()) {
        // 移除最后一个字符
        currentText.chop(1);
        // 设置修改后的文本
        ui->plainTextEdit->setPlainText(currentText);
    }
    // 创建一个文本光标
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    // 移动光标到文本末尾
    cursor.movePosition(QTextCursor::End);
    // 设置光标
    ui->plainTextEdit->setTextCursor(cursor);
}


void Widget::on_pushButton_equal_clicked()
{
    QString currentText = ui->plainTextEdit->toPlainText();
    // 检查符号数量
    // // int operatorCount = currentText.count(QRegularExpression("[+*/-.%]"));//顺序会有影响？
    // int operatorCount = currentText.count(QRegularExpression("[+*/-%.]"));
    // qDebug()<<QString("operatorCount=%1").arg(operatorCount);
    // if (operatorCount >1) {
    //     // 检查是否有多个符号相连
    //     if (currentText.contains(QRegularExpression("[+*/-%.]{2,}"))) {
    //         ui->plainTextEdit->appendPlainText("表达式错误\n");
    //         return; // 结束函数
    //     }
    // }
    // 检查符号数量
    int operatorCount = currentText.count(QRegularExpression("[+*/-]"));//顺序会有影响
    qDebug() << QString("operatorCount=%1").arg(operatorCount);

    // 检查是否有多个符号相连
    if (currentText.contains(QRegularExpression("[+*/-]{2,}"))) {
        ui->plainTextEdit->appendPlainText("表达式错误\n");
        return; // 结束函数
    }
    // qDebug()<<"1111111111111";

    // 检查符号是否在最前面=>同时进行单字符处理
    if (currentText[0] == '-'|| currentText[0].isDigit()) {
        QStringList tokens = currentText.split(QRegularExpression("(?<=[*/%-])|(?=[*/%-])|(?<=[+-])|(?=[+-])"));
        for(int i=0;i<tokens.size();i++)
        {
            if (tokens[i].isEmpty()) {//处理%放后面为空的情况
                tokens.removeAt(i); // 删除空的元素
                continue; // 继续下一次循环
            }
            // ui->plainTextEdit->insertPlainText(QString(" %1").arg(tokens.at(i)));
            // qDebug() << QString("tokens.at(%1)=%2").arg(tokens.size()).arg(tokens.at(i));
        }
        // qDebug() << QString("tokens[tokens.size()]").arg(tokens[tokens.size()-2]);
        // if(tokens[tokens.size()-2]=="%")
        // {
        //     tokens.removeAt(tokens.size()-2);
        // }

        // 处理百分比
        // for (int i = 0; i < tokens.size(); ++i) {
        //     if (tokens[i].endsWith("%")) {
        //         // QString percentageStr = tokens[i].chopped(1); // 去掉百分号
        //         ui->plainTextEdit->insertPlainText(QString(" ---%1").arg(tokens[i]));
        //         double percentageValue = tokens[i-1].toDouble() / 100; // 转换为小数

        //         ui->plainTextEdit->insertPlainText(QString(" ---%1").arg(percentageValue));
        //         qDebug() << QString("percentageValue=%1").arg(percentageValue);
        //         tokens.replace(i-1, QString::number(percentageValue, 'f', 6)); // 替换为小数，保留6位小数
        //         tokens.removeAt(i);
        //     }
        // }

        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i].endsWith("%")) {
                int count = 0; // 用于统计连续的 %

                // 统计连续的 %
                while (i < tokens.size() && tokens[i].endsWith("%")) {
                    count++;
                    i++; // 移动到下一个元素
                }

                // 确保 i - count - 1 是有效索引
                if (i - count - 1 >= 0) {
                    QString percentageStr = tokens[i - count - 1]; // 获取前一个非 % 元素
                    double baseValue = percentageStr.toDouble(); // 转换为基础数值

                    // 计算百分比值
                    double percentageValue = baseValue;
                    for (int j = 0; j < count; ++j) {
                        percentageValue *= 0.01; // 每个 % 都要乘以 0.01
                    }

                    // 替换为计算后的值
                    tokens.replace(i - count - 1, QString::number(percentageValue, 'f', 6)); // 替换为计算后的值
                    // qDebug() << QString("Converted %: baseValue=%1, count=%2, percentageValue=%3")
                    //                 .arg(baseValue)
                    //                 .arg(count)
                    //                 .arg(percentageValue);

                    // 移除处理过的 % 元素
                    for (int k = 0; k < count; ++k) {
                        tokens.removeAt(i - count); // 从当前索引中移除 % 符号
                    }

                    i--; // 调整索引，避免跳过下一个元素
                }
            }
        }

        // for(int i=0;i<tokens.size();i++)
        // {
        //     ui->plainTextEdit->insertPlainText(QString(" %1").arg(tokens.at(i)));
        //     qDebug() << QString("tokens.at(i)=%1").arg(tokens.at(i));
        // }
        // 先处理乘除
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "*" || tokens[i] == "/") {
                double left = tokens[i - 1].toDouble();
                double right = tokens[i + 1].toDouble();
                double intermediateResult;
                // 根据操作符计算结果
                if (tokens[i] == "*") {
                    intermediateResult = left * right;
                } else if (tokens[i] == "/") {
                    if (right == 0) {
                        ui->plainTextEdit->appendPlainText("除数不能为零\n");
                        return; // 结束函数
                    }
                    intermediateResult = left / right;
                }
                tokens.replace(i - 1, QString::number(intermediateResult));
                tokens.removeAt(i); // 移除运算符
                tokens.removeAt(i); // 移除右操作数
                i--; // 调整索引
            }
        }
        // 处理加减
        double finalResult;
        if(operatorCount==1&&currentText[0] == '-')
        {
            finalResult=-tokens[1].toDouble();;
        }
        else{
            finalResult = tokens[0].toDouble();
            for (int i = 1; i < tokens.size(); i += 2) {
                double next = tokens[i + 1].toDouble();
                if (tokens[i] == "+") {
                    finalResult += next;
                } else if (tokens[i] == "-") {
                    finalResult -= next;
                }
            }
        }
        ui->plainTextEdit->insertPlainText(QString("=\n%1").arg(finalResult));
    }
    else{
        ui->plainTextEdit->appendPlainText("表达式错误\n");
    }
}

