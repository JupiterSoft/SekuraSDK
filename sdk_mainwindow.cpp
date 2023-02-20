/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#include "sdk_mainwindow.h"
#include "./ui_sdk_mainwindow.h"

SDK_MainWindow::SDK_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SDK_MainWindow)
{
    ui->setupUi(this);
}

SDK_MainWindow::~SDK_MainWindow()
{
    delete ui;
}

