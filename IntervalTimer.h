#ifndef INTERVALTIMER_H
#define INTERVALTIMER_H

#include "TimerInterface.h"


namespace TiCare {

    /*
     * Classe derivata dall'interfaccia TimerInterface a sua volta derivata da QTimer
     * Le classi concrete devono per forza implementare il metodo getTimerName che
     * restituisce il nome univoco assegnato al timer in fase di istanziazione
     */
    class IntervalTimer : public virtual TimerInterface
    {
        public:
            explicit IntervalTimer( const QString _timerName, const int _interval );
            explicit IntervalTimer( const QString _timerName, const int _interval, const QDateTime dateTime );
            virtual QString getTimerName() const override;

        private:
            // Questa macro permette di usare il sistema di slot e signals di QT
            Q_OBJECT
            // Questa macro dice a QT quale interfaccia implementare
            Q_INTERFACES( TiCare::TimerInterface )

            QString timerName;

    };

}

#endif // INTERVALTIMER_H
