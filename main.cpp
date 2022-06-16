#include <mainwindow/mainwindow.h>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //QQuickWidget *view = new QQuickWidget;
    //view->setSource(QUrl::fromLocalFile("../assert/qml/map.qml"));
    //view->show();

    return a.exec();
}
