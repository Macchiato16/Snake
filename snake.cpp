#include "snake.h"
#include <QPainter>

// 贪吃蛇构造函数，初始化蛇的身体和方向
Snake::Snake(QWidget *parent) : QWidget(parent), direction(10, 0)
{
    body << QPoint(50, 50) << QPoint(40, 50) << QPoint(30, 50);  // 初始化蛇的身体
}

// 绘制蛇
void Snake::draw(QPainter &qp)
{
    qp.setBrush(Qt::black);  // 设置笔刷颜色为黑色
    qp.drawEllipse(body.first(), DOT_SIZE / 2, DOT_SIZE / 2);  // 绘制蛇头
    qp.setBrush(Qt::NoBrush);  // 设置笔刷为无颜色
    for (int i = 1; i < body.size(); ++i) {  // 绘制蛇身
        qp.drawEllipse(body[i], DOT_SIZE / 2, DOT_SIZE / 2);
    }
}

// 移动蛇
bool Snake::move(bool wallPass)
{
    for (int i = body.size() - 1; i > 0; --i) {  // 更新蛇身位置
        body[i] = body[i - 1];
    }
    body[0] += direction;  // 更新蛇头位置

    if (wallPass) {  // 如果穿墙模式开启
        if (body[0].x() < 0) {
            body[0].setX(590);  // 从左侧穿到右侧
        } else if (body[0].x() >= 600) {
            body[0].setX(0);  // 从右侧穿到左侧
        }

        if (body[0].y() < 0) {
            body[0].setY(390);  // 从上侧穿到下侧
        } else if (body[0].y() >= 400) {
            body[0].setY(0);  // 从下侧穿到上侧
        }
    }

    return !checkCollision(wallPass);  // 检查是否碰撞并返回结果
}

// 增加蛇的长度
void Snake::grow()
{
    body.append(body.last());  // 在蛇尾添加一个新的点
}

// 改变蛇的方向
void Snake::changeDirection(int key)
{
    switch (key) {
    case Qt::Key_Left:
        if (direction != QPoint(10, 0)) direction = QPoint(-10, 0);  // 改变方向为左
        break;
    case Qt::Key_Right:
        if (direction != QPoint(-10, 0)) direction = QPoint(10, 0);  // 改变方向为右
        break;
    case Qt::Key_Up:
        if (direction != QPoint(0, 10)) direction = QPoint(0, -10);  // 改变方向为上
        break;
    case Qt::Key_Down:
        if (direction != QPoint(0, -10)) direction = QPoint(0, 10);  // 改变方向为下
        break;
    }
}

// 检查碰撞
bool Snake::checkCollision(bool wallPass)
{
    return checkSelfCollision() || (!wallPass && (body.first().x() < 0 || body.first().x() >= 600 ||
           body.first().y() < 0 || body.first().y() >= 400));  // 检查是否自我碰撞或撞墙
}

// 检查自我碰撞
bool Snake::checkSelfCollision()
{
    for (int i = 1; i < body.size(); ++i) {
        if (body[i] == body.first()) {
            return true;  // 如果蛇头与蛇身重合，则发生自我碰撞
        }
    }
    return false;
}

// 获取蛇的身体
QList<QPoint> Snake::getBody() const
{
    return body;
}

// 获取蛇的头部
QPoint Snake::getHead() const
{
    return body.first();
}
