/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#ifndef SYSTEMCOMMANDFORM_H
#define SYSTEMCOMMANDFORM_H

#include <QWidget>
#include <RestClient>
#include <RestSettings>

namespace Ui {
    class SystemCommandForm;
}

class SystemCommandForm : public QWidget {
    Q_OBJECT

  public:
    explicit SystemCommandForm(const QString &sys, QWidget *parent = nullptr);
    ~SystemCommandForm();

  public slots:

  private:
    Ui::SystemCommandForm *ui;
    Sekura::RestSettings *m_settings;
    Sekura::RestClient *m_client;
};

#endif // SYSTEMCOMMANDFORM_H
