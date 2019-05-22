#include "my2048.h"
#include "ui_my2048.h"

#include <QPainter>
#include <QDebug>
#include <QTime>

//Direction enum_direction = DR_NULL;
//CheckStatus enum_checkstatus = CS_NULL;

My2048::My2048(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::My2048)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap(":/new/prefix1/res/logo.png"));

    //也可在UI属性中设置
    setFixedSize(540, 375);
    this->setWindowTitle("GAME2048");
    initEachGrid();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //变量
    m_canGetKeyToMove = false;


    //信号槽
    //connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_clicked()));
}

My2048::~My2048()
{
    delete ui;
}

//初始化数组为0
void My2048::initEachGrid()
{
    for(int row = 0; row < COORX; row++)
    {
        for(int col = 0; col < COORY; col++)
        {
            m_block[row][col] = 0;
        }
    }
    qDebug() << "init Over";
}

//开启按钮按下事件
void My2048::on_pushButton_clicked()
{
    //初始化数组
    initEachGrid();
//    enum_checkstatus = CS_NULL;
//    enum_direction = DR_NULL;

    m_score = 0;
    m_canGetKeyToMove = true;

    randBlockNumber();
    randBlockNumber();
}

//画图事件
void My2048::paintEvent(QPaintEvent *event)
{
    //QWidget::paintEvent(event);
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    //使用画刷填充一个矩形区域         MAIMWINDOW_WIDTH
    painter.fillRect(QRect(10, 10, MAIMWINDOW_WIDTH, MAINWINDOW_HEIGHT), QColor(187, 173, 160));
    for(int row=0; row<COORX; row++)
    {
        for(int col=0; col<COORY; col++)
        {
            painter.fillRect( 20 + ( 10 + GRID_HEIGHT ) * row, 20 + ( 10 + GRID_WIDTH ) * col,
                              GRID_HEIGHT, GRID_WIDTH, QColor(205, 193, 179));
        }
    }

    for(int row=0; row<COORX; row++)
    {
        for(int col=0; col<COORY; col++)
        {
            if(m_block[row][col] != 0)
            {
                painter.drawPixmap(20 + ( 10 + GRID_HEIGHT ) * row, 20 + ( 10 + GRID_WIDTH ) * col,
                                    GRID_HEIGHT, GRID_WIDTH, QPixmap(getBlockColor(m_block[row][col])));
            }
            else
            {
                painter.fillRect(20 + ( 10 + GRID_HEIGHT ) * row, 20 + ( 10 + GRID_WIDTH ) * col,
                                 GRID_HEIGHT, GRID_WIDTH, QColor(205, 193, 179));
            }
        }
    }
    update();
}

//按键事件
void My2048::keyPressEvent(QKeyEvent *event)
{
    //开始游戏后允许输入
    if(!m_canGetKeyToMove)
    {
        return;
    }

    switch(event->key())
    {
        case Qt::Key_W:
            //enum_direction = DR_UP;
            qDebug() << "W";
            calcBlocks (DR_UP);
            break;
        case Qt::Key_S:
            //enum_direction = DR_DOWN;
            qDebug() << "S";
            calcBlocks (DR_DOWN);
            break;
        case Qt::Key_A:
            //enum_direction = DR_LEFT;
            qDebug() << "A";
            calcBlocks (DR_LEFT);
            break;
        case Qt::Key_D:
            qDebug() << "D";
            //enum_direction = DR_RIGHT;
            calcBlocks (DR_RIGHT);
            break;
        default:
            qDebug() << "error input keyEvent";
            break;
    }
    //update ();
    CheckStatus C = checkBlockNumber ();

    if(C == CS_WIN)
    {
        QString x = "WIN";
        ui->label_3->setText (x);
    }
    else if(C == CS_LOSE)
    {
        QString x = "LOSE";
        ui->label_3->setText (x);
    }
    else {
        if(getEmptyGridNumber () != 0)
        {
            //非赢非输状态，生成新的方块
            randBlockNumber ();
        }
    }



}

//获得图片对应标签名称
QString My2048::getBlockColor(int number)
{
    switch( number )
    {
      case 2:
      case 4:
      case 8:
      case 16:
      case 32:
      case 64:
      case 128:
      case 256:
      case 512:
      case 1024:
      case 2048:
          return ":/new/prefix1/res/" + QString::number(number);
      default:
          return ":/new/prefix1/res/4096";
    }
}

// 获得空的方块数
int My2048::getEmptyGridNumber()
{
    int empty_number = 0;
    for(int i = 0; i < COORX; i++)
    {
        for(int j = 0; j < COORY; j++)
        {
            if(isEmpty(i, j))
            {
                empty_number++;
            }
        }
    }

    return empty_number;
}

CheckStatus My2048::checkBlockNumber()
{
    int e = getEmptyGridNumber();
    qDebug() << "empty grid = "<< e;
    if(e == 0)
    {
        int a, b, c;
        for(a = 0; a < 4; a++)
        {
            for(b = 0; b < 4; b ++)
            {
                c = b + 1;
                if(c >= 0 && c < 4)
                {
                    if(m_block[a][c] == m_block[a][b])
                        return CS_NULL;
                }
                c = b - 1;
                if(c >= 0 && c < 4)
                {
                    if(m_block[a][c] == m_block[a][b])
                        return CS_NULL;
                }
                c = a + 1;
                if(c >= 0 && c < 4)
                {
                    if(m_block[c][b] == m_block[a][b])
                        return CS_NULL;
                }
                c = a - 1;
                if(c >= 0 && c < 4)
                {
                    if(m_block[c][b] == m_block[a][b])
                        return CS_NULL;
                }
            }
        }
        m_canGetKeyToMove = false;
        return CS_LOSE;
    }
    for(int row=0; row<COORX; row++)
    {
        for(int col=0; col<COORY; col++)
        {
            if(m_block[row][col] == 2048)
            {
                return CS_WIN;
            }
        }
    }
    return CS_NULL;
}


bool My2048::isEmpty(int x, int y)
{
   if(m_block[x][y] == 0)
   {
       return true;
   }
   return false;
}

//void My2048::exchange(int x, int y)
//{
//    m_block[x][y] = m_block[x][y+1];
//    m_block[x][y+1] = 2048;
//}

//bool My2048::judgeEqual(int x1, int y1, int x2, int y2)
//{
//    if(isEmpty (x1, y1) || isEmpty (x2, y2))
//    {
//        return false;
//    }

//    if(m_block[x1][y1] == m_block[x2][y2])
//    {
//        return true;
//    }

//    return false;
//}

//void My2048::addUp(int x1, int y1, int x2, int y2)
//{
//    m_block[x1][y1] = m_block[x1][y1] * 2;
//    m_block[x2][y2] = 0;

//}

// 随机位置 随机值 2
void My2048::randBlockNumber()
{
    int p = qrand() % (COORX * COORY);//0-15
    int x = p % COORX;//列
    int y = p / COORX + 1;;//行

    qDebug() << "(x,y) = " << x << y << "first";
    while(!isEmpty(x, y))
    {
        p = qrand() % (COORX * COORY);
        x = p % COORX;//列
        y = p / COORX + 1;//行
    }
    switch(qrand() % 2)
    {
        case 0:
            m_block[x][y] = 2;
            break;
        default:
            m_block[x][y] = 4;
            break;
    }

    qDebug() << "(x,y) = " << x << y << "second";
}


//    CheckStatus My2048::checkBlockNumber();  //判断输赢

//根据方向移动合并 update();
void My2048::calcBlocks(int dir)
{
    switch (dir)
    {
        case DR_UP:
            calcBlocksup ();
            break;
        case DR_DOWN:
            calcBlocksdown ();
            break;
        case DR_LEFT:
            calcBlocksleft ();
            break;
        case DR_RIGHT:
            calcBlocksright ();
            break;
        default:
            qDebug() << "error dir";
            break;
    }

    if(getEmptyGridNumber() == 0)
    {
        //enum_checkStatus = CS_LOSE;
    }
}

