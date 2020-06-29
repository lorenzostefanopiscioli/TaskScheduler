# TaskScheduler

## Approccio al progetto
Una volta ricevute le specifiche, e sapendo di dover sviluppare uno scheduler, sono andato a verificare in letteratura se esistessero dei pattern specifici considerati più adatti allo sviluppo di un tale tipo di applicazione. In effetti alcuni documenti suggeriscono di utilizzare un behavioral design pattern: il command. Questo tipo di pattern nella versione più semplice assomigliava molto all'idea di sviluppo che mi stavo facendo ed in effetti è rintracciabile nella interfaccia creata per i task.

Per quanto riguarda il codice, ho cercato di aderire alle linee guida SOLID & DRY. Il codice è suddiviso in molte classi, e in molti piccoli metodi, ciascuno con le proprie responabilità.

Ho sviluppato l'applicazione con QT-Creator, ma non potendo utilizzare il QT-Designer e componenti QML, le parti di interfaccia grafica presenti nel programma sono tutte create dinamicamente nel codice.

Il codice specifico per il test è stato sviluppato all'interno del namespace TiCare.

## Richieste
Come richiesto nella versione attuale l'applicazione esegue due task:
 - Un task, che ho chiamato TaskPrintText, che stampa ogni 10 secondi un testo che può essere impostato a build-time e a run-time.
 - Un task, chiamato TaskFileExists, che ogni 30 secondi controlla se esiste un file su disco ("c:/exempio.txt") e in caso negativo lo segnala sulla console di debug. Il nome del file da controllare può essere modificato a build-time e a run-time.
 
## Logica dell'applicazione
Il tutto parte da una classe Scheduler che permette di programmare l'esecuzione di task. I task vengono elencati in un vettore di puntatori della classe Task.
La classe Task in modo polimorfico è in grado di conservare un puntatore a task che aderisce all'interfaccia definita con la classe astratta TaskInterface, che impone ai task di definire una serie di metodi  necessari per l'esecuzione del task (ExecuteTask), per impostare parametri di configurazione del task (setConfiguration) e in ultimo un getter che restituisce il nome che si vuole attribuire ad un task. Inoltre la classe Task è in grado di associare al proprio task un vettore di puntatori alle classi derivate dall'interfaccia TimerInterface. La classe astratta TimerInterface deriva dalla classe QTimer e sostanzialmente impone alle classi derivate di pubblicare un metodo per restituire il nome univoco usato per identificare uno specifico timer attribuito ad un task. I timer hanno il compito di gestire lo scheduling dei task.
Al momento ho sviluppato due tipi di timer derivanti da TimerInterface:
1) IntervalTimer
2) TimeoutTimer.

#### IntervalTimer
Permette di impostare un compito ripetitivo indicando il momento di inizio delle ripetizioni e l'intervallo di ripetizione (in millisecondi).
Se non viene indicato un momento di inizio, l'avvio del timer a intervalli regolari è immediato.
Nel caso in cui il momento indicato per l'inizio dell'esecuzione dei task sia posteriore al momento attuale, l'avvio dell'intervallo di esecuzione avviene immediatamente.

Esempio: creo un IntervalTimer identificato dalla QString "Controllo file ogni 30s", che avvisa quando è il momento di mandare in esecuzione un task a intervalli regolari di 30 secondi. L'avvio del timer è immediato.

new TiCare::IntervalTimer( "Controllo file ogni 30s", 30000 );

Se per esempio volessimo avviare il timer in modo che mandi in esecuzione un task ogni martedì alle 12 a partire da Martedì 30 giugno 2020, basterebbe istanziare come segue:

new TiCare::IntervalTimer( "Controllo file ogni 30s", 7 * 24 * 3600 * 1000, QDateTime( QDate( 2020, 6, 30 ), QTime( 12, 0, 0 ) ) );


#### TimeoutTimer
Segue una logica simile al timer IntervalTimer, ma è single shot. Quindi il task può essere eseguito una volta sola alla data e all'ora prestabilite.

Esempio:

new TiCare::TimeoutTimer( "Timeout to Print Text", QDateTime( QDate( 2020, 6, 29 ), QTime( 11, 43, 0 ) ) );

#### Nota
Se c'è bisogno di un tipo di timer che svolga ulteriori e diversi scheduling rispetto ai due che ho implementato, basta sviluppare una classe che soddisfi l'interfaccia TimerInterface.


## i Task
Per trasformare una classe in un task utilizzabile da Scheduler basta che derivi e implementi l'interfaccia TaskInterface.
Per questa applicazione come da richieste ho realizzato due miniclassi:

- TaskPrinterText: che stampa su console di debug un testo definito dall'utente
- TaskFileExists: che verifica se un file è presente su disco e in caso negativo lo segnala nella console di debug

Per aggiungere questi task allo scheduler secondo le richieste nel main ho inserito le seguenti linee di codice:

    TiCare::Scheduler scheduler{};

    scheduler.addTask( new TiCare::TaskPrintText( "Print Text", "Testo di default" ), new TiCare::IntervalTimer( "Interval Timer1 of Print Text", 10000 ) );
    scheduler.addTask( new TiCare::TaskFileExists( "File Exists", "c:/esempio.txt" ), new TiCare::IntervalTimer( "Controllo file ogni 2s", 30000 ) );

## L'applicazione
All'avvio dell'applicazione viene aggiunta una icona nella system tray. Cliccando col tasto destro sull'icona del programma appare un menu contestuale col quale si può:

1) chiudere l'applicazione
2) aprire la finestra di dialogo delle impostazioni

Nella finestra di dialogo è visibile un combobox con l'elenco dei Task attualmente in scheduler. Selezionando uno dei task, nella listview sottostante appare l'elenco dei timer associati al task che definiscono quando il task verrà eseguito.

Più in basso è presente il pulsante configurazione che richiama le funzioni di configurazione previste dal task selezionato nel combobox.

### Nota
E' implementato un sistema di controlli per evitare che vengano aggiunti due task con lo stesso nome, e all'interno di un task viene impedito che vengano aggiunti due timer con lo stesso nome.


## Specifiche:

- Sistema operativo di sviluppo: Windows
- Versione QT 5.15.0
- Compilatore C++ MinGW
- Impostazioni di compilazione C++ 17
- Non è stato usato QT-Designer
- Non ho usato componenti QML
- Ho usato quasi esclusivamente componenti della libreria QT
- Non ho fatto uso di STL
- Progetto caricato su GitHub
- L'applicazione fa uso del componente QSystemTrayIcon
- Possibilità di espandere i task al bisogno
- Possibilità di schedulare l'esecuzione dei task in modo molto flessibile e modulare
