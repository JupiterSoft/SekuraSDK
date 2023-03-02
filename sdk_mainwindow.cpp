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
    ui->mdiArea->setActivationOrder(QMdiArea::ActivationHistoryOrder);
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

void SDK_MainWindow::appendWidget(BaseWidget *widget) {
    widget->setParent(this);
    QTimer::singleShot(100, this, [this, widget]() {
        QMdiSubWindow *w = ui->mdiArea->addSubWindow(widget);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
        connect(widget, &BaseWidget::appendWidget, this, &SDK_MainWindow::appendWidget);
        connect(widget, &BaseWidget::closeParent, w, &QMdiSubWindow::close);
    });
}

void SDK_MainWindow::start() {
    Sekura::Interface::setSettings(m_settings);
    Menu *menu = Interface::createMenu(ui->menubar, this);
    connect(menu, &Menu::childCreated, this, &SDK_MainWindow::appendWidget);
}
