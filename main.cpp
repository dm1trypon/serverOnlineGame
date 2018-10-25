#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget _widget;
    _widget.show();

    return a.exec();
}
