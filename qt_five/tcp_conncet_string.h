#ifndef TCP_CONNCET_STRING_H
#define TCP_CONNCET_STRING_H

#include <QObject>

#include <QTcpSocket>
#include <QTcpServer>

#include <QQueue>

#define _WORD_IN_ "##%@*__WORD_IN__*@%##"
#define _WORD_RETURN_ "##%@*__WORD_RETURN__*@%##"
#define _WORD_END_ "##%@*__WORD_END__*@%##"

//======================
#include <QDebug>
#define out qDebug()
//======================

//Qt 6.2.4 版本
class tcp_conncet_string : public QObject
{
    Q_OBJECT
public:
    explicit tcp_conncet_string(QObject *parent = nullptr);

    //开启连接
    void open_socket(QString IP,int port);
    void open_server(int port);

    //关闭服务器连接
    void close_server();
    void close_socket();

    void write_word(QString word);//参数:文字
    QString read_word();//获取文字

signals:

    //连接成功
    emit void fa_connect_socket();
    emit void fa_connect_server();

    emit void fa_finish_word();//完成发送
    emit void fa_disconnect();//断开连接

protected:
    QTcpSocket *socket_so;//接收端套接字
    QTcpSocket *socket_se;//发送端套接字
    QTcpServer *server_connect;//请求接收套接字
//    QTcpSocket *socket_write;//发送端套接字

private:
    QString str_temp;
    QQueue<QString> queue_word;//发送word队列


    void read_shift(QTcpSocket &socket);//内容接收中转站

    void write_word_transfer(QTcpSocket *socket);
    void write_ask(QTcpSocket *socket);
};

#endif // TCP_CONNCET_STRING_H
