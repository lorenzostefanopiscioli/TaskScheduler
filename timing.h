#ifndef TIMING_H
#define TIMING_H


namespace TiCare {

    enum class dayOfWeek { Lunedi, Martedi, Mercoledi, Giovedi,
                           Venerdi, Sabato, Domenica };

    enum class month { Gennaio, Febbraio, Marzo, Aprile, Maggio, Giugno,
                       Luglio, Agosto, Settembre, Ottobre, Novembre, Dicembre };


    // Interfaccia Timing
    class TimingInterface {

        public:

            TimingInterface(){};
            // Necessario distruttore virtuale
            virtual ~TimingInterface(){};

            // Inibisco i costruttori per copia e per spostamento, e
            // gli operatori di assegnamento per copia e spostamento
            TimingInterface( const TimingInterface& other) = delete;
            TimingInterface& operator=( const TimingInterface& other ) = delete;

            TimingInterface( TimingInterface&& other) = delete;
            TimingInterface& operator=( TimingInterface&& other ) = delete;

        // Metodi virtuali puri dell'interfaccia

            // Restituisce un timestamp alla scadenza dell'intervallo attuale
            // Quando restituisce 0, la deadline è scaduta
            virtual unsigned long int getNextDeadlineTimestamp() const = 0;
    };


    // Gestisce le scadenze ad intervalli regolari
    class IntervalTiming : public virtual TimingInterface {

        public:

            // constructor con intervallo per timing a intervalli regolari.
            // _interval è misurato in secondi
            // _timeBeforeStarting indica tra quanti secondi si dovrà iniziare a
            // calcolare intervalli di tempo. Se è 0 parte immediatamente.
            IntervalTiming( const unsigned long int _interval,
                            const unsigned long int _timeBeforeStarting = 0 ) :
                            interval( _interval ),
                            timeBeforeStarting( _timeBeforeStarting ) {};

            // Restituisce un timestamp alla scadenza dell'intervallo attuale
            // Quando restituisce 0, la deadline è scaduta
            virtual unsigned long int getNextDeadlineTimestamp() const override;

        private:
            unsigned long int interval = 0;
            unsigned long int timeBeforeStarting;
    };


    // Gestisce una singola scadenza
    class OneShotTiming : public virtual TimingInterface {

        public:

            // constructor con indicazione del timestamp futuro in cui
            // ci sarà la deadline
            // controllare che _deadlineTimestamp sia maggiore del
            // timestamp attuale
            OneShotTiming( const unsigned long int _deadlineTimestamp ) :
                           _deadlineTimestamp( _deadlineTimestamp ) {};

            // Restituisce un timestamp alla scadenza dell'intervallo attuale
            // Quando restituisce 0, la deadline è scaduta
            virtual unsigned long int getNextDeadlineTimestamp() const override;

        private:
            unsigned long int _deadlineTimestamp = 0;
    };


    // Gestisce scadenze programmate in momenti precisi
    class CronTiming : public virtual TimingInterface {

        public:

            // Costruttore di default per un timing in stile cron
            CronTiming( const short int secondIndex = -1,
                        const short int minuteIndex = -1,
                        const short int hourIndex = -1,
                        const short int dayOfWeekIndex = -1,
                        const short int dayOfMonthIndex = -1,
                        const short int monthIndex = -1 );

            // Restituisce un timestamp alla scadenza dell'intervallo attuale
            // Quando restituisce 0, la deadline è scaduta
            virtual unsigned long int getNextDeadlineTimestamp() const override;


            // Setter & Getter per impostare in quali secondi all'interno di un
            // minuto deve essere emesso un segnale di deadline
            void setSecond( const short int secondIndex, const bool activate = true );
            bool getSecond( const short int secondIndex );

            // Imposta tutti i secondi
            void setAllSeconds( const bool activate = true );


            // Setter & Getter per impostare in quali minuti all'interno di un'ora
            // deve essere emesso un segnale di deadline
            void setMinute( const short int minuteIndex, const bool activate = true );
            bool getMinute( const short int minuteIndex );

            // Imposta tutti i minuti
            void setAllMinutes( const bool activate = true );


            // Setter & Getter per impostare in quali ore all'interno di un giorno
            // deve essere emesso un segnale di deadline
            void setHour( const short int hourIndex, const bool activate = true );
            bool getHour( const short int hourIndex );

            // Imposta tutte le ore
            void setAllHours( const bool activate = true );


            // Setter & Getter per impostare in quali giorni all'interno di una
            // settimana deve essere emesso un segnale di deadline
            void setDayOfWeek( const short int dayOfWeekIndex, const bool activate = true );
            bool getDayOfWeek( const short int dayOfWeekIndex );

            // Imposta tutti i giorni della settimana
            void setAllDayOfWeek( const bool activate = true );


            // Setter & Getter per impostare in quali giorni all'interno di un
            // mese deve essere emesso un segnale di deadline
            void setDayOfMonth( const short int dayOfMonthIndex, const bool activate = true );
            bool getDayOfMonth( const short int dayOfMonthIndex );

            // Imposta tutti i giorni del mese
            void setAllDayOfMonth( const bool activate = true );


            // Setter & Getter per impostare in quali mesi all'interno di un
            // anno deve essere emesso un segnale di deadline
            void setMonth( const short int monthIndex, const bool activate = true );
            bool getMonth( const short int monthIndex );

            // Imposta tutti i mesi
            void setAllMonths( const bool activate = true );


        private:
            bool seconds[ 59 ] = { false };
            bool minutes[ 59 ] = { false };
            bool hours[ 23 ] = { false };
            bool dayOfWeek[ 6 ] = { false };
            bool dayOfMonth[ 30 ] = { false };
            bool month[ 11 ] = { false };
    };

}

#endif // TIMING_H
