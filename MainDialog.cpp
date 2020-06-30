#include "MainDialog.h"


MainDialog::MainDialog( const TiCare::Scheduler *_scheduler, QWidget *parent ) : QDialog( parent ), scheduler( _scheduler )
{   
    createSystemTrayIconActions();
    createSystemTrayIcon();

    taskComboBox = new QComboBox;
    taskComboBox->addItem( tr( "Seleziona un task" ) );
    taskComboBox->addItems( scheduler->getTaskNameList() );

    timeList = new QListWidget;

    QGroupBox *taskListGroupBox = new QGroupBox( tr( "List" ) );
        QVBoxLayout *taskListLayout = new QVBoxLayout;
            taskListLayout->addWidget( taskComboBox );
            taskListLayout->addWidget( timeList );
    taskListGroupBox->setLayout( taskListLayout );

    QPushButton *configButton = new QPushButton( "Configurazione" );
    QPushButton *closeButton = new QPushButton( "Nascondi" );

    QGroupBox *buttonGroupBox = new QGroupBox();
        QHBoxLayout *buttonGroupLayout = new QHBoxLayout;
        buttonGroupLayout->addWidget( configButton );
        buttonGroupLayout->addWidget( closeButton );
    buttonGroupBox->setLayout( buttonGroupLayout );


    QGridLayout *mainLayout = new QGridLayout;

        mainLayout->addWidget( taskListGroupBox, 0, 0, 5, 1 );
        mainLayout->addWidget( buttonGroupBox, 5, 0, 1, 1 );

    setLayout( mainLayout );

    connect( taskComboBox, &QComboBox::currentTextChanged, this, &MainDialog::setTimeList );
    connect( closeButton, &QAbstractButton::clicked, this, &MainDialog::hide );
    connect( configButton, &QAbstractButton::clicked, this, &MainDialog::configTask );

    systemTrayIcon->show();

    // Assegna titolo, icona e dimensione alla finestra di gestione
    // delle impostazioni dello Scheduler
    setWindowTitle( tr( "Ti-Care | Scheduler" ) );
    setWindowIcon( QIcon( ":/Icons/logo64x64.png" ) );
    resize( 500, 400 );
}


void MainDialog::closeEvent( QCloseEvent *event )
{
    if ( systemTrayIcon->isVisible() )
    {
         QMessageBox::information( this, tr( "Ti-Care | Scheduler" ),
                                   tr( "Il programma resterà attivo nella "
                                       "system tray di Windows. Per terminare, "
                                       "l'applicazione, cliccare <b>Chiudi</b> "
                                       "nel menu contestuale della system "
                                       "tray." ) );

        // Nascondo il dialogo delle impostazioni
        hide();
        // Interrompo l'ulteriore propagazione dell'evento
        event->ignore();
    }
}


void MainDialog::createSystemTrayIconActions()
{
    // Connette la voce del menu contestuale della system tray "Impostazioni"
    // all'apertura della finestra di dialogo per il controllo delle
    // configurazioni
    showSettingsDialogAction = new QAction( tr( "&Impostazioni" ), this );
    connect( showSettingsDialogAction, &QAction::triggered, this, &QWidget::showNormal );

    // Istanzia l'azione di chiusura e la connette con
    // l'effettiva chiusura dell'applicazione
    quitAction = new QAction( tr( "&Chiudi" ), this );
    connect( quitAction, &QAction::triggered, qApp, &QCoreApplication::quit );
}


// Metodo che imposta l'interazione dell'applicazione
// con la system tray del sistema operativo
void MainDialog::createSystemTrayIcon()
{
    // Crea un menu contestuale per la System Tray
    systemTrayIconMenu = new QMenu( this );
    // Aggiunge al menu contestuale il comando per mostrare
    // la finestra di gestione delle impostazioni
    systemTrayIconMenu->addAction( showSettingsDialogAction );
    systemTrayIconMenu->addSeparator();
    // Aggiunge al menu contestuale il comando per chiudere
    // l'applicazione
    systemTrayIconMenu->addAction( quitAction );

    // Istanzia un oggetto System Tray Icon
    systemTrayIcon = new QSystemTrayIcon( this );
    // Assegna alla System Tray il menu contestulae
    systemTrayIcon->setContextMenu( systemTrayIconMenu );

    // Assegna l'icona che verrà visualizzata nella System Tray di Windows
    systemTrayIcon->setIcon( QIcon( ":/Icons/logo64x64.png" ) );
}


// Questo metodo serve ad aggiornare la lista dei timer
void MainDialog::setTimeList( const QString currentText )
{
    // Se non viene selezionato alcun task, esco
    if ( currentText == "Seleziona un task" )
    {
        timeList->clear();
        return;
    }
    // Svuoto la lista dei nomi dei timer associata al task scelto in
    // precedenza
    timeList->clear();
    // aggiungo i nomi dei timer alla lista associata al nuovo task scelto
    timeList->addItems( scheduler->getTask( currentText )->getTimerNameList() );
}


// Questo metodo viene invocato a seguito di un click sul bottone impostazioni
// ed eseguie il metodo virtuale setConfiguration() del task selezionato nel
// combobox
void MainDialog::configTask()
{
    // Se non viene selezionato alcun task, esco
    if ( taskComboBox->currentText() == "Seleziona un task" )
    {
        return;
    }
    // Invoco il metodo virtuale per la configurazione del task
    scheduler->getTask( taskComboBox->currentText() )->setConfiguration();
}






























