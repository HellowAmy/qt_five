#include "chess_play.h"

chess_play::chess_play(QObject *parent)
    : QObject{parent}
{

}

chess_play::~chess_play()
{
    delete c_black;
    delete c_white;
    delete c_board;
    delete c_rules;
}

void chess_play::add_player
    (chess_hand *black,chess_hand *white,chess_board *board,chess_rules *rules)
{
    c_board=board;//棋盘
    c_rules=rules;//规则

    //先手
    c_black = black;
    c_black->set_black(true);
    c_black->set_board(c_board);

    //后手
    c_white = white;
    c_white->set_black(false);
    c_white->set_board(c_board);
}

void chess_play::down_pos(QPoint pos)
{
    //黑白落子
    if(c_board->is_limit(pos)
            && c_black->get_is_balck() == c_board->get_is_black()) c_black->down_pos(pos);
    else c_white->down_pos(pos);

    //落子后判断胜利并发信号
    if(c_rules->is_win(pos))
    {
        if(c_rules->is_black_win()) emit fa_win(true);
        else emit fa_win(false);
    }
}
