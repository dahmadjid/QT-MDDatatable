#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include "MDDatatable.h"
#include <fmt/format.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    
    w.setFixedSize(1280, 720);
    
    std::vector<MDRow*> rows;

    
    auto row = MDRow::fromStringVector({"email", "nameaaaaaaaaaaa", "Message", "garbage", "garbage","zaeazdazdzadazdzad"}, true);
    rows.push_back(row);
    row = MDRow::fromStringVector({"dah@gmail.com", "madjid", "sdzdazdazd", "azsazsadzdaz"});
    rows.push_back(row);
    row = MDRow::fromStringVector({"crappy@gmail.com", "crapaaaa", "sdzdazdazd", "fafazdqwwwwwwwwwwwazds", "qqqqqq"});
    rows.push_back(row);

   
    
    auto datatable = new MDDatatable(rows, &w);
    datatable->setFixedSize(1000, 1000);
    w.show();

    return a.exec();
}