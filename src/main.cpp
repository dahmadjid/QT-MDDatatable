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

    
    auto row = MDRow::fromStringVector({"Status", "Signal Name", "Severity", "Stage", "Lapsed Time","Team Lead"}, true);
    rows.push_back(row);
    row = MDRow::fromStringVector({"Online", "Astrid: NE ", "Medium", "Triaged", "10:12","Chase Nguyen"});
    rows.push_back(row);
    row = MDRow::fromStringVector({"Online", "Cosmo Prod Shared vm", "Huge", "Triaged", "12:45", "Brie Furman"});
    rows.push_back(row);

    row = MDRow::fromStringVector({"Online", "Cosmo Prod Shared vm", "Huge", "Triaged", "12:45", "Brie Furman"});
    rows.push_back(row);
    auto datatable = new MDDatatable(rows ,&w);

    
    
    datatable->move(0,0);
    datatable->resizeColumns({100, 100, 100, 100, 100, 100});
    datatable->setMaxCharCount({10,10,10,10,10,10});

    
    std::vector<MDRow*> adazdazd;

    row = MDRow::fromStringVector({"Status", "Signalaz Name", "Severity", "Stage", "Lapsed Time","Team Lead"}, true);
    adazdazd.push_back(row);
    row = MDRow::fromStringVector({"Online", "Astrzaaaaaaaaaaaaazdid: NE Shared managed-features-providvy", "Medium", "Triaged", "10:12","Chase Nguyen"});
    adazdazd.push_back(row);
    row = MDRow::fromStringVector({"Onlaz dazdazdazdazine", "Cosadazdazdazxmo Prod Shared vm", "Huge", "Triaged", "12:45", "Brie Furmfan"});
    adazdazd.push_back(row);

    row = MDRow::fromStringVector({"Online", "azdzadazdazdazdazdazdazdazdazdazdaz Prod Shared vm", "Huge", "Triaged", "12:45", "Brie Furman"});
    adazdazd.push_back(row);
    QTimer::singleShot(1000, [&]{
        datatable->load(adazdazd);


    });
    
    w.setFixedSize(1280, 720);
    w.show();
    
    return a.exec();
}