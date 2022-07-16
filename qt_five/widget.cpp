#include "widget.h"
#include "ui_widget.h"

//

#include "chess_wid.h"
#include "chess_five.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(800,800);
    chess_five *five=new chess_five(this);

//    chess_wid *wid = new chess_wid(this);
//    wid->resize(200,400);
//    wid->show();



}

Widget::~Widget()
{
    delete ui;
}

