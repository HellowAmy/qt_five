#include "chess_view.h"

chess_view::chess_view(QWidget *parent)
    : QWidget{parent}
{
    this->resize(parent->width(),parent->height());
    this->setMouseTracking(true);

    pix_background=QPixmap(":/map/3.jpeg");
    pix_black=QPixmap(":/map/black.png");
    pix_white=QPixmap(":/map/white.png");
}

void chess_view::set_borad(chess_board *board)
{
    c_board=board;
    v_count=c_board->get_size_line();
}

void chess_view::set_pic_picss(QPixmap black, QPixmap white)
{
    pix_black=black;
    pix_white=white;
}

void chess_view::set_pic_background(QPixmap background)
{
    pix_background=background;
}

void chess_view::draw_backdrop(QPainter *show, QPixmap map)
{
    if(!map.isNull()) show->drawPixmap(this->rect(),map);//图片背景
}

void chess_view::paintEvent(QPaintEvent *)
{
    QPainter *show=new QPainter(this);

    show->save();
    draw_backdrop(show,pix_background);//画图片背景
    draw_board_flg(show,v_length,v_count);//画棋盘点
    draw_board(show,v_length,v_count);//画棋盘
    draw_pieces(show);//画棋子
    show->restore();

    if(c_board->get_history().empty() == false)
    {
        pos_back=c_board->get_history().top();
        draw_flg_centre(show,pos_back);//画上次棋子标记
    }


    draw_flg(show,pos_move);//画移动落点

    show->end();
}

void chess_view::mousePressEvent(QMouseEvent *e)
{
    if(is_valid_rect(e->pos()))
        emit fa_press_pos(return_pieces_pos(e->pos()));//发送棋盘点击位置
}

void chess_view::mouseMoveEvent(QMouseEvent *e)
{
    pos_move = return_pieces_pos(e->pos());
    this->update();

    QWidget::mouseMoveEvent(e);
}

void chess_view::draw_flg_centre(QPainter *show, QPoint pos)
{
    QPen pen_board=QPen(QColor(40,40,40),2);
    QPen pen_black=QPen(QColor(40,40,40),2);
    QPen pen_white=QPen(QColor(250,250,250),2);

    //画上次落子
    show->setPen(pen_board);

    if(c_board->get_flg(pos) == chess_board::en_black) show->setPen(pen_white);
    else show->setPen(pen_black);

    int li=10;
    int shift_lien=v_length;
    for(int i=0;i<pos.x();i++) show->translate(shift_lien,0);
    for(int i=0;i<pos.y();i++) show->translate(0,shift_lien);

    show->drawLine(shift_lien-li,shift_lien,shift_lien+li,shift_lien);
    show->drawLine(shift_lien,shift_lien-li,shift_lien,shift_lien+li);

    for(int i=0;i<pos.x();i++) show->translate(-shift_lien,0);
    for(int i=0;i<pos.y();i++) show->translate(0,-shift_lien);
}

void chess_view::draw_flg(QPainter* show,QPoint pos)
{
    if(c_board->is_limit(pos) == false) return ;

    QPen pen_black=QPen(QColor(40,40,40),2);
    QPen pen_white=QPen(QColor(250,250,250),2);

    //画落子标记
    show->setPen(pen_black);

    if(c_board->get_flg(pos) == chess_board::en_black) show->setPen(pen_black);
    else if(c_board->get_flg(pos) == chess_board::en_black) show->setPen(pen_white);

    int li=10;
    int shift_lien=50;
    QPointF points[5] = {
        QPointF(shift_lien,shift_lien/2+li),
        QPointF(shift_lien/2+li,shift_lien),
        QPointF(shift_lien,shift_lien+shift_lien/2-li),
        QPointF(shift_lien+shift_lien/2-li,shift_lien),
        QPointF(shift_lien,shift_lien/2+li)
    };

    for(int i=0;i<pos.x();i++) show->translate(shift_lien,0);
    for(int i=0;i<pos.y();i++) show->translate(0,shift_lien);

    show->drawPolyline(points,5);

    for(int i=0;i<pos.x();i++) show->translate(-shift_lien,0);
    for(int i=0;i<pos.y();i++) show->translate(0,-shift_lien);
}

