#include "Task.h"


namespace TiCare {

    Task::Task( TaskInterface *tempTask, TimerInterface* tempTimer )
    {
        task = tempTask;
        addTimer( tempTimer );
    }


    // Libero le risorse occupate dalle istanze dei timer associati al task
    Task::~Task()
    {
        removeAllTimer();
    }


    // Restituisce il nome del task
    QString Task::getTaskName() const
    {
        return task->getTaskName();
    }


    // Invoca il metodo virtuale di esecuzione di un task
    void Task::ExecuteTask()
    {
        task->ExecuteTask();
    }


    // Invoca il metodo virtuale di configurazione di un task
    void Task::setConfiguration()
    {
        task->setConfiguration();
    }


    // agginge un timer
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


    // Rimuovo un timer
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


    // Rimuovo tutti i timer
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


    // Verifica se esiste un timer con un certo nome
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


    // Restituisce la lista dei nomi dei timer
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


