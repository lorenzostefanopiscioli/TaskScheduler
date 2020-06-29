#include "Scheduler.h"


namespace TiCare {

    Scheduler::Scheduler( QObject *parent ) : QObject( parent ) {}


    Task* Scheduler::getTask( const QString taskName  ) const
    {
        for ( auto task : taskList )
        {
            if ( taskName == task->getTaskName() )
            {
                return task;
            }
        }
        return nullptr;
    }


    // Add a task to the Scheduler
    void Scheduler::addTask( TaskInterface *task )
    {
        if ( taskExists( task->getTaskName() ) )
        {
            qDebug() << "Esiste già un task con questo nome " << task->getTaskName()
                     << " pertanto non può essere aggiunto!";
            return;
        }
        taskList.push_back( new Task( task ) );
    }


    // Add a task and a timer to the Scheduler
    void Scheduler::addTask( TaskInterface *task, TimerInterface *timer )
    {
        if ( taskExists( task->getTaskName() ) )
        {
            qDebug() << "Esiste già un task con questo nome " << task->getTaskName()
                     << " pertanto non può essere aggiunto!";
            return;
        }

        Task *tempTask = new Task( task, timer );
        taskList.push_back( tempTask );

        QObject::connect( timer, &QTimer::timeout, [ tempTask ]()
        {
            tempTask->ExecuteTask();
        });
    }


    QStringList Scheduler::getTaskNameList() const
    {
        QStringList taskNameList{};

        for ( auto task : taskList )
        {
            taskNameList.push_back( task->getTaskName() );
        }

        return taskNameList;
    }


    void Scheduler::removeTask( const QString taskName )
    {
        for ( auto &task : taskList )
        {
            if ( taskName == task->getTaskName() )
            {
                int taskIndex = taskList.indexOf( task );
                if ( taskIndex != -1 )
                {
                    task->removeAllTimer();
                    delete task;
                    taskList.remove( taskIndex );
                }
                return;
            }
        }
    }


    bool Scheduler::taskExists( const QString taskName ) const
    {
        for ( auto task : taskList )
        {
            if ( taskName == task->getTaskName() )
            {
                return true;
            }
        }
        return false;
    }

}