QPoint chess_view::return_pieces_pos(QPoint pos)
{
    //返回棋子在棋盘上的落点
    pos-=QPoint(v_length/2,v_length/2);
    return QPoint(pos.x()/v_length,pos.y()/v_length);
}

void chess_view::draw_pieces(QPainter *show)
{
    for(int x=0;x<v_count;x++)
    {
        for(int y=0;y<v_count;y++)
        {
            if(is_empty(QPoint(x,y)) == false)
            {
                if(is_black(QPoint(x,y))) draw_pieces_pic(show,pix_black,x,y);
                else draw_pieces_pic(show,pix_white,x,y);
            }
        }
    }
}

void chess_view::draw_board_flg(QPainter *show, int length, int count)
{
    QPen pen_board_little=QPen(QColor(40,40,40),0.2);

    //画外线
    int half=length/2;
    int longs=length*count;
    QLine xl(length-half,length-half,longs+half,length-half);
    QLine yl(length-half,length-half,length-half,longs+half);

    show->setPen(pen_board_little);
    show->drawLine(xl);
    show->drawLine(yl);

    xl.translate(0,longs);
    yl.translate(longs,0);

    show->drawLine(xl);
    show->drawLine(yl);

    //画棋盘点
    int size=10;
    int flg=(count+1)/4;
    int flg_ex=(count+1)/2;

    show->setBrush(QColor(40,40,40));

    QRectF epos(-size/2,-size/2,size,size);
    epos.translate(length*flg,length*flg);
    show->drawRect(epos);

    epos.translate(length*((flg_ex-flg)+(flg_ex-flg)),0);
    show->drawRect(epos);

    epos.translate(0,length*((flg_ex-flg)+(flg_ex-flg)));
    show->drawRect(epos);

    epos.translate(-length*((flg_ex-flg)+(flg_ex-flg)),0);
    show->drawRect(epos);

    epos.translate(length*(flg_ex-flg),-length*(flg_ex-flg));
    show->drawRect(epos);
}

void chess_view::draw_board(QPainter* show,int length, int count)
{
    QPen pen_board=QPen(QColor(40,40,40),2);
    QPen pen_board_strong=QPen(QColor(40,40,40),3);

    //画棋盘
    QLine xl(length,length,length*count,length);
    QLine yl(length,length,length,count*length);

    show->setPen(pen_board);
    for(int temp=0;temp<count;temp++)
    {
        show->drawLine(xl);
        show->drawLine(yl);
        xl.translate(0,length);
        yl.translate(length,0);
    }

    //画边框
    show->setPen(pen_board_strong);
    xl.translate(0,-length);
    yl.translate(-length,0);
    show->drawLine(xl);
    show->drawLine(yl);

    xl.translate(0,-length*(count-1));
    yl.translate(-length*(count-1),0);
    show->drawLine(xl);
    show->drawLine(yl);

    xl.translate(0,length*(count/2));
    yl.translate(length*(count/2),0);
    show->drawLine(xl);
    show->drawLine(yl);
}


void chess_view::draw_pieces_pic(QPainter *show, QPixmap pic, int x, int y)
{
    if(pic.isNull() == false)
    {
        int xl=(x+1)*v_length-(v_length/2);
        int yl=(y+1)*v_length-(v_length/2);
        show->drawPixmap(xl,yl,pic);
    }
}

bool chess_view::is_black(QPoint pos)
{
    if(c_board->get_flg(pos) == chess_board::en_black) return true;
    else return false;
}

bool chess_view::is_empty(QPoint pos)
{
    if(c_board->get_flg(pos) == chess_board::en_empty) return true;
    else return false;
}

bool chess_view::is_valid_rect(QPoint pos)
{
    QRect rect(v_length/2,v_length/2,v_length*v_count,v_length*v_count);

    //判断是否在有效范围
    if(rect.contains(pos)) return true;
    else return false;
}
