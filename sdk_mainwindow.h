/*
 * © 2023
 * Author: Akhat T. Kuangaliyev
 * Company: Jupiter Soft
 */
#ifndef SDK_MAINWINDOW_H
#define SDK_MAINWINDOW_H

#include <QMainWindow>
#include <RestSettings>
#include <TreeModel>

namespace Sekura {

    QT_BEGIN_NAMESPACE
    namespace Ui {
        class SDK_MainWindow;
    }
    QT_END_NAMESPACE

    class SDK_MainWindow : public QMainWindow {
        Q_OBJECT

      public:
        SDK_MainWindow(QWidget *parent = nullptr);
        ~SDK_MainWindow();

      public slots:
        void appendWidget(Sekura::BaseWidget *widget);

      private:
        Ui::SDK_MainWindow *ui;

        RestSettings *m_settings;
        bool m_authorized;

        void start();
        void createActions();
    };

} // namespace Sekura
#endif // SDK_MAINWINDOW_H
