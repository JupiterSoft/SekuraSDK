/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#include "sdk_mainwindow.h"

#include <QApplication>
#include <Sekura>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    sekura_init_resources();
    Sekura::SDK_MainWindow w;
    w.show();
    return a.exec();
}
