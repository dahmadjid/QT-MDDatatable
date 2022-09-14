#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include "MDDatatable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.setFixedSize(1280, 720);
    auto row = std::make_unique<MDRow>(&w);


    w.show();

  

    return a.exec();
}