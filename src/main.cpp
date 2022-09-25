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

    auto datatable = new MDDatatable( &w);
    
    auto row = MDRow::fromStringVector({"Status", "Signal Name", "Severity", "Stage", "Lapsed Time","Team Lead"}, true);
    rows.push_back(row);
    row = MDRow::fromStringVector({"Online", "Astrid: NE Shared managed-features-providvy", "Medium", "Triaged", "10:12","Chase Nguyen"});
    rows.push_back(row);
    row = MDRow::fromStringVector({"Online", "Cosmo Prod Shared vm", "Huge", "Triaged", "12:45", "Brie Furman"});
    rows.push_back(row);

    datatable->load(rows);
    row = MDRow::fromStringVector({"Online", "Cosmo Prod Shared vm", "Huge", "Triaged", "12:45", "Brie Furman"});
    datatable->addRow(row);

    
    
    datatable->move(0,0);
    datatable->resizeColumns({100, 100, 100, 100, 100, 100});
    w.setFixedSize(1280, 720);
    w.show();
    
    return a.exec();
}