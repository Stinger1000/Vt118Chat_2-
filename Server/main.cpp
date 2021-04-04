#include <QCoreApplication>
#include <QDebug>
#include "MainController.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<quintptr>("quintptr");

    QCoreApplication a(argc, argv);

    MainController controller;

    return a.exec();
}
