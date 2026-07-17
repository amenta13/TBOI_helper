#include <QApplication>
#include "ui/MainWindow.h"
#include "src/ItemDB.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load items from csv to database
    ItemDatabase::instance().loadFromCSV("data/isaac_items.csv");
    //ItemDatabase::instance().printAll(); // DEBUG

    MainWindow w;
    w.show();

    return app.exec();
}