#ifndef CHESS_FIVE_H
#define CHESS_FIVE_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

//#include "chess_board.h"
#include "chess_play.h"
#include "chess_view.h"
#include "chess_rules.h"
#include "chess_ai.h"
#include "chess_net.h"
#include "chess_wid.h"

class chess_five : public QWidget
{
    Q_OBJECT

public:
    enum play_mode
    {
        en_self,
        en_ai,
        en_net
    };

public:
    explicit chess_five(QWidget *parent = nullptr);

signals:
    emit void fa_down_pos(QPoint pos);
    emit void fa_open_net(QString IP,int port,bool first);

protected:
    play_mode enum_play = en_self;
    bool is_first=true;

    int v_port=8080;



};

#endif // CHESS_FIVE_H
