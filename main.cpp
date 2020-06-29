#include <QApplication>
#include <QMessageBox>

#include "Scheduler.h"
#include "TaskPrintText.h"
#include "TaskFileExists.h"
#include "MainDialog.h"



int main( int argc, char *argv[] )
{
    // forza l'inizializzazione delle risorse nella libreria,
    // assicurando che verranno linkate nell'applicazione
    Q_INIT_RESOURCE( Resources );

    // Istanzia l'applicazione
    QApplication application( argc, argv );

    // Se il sistema non supporta una system tray l'applicazione avvisa
    // che non può avviarsi e termina l'esecuzione
    if ( !QSystemTrayIcon::isSystemTrayAvailable() ) {
        QMessageBox::critical( nullptr,
                               QObject::tr( "Ti-Care | Scheduler" ),
                               QObject::tr( "Non è possibile avviare l'applicazione "
                                            "perchè in questo sistema non è stata "
                                            "individuata una system tray." ) );
        return EXIT_SUCCESS;
    }

    // Evita che l'applicazione venga chiusa anche se vengono chiuse tutte le finestre
    QApplication::setQuitOnLastWindowClosed( false );



    /* ------------------------------------------------------------------------
     * IMPOSTAZIONE SCHEDULER
     * ------------------------------------------------------------------------
     * Come previsto dal test tecnico nell'applicazione sono impostati a
     * build-time due task nello scheduler.
     * 1) TaskPrintText che permette di impostare un testo e lo stampa ogni
     *    10 secondi nella console di debug
     * 2) TaskFileExists che verifica se un file esiste su disco o meno e in
     *    caso negativo avvisa nella console di debug
    ------------------------------------------------------------------------ */
    TiCare::Scheduler scheduler{};

    scheduler.addTask( new TiCare::TaskPrintText( "Print Text", "Testo di default" ), new TiCare::IntervalTimer( "Interval Timer1 of Print Text", 10000 ) );
    scheduler.addTask( new TiCare::TaskFileExists( "File Exists", "c:/esempio.txt" ), new TiCare::IntervalTimer( "Controllo file ogni 2s", 30000 ) );

    // scheduler.getTask( "File Exists" )->addTimer( new TiCare::IntervalTimer( "Controllo file ogni 5s", 5000 ) );
    // scheduler.addTask( new TiCare::TaskPrintText( "Test", "xxxx" ), new TiCare::TimeoutTimer( "Timeout to Print Text", QDateTime( QDate( 2020, 6, 29 ), QTime( 11, 43, 0 ) ) ) );   // year, month, day | hour, min, sec
    // scheduler.getTask( "File Exists" )->removeTimer( "Interval Timer of File Exists" );
    // scheduler.getTask( "File Exists" )->removeAllTimer();
    // scheduler.removeTask( "File Exists" );

    // ------------------------------------------------------------------------


    
    // Istanzia la finestra di gestione delle impostazioni dello Scheduler
    MainDialog mainDialog( &scheduler );

    return application.exec();
}
