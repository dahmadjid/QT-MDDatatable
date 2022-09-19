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
    
    
    std::vector<MDRow*> rows;

    
    auto row = MDRow::fromStringVector({"email", "nameaaaaaaaaaaa", "Message", "garbage", "garbage","zaeazdazdzadazdzad"}, true);
    rows.push_back(row);
    row = MDRow::fromStringVector({"dah@gmail.com", "madjid", "sdzdazdazd", "azsazsadzdaz"});
    rows.push_back(row);
    row = MDRow::fromStringVector({"crappy@gmail.com", "crapaaaa", "sdzdazdazd", "fafazdqwwwwwwwwwwwazds", "qqqqqq"});
    rows.push_back(row);


    
    auto datatable = new MDDatatable(rows, &w);
    auto rowa = MDRow::fromStringVector({"dah@gazeazeazeazmail.com", "madjid", "sdzdazdazd", "azsazsadzdaz"});

    datatable->addRow(rowa);
    // QTimer::singleShot(1000, [=]{auto rsow = MDRow::fromStringVector({"dah@gmail.com", "madjid", "sdzdazdazd", "azsazsadzdaz"});datatable->addRow(rsow);});

    w.setFixedSize(1280, 720);
    w.show();

    return a.exec();
}