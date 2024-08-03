#include "mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QVBoxLayout>

// 主窗口构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), snake(nullptr), apple(nullptr), wallPass(false)
{
    setFixedSize(B_WIDTH, B_HEIGHT);  // 设置固定窗口大小

    startButton = new QPushButton("开始游戏", this);  // 创建开始按钮
    wallPassCheckBox = new QCheckBox("穿墙模式", this);  // 创建穿墙模式复选框
    QVBoxLayout *layout = new QVBoxLayout;  // 创建垂直布局
    layout->addWidget(startButton);  // 添加按钮到布局
    layout->addWidget(wallPassCheckBox);  // 添加复选框到布局
    QWidget *widget = new QWidget(this);  // 创建中心窗口部件
    widget->setLayout(layout);  // 设置布局
    setCentralWidget(widget);  // 设置中心窗口部件

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);  // 连接按钮点击信号到开始游戏槽函数
}

// 主窗口析构函数
MainWindow::~MainWindow()
{
    delete snake;  // 删除蛇对象
    delete apple;  // 删除苹果对象
}

// 开始游戏槽函数
void MainWindow::startGame()
{
    delete snake;  // 删除旧蛇对象
    delete apple;  // 删除旧苹果对象

    snake = new Snake(this);  // 创建新蛇对象
    apple = new Apple(this);  // 创建新苹果对象
    wallPass = wallPassCheckBox->isChecked();  // 获取穿墙模式状态

    setCentralWidget(nullptr);  // 清除中心窗口部件
    setStyleSheet("background-color: white;");  // 设置背景颜色为白色
    qsrand(QTime::currentTime().msec());  // 初始化随机数种子
    apple->generateNewApple(snake->getBody());  // 生成新苹果
    timerId = startTimer(DELAY);  // 启动定时器
}

// 重新开始游戏槽函数
void MainWindow::restartGame()
{
    delete snake;  // 删除旧蛇对象
    delete apple;  // 删除旧苹果对象

    snake = new Snake(this);  // 创建新蛇对象
    apple = new Apple(this);  // 创建新苹果对象
    wallPass = wallPassCheckBox->isChecked();  // 获取穿墙模式状态

    qsrand(QTime::currentTime().msec());  // 初始化随机数种子
    apple->generateNewApple(snake->getBody());  // 生成新苹果
    timerId = startTimer(DELAY);  // 启动定时器
}

// 重绘事件处理函数
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (snake && apple) {  // 确保蛇和苹果对象已创建
        QPainter qp(this);  // 创建绘图对象
        snake->draw(qp);  // 绘制蛇
        apple->draw(qp);  // 绘制苹果
    }
}

// 按键事件处理函数
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (snake) {  // 确保蛇对象已创建
        snake->changeDirection(event->key());  // 改变蛇的方向
    }
}

// 定时器事件处理函数
void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (snake && apple) {  // 确保蛇和苹果对象已创建
        if (snake->move(wallPass)) {  // 移动蛇并检查是否碰撞
            checkApple();  // 检查是否吃到苹果
            checkCollision();  // 检查是否碰撞
            repaint();  // 重新绘制
        } else {
            killTimer(timerId);  // 停止定时器
            gameOver();  // 游戏结束处理
        }
    }
}

// 检查碰撞函数
void MainWindow::checkCollision()
{
    if (snake->checkCollision(wallPass)) {  // 检查是否碰撞
        killTimer(timerId);  // 停止定时器
        gameOver();  // 游戏结束处理
    }
}

// 检查是否吃到苹果函数
void MainWindow::checkApple()
{
    if (snake->getHead() == apple->getPosition()) {  // 检查蛇头是否与苹果重合
        snake->grow();  // 增加蛇的长度
        apple->generateNewApple(snake->getBody());  // 生成新苹果
    }
}

// 游戏结束处理函数
void MainWindow::gameOver()
{
    QMessageBox msgBox;  // 创建消息框
    msgBox.setText("游戏失败");  // 设置消息文本
    msgBox.setInformativeText(QString("当前长度为: %1").arg(snake->getBody().size()));  // 显示当前长度
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);  // 添加按钮
    msgBox.setDefaultButton(QMessageBox::Retry);  // 设置默认按钮
    int ret = msgBox.exec();  // 显示消息框并获取用户选择

    switch (ret) {
    case QMessageBox::Retry:
        restartGame();  // 重新开始游戏
        break;
    case QMessageBox::Cancel:
        delete snake;  // 删除蛇对象
        delete apple;  // 删除苹果对象
        snake = nullptr;  // 将蛇对象指针置空
        apple = nullptr;  // 将苹果对象指针置空
        setCentralWidget(nullptr);  // 清除中心窗口部件
        startButton = new QPushButton("开始游戏", this);  // 创建新开始按钮
        wallPassCheckBox = new QCheckBox("穿墙模式", this);  // 创建新穿墙模式复选框
        QVBoxLayout *layout = new QVBoxLayout;  // 创建新垂直布局
        layout->addWidget(startButton);  // 添加按钮到布局
        layout->addWidget(wallPassCheckBox);  // 添加复选框到布局
        QWidget *widget = new QWidget(this);  // 创建新中心窗口部件
        widget->setLayout(layout);  // 设置布局
        setCentralWidget(widget);  // 设置中心窗口部件
        connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);  // 连接按钮点击信号到开始游戏槽函数
        break;
    }
}
