
#include <QApplication>

#include "ui/Start.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Start w;
    w.show();

    return a.exec();
}
