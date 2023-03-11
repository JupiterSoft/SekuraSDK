/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
// #include "sdk_mainwindow.h"

#include <AuthWidget>
#include <CryptSettings>
#include <MainWindow>
#include <QApplication>
#include <QCommandLineParser>
#include <Sekura>
#include <SystemCommandWidget>
#include <appObject>

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
    QCommandLineOption systemWidget(QStringList() << "s"
                                                  << "system",
                                    "system <password>", "password");
    parse.addOption(systemWidget);
    parse.process(a);

    QString data_conf = "Default";
    if (parse.isSet(conf)) {
        data_conf = parse.value(conf);
    }
    sekura_init_resources();
    Sekura::CryptSettings settings;
    settings.setPubKey("default-password");
    Sekura::Interface::setSettings(&settings);

    if (parse.isSet(startAuth)) {
        Sekura::AuthWidget w2;
        w2.show();
        return a.exec();
    } else if (parse.isSet(startWidget)) {
        if (!settings.load(data_conf))
            return -1;
        Sekura::appObject obj;
        Sekura::BaseWidget *ptr = obj.loadFromFile(parse.value(startWidget));
        if (ptr != nullptr)
            obj.startWidget(ptr);
        return a.exec();
    } else if (parse.isSet(systemWidget)) {
        Sekura::SystemCommandWidget form(parse.value(systemWidget));
        form.show();
        return a.exec();
    }

    if (!settings.load(data_conf))
        return -1;

    Sekura::MainWindow w;
    w.show();

    return a.exec();
}
