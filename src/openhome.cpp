#include <QApplication>

#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationName("Open Home Designer");

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
