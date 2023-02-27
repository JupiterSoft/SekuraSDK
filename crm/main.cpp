/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#include "crm_mainwindow.h"

#include <QApplication>
#include <Sekura>

using namespace Sekura;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    sekura_init_resources();
    CRM_MainWindow w;
    w.show();
    return a.exec();
}
