/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#include "sdk_mainwindow.h"
#include "./ui_sdk_mainwindow.h"

#include <AuthDialog>
#include <Menu>
#include <QMdiSubWindow>
#include <QTimer>
#include <TableWidget>
#include <TreeWidget>

using namespace Sekura;

SDK_MainWindow::SDK_MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SDK_MainWindow) {
    ui->setupUi(this);
    m_settings = new RestSettings(this);

    if (!m_settings->load("SekuraSDK")) {
        QByteArrayMap headers;
        headers["Content-Type"] = "application/json";
        headers["charset"] = "utf-8";
        headers["sekura-application"] = "9df49aec-ad3f-11ed-b1da-d00da1480190";
        m_settings->setHeaders(headers);
        m_settings->setPath("http://localhost:8081/sekura/api/v1.0");
        m_settings->save("SekuraSDK");
        m_authorized = false;
    } else {
        m_settings->setPath("http://localhost:8081/sekura/api/v1.0");
        m_settings->save("SekuraSDK");
        if (m_settings->headers().contains("Authorization")) {
            m_authorized = true;
        }
    }

    if (!m_authorized) {
        QTimer::singleShot(100, this, [=]() {
            // m_settings->removeHeaderValue("Authorization");
            AuthDialog *dialog = new AuthDialog(m_settings, true, this);
            connect(dialog, &AuthDialog::accepted, this, [this, dialog]() {
                m_authorized = true;
                this->start();
                dialog->deleteLater();
            });
            connect(dialog, &AuthDialog::rejected, this, [this]() {
                qDebug() << "Rejected";
                QTimer::singleShot(100, this, &SDK_MainWindow::close);
            });
            dialog->exec();
        });
    } else
        start();

    // createActions();
}

SDK_MainWindow::~SDK_MainWindow() { delete ui; }

void SDK_MainWindow::start() {
    Menu *menu = Interface::createMenu(ui->menubar, m_settings, this);
    connect(menu, &Menu::childCreated, this, [this](BaseWidget *widget) {
        widget->setParent(this);
        connect(widget, &BaseWidget::appendWidget, this, [this](QWidget *child) {
            QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->showMaximized();
        });
        QMdiSubWindow *w = ui->mdiArea->addSubWindow(widget);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    });
}

void SDK_MainWindow::createActions() {
    QMenu *menu = ui->menubar->addMenu(tr("System"));
    QAction *action = new QAction(tr("Applications"));
    connect(action, &QAction::triggered, this, [this]() {
        QVariantMap map;
        map["title"] = tr("Applications");
        map["model"] = "a_applications";
        TableWidget *child = new TableWidget(map, m_settings, this);
        connect(child, &TableWidget::appendWidget, this, [this](QWidget *child) {
            QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->showMaximized();
        });
        QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    });
    menu->addAction(action);
    action = new QAction(tr("Software keys"));
    connect(action, &QAction::triggered, this, [this]() {
        QVariantMap map;
        map["title"] = tr("Software keys");
        map["model"] = "a_software_keys";
        TableWidget *child = new TableWidget(map, m_settings, this);
        connect(child, &TableWidget::appendWidget, this, [this](QWidget *child) {
            QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->showMaximized();
        });
        QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    });
    menu->addAction(action);
    action = new QAction(tr("Menus"));
    connect(action, &QAction::triggered, this, [this]() {
        QVariantMap map;
        map["title"] = tr("Menus");
        map["model"] = "a_menus";
        TreeWidget *child = new TreeWidget(map, m_settings, this);
        connect(child, &TreeWidget::appendWidget, this, [this](QWidget *child) {
            QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->showMaximized();
        });
        QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    });
    menu->addAction(action);
    action = new QAction(tr("Tables"));
    connect(action, &QAction::triggered, this, [this]() {
        QVariantMap map;
        map["title"] = tr("Tables");
        map["model"] = "a_tables";

        TableWidget *child = new TableWidget(map, m_settings, this);
        connect(child, &TableWidget::appendWidget, this, [this](QWidget *child) {
            QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
            w->setAttribute(Qt::WA_DeleteOnClose);
            w->showMaximized();
        });
        QMdiSubWindow *w = ui->mdiArea->addSubWindow(child);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
    });
    menu->addAction(action);
}
