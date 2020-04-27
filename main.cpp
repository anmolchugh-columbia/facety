#include <QApplication>
#include "src/QT/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*TODO
 * test for 11 or more clusters
 * Horizontal images
 * thumbnail as directory icon
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