#include "MainDialog.h"


MainDialog::MainDialog( TiCare::Scheduler *_scheduler, QWidget *parent ) : QDialog( parent )
{   
    scheduler = _scheduler;

    createSystemTrayIconActions();
    createSystemTrayIcon();



    taskComboBox = new QComboBox;
    taskComboBox->addItem( tr( "Seleziona un task" ) );
    taskComboBox->addItems( scheduler->getTaskNameList() );


    timeList = new QListWidget;
        // timeList->addItems( scheduler.getTask( "File Exists" )->getTimerNameList() );

    QGroupBox *taskListGroupBox = new QGroupBox( tr( "List" ) );
        QVBoxLayout *taskListLayout = new QVBoxLayout;
            taskListLayout->addWidget( taskComboBox );
            taskListLayout->addWidget( timeList );
    taskListGroupBox->setLayout( taskListLayout );

    configButton = new QPushButton( "Configurazione" );
    QPushButton *closeButton = new QPushButton( "Chiudi" );

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


MainDialog::~MainDialog()
{
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
    showSettingsDialogAction = new QAction( tr( "&Impostazioni" ), this );
    connect( showSettingsDialogAction, &QAction::triggered, this, &QWidget::showNormal );

    // Istanzia l'azione di chiusura e la connette con
    // l'effettiva chiusura dell'applicazione
    quitAction = new QAction( tr( "&Chiudi" ), this );
    connect( quitAction, &QAction::triggered, qApp, &QCoreApplication::quit );
}


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


void MainDialog::setTimeList( const QString currentText )
{
    if ( currentText == "Seleziona un task" )
    {
        timeList->clear();
        return;
    }
    timeList->clear();
    timeList->addItems( scheduler->getTask( currentText )->getTimerNameList() );
}


void MainDialog::configTask()
{
    if ( taskComboBox->currentText() == "Seleziona un task" )
    {
        return;
    }
    scheduler->getTask( taskComboBox->currentText() )->setConfiguration();
}






























