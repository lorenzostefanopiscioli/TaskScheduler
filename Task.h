#ifndef TASK_H
#define TASK_H


#include <QDebug>
#include "TaskInterface.h"
#include "TimerInterface.h"


namespace TiCare {

    // Classe che contiene un puntatore ad un task derivato da TaskInterface
    // e lo associa ad un numero a piacere di puntatori a timer derivati
    // da TimerInterface
    class Task
    {
        public:
            Task( TaskInterface *tempTask ) : task( tempTask ) {};
            Task( TaskInterface *tempTask, TimerInterface* tempTimer );
            ~Task();
            QString getTaskName() const;
            void ExecuteTask();
            void setConfiguration();
            void addTimer( TimerInterface* tempTimer );
            void removeTimer( const QString _timerName );
            void removeAllTimer();
            bool timerExists( const QString _timerName ) const;
            QStringList getTimerNameList() const;

        private:
            TaskInterface *task;
            QVector < TimerInterface* > timerList;
    };


}

#endif // TASK_H
