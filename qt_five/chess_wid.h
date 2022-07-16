#ifndef CHESS_WID_H
#define CHESS_WID_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDialog>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QLabel>
#include <QVector>

#include "line_edit.h"
#include "push_button.h"

class chess_wid : public QDialog
{
    Q_OBJECT
public:
    explicit chess_wid(QWidget *parent = nullptr);

    void set_hint(QString str);

    QString get_ip();
    int get_port();

    void open_default();//默认
    void open_ask();//询问
    void open_connect();//选择连接
    void open_net();//连接成功

signals:
    emit void fa_butt_connect(bool is_first);//连接时选择先手或者后手
    emit void fa_butt_exit();//关闭对战
    emit void fa_port(int port);//返回端口
    emit void fa_ask(bool is_ok);//是否接收

protected:
    QVector<QWidget *> vec_hide;

    QLabel *label_hint;

    push_button *butt_variation;
    push_button *butt_first;
    push_button *butt_second;

    line_edit *edit_ip;
    line_edit *edit_port;
    line_edit *show_port;
    line_edit *show_ip;

    QString net_open="开启网络";
    QString net_exit="断开连接";

    QString first_first="先手";
    QString first_ok="接受对战";

    QString second_second="后手";
    QString second_no="拒绝对战";


    void hide_all();//隐藏全部控件
    void to_net(bool first);//发送连接信号

    void init_wid();
    void init_signal();






};

#endif // CHESS_WID_H
