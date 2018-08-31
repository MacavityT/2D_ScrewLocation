#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

typedef void (*Handler)(const Halcon::HException &exception);

void MyHalconExceptionHandler(const Halcon::HException& except)
{
    throw except;
}

int main(int argc, char *argv[])
{
    HException::InstallHHandler(&MyHalconExceptionHandler);

    QApplication app(argc, argv);
    //Show ICON
    QPixmap pixmap(":AqLogo.PNG");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();
    //continue
    MainWindow MainWin;
    MainWin.setWindowTitle("Home");
    MainWin.show();

    splash.finish(&MainWin);
    return app.exec();
}
