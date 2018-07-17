#include "mainwindow.h"
#include <QApplication>

typedef void (*Handler)(const Halcon::HException &exception);

void MyHalconExceptionHandler(const Halcon::HException& except)
{
    throw except;
}

int main(int argc, char *argv[])
{
    HException::InstallHHandler(&MyHalconExceptionHandler);

    QApplication app(argc, argv);
    MainWindow MainWin;
    MainWin.setWindowTitle("Home");
    MainWin.show();

    return app.exec();
}
