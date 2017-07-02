#include "widget.h"
#include <QApplication>
#include <QSize>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFixedSize(680,500);
    w.show();

    return a.exec();
}
