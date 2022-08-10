#include <QApplication>
#include <QMainWindow>
#include "../qmlview/qmlview.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMainWindow w;
    QmlView q;

    w.setCentralWidget(&q);
    w.show();

    return a.exec();
}
