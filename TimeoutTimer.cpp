#include "TimeoutTimer.h"


namespace TiCare {

    TimeoutTimer::TimeoutTimer( const QString _timerName, const int _timeout  )
    {
        timerName = _timerName;
        setSingleShot( true );
        start( _timeout );
    }


    TimeoutTimer::TimeoutTimer( const QString _timerName, const QDateTime dateTime )
    {
        timerName = _timerName;
        setSingleShot( true );

        QDateTime now = QDateTime::currentDateTime();
        auto _timeout = now.msecsTo( dateTime );

        if ( _timeout < 0 )
        {
            qDebug() << "Per avviare il timeout bisogna indicare una data futura!";
            return;
        }

        start( _timeout );
    }


    QString TimeoutTimer::getTimerName() const {
        return timerName;
    }

}
