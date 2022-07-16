#include "tcp_conncet_string.h"

tcp_conncet_string::tcp_conncet_string(QObject *parent)
    : QObject{parent}
{
    server_connect=new QTcpServer(this);
//    socket_write=new QTcpSocket(this);
    socket_so=new QTcpSocket(this);
    socket_se=new QTcpSocket(this);

//    server_connect->setMaxPendingConnections(1);

}

void tcp_conncet_string::open_socket(QString IP, int port)
{
    socket_so->connectToHost(IP,port);//寻找连接对象
//    socket_write=socket_so;//获取发送套接字

    //创建连接并获取socket
    connect(socket_so,&QTcpSocket::connected,this,[=](){
        emit fa_connect_socket();

        //传送内容信号
        connect(socket_so,&QTcpSocket::readyRead,this,[=](){
//            read_shift(*socket_so);

            str_temp=socket_so->readAll();
            emit fa_finish_word();
        });

//        connect(socket_write,&QTcpSocket::disconnected,this,[=](){
//            delete socket_write;
//            socket_write=new QTcpSocket(this);
//            emit fa_disconnect();
//            out<<"close";
//        });

//        connect(socket_so,&QTcpSocket::errorOccurred,this,
//                [=](QAbstractSocket::SocketError error){
//            out<<error;
//        });

        connect(socket_so,&QTcpSocket::disconnected,this,[=](){
            delete socket_so;
            socket_so=new QTcpSocket(this);
            emit fa_disconnect();
        });


    });
}

void tcp_conncet_string::open_server(int port)
{
//    if(server_connect->isListening()) server_connect->close();

    server_connect->listen(QHostAddress::Any,port);

    //创建连接并获取socket
    connect(server_connect,&QTcpServer::newConnection,this,[=](){
        socket_se=server_connect->nextPendingConnection();//服务端接收socket

        //传送内容信号
        connect(socket_se,&QTcpSocket::readyRead,this,[=](){
//                out<<"144="<<socket_se->state();
//                read_shift(*socket_se);

//            socket_se=server_connect->nextPendingConnection();
            str_temp=socket_se->readAll();
            emit fa_finish_word();
        },Qt::QueuedConnection);//,Qt::QueuedConnection

        connect(socket_se,&QTcpSocket::disconnected,this,[=](){
                delete socket_se;
                socket_se=new QTcpSocket(this);

//                int tt=0;
                delete server_connect;
                server_connect=new QTcpServer(this);

//            server_connect->close();
            emit fa_disconnect();

        },Qt::QueuedConnection);

//            connect(socket_write,&QTcpSocket::disconnected,this,[=](){
//                delete socket_write;
//                socket_write=new QTcpSocket(this);

//                emit fa_disconnect();
//            out<<"close";
//            });

    },Qt::QueuedConnection);








}

void tcp_conncet_string::close_server()
{
//    server_connect->close();
    out<<"关闭se====";
}

void tcp_conncet_string::close_socket()
{
//    if(socket_so->state() == QAbstractSocket::ConnectedState)
        socket_so->disconnectFromHost();

//    if(socket_se->state() == QAbstractSocket::ConnectedState)
        socket_se->disconnectFromHost();

//        socket_write->disconnectFromHost();

        out<<"关闭so====";

//    if(socket_write->state() == QAbstractSocket::ConnectedState)
//        socket_write->disconnectFromHost();
}

void tcp_conncet_string::write_word(QString word)
{

    if(socket_so->state() == QAbstractSocket::ConnectedState)
        socket_so->write(word.toUtf8());

    if(socket_se->state() == QAbstractSocket::ConnectedState)
        socket_se->write(word.toUtf8());


//    socket_write->write(word.toUtf8());
//    queue_word.enqueue(word);
//    if(queue_word.size() == 1) write_ask(socket_write);//多次加入队列只发送一次请求
}

QString tcp_conncet_string::read_word()
{
    return str_temp;
}



void tcp_conncet_string::read_shift(QTcpSocket &socket)
{
    out<<"reso="<<socket.state();
    str_temp=socket.readAll();
    emit fa_finish_word();

//    //接收内容
//    if(temp.contains(_WORD_END_))
//    {
//        str_temp=temp.section(_WORD_END_,0,0);
//        emit fa_finish_word();

//        write_word_transfer(socket);//继续发送
//    }

//    if(temp == _WORD_IN_) socket->write(_WORD_RETURN_);//确认接收——se
//    if(temp == _WORD_RETURN_) write_word_transfer(socket);//接收反馈，开始发送——so
}

void tcp_conncet_string::write_word_transfer(QTcpSocket *socket)
{
    //队列不为空发送word
    if(queue_word.isEmpty() == false)
    {
        QString temp=queue_word.dequeue();//发送后移出队列
        socket->write(temp.toUtf8());
        socket->write(_WORD_END_);
    }
}

void tcp_conncet_string::write_ask(QTcpSocket *socket)
{
    socket->write(_WORD_IN_);
}

