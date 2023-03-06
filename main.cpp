/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
// #include "sdk_mainwindow.h"

#include <AuthWidget>
#include <MainWindow>
#include <QApplication>
#include <QCommandLineParser>
#include <Sekura>
#include <appobject.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName("SekuraSDK");
    a.setApplicationVersion("1.0");

    QCommandLineParser parse;
    parse.setApplicationDescription("SekuraSDK");
    parse.addHelpOption();
    parse.addVersionOption();
    QCommandLineOption conf(QStringList() << "c"
                                          << "conf",
                            "set conf <name>", "name");
    parse.addOption(conf);

    QCommandLineOption startAuth("a", QCoreApplication::translate("main", "Start auth window"));
    parse.addOption(startAuth);
    QCommandLineOption startWidget(QStringList() << "w"
                                                 << "widget",
                                   "load widget <file_name>", "file_name");
    parse.addOption(startWidget);
    parse.process(a);

    QString data_conf = "Default";
    if (parse.isSet(conf)) {
        data_conf = parse.value(conf);
    }
    sekura_init_resources();

    if (parse.isSet(startAuth)) {
        Sekura::AuthWidget w2;
        w2.show();
        return a.exec();
    } else if (parse.isSet(startWidget)) {
        Sekura::appObject obj(data_conf);
        if (obj.isError())
            return -1;
        Sekura::BaseWidget *ptr = obj.loadFromFile(parse.value(startWidget));
        if (ptr != nullptr)
            obj.startWidget(ptr);
        return a.exec();
    }

    Sekura::MainWindow w(data_conf);
    if (w.isError())
        return -1;
    w.show();

    return a.exec();
}
