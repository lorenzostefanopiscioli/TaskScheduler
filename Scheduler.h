#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QObject>
#include <QVector>
#include <QVector>
#include <QTimer>
#include <QDebug>
#include "TaskInterface.h"
#include "TimerInterface.h"
#include "Task.h"
#include "IntervalTimer.h"
#include "TimeoutTimer.h"


namespace TiCare {

    /*
     * Classe di gestione della programmazione temporale di task.
     * Scheduler permette la relazione uno a molti tra task e
     * timer di vario genere. Quindi un stesso task può essere invocato
     * in esecuzione da timer diversi ad esso assocati.
    */
    class Scheduler : public QObject
    {
        public:
            explicit Scheduler( QObject *parent = nullptr );
            ~Scheduler();
            Task* getTask( const QString taskName  ) const;
            void addTask( TaskInterface* task );
            void addTask( TaskInterface* task, TimerInterface* timer );
            QStringList getTaskNameList() const;
            void removeTask( const QString taskName );
            bool taskExists( const QString taskName ) const;

        private:
            // Questa macro permette di usare il sistema di slot e signals di QT
            Q_OBJECT

            // Lista dei task
            QVector < Task* > taskList;

    };

}

#endif // SCHEDULER_H
