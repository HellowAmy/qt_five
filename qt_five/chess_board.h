#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QObject>
#include <QPoint>
#include <QStringList>
#include <QVector>
#include <QStack>

//======================
#include <QDebug>
#define out qDebug()
//======================

class chess_board : public QObject
{
    Q_OBJECT

public:
    enum chess_state
    {
        en_black,
        en_white,
        en_empty
    };

public:
    static chess_board* return_this();//返回单例

    void set_size(int size);//设置棋盘线数量
    void init_vec();//初始化棋盘
    bool down_pos(QPoint pos,bool chess_black);//下棋
    bool down_back();//悔棋
    bool is_empty_vec();//判断棋盘是否为空(全部)
    bool is_empty_pos(QPoint pos);//判断棋盘是否为空(点)
    int get_size_line();//获取棋盘线数量
    bool get_is_black();//获取下一个是黑棋还是白棋
    void show_vec();//显示棋盘容器
    void show_vec(const QVector<QVector<chess_state>> vec);//显示棋盘容器
    void restart_board();//重启棋盘
    bool is_limit(QPoint pos);//判断是否超界，超界返回true
    bool is_equal(QPoint pos_1,QPoint pos_2);//判断棋子颜色是否相等

    chess_state get_flg(QPoint pos);//获取棋盘容器
    const QVector<QVector<chess_state>>& get_board();//读取棋盘标记容器内容
    QStack<QPoint> get_history();//获取历史记录

signals:

private:
    //私有化构造，创建静态对象
    chess_board();
    static chess_board self;

    QStack<QPoint> vec_history;//落子记录容器
    QVector<QVector<chess_state>> vec_board;//棋盘容器

    bool is_black=true;//先手黑棋
    int size_line=15;//棋盘线数量

    void set_flg(QPoint pos,chess_state flg);//设置棋盘容器标记
};
#endif // CHESS_BOARD_H

