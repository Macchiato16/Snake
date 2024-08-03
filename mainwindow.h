#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include "snake.h"
#include "apple.h"

// 主窗口类，管理游戏的整体流程
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // 构造函数
    ~MainWindow();  // 析构函数

protected:
    void paintEvent(QPaintEvent *event) override;  // 重绘事件
    void keyPressEvent(QKeyEvent *event) override;  // 按键事件
    void timerEvent(QTimerEvent *event) override;  // 定时器事件

private slots:
    void startGame();  // 开始游戏槽函数
    void restartGame();  // 重新开始游戏槽函数

private:
    Snake *snake;  // 贪吃蛇对象
    Apple *apple;  // 苹果对象
    int timerId;  // 定时器ID
    void checkCollision();  // 检查碰撞
    void checkApple();  // 检查苹果S
    void gameOver();  // 游戏结束处理

    static const int B_WIDTH = 600;  // 游戏窗口宽度
    static const int B_HEIGHT = 400;  // 游戏窗口高度
    static const int DELAY = 100;  // 定时器延迟

    QPushButton *startButton;  // 开始游戏按钮
    QCheckBox *wallPassCheckBox;  // 穿墙模式复选框
    bool wallPass;  // 是否穿墙标志
};

#endif // MAINWINDOW_H
