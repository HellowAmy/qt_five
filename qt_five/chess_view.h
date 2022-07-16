#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>

#include "chess_board.h"

class chess_view : public QWidget
{
    Q_OBJECT
public:
    explicit chess_view(QWidget *parent = nullptr);

    void set_pic_background(QPixmap background);//设置背景图片
    void set_pic_picss(QPixmap black,QPixmap white);//设置棋子图片
    void set_borad(chess_board *board);//获取棋盘指针

signals:
    emit void fa_press_pos(QPoint pos);//发送可落子点击位置

protected:
    void paintEvent(QPaintEvent *event) override;//绘画棋盘
    void mousePressEvent(QMouseEvent *event) override;//点击下棋
    void mouseMoveEvent(QMouseEvent *event) override;//移动标记

    void draw_backdrop(QPainter* show,QPixmap pic_background);//画背景
    void draw_board(QPainter* show,int length,int count);//画棋盘
    void draw_board_flg(QPainter* show,int length,int count);//画棋盘点
    void draw_pieces(QPainter* show);//画棋子
    void draw_pieces_pic(QPainter* show,QPixmap pic,int x,int y);//画棋子——图片
    void draw_flg(QPainter* show,QPoint pos);//移动落子标记
    void draw_flg_centre(QPainter* show,QPoint pos);//画上一次落子标记

private:
    chess_board *c_board;

    QPixmap pix_background;
    QPixmap pix_black;
    QPixmap pix_white;

    QPoint pos_move;
    QPoint pos_back;
    int v_length=50;
    int v_count=0;

    bool is_black(QPoint pos);//判断棋子是否为黑色
    bool is_empty(QPoint pos);//判断棋子是否为空
    bool is_valid_rect(QPoint pos);//判断是否在有效范围
    QPoint return_pieces_pos(QPoint pos);//返回棋盘坐标
};

#endif // CHESS_VIEW_H
