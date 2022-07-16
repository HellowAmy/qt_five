#include "widget.h"

#include <QApplication>

//Qt 6.2.4版本
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();
    return a.exec();
}
