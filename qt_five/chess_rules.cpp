#include "chess_rules.h"

chess_rules::chess_rules(QObject *parent)
    : QObject{parent}
{

}

void chess_rules::set_borad(chess_board *board)
{
    c_board=board;
}

bool chess_rules::is_win(QPoint pos)
{
    //胜利规则
    if(this->return_count(pos,QPoint(-1,0),QPoint(1,0))+1 >= sum_five
            || this->return_count(pos,QPoint(0,-1),QPoint(0,1))+1 >= sum_five
            || this->return_count(pos,QPoint(-1,-1),QPoint(1,1))+1 >= sum_five
            || this->return_count(pos,QPoint(1,-1),QPoint(-1,1))+1 >= sum_five)
    {
        pos_win=pos;//标记胜利后的点
        return true;
    }
    else return false;
}

bool chess_rules::is_black_win()
{
    if(c_board->get_flg(pos_win) == chess_board::en_black) return true;
    else return false;
}

int chess_rules::return_sum(QPoint pos, QPoint move,int sum)
{
    //返回一侧连子数
    if(c_board->get_flg(pos) == chess_board::en_empty) return 0;
    if(!is_limit(pos,move) && is_equal(pos,move))
    {
        sum++;
        pos+=move;
        return return_sum(pos,move,sum);
    }
    else return sum;
}

int chess_rules::return_count(QPoint pos, QPoint left, QPoint right)
{
    return return_sum(pos,left)+return_sum(pos,right);//返回一线连子数
}

bool chess_rules::is_limit(QPoint pos, QPoint move)
{
    int size=c_board->get_size_line()-1;

    //判断棋盘边界
    pos+=move;
    if((pos.x()<0 || pos.y()<0) || (pos.x()>size || pos.y()>size)) return true;
    else return false;
}

bool chess_rules::is_equal(QPoint pos, QPoint move)
{
    //判断棋子相等
    if(is_limit(pos,move)) return false;
    else
    {
        QPoint temp=pos+move;
        if(c_board->get_flg(pos) == c_board->get_flg(temp)) return true;
        else return false;
    }
}

