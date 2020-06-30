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
        MainDialog( const TiCare::Scheduler *_scheduler, QWidget *parent = nullptr );

    protected:
        void closeEvent( QCloseEvent *event ) override;

    private slots:
        void setTimeList( const QString currentText );
        void configTask();

    private:
        void createSystemTrayIconActions();
        void createSystemTrayIcon();

        // Questo puntatore punta all'indirizzo in cui si trova lo scheduler
        // creato in main con la restrizione di poterlo usare solo in lettura (const)
        const TiCare::Scheduler *scheduler;

        // Quando un oggetto derivato da QObject viene distrutto
        // in automatico distrugge anche tutti i suoi figli, dunque
        // non c'è bisogno di eseguire delete sui puntatori seguenti
        // che sono tutti riferiti a classi derivate da QObject

        QAction *showSettingsDialogAction;
        QAction *quitAction;

        QSystemTrayIcon *systemTrayIcon;
        QMenu *systemTrayIconMenu;

        QComboBox *taskComboBox;
        QListWidget *timeList;
};

#endif // MAINDIALOG_H
