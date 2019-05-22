#ifndef MY2048_H
#define MY2048_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QKeyEvent>

namespace Ui {
    class My2048;
    }


#define MAINWINDOW_HEIGHT       350		// 75 * 4 + ������
#define MAIMWINDOW_WIDTH		350
#define GRID_HEIGHT				75		// ÿ��ͼƬ�Ĵ�С
#define GRID_WIDTH				75
#define VICTORY					2048
#define COORY					4		// ���ݾ����С
#define COORX					4

enum CheckStatus
{//ö�� ״̬
    CS_WIN,
    CS_LOSE,
    CS_NULL
};

enum Direction
{// ����
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

    int m_block[COORX][COORY]; //��ά����
    bool m_canGetKeyToMove;  // �Ƿ���԰���
    int m_score;    //����

    void initEachGrid();  //��ʼ������ֵ
    int getEmptyGridNumber(); // ��÷ǿ� ������
    void randBlockNumber();   // ���λ�� ���ֵ 2
    QString getBlockColor(int number); //������ֵ�����ض�Ӧ��ͼƬ·��
    CheckStatus checkBlockNumber();  //�ж���Ӯ
    void calcBlocks(int dir);  //���ݷ����ƶ��ϲ� update();

    bool isEmpty(int x, int y);
    void exchange(int x, int y);
    bool judgeEqual(int x1, int y1, int x2, int y2);
    void addUp(int x1, int y1, int x2, int y2);

    void calcBlocksup();
    void calcBlocksdown();
    void calcBlocksleft();
    void calcBlocksright();
protected:
    //��ͼ�¼�
    virtual void paintEvent(QPaintEvent *event) override;
    //�����¼�
    virtual void keyPressEvent(QKeyEvent *event) override;

};


#endif // MY2048_H
