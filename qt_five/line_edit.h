#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QLineEdit>
#include <QPalette>

class line_edit : public QLineEdit
{
    Q_OBJECT

public:
    explicit line_edit(QWidget *parent = nullptr);
    bool to_load(QString pix);//获取图片路径

signals:

protected:
    void paintEvent(QPaintEvent *e) override;//重绘背景

private:
    //绘画组件
    QPixmap pix;
    QRect area;

    int height=0;
    int width=0;

};

#endif // LINE_EDIT_H
