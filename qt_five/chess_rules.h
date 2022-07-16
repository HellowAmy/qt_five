#ifndef CHESS_RULES_H
#define CHESS_RULES_H

#include <QObject>

#include "chess_board.h"

class chess_rules : public QObject
{
    Q_OBJECT
public:
    explicit chess_rules(QObject *parent = nullptr);

    void set_borad(chess_board *board);//获取棋盘指针
    bool is_win(QPoint pos);//落子后判断是否胜利
    virtual bool is_black_win();//是否为黑方胜利

signals:

private:
    chess_board *c_board;

    QPoint pos_win;
    int sum_five=5;//连成五子

    int return_sum(QPoint pos,QPoint move,int sum=0);//统计一侧相同棋子数量
    int return_count(QPoint pos,QPoint left,QPoint right);//统计一排相同棋子数量
    bool is_limit(QPoint pos,QPoint move);//判断棋盘界限
    bool is_equal(QPoint pos,QPoint move);//判断棋子颜色是否相等
};

#endif // CHESS_RULES_H
