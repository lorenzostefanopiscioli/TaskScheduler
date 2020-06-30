#ifndef TASKPRINTTEXT_H
#define TASKPRINTTEXT_H


#include <QCoreApplication>
#include <QObject>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QTimer>

#include "TaskInterface.h"


namespace TiCare {

    // Classe del task di stampa di un testo scelto dall'utente
    class TaskPrintText : public virtual TaskInterface
    {
        public:
            explicit TaskPrintText( QString _taskName, QString _textToBePrinted = "" )
            : taskName( _taskName ), textToBePrinted( _textToBePrinted ) {};

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
            QString textToBePrinted;
    };

}

#endif // TASKPRINTTEXT_H
