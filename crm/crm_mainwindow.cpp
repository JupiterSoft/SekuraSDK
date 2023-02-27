/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#include "crm_mainwindow.h"
#include "./ui_crm_mainwindow.h"

#include <AuthDialog>
#include <BaseWidget>
#include <Menu>
#include <QMdiSubWindow>
#include <QTimer>
#include <RestSettings>

using namespace Sekura;

RestSettings *CRM_MainWindow::_global_settings = nullptr;

CRM_MainWindow::CRM_MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CRM_MainWindow) {
    ui->setupUi(this);
    m_settings = new RestSettings(this);
    if (_global_settings == nullptr) {
        _global_settings = m_settings;
    }
    if (!m_settings->load("SekuraCRM")) {
        QByteArrayMap headers;
        headers["Content-Type"] = "application/json";
        headers["charset"] = "utf-8";
        headers["sekura-application"] = "d8660fea-b667-11ed-8bdd-e6ece5f4476b";
        m_settings->setHeaders(headers);
        m_settings->setPath("http://localhost:8081/sekura/api/v1.0");
        m_settings->save("SekuraCRM");
        m_authorized = false;
    } else {
        m_settings->setPath("http://localhost:8081/sekura/api/v1.0");
        m_settings->save("SekuraCRM");
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
                QTimer::singleShot(100, this, &CRM_MainWindow::close);
            });
            dialog->exec();
        });
    } else
        start();

    createActions();
}

CRM_MainWindow::~CRM_MainWindow() {
    delete ui;
    if (_global_settings == m_settings) {
        _global_settings = nullptr;
    }
    delete m_settings;
}

RestSettings *CRM_MainWindow::settings() { return _global_settings; }

void CRM_MainWindow::appendWidget(BaseWidget *widget) {
    widget->setParent(this);
    QTimer::singleShot(100, [this, widget]() {
        QMdiSubWindow *w = ui->mdiArea->addSubWindow(widget);
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
        connect(widget, &BaseWidget::appendWidget, this, &CRM_MainWindow::appendWidget);
        connect(widget, &BaseWidget::closeParent, w, &QMdiSubWindow::close);
    });
}

void CRM_MainWindow::start() {
    Menu *menu = Interface::createMenu(ui->menubar, m_settings, this);
    connect(menu, &Menu::childCreated, this, &CRM_MainWindow::appendWidget);
}

void CRM_MainWindow::createActions() {}
