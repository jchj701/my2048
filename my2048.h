#ifndef MY2048_H
#define MY2048_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QKeyEvent>

namespace Ui {
    class My2048;
    }


#define MAINWINDOW_HEIGHT       350		// 75 * 4 + 方格间隔
#define MAIMWINDOW_WIDTH		350
#define GRID_HEIGHT				75		// 每张图片的大小
#define GRID_WIDTH				75
#define VICTORY					2048
#define COORY					4		// 数据矩阵大小
#define COORX					4

enum CheckStatus
{//枚举 状态
    CS_WIN,
    CS_LOSE,
    CS_NULL
};

enum Direction
{// 方向
    DR_UP,
    DR_DOWN,
    DR_LEFT,
    DR_RIGHT,
    DR_NULL
};

class My2048 : public QMainWindow
{
    Q_OBJECT

public:
    explicit My2048(QWidget *parent = nullptr);
    ~My2048();


private slots:
    void on_pushButton_clicked();

private:
    Ui::My2048 *ui;

    int m_block[COORX][COORY]; //二维数组
    bool m_canGetKeyToMove;  // 是否可以按键
    int m_score;    //分数

    void initEachGrid();  //初始化方块值
    int getEmptyGridNumber(); // 获得非空 方块数
    void randBlockNumber();   // 随机位置 随机值 2
    QString getBlockColor(int number); //根据数值，返回对应的图片路径
    CheckStatus checkBlockNumber();  //判断输赢
    void calcBlocks(int dir);  //根据方向移动合并 update();

    bool isEmpty(int x, int y);
    void exchange(int x, int y);
    bool judgeEqual(int x1, int y1, int x2, int y2);
    void addUp(int x1, int y1, int x2, int y2);

    void calcBlocksup();
    void calcBlocksdown();
    void calcBlocksleft();
    void calcBlocksright();
protected:
    //绘图事件
    virtual void paintEvent(QPaintEvent *event) override;
    //键盘事件
    virtual void keyPressEvent(QKeyEvent *event) override;

};


#endif // MY2048_H
