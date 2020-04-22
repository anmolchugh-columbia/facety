#include <iostream>
#include "src/FileExplorer/header/ImageIterator.h"
#include <unordered_map>
#include "src/FaceRec/header/faceClustering.h"
#include "src/FileExplorer/header/ImageOrganizer.h"
#include <QApplication>
#include "src/QT/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*TODO
 * Horizontal images
 * thumbnail as directory icon
 * thumbnail as representation based on confidence score
 * unit tests
 * use case scenario with implementation
 * some quantitative tests
 * Slides–Design/rationale document
 * Tutorial
 * Documentation
 * Working code
 * make a separate library for all directory related functionalities -> create delete update
 * speed up
*/