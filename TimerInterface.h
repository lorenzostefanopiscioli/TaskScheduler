#ifndef TIMERINTERFACE_H
#define TIMERINTERFACE_H


#include <QCoreApplication>
#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QDebug>


namespace TiCare {

    // Interfaccia per i timer dello scheduler: garantisce uniformità
    // dei timer nel caso si voglia aggiungere un nuovo tipo di timer
    // con nuove funzionalità
    class TimerInterface : public QTimer {

        public:

            // Deve esserci un solo costruttore
            explicit TimerInterface(){};

            // Necessario distruttore virtuale
            virtual ~TimerInterface(){};

            // Inibisco i costruttori per copia e per spostamento, e
            // gli operatori di assegnamento per copia e spostamento
            Q_DISABLE_COPY_MOVE( TimerInterface );

        // Metodi virtuali puri dell'interfaccia

            virtual QString getTimerName() const = 0;
    };

}

// Dichiaro l'interfaccia in stile QT
Q_DECLARE_INTERFACE( TiCare::TimerInterface, "TiCare.TimerInterface" );


#endif // TIMERINTERFACE_H
