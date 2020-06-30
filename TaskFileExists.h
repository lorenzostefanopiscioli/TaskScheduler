#ifndef TASKFILEEXISTS_H
#define TASKFILEEXISTS_H

#include <QCoreApplication>
#include <QObject>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include "TaskInterface.h"


namespace TiCare {

    // Classe del task che controlla se esiste un file su disco
    class TaskFileExists : public virtual TaskInterface
    {
        public:
            explicit TaskFileExists( QString _taskName, QString _fileName = "" )
            : taskName( _taskName ), fileName( _fileName ) {};

            // Per rendere concreta questa classe, implemento i metodi virtuali
            // dell'interfaccia TaskInterface
            virtual QString getTaskName() const override;
            virtual void ExecuteTask() override;
            virtual void setConfiguration() override;

        private:
            // Questa macro permette di usare il sistema di slot e signals di QT
            Q_OBJECT
            // Questa macro dice a QT quale interfaccia implementare
            Q_INTERFACES( TiCare::TaskInterface )

            QString taskName;
            QString fileName;
    };

}

#endif // TASKFILEEXISTS_H
