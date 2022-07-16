#include "chess_board.h"

chess_board chess_board::self;

chess_board *chess_board::return_this()
{
    return &self;
}

void chess_board::set_size(int size)
{
    size_line=size;
    init_vec();
}

bool chess_board::is_empty_vec()
{
    for(int x=0;x<size_line;x++)
    {
        for(int y=0;y<size_line;y++)
        {
            if(y!=0) return false;
        }
    }
    return true;
}

bool chess_board::is_empty_pos(QPoint pos)
{
    if(is_limit(pos))
    {
        if(get_flg(pos) == en_empty) return true;
    }

    return false;
}

int chess_board::get_size_line()
{
    return size_line;
}

bool chess_board::get_is_black()
{
    return is_black;
}

void chess_board::show_vec()
{
    for(int x=0;x<size_line;x++)
    {
        QStringList list;
        for(int y=0;y<size_line;y++)
        {
            if(vec_board[x][y] == en_empty) list<<"0";
            else if(vec_board[x][y] == en_black) list<<"1";
            else if(vec_board[x][y] == en_white) list<<"2";
        }
        out<<list;
    }
}

void chess_board::show_vec(const QVector<QVector<chess_state>> vec)
{
    for(int x=0;x<size_line;x++)
    {
        QStringList list;
        for(int y=0;y<size_line;y++)
        {
            if(vec[x][y] == en_empty) list<<"0";
            else if(vec[x][y] == en_black) list<<"1";
            else if(vec[x][y] == en_white) list<<"2";
        }
        out<<list;
    }
}

void chess_board::restart_board()
{
    vec_board.clear();
    is_black=true;

    init_vec();
}

bool chess_board::is_limit(QPoint pos)
{
    if(pos.x()<size_line && pos.y()<size_line
            && pos.x()>=0 && pos.y()>=0) return true;
    else return false;
}

bool chess_board::is_equal(QPoint pos_1, QPoint pos_2)
{
    //判断棋子相等
    if(get_flg(pos_1) == get_flg(pos_2)) return true;
    else return false;
}

const QVector<QVector<chess_board::chess_state> > &chess_board::get_board()
{
    return vec_board;
}

QStack<QPoint> chess_board::get_history()
{
    return vec_history;
}

void chess_board::set_flg(QPoint pos, chess_state flg)
{
    vec_board[pos.x()][pos.y()] = flg;
}

chess_board::chess_state chess_board::get_flg(QPoint pos)
{
    return vec_board[pos.x()][pos.y()];
}

chess_board::chess_board()
{
    init_vec();//数组初始化
}

void chess_board::init_vec()
{
    //数组初始化
    QVector<chess_state> temp;
    for(int i=0;i<size_line;i++) temp.push_back(chess_state::en_empty);
    for(int i=0;i<size_line;i++) vec_board.push_back(temp);
}

bool chess_board::down_pos(QPoint pos, bool chess_black)
{
    //判断棋盘容器是否为空
    if(is_empty_pos(pos)==true && chess_black==is_black)
    {
        if(is_black==true) set_flg(pos,en_black);
        else set_flg(pos,en_white);

        vec_history.push(pos);//加入历史
        is_black=!is_black;//反转棋子颜色
        return true;
    }
    else return false;
}

bool chess_board::down_back()
{
    if(vec_history.empty() == false)
    {
        //移除栈并回复棋盘原状
        QPoint pos=vec_history.pop();
        set_flg(pos,en_empty);

        is_black=!is_black;//反转棋子颜色
        return true;
    }
    else return false;
}
