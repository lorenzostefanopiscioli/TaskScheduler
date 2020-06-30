#include "Scheduler.h"


namespace TiCare {

    Scheduler::Scheduler( QObject *parent ) : QObject( parent ) {}


    Scheduler::~Scheduler()
    {
        // Alla chiusura libero lo spazio occupato dai task aggiunti
        // allo scheduler
        for ( auto task : taskList )
        {
            delete task;
        }
    }


    // Restituisce un puntatore in sola lettura ad un task di nome taskName
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


    // Aggiunge un task allo scheduler
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


    // Aggiunge allo scheduler un task e un timer associato
    void Scheduler::addTask( TaskInterface *task, TimerInterface *timer )
    {
        // Verifico che non esista già un task con lo stesso nome di quello
        // che voglio aggiungere
        if ( taskExists( task->getTaskName() ) )
        {
            qDebug() << "Esiste già un task con questo nome " << task->getTaskName()
                     << " pertanto non può essere aggiunto!";
            return;
        }

        // Istanzio un task e lo aggiungo al vettore taskList
        Task *tempTask = new Task( task, timer );
        taskList.push_back( tempTask );

        // Connetto l'evento di timeout del timer associato al task con l'esecuzione
        // del task stesso
        QObject::connect( timer, &QTimer::timeout, [ tempTask ]()
        {
            tempTask->ExecuteTask();
        });
    }


    // Restituisce la lista dei nomi dei task
    QStringList Scheduler::getTaskNameList() const
    {
        QStringList taskNameList{};

        for ( auto task : taskList )
        {
            taskNameList.push_back( task->getTaskName() );
        }

        return taskNameList;
    }


    // Elimina un task
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


    // Verifica se un task di nome taskName esista già in taskList
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


