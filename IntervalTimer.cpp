#include "IntervalTimer.h"


namespace TiCare {


    IntervalTimer::IntervalTimer( const QString _timerName, const int _interval  )
    {
        timerName = _timerName;
        start( _interval );
    }


    IntervalTimer::IntervalTimer( const QString _timerName, const int _interval, const QDateTime dateTime )
    {
        timerName = _timerName;

        QDateTime now = QDateTime::currentDateTime();
        auto _timeout = now.msecsTo( dateTime );

        // Se la data risulta antecedente al momento attuale
        // avvio subito l'interval timer
        if ( _timeout < 0 )
        {
            _timeout = 0;
        }

        QTimer::singleShot( _timeout, [ = ] ()
        {
            start( _interval );
        });
    }

    QString IntervalTimer:: getTimerName() const {
        return timerName;
    }

}
