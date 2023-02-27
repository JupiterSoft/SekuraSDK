/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#ifndef CRM_MAINWINDOW_H
#define CRM_MAINWINDOW_H

#include <QJsonObject>
#include <QMainWindow>
#include <Sekura>

namespace Sekura {

    QT_BEGIN_NAMESPACE
    namespace Ui {
        class CRM_MainWindow;
    }
    QT_END_NAMESPACE

    class CRM_MainWindow : public QMainWindow {
        Q_OBJECT

      public:
        CRM_MainWindow(QWidget *parent = nullptr);
        ~CRM_MainWindow();

        static RestSettings *settings();

      public slots:
        void appendWidget(Sekura::BaseWidget *widget);

      private:
        Ui::CRM_MainWindow *ui;
        RestSettings *m_settings;
        bool m_authorized;

        static RestSettings *_global_settings;

        void start();
        void createActions();
    };

} // namespace Sekura
#endif // CRM_MAINWINDOW_H
