#ifndef TASKINTERFACE_H
#define TASKINTERFACE_H


#include <QCoreApplication>
#include <QObject>


namespace TiCare {

    // Interfaccia per i Task: ogni task deve garantire l'overriding dei metodi
    // virtuali pure di questa interfaccia
    // Questa interfaccia integra il tipo più semplice di Command Pattern
    class TaskInterface : public QObject {

        public:

            // Deve esserci un solo costruttore
            explicit TaskInterface(){};

            // Necessario distruttore virtuale
            virtual ~TaskInterface(){};

            // Inibisco i costruttori per copia e per spostamento, e
            // gli operatori di assegnamento per copia e spostamento
            Q_DISABLE_COPY_MOVE( TaskInterface );

        // Metodi virtuali puri dell'interfaccia

            virtual QString getTaskName() const = 0;
            virtual void ExecuteTask() = 0;
            virtual void setConfiguration() = 0;

    };

}

// Dichiaro l'interfaccia in stile QT
Q_DECLARE_INTERFACE( TiCare::TaskInterface, "TiCare.TaskInterface" );


#endif // TASKINTERFACE_H
