#ifndef TASK_H
#define TASK_H


#include <QDebug>
#include "TaskInterface.h"
#include "TimerInterface.h"


namespace TiCare {

    class Task
    {
        public:
            Task( TaskInterface *tempTask ) : task( tempTask ) {};
            Task( TaskInterface *tempTask, TimerInterface* tempTimer );
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
