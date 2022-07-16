#include "chess_ai.h"

chess_ai::chess_ai(QObject *parent)
    : QObject{parent}
{

}

QPoint chess_ai::return_high_pos(bool is_black)
{
    vec_board=c_board->get_board();

    //计算目前最优落子点
    QVector<core_pos> vec_co=vec_score(is_black);
    vec_sort(vec_co);

    return vec_co.begin()->pos;
}

void chess_ai::set_board(chess_board *borad)
{
    c_board=borad;
}

QVector<chess_ai::core_pos> chess_ai::vec_score(bool black)
{
    core_pos co;
    co.pos=QPoint(0,0);
    co.sum=0;

    QVector<core_pos> vec_co;
    QVector<QPoint> vec_pos=vec_no_empty();//获取有效空点位

    for(QVector<QPoint>::iterator it=vec_pos.begin();it!=vec_pos.end();it++)
    {
        if(c_board->is_limit(*it))
        {
            co.pos=*it;
            co.sum=score_sum(*it,black);//进行评分
            vec_co.push_back(co);
        }
    }

    return vec_co;
}

void chess_ai::vec_sort(QVector<chess_ai::core_pos> &vec, int max)
{
    //容器排序
    for(int i=0;i<vec.count();i++)
    {
        for(int j=i;j<vec.count();j++)
        {
            if(vec[i].sum<vec[j].sum)
            {
                core_pos temp=vec[j];
                vec[j]=vec[i];
                vec[i]=temp;
            }
        }
    }

    //收缩容器
    if(max > 0)
    {
        int count=0;
        if(max < vec.count()) count=max;
        else count=vec.count();

        QVector<chess_ai::core_pos>::iterator it=vec.begin();
        for(int temp=0;temp<count;temp++) it++;

        QVector<chess_ai::core_pos> vec_temp(vec.begin(),it);
        vec=vec_temp;
    }
}

QVector<QPoint> chess_ai::vec_no_empty()
{
    //返回不为空的棋盘容器
    QVector<QPoint> vec;
    for(int x=0;x<c_board->get_size_line();x++)
    {
        for(int y=0;y<c_board->get_size_line();y++)
        {
            if(c_board->is_limit(QPoint(x,y))
                    && vec_board[x][y] != chess_board::en_empty)
            {
                is_empty_round(QPoint(x,y),vec);
            }
        }
    }
    return vec;
}

void chess_ai::is_empty_round(QPoint pos,QVector<QPoint> &vec)
{
    //周围是否为空
    for(int x=-1;x<=1;x++)
    {
        for(int y=-1;y<=1;y++)
        {
            if(x!=0 || y!=0)
            {
                QPoint temp = pos+QPoint(x,y);
                if(c_board->is_limit(temp)
                        && vec_board[temp.x()][temp.y()] == chess_board::en_empty)
                {
                    vec.push_back(temp);
                }
            }
        }
    }
}

int chess_ai::score_sum(QPoint pos, bool black)
{
    //自身评分
    if(black == true) vec_board[pos.x()][pos.y()]=chess_board::en_black;
    else vec_board[pos.x()][pos.y()]=chess_board::en_white;

    int begin=score_height(pos);//评分
    vec_board[pos.x()][pos.y()]=chess_board::en_empty;

    //对手评分
    if(black == false) vec_board[pos.x()][pos.y()]=chess_board::en_black;
    else vec_board[pos.x()][pos.y()]=chess_board::en_white;

    int end=score_height_rival(pos);//评分
    vec_board[pos.x()][pos.y()]=chess_board::en_empty;

    return begin+end;
}

int chess_ai::score_height_rival(QPoint pos)
{
    //统计连子数量且判断是否活子
    core co_heri=return_count_dead(pos,QPoint(-1,0),QPoint(1,0));
    core co_vert=return_count_dead(pos,QPoint(0,-1),QPoint(0,1));
    core co_right_up=return_count_dead(pos,QPoint(-1,-1),QPoint(1,1));
    core co_left_up=return_count_dead(pos,QPoint(1,-1),QPoint(-1,1));

    int sum=return_score_rival(co_heri)+return_score_rival(co_vert)
            +return_score_rival(co_right_up)+return_score_rival(co_left_up);

    return sum;
}

int chess_ai::return_score_rival(chess_ai::core score)
{
    //评分系统
    int sum=0;
    if(score.is_dead==false)
    {
        switch (score.sum)
        {
            case 5: sum+=1000000; break;
            case 4: sum+=100000; break;
            case 3: sum+=10000; break;
            case 2: sum+=1000; break;
            case 1: sum+=100; break;
            default:sum+=100000; break;
        }
        sum/=2;
    }
    else
    {
        switch (score.sum)
        {
            case 5: sum+=1000000; break;
            case 4: sum+=100000; break;
            case 3: sum+=1000/2; break;
            case 2: sum+=100/2; break;
            case 1: sum+=10/2; break;
            default:sum+=1000000; break;
        }
        sum/=2;
    }
    return sum;
}

chess_ai::core chess_ai::return_count_dead(QPoint pos, QPoint left, QPoint right)
{
    core co;
    co.sum=0;
    co.is_dead=true;

    core co_left=return_sum_dead(pos,left);
    core co_right=return_sum_dead(pos,right);

    //双方向统计判断
    co.sum=co_left.sum+co_right.sum +1;
    if(co_left.is_dead == false && co_right.is_dead == false) co.is_dead=false;

    return co;
}

chess_ai::core chess_ai::return_sum_dead(QPoint pos, QPoint move)
{
    core co;
    co.sum=0;
    co.is_dead=true;

    //单方向统计判断
    co.sum=return_sum(pos,move);
    for(int temp=0;temp<co.sum+1;temp++)
    {
        if(c_board->is_limit(pos+move)) pos+=move;
    }

    if(vec_board[pos.x()][pos.y()] == chess_board::en_empty) co.is_dead=false;
    return co;
}

int chess_ai::score_height(QPoint pos)
{
    //统计连子数量且判断是否活子
    core co_heri=return_count_dead(pos,QPoint(-1,0),QPoint(1,0));
    core co_vert=return_count_dead(pos,QPoint(0,-1),QPoint(0,1));
    core co_right_up=return_count_dead(pos,QPoint(-1,-1),QPoint(1,1));
    core co_left_up=return_count_dead(pos,QPoint(1,-1),QPoint(-1,1));

    //返回评分四个方向的评分情况
    int sum=return_score(co_heri)+return_score(co_vert)
            +return_score(co_right_up)+return_score(co_left_up);

    return sum;
}

int chess_ai::return_score(chess_ai::core score)
{
    //评分系统
    int sum=0;
    if(score.is_dead==false)
    {
        switch (score.sum)
        {
            case 5: sum+=1000000; break;
            case 4: sum+=100000; break;
            case 3: sum+=10000; break;
            case 2: sum+=1000; break;
            case 1: sum+=100; break;
            default:sum+=100000; break;
        }
    }
    else
    {
        switch (score.sum)
        {
            case 5: sum+=1000000; break;
            case 4: sum+=1000/2; break;
            case 3: sum+=100/2; break;
            case 2: sum+=10/2; break;
            case 1: sum+=1; break;
            default:sum+=1000000; break;
        }
    }
    return sum;
}

int chess_ai::return_sum(QPoint pos, QPoint move,int sum)
{
    QPoint temp=pos+move;

    //返回一侧连子数
    if(vec_board[pos.x()][pos.y()] == chess_board::en_empty) return 0;

    //如果相邻的棋子为同颜色则计数
    if(c_board->is_limit(pos+move)
            && vec_board[pos.x()][pos.y()] == vec_board[temp.x()][temp.y()])
    {
        sum++;
        pos+=move;
        return return_sum(pos,move,sum);
    }
    else return sum;
}
