#include "VisMainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisMainWindow w;
    w.show();

    return a.exec();
}
