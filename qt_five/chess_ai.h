#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <QObject>

#include "chess_board.h"

class chess_ai : public QObject
{
    Q_OBJECT

public:
    //判断活子结构体
    struct core
    {
        int sum;
        bool is_dead;
    };

    //组合落点及分数结构体
    struct core_pos
    {
        QPoint pos;
        int sum;
    };

public:
    explicit chess_ai(QObject *parent = nullptr);

    virtual QPoint return_high_pos(bool is_black);//返回最佳评分点
    void set_board(chess_board *borad);//设置棋盘

signals:

private:
    chess_board *c_board;//棋盘
    QVector<QVector<chess_board::chess_state>> vec_board;//复制的可修改棋盘

    QVector<core_pos> vec_score(bool black);//获取棋点评分容器
    QVector<QPoint> vec_no_empty();//获取有效空点棋盘容器

    void vec_sort(QVector<core_pos> &vec,int max=0);//容器排序
    void is_empty_round(QPoint pos,QVector<QPoint>& vec);//判断点周围是否为空

    core return_count_dead(QPoint pos,QPoint left,QPoint right);//统计点两侧活子数
    core return_sum_dead(QPoint pos,QPoint move);//统计点一侧活子数
    int return_sum(QPoint pos,QPoint move,int sum=0);//返回一侧相同棋子数量

    int score_height(QPoint pos);//棋盘点评分结果-自身
    int score_height_rival(QPoint pos);//棋盘点评分结果-对手

    int return_score(core score);//评分系统-自身
    int return_score_rival(core score);//评分系统-对手
    int score_sum(QPoint pos,bool black);//棋盘评分
};

#endif // CHESS_AI_H