void My2048::calcBlocksup()
{
    int a, b, c;
    for(a = 0; a < 4; ++a)
    {
        for(b = 0; b < 4; ++b)
        {
            if(m_block[a][b] == 0)
                ;
            else
            {
                for(c = b + 1; c < 4 ; ++c)
                {
                    if(m_block[a][c] == 0)
                        ;
                    else if(m_block[a][c] == m_block[a][b])
                    {
                        m_block[a][b] += m_block[a][c];
                        m_score += m_block[a][b];
                        m_block[a][c] = 0;
                        b = c;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    for(a = 0; a < 4; ++a)
    {
        for(b = 0; b < 4; ++b)
        {
            if(m_block[a][b] == 0)
                ;
            else
            {
                for(c = b; (c > 0) && (m_block[a][c-1] == 0); --c)
                {
                    m_block[a][c-1] = m_block[a][c];
                    m_block[a][c] = 0;
                }
            }
        }
    }
}

void My2048::calcBlocksdown()
{
    int a, b, c;
    for(a = 0; a < 4; ++a)
    {
        for(b = 3; b >= 0; --b)
        {
            if(m_block[a][b] == 0)
                ;
            else
            {
                for(c = b - 1; c >= 0 ; --c)
                {
                    if(m_block[a][c] == 0)
                        ;
                    else if(m_block[a][c] == m_block[a][b])
                    {
                        m_block[a][b] += m_block[a][c];
                        m_score += m_block[a][b];
                        m_block[a][c] = 0;
                        b = c;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    for(a = 0; a < 4; ++a)
    {
        for(b = 3; b >= 0; --b)
        {
            if(m_block[a][b] == 0)
                ;
            else
            {
                for(c = b; (c < 3) && (m_block[a][c+1] == 0); ++c)
                {
                    m_block[a][c+1] = m_block[a][c];
                    m_block[a][c] = 0;
                }
            }
        }
    }
}

void My2048::calcBlocksleft()
{
    int a, b, c;
    for(a = 0; a < 4; ++a)
    {
        for(b = 0; b < 4; ++b)
        {
            if(m_block[b][a] == 0)
                ;
            else
            {
                for(c = b + 1; c < 4; ++c)
                {
                    if(m_block[c][a] == 0)
                        ;
                    else if(m_block[b][a] == m_block[c][a])
                    {
                        m_block[b][a] += m_block[c][a];
                        m_score += m_block[b][a];
                        m_block[c][a] = 0;
                        b = c;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    for(a = 0; a < 4; ++a)
    {
        for(b = 0; b < 4; ++b)
        {
            if(m_block[b][a] == 0)
                ;
            else
            {
                for(c = b; (c > 0) && (m_block[c-1][a] == 0); --c)
                {
                    m_block[c-1][a] = m_block[c][a];
                    m_block[c][a] = 0;
                }
            }
        }
    }
}

void My2048::calcBlocksright()
{
    int a, b, c;
    for(a = 0; a < 4; ++a)
    {
        for(b = 3; b >= 0; --b)
        {
            if(m_block[b][a] == 0)
                ;
            else
            {
                for(c = b - 1; c > 0; --c)
                {
                    if(m_block[c][a] == 0)
                        ;
                    else if(m_block[b][a] == m_block[c][a])
                    {
                        m_block[b][a] += m_block[c][a];
                        m_score += m_block[b][a];
                        m_block[c][a] = 0;
                        b = c;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    for(a = 0; a < 4; ++a)
    {
        for(b = 3; b >= 0; --b)
        {
            if(m_block[b][a] == 0)
                ;
            else
            {
                for(c = b; (c < 3) && (m_block[c+1][a] == 0); ++c)
                {
                    m_block[c+1][a] = m_block[c][a];
                    m_block[c][a] = 0;
                }
            }
        }
    }
}
