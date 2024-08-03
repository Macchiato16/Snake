#ifndef APPLE_H
#define APPLE_H

#include <QWidget>
#include <QPoint>
#include <QList>

// 苹果类，管理苹果的位置和绘制
class Apple : public QWidget
{
    Q_OBJECT

public:
    explicit Apple(QWidget *parent = nullptr);  // 构造函数
    void draw(QPainter &qp);  // 绘制苹果
    void generateNewApple(const QList<QPoint> &snakeBody);  // 生成新苹果
    QPoint getPosition() const;  // 获取苹果的位置

private:
    QPoint position;  // 苹果的位置

    static const int DOT_SIZE = 10;  // 苹果的大小
};

#endif // APPLE_H
