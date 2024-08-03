#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QList>
#include <QPoint>

// 贪吃蛇类，管理蛇的状态和行为
class Snake : public QWidget
{
    Q_OBJECT

public:
    explicit Snake(QWidget *parent = nullptr);  // 构造函数
    void draw(QPainter &qp);  // 绘制蛇
    bool move(bool wallPass);  // 移动蛇，返回是否移动成功
    void grow();  // 增加蛇的长度
    void changeDirection(int key);  // 改变蛇的方向
    bool checkCollision(bool wallPass);  // 检查碰撞
    QList<QPoint> getBody() const;  // 获取蛇的身体
    QPoint getHead() const;  // 获取蛇的头部

private:
    QList<QPoint> body;  // 蛇的身体，由一系列点组成
    QPoint direction;  // 蛇的移动方向
    bool checkSelfCollision();  // 检查自我碰撞

    static const int DOT_SIZE = 10;  // 每个蛇身圆圈的大小
    static const int ALL_DOTS = 900;  // 蛇的最大长度
};

#endif // SNAKE_H
