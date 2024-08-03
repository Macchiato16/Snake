#include "apple.h"
#include <QPainter>
#include <QRandomGenerator>

// 苹果构造函数，初始化苹果位置
Apple::Apple(QWidget *parent) : QWidget(parent)
{
    generateNewApple(QList<QPoint>());  // 初始化生成一个苹果
}

// 绘制苹果
void Apple::draw(QPainter &qp)
{
    qp.setBrush(Qt::red);  // 设置笔刷颜色为红色
    qp.drawEllipse(position, DOT_SIZE / 2, DOT_SIZE / 2);  // 绘制苹果
}

// 生成新苹果
void Apple::generateNewApple(const QList<QPoint> &snakeBody)
{
    int x, y;
    do {
        x = QRandomGenerator::global()->bounded(60) * 10;  // 随机生成x坐标
        y = QRandomGenerator::global()->bounded(40) * 10;  // 随机生成y坐标
        position = QPoint(x, y);  // 设置苹果位置
    } while (snakeBody.contains(position));  // 确保苹果不生成在蛇身上
}

// 获取苹果的位置
QPoint Apple::getPosition() const
{
    return position;
}
