#include "my2048.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    My2048 w;

    w.show();

    return a.exec();
}
