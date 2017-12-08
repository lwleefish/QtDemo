#include "WindowDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowDemo w;
    w.show();
    return a.exec();
}
