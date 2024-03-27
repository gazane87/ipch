#include "ipch.h"
#include <string>
#include <QApplication>
#include <QFile>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    ipch w;
    w.show();
    return a.exec();
}
