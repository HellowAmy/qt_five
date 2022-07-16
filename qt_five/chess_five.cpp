#include "chess_five.h"

chess_five::chess_five(QWidget *parent)
    : QWidget{parent}
{
    enum_play=en_self;

    this->resize(parent->size());

    chess_board *board=chess_board::return_this();

    chess_rules *rules=new chess_rules(this);
    rules->set_borad(board);

    chess_view *view=new chess_view(this);
    view->set_borad(board);

    chess_ai *ai=new chess_ai(this);
    ai->set_board(board);

    chess_hand *h1=new chess_hand(this);
    chess_hand *h2=new chess_hand(this);

    chess_play *play=new chess_play(this);
    play->add_player(h1,h2,board,rules);

    chess_net *net=new chess_net(this);
//    net->opne_net_se(v_port);//===================================

    chess_wid *wid=new chess_wid(this);
    wid->resize(200,400);
    wid->show();
//    wid->set_show_port(v_port);//===================================

//    chess_net *net=new chess_net(this);
//    net->opne_net_so("127.0.0.1",8888);
//    net->opne_net_se(8888);




//本地信号===================================================================

    //落子点击信号
    connect(view,&chess_view::fa_press_pos,this,[=](QPoint pos){

        //自娱自乐
        if(enum_play == en_self) play->down_pos(pos);

        //玩家对战ai
        else if(enum_play == en_ai)
        {
            if(is_first == board->get_is_black()) play->down_pos(pos);//ai下棋

            //延时——增加体验
            if(board->get_is_black() == !is_first)
            {
                //ai计算所需时间，并延时
                QDateTime t_begin=QDateTime::currentDateTime();
                QPoint temp = ai->return_high_pos(is_first);
                QDateTime t_end=QDateTime::currentDateTime();

                int space=t_begin.msecsTo(t_end);
                if(200-space > 0)
                {
                    QTimer::singleShot(200-space,this,[=](){
                        play->down_pos(temp);
                    });
                }
                else play->down_pos(temp);
            }
        }

        //玩家对战玩家（局域网）
        else if(enum_play == en_net)
        {
            //双方可点击控制
            if(is_first == board->get_is_black())
            {
                play->down_pos(pos);//落子
                emit fa_down_pos(pos);//将落子位置通知对方
            }
        }

        view->update();
    });

    //胜利信号
    connect(play,&chess_play::fa_win,this,[=](bool is_black){
        if(is_black) out<<"黑色胜利";
        else out<<"白色胜利";
        board->restart_board();
        view->update();
    });

    //开启网络模式——接收port
    connect(wid,&chess_wid::fa_port,this,[=](int port){
        net->opne_net_se(port);
    });

    //断开连接
    connect(net,&chess_net::fa_disconnect,this,[=](){
        wid->open_default();//切换默认窗口
        board->restart_board();
        view->update();
        out<<"断开";
    });

//本地信号===================================================================

//双方信号===================================================================

    //关闭连接
    connect(wid,&chess_wid::fa_butt_exit,this,[=](){
        net->close_se();
        net->close_so();
        out<<"断开===========";
    });

    //连接成功
    connect(net,&chess_net::fa_finish_connect,this,[=](){
        wid->set_hint("==连接成功==");
//        board->restart_board();
        out<<"连接成功=";
    });

    //落子后通过网络传输到
    connect(this,&chess_five::fa_down_pos,this,[=](QPoint pos){
        net->transfer_pos(pos);
        out<<"发送棋子="<<pos;
    });

    //接收棋子
    connect(net,&chess_net::fa_net_pos,this,[=](QPoint pos){
        play->down_pos(pos);
        view->update();
        out<<"接收棋子并落子="<<pos;
    });

//双方信号===================================================================

//发送方信号===================================================================

    //网络连接信号——主动连接方
    connect(this,&chess_five::fa_open_net,this,[=](QString IP,int port,bool first){
        enum_play=en_net;
        is_first=first;//设置先手或者后手——连接方
        net->opne_net_so(IP,port,first);
        wid->set_hint("==发送对战请求==");
        out<<"主机连接成功";
    });

    //连接按钮——判断先后手
    connect(wid,&chess_wid::fa_butt_connect,this,[=](bool first){
        is_first=first;
        board->restart_board();
        emit this->fa_open_net(wid->get_ip(),wid->get_port(),is_first);
    });

//发送方信号===================================================================

//接收方信号===================================================================

    //初始化信息——被连接方——首次连接
    connect(net,&chess_net::fa_net_connect,this,[=](bool first){
        enum_play=en_net;
        is_first=first;//设置先手或者后手——被连接方
        wid->open_ask();//询问是否同意

        board->restart_board();
        if(is_first == true) wid->set_hint("开始对局？(先手)");
        else wid->set_hint("开始对局？(后手)");

        out<<"主机被连接";
    });


    connect(wid,&chess_wid::fa_ask,this,[=](bool first){

        out<<"触发询问";
        if(first == true)
        {
            wid->set_hint("==对局开始==");
            wid->open_net();
        }
        else
        {
            wid->open_default();
            net->close_so();
            net->close_se();
        }
    });


    //是否同意连接
//    connect(wid,&chess_wid::fa_ask,this,[=](bool first){
//        if(first == true)
//        {
//            emit net->fa_net_connect();
//            wid->set_hint("==对局开始==");
//        }

//        else net->close_so();

//        enum_play=en_net;
//        is_first=first;//设置先手或者后手——被连接方
//        wid->open_net();

//        out<<"主机被连接";
//    });

//接收方信号===================================================================


}
