#ifndef CHESS_PLAY_H
#define CHESS_PLAY_H

#include <QObject>

#include "chess_hand.h"
#include "chess_board.h"
#include "chess_rules.h"

class chess_play : public QObject
{
    Q_OBJECT
public:
    explicit chess_play(QObject *parent = nullptr);
    ~chess_play();

    //加入玩家和棋盘
    void add_player
        (chess_hand *black, chess_hand *white,chess_board *board,chess_rules *rules);

    //下棋
    void down_pos(QPoint pos);

signals:
    emit void fa_win(bool is_black);

private:
    chess_hand *c_black;
    chess_hand *c_white;

    chess_board *c_board;
    chess_rules *c_rules;
};

#endif // CHESS_PLAY_H
