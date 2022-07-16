#include "chess_hand.h"

chess_hand::chess_hand(QObject *parent)
    : QObject{parent}
{

}

chess_hand::~chess_hand()
{
    delete c_borad;
}

bool chess_hand::down_pos(QPoint pos)
{
    return c_borad->down_pos(pos,is_black);
}

void chess_hand::down_back()
{
    emit fa_back(QPrivateSignal());
}

void chess_hand::is_lose()
{
    emit fa_lose(QPrivateSignal());
}

void chess_hand::set_black(bool black)
{
    is_black=black;
}

bool chess_hand::get_is_balck()
{
    return is_black;
}

void chess_hand::set_board(chess_board *borad)
{
    c_borad=borad;
}


