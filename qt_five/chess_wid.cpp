#include "chess_wid.h"


//======================
#include <QDebug>
#define out qDebug()
//======================

chess_wid::chess_wid(QWidget *parent)
    : QDialog{parent}
{

    init_wid();//初始化界面
    init_signal();//初始化信号

    //获取自身IP地址
    QString local_ip;
    for(auto address : QNetworkInterface::allAddresses())
    {
        //排除IPV6，排除回环地址
        if(address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress::LocalHost) local_ip= address.toString();//地址转文本
    }
    show_ip->setText(local_ip);

    open_default();//默认界面
}

void chess_wid::set_hint(QString str)
{
    label_hint->setText(str);
}

QString chess_wid::get_ip()
{
    return edit_ip->text();
}

int chess_wid::get_port()
{
    return edit_port->text().toInt();
}

void chess_wid::open_connect()
{
    hide_all();

    //显示自身ip
    show_ip->show();
    show_ip->setEnabled(false);
    show_ip->move(0,0);

    //显示自身port
    show_port->show();
    show_port->setEnabled(false);
    show_port->move(0,0 + 30 * 1);

    //显示可输入对方ip
    edit_ip->show();
    edit_ip->move(0,0 + 30 * 2);

    //显示可输入对方port
    edit_port->show();
    edit_port->move(0,0 + 30 * 3);

    //显示确认按键——先手
    butt_first->show();
    butt_first->setText(first_first);
    butt_first->set_txt(first_first);
    butt_first->move(0,0 + 30 * 6);

    //显示确认按键——后手
    butt_second->show();
    butt_second->setText(second_second);
    butt_second->set_txt(second_second);
    butt_second->move(0,0 + 30 * 7);

    //显示提示窗口
    label_hint->show();
    label_hint->move(0,0 + 30 * 8 + 10);
}

void chess_wid::open_net()
{
    hide_all();

    //显示断开按钮
    butt_variation->show();
    butt_variation->move(0,0);
    butt_variation->setText(net_exit);
    butt_variation->set_txt(net_exit);

    //显示提示窗口
    label_hint->show();
    label_hint->move(0,0 + 30 * 1 + 10);
}

void chess_wid::open_default()
{
    hide_all();

    //显示网络开启按钮
    butt_variation->show();
    butt_variation->move(0,0);
    butt_variation->setText(net_open);
    butt_variation->set_txt(net_open);
    butt_variation->move(0,0);

    //显示输入的port
    show_port->show();
    show_port->move(0,0 + 30 * 1);
    show_port->setEnabled(true);
}

void chess_wid::open_ask()
{
    hide_all();

    //同意按钮
    butt_first->show();
    butt_first->setText(first_ok);
    butt_first->set_txt(first_ok);
    butt_first->move(0,0);

    //拒绝按钮
    butt_second->show();
    butt_second->setText(second_no);
    butt_second->set_txt(second_no);
    butt_second->move(0,0 + 30 * 1);

    //显示提示窗口
    label_hint->show();
    label_hint->move(0,0 + 30 * 2 + 10);
}

void chess_wid::init_wid()
{
    //提示框
    label_hint = new QLabel(this);
    label_hint->setText("提示");
    label_hint->setFont(QFont("楷体",13));
    label_hint->setFrameShape(QFrame::Box);
    label_hint->resize(200,60);
    label_hint->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    //输入框
    show_ip=new line_edit(this);
    show_ip->to_load(":/map/wid/edit_1.png");

    show_port=new line_edit(this);
    show_port->setText("8080");
    show_port->to_load(":/map/wid/edit_1.png");

    edit_ip=new line_edit(this);
    edit_ip->to_load(":/map/wid/edit_1.png");
    edit_ip->setText("127.0.0.1");

    edit_port=new line_edit(this);
    edit_port->to_load(":/map/wid/edit_1.png");
    edit_port->setText("8080");

    //按钮
    butt_variation=new push_button(this);
    butt_variation->open_normal(":/map/wid/butt_normal.png");
    butt_variation->open_enter(":/map/wid/butt_enter.png");
    butt_variation->open_press(":/map/wid/butt_press.png");
    butt_variation->open();

    butt_first=new push_button(this);
    butt_first->open_normal(":/map/wid/butt_normal.png");
    butt_first->open_enter(":/map/wid/butt_enter.png");
    butt_first->open_press(":/map/wid/butt_press.png");
    butt_first->open();

    butt_second=new push_button(this);
    butt_second->open_normal(":/map/wid/butt_normal.png");
    butt_second->open_enter(":/map/wid/butt_enter.png");
    butt_second->open_press(":/map/wid/butt_press.png");
    butt_second->open();

    vec_hide.push_back((QWidget *)label_hint);
    vec_hide.push_back((QWidget *)show_ip);
    vec_hide.push_back((QWidget *)show_port);
    vec_hide.push_back((QWidget *)edit_ip);
    vec_hide.push_back((QWidget *)edit_port);
    vec_hide.push_back((QWidget *)butt_variation);
    vec_hide.push_back((QWidget *)butt_first);
    vec_hide.push_back((QWidget *)butt_second);

}

void chess_wid::init_signal()
{
    //可变信号——界面切换
    connect(butt_variation,&push_button::clicked,this,[=](){

        //点击开启网络——选择连接界面
        if(butt_variation->text() == net_open)
        {
            open_connect();
            emit fa_port(show_port->text().toInt());//返回要连接的port
            out<<"点击net_open";
        }

        //点击断开——默认界面
        else if(butt_variation->text() == net_exit)
        {
            open_default();
            emit fa_butt_exit();//关闭对战
            out<<"点击net_exit";
        }
    });

    //发送确认信号——先手
    connect(butt_first,&push_button::clicked,this,[=](){
        //选择先手
        if(butt_first->text() == first_first) to_net(true);

        //选择接受对战
        else if(butt_first->text() == first_ok) emit fa_ask(true);
    });

    //发送确认信号——后手
    connect(butt_second,&push_button::clicked,this,[=](){
        //选择先手
        if(butt_second->text() == second_second) to_net(false);

        //选择接受对战
        else if(butt_second->text() == second_no) emit fa_ask(false);
    });
}

void chess_wid::hide_all()
{
    for(const auto &a:vec_hide)
    {
        a->hide();
    }
}

void chess_wid::to_net(bool first)
{
    out<<"inhh================";
    if(edit_port->text() != show_port->text() || edit_ip->text() != "127.0.0.1")
    {
        open_net();
        emit fa_butt_connect(first);
    }
    else
    {
        if(first == true) label_hint->setText("错误:端口相等(后手)");
        else label_hint->setText("错误:端口相等(先手)");
    }
}
