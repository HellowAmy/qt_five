#ifndef CHESS_NET_H
#define CHESS_NET_H

#include <QObject>
#include <QPoint>

#include "tcp_conncet_string.h"

class chess_net : public QObject
{
    Q_OBJECT
public:
    explicit chess_net(QObject *parent = nullptr);

    void opne_net_so(QString IP,int port,bool first);
    void opne_net_se(int port);
    void close_se();
    void close_so();

    void transfer_pos(QPoint pos);

signals:
    emit void fa_net_connect(bool is_first);//发送接收的初始化信息
    emit void fa_net_pos(QPoint pos);//发送接收的落子点
    emit void fa_disconnect();//断开连接
    emit void fa_finish_connect();//完成连接，双发都触发

protected:
    tcp_conncet_string *tcp;

    QString flg="||";
    QString flg_init="##";
    bool is_first=true;

};

#endif // CHESS_NET_H
