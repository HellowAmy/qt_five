#include "push_button.h"

void push_button::paintEvent(QPaintEvent *e)
{
    //打开成功
    if(is_open==true)
    {
        //画手
        QPainter *show=new QPainter(this);
        show->drawPixmap(ban,tu);
        show->setFont(QFont("华文彩云",13));
        show->drawText(this->rect(),Qt::AlignCenter,v_txt);
        show->end();
    }
    else QPushButton::paintEvent(e);//失败则使用父类
}

void push_button::tu_zhong(QString tu_ru)
{
    is_open=tu.load(tu_ru);//首次进入
    if(is_open)
    {
        //进行拉伸，可以在外部设置，有默认值
        tu_load(tu_ru);

        //获取图片高、宽，并设置设置绘图区域——adjust（左缩进，上缩进，宽，高）
        this->resize(tu.width(),tu.height());
        ban.adjust(line,line,tu.width()-line,tu.height()-line);

        //设置png的按键透明映射（透明处不反应）
        this->setMask(tu.mask());
    }
    this->update();
}

void push_button::set_txt(QString txt)
{
    v_txt=txt;
}

void push_button::open(int kuan,int gao)
{
    //默认值：宽、高、拉伸
    if(kuan!=0&&gao!=0)
    {
        this->kuan=kuan;
        this->gao=gao;
        la_shen=true;//有数据则根据数值比例
    }
    tu_zhong(tu_normal);
}

//照片平滑
void push_button::tu_load(QString tu_ru)
{
    //拉伸
    if(tu.load(tu_ru))
    {
        //判断是否有比例要求
        if(la_shen==true) tu=tu.scaled(kuan,gao,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        else tu=tu.scaled(tu.width(),tu.height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
}

//鼠标进入
void push_button::enterEvent(QEnterEvent *e)
{
    if(tu_enter.isEmpty() == false)
    {
        tu_load(tu_enter);
        this->update();
    }
    QPushButton::enterEvent(e);
}

//鼠标按下
void push_button::mousePressEvent(QMouseEvent *e)
{
    if(tu_press.isEmpty() == false)
    {
        tu_load(tu_press);
        this->update();
    }
    QPushButton::mousePressEvent(e);
}

//鼠标离开
void push_button::leaveEvent(QEvent *e)
{
    if(tu_normal.isEmpty() == false)
    {
        tu_load(tu_normal);
        this->update();
    }
    QPushButton::leaveEvent(e);
}

//鼠标释放
void push_button::mouseReleaseEvent(QMouseEvent *e)
{
    if(tu_enter.isEmpty() == false)
    {
        tu_load(tu_enter);
        this->update();
    }
    QPushButton::mouseReleaseEvent(e);
}

//进入图片
void push_button::open_enter(QString tu_ru)
{
    tu_enter=tu_ru;
}

//按下图片
void push_button::open_press(QString tu_ru)
{
    tu_press=tu_ru;
}

//正常图片
void push_button::open_normal(QString tu_ru)
{
    tu_normal=tu_ru;
}





