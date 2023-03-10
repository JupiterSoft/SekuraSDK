/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#include "systemcommandform.h"
#include "ui_systemcommandform.h"

SystemCommandForm::SystemCommandForm(const QString &sys, QWidget *parent)
    : QWidget(parent), ui(new Ui::SystemCommandForm) {
    ui->setupUi(this);
}

SystemCommandForm::~SystemCommandForm() { delete ui; }
