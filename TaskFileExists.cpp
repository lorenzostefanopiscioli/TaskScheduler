#include "TaskFileExists.h"


namespace TiCare {

    QString TaskFileExists::getTaskName() const
    {
        return taskName;
    }


    // Implemento il task da eseguire
    void TaskFileExists::ExecuteTask()
    {
        if ( !QFile( fileName ).exists() )
        {
            qDebug() << "Il file " << fileName << " non esiste o non c'è nel percorso indicato!";
        }
    }


    void TaskFileExists::setConfiguration()
    {
        bool ok;
        // do-while mi garantisce almeno una volta la richiesta del nome
        do
        {
            fileName = QInputDialog::getText( 0,
                                              "Ti-Care",
                                              "File da controllare:",
                                              QLineEdit::Normal,
                                              fileName,
                                              &ok );
            if ( fileName.isEmpty() )
            {
                QMessageBox::information( 0,
                                          "Attenzione",
                                          "Deve per forza essere indicato il nome di un file!" );
            }
        } while ( fileName.isEmpty() || !ok );
    }

}
