#include "mytable.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTable table;
    table.show();
    return a.exec();
}