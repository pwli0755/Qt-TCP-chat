#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
       w.setFixedSize(680,500);
    w.show();

    return a.exec();
}
