#include "chess_net.h"

//======================
#include <QDebug>
#define out qDebug()
//======================


chess_net::chess_net(QObject *parent)
    : QObject{parent}
{
    tcp=new tcp_conncet_string(this);

    //接收信息
    connect(tcp,&tcp_conncet_string::fa_finish_word,this,[=](){
        QString temp=tcp->read_word();

        if(temp.contains(flg_init))//初始化信息
        {
            bool first=temp.section(flg_init,0,0).toInt();
            emit fa_net_connect(!first);
        }
        else//落子信息
        {
            int x=temp.section(flg,0,0).toInt();
            int y=temp.section(flg,1,1).toInt();
            emit fa_net_pos(QPoint(x,y));
            out<<"接收=========";
        }
    });

    //连接成功——发送初始化信息——发送方
    connect(tcp,&tcp_conncet_string::fa_connect_socket,this,[=](){
        tcp->write_word(QString::number(is_first)+flg_init);//发出初始化数据（确认先后手）
        emit fa_finish_connect();
    });

    //连接成功——接收方
    connect(tcp,&tcp_conncet_string::fa_connect_server,this,[=](){
        emit fa_finish_connect();
    });

    //断开连接
    connect(tcp,&tcp_conncet_string::fa_disconnect,this,[=](){
        out<<"asdas";
        emit fa_disconnect();
//        &chess_net::fa_disconnect
    });

}

void chess_net::opne_net_so(QString IP, int port, bool first)
{
    is_first=first;
    tcp->open_socket(IP,port);
}

void chess_net::opne_net_se(int port)
{
    tcp->open_server(port);
}

void chess_net::close_se()
{
    tcp->close_server();
}

void chess_net::close_so()
{
    tcp->close_socket();
}

void chess_net::transfer_pos(QPoint pos)
{
    QString temp;
    temp=QString::number(pos.x())+flg+QString::number(pos.y());
    tcp->write_word(temp);
}
