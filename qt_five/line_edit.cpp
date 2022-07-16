#include "line_edit.h"

line_edit::line_edit(QWidget *parent) : QLineEdit(parent)
{
    this->setFrame(false);//去边框
    this->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);//居中——水平+垂直

    //设置背景
    QPalette palette;
    palette.setColor(QPalette::Base,(QColor(0,0,0,0)));//全透明背景（需要自定义添加背景）
    this->setPalette(palette);//设置画板

    //设置字体
    QFont font;
    font.setPointSize(13);
    font.setFamily("华文彩云");
    this->setFont(font);
}

void line_edit::paintEvent(QPaintEvent *e)
{
    //加载背景图片
    QPainter *show=new QPainter(this);
    show->drawPixmap(QRect(0,0,width,height),this->pix);
    show->end();
    QLineEdit::paintEvent(e);
}

bool line_edit::to_load(QString pix)
{
    //获取图片路径和图片大小
    if(this->pix.load(pix))
    {
        height=this->pix.height();
        width=this->pix.width();
        this->resize(width,height);//重新定义画布大小

        return true;
    }
    else return false;
}
