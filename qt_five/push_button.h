#ifndef M_PUSH_H
#define M_PUSH_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QRect>
#include <QPixmap>
#include <QBitmap>
#include <QEvent>
#include <QFont>

#include <QDebug>
#define cout qDebug()

class push_button : public QPushButton
{
    Q_OBJECT

public:
    explicit push_button(QWidget *parent = nullptr) : QPushButton(parent){}

    push_button(QString normal,QString press,QString enter,QWidget *parent = nullptr)
        : QPushButton(parent),tu_normal(normal),tu_press(press),tu_enter(enter){}

    void set_txt(QString txt);
    void open(int kuan=0,int gao=0);

    void open_normal(QString tu_ru);
    void open_enter(QString tu_ru);
    void open_press(QString tu_ru);

signals:

private:
    void tu_zhong(QString tu);
    void tu_load(QString tu);

    //重绘
    QPixmap tu;
    QRect ban;


    QString tu_normal;
    QString tu_press;
    QString tu_enter;

    QString tu_zong;

    QString v_txt;

    bool la_shen=false;
    bool is_open=false;

    int kuan;
    int gao;
    int line=2;

protected:
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEnterEvent *event) override;
    void mousePressEvent(QMouseEvent *) override;
    void leaveEvent(QEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

};

#endif // M_PUSH_H
