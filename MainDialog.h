#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QCoreApplication>
#include <QDialog>
#include <QCloseEvent>
#include <QIcon>
#include <QAction>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

#include "Scheduler.h"


class MainDialog : public QDialog
{
    Q_OBJECT

    public:
        MainDialog( TiCare::Scheduler *_scheduler, QWidget *parent = nullptr );
        ~MainDialog();

    protected:
        void closeEvent( QCloseEvent *event ) override;

    private slots:
        void setTimeList( const QString currentText );
        void configTask();

    private:
        void createSystemTrayIconActions();
        void createSystemTrayIcon();

        QAction *showSettingsDialogAction;
        QAction *quitAction;

        QSystemTrayIcon *systemTrayIcon;
        QMenu *systemTrayIconMenu;

        QComboBox *taskComboBox;
        QListWidget *timeList;
        QPushButton *configButton;

        TiCare::Scheduler *scheduler;
};

#endif // MAINDIALOG_H
