/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#include "systemcommandform.h"
#include "ui_systemcommandform.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <sekura.h>

using namespace Sekura;

SystemCommandForm::SystemCommandForm(const QString &sys, QWidget *parent)
    : QWidget(parent), ui(new Ui::SystemCommandForm), m_systemKey(sys) {
    ui->setupUi(this);
    m_settings = new RestSettings;
    Interface::setSettings(m_settings);
    m_client = new RestClient;
    connect(m_client, &RestClient::success, this, &SystemCommandForm::success);
    connect(m_client, &RestClient::error, this, &SystemCommandForm::error);
    connect(ui->pbCommands, &QPushButton::clicked, this, &SystemCommandForm::pbCommands);
    connect(ui->pbSend, &QPushButton::clicked, this, &SystemCommandForm::pbSend);
    m_settings->setHeaderValue("Content-Type", "application/json");
    m_settings->setHeaderValue("charset", "utf-8");
}

SystemCommandForm::~SystemCommandForm() {
    delete ui;
    delete m_settings;
    delete m_client;
}

void SystemCommandForm::success(const QJsonObject &obj) {
    qDebug() << obj;
    ui->te->setText(QJsonDocument(obj).toJson());
}

void SystemCommandForm::error(const QJsonObject &obj) { qDebug() << obj; }

void SystemCommandForm::pbCommands() {
    m_fileName = QFileDialog::getOpenFileName(this, "Open file", QString(), "*.json");
}

void SystemCommandForm::pbSend() {
    m_settings->setPath(ui->leAddress->text() + "/sekura/api/v1.0");
    m_settings->setHeaderValue("sekura-application", m_systemKey.toUtf8());
    if (m_fileName.isEmpty())
        return;
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject())
        return;
    QJsonObject obj = doc.object();
    QVariantMap req = obj.toVariantMap();
    req["transaction"] = "cmd";
    m_client->request("/query", "POST", req);
}
