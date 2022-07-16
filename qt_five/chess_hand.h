#ifndef CHESS_HAND_H
#define CHESS_HAND_H

#include <QObject>

#include "chess_board.h"


class chess_hand : public QObject
{
    Q_OBJECT

public:
    explicit chess_hand(QObject *parent = nullptr);
    ~chess_hand();

    bool down_pos(QPoint pos);//落子
    void down_back();//悔棋申请
    void is_lose();//认输
    void set_black(bool black);//是否先手
    bool get_is_balck();//返回先手标记
    void set_board(chess_board *borad);//设置棋盘

signals:
    emit void fa_back(QPrivateSignal);
    emit void fa_lose(QPrivateSignal);

private:
    chess_board *c_borad;

    bool is_black=true;
};

#endif // CHESS_HAND_H
