#include "Task.h"


namespace TiCare {

    Task::Task( TaskInterface *tempTask, TimerInterface* tempTimer )
    {
        task = tempTask;
        addTimer( tempTimer );
    };


    QString Task::getTaskName() const
    {
        return task->getTaskName();
    }


    void Task::ExecuteTask()
    {
        task->ExecuteTask();
    }


    void Task::setConfiguration()
    {
        task->setConfiguration();
    }


    void Task::addTimer( TimerInterface* tempTimer )
    {
        // Controllo che non esista già un timer con questo nome
        // se esiste già evito di aggiungerlo e mostro
        // un errore a debug
        if ( timerExists( tempTimer->getTimerName() ) )
        {
            qDebug() << "Questo task ha già un timer con questo nome " << tempTimer->getTimerName() << " pertanto non può essere aggiunto!";
            return;
        }
        timerList.push_back( tempTimer );
    }


    void Task::removeTimer( const QString _timerName )
    {
        for ( auto &timer : timerList )
        {
            if ( _timerName == timer->getTimerName() )
            {
                int timerIndex = timerList.indexOf( timer );
                if ( timerIndex != -1 )
                {
                    delete timer;
                    timerList.remove( timerIndex );
                }
                return;
            }
        }
    }


    void Task::removeAllTimer()
    {
        for ( auto &timer : timerList )
        {
            int timerIndex = timerList.indexOf( timer );
            if ( timerIndex != -1 )
            {
                delete timer;
                timerList.remove( timerIndex );
            }
        }
    }


    bool Task::timerExists( const QString _timerName ) const
    {
        for ( auto timer : timerList )
        {
            if ( _timerName == timer->getTimerName() )
            {
                return true;
            }
        }
        return false;
    }


    QStringList Task::getTimerNameList() const
    {
        QStringList timerNameList{};

        for ( auto timer : timerList )
        {
            timerNameList.push_back( timer->getTimerName() );
        }

        return timerNameList;
    }

}


