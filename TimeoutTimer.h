#ifndef TIMEOUTTIMER_H
#define TIMEOUTTIMER_H


#include "TimerInterface.h"


namespace TiCare {

    class TimeoutTimer : public virtual TimerInterface
    {
        public:
            // Il nome del timer deve essere univoco
            explicit TimeoutTimer( const QString _timerName, const int _timeout );
            explicit TimeoutTimer( const QString _timerName, const QDateTime dateTime );
            virtual QString getTimerName() const override;

        private:
            // Questa macro permette di usare il sistema di slot e signals di QT
            Q_OBJECT
            // Questa macro dice a QT quale interfaccia implementare
            Q_INTERFACES( TiCare::TimerInterface )

            QString timerName;

    };

}

#endif // TIMEOUTTIMER_H
