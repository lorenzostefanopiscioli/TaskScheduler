#include "TaskPrintText.h"


namespace TiCare {

    QString TaskPrintText::getTaskName() const
    {
        return taskName;
    }


    // Implemento il task da eseguire
    void TaskPrintText::ExecuteTask()
    {
        // Se il testo non è ancora stato configurato, non stampo nulla
        if ( textToBePrinted.isEmpty() )
        {
            return;
        }

        qDebug() << textToBePrinted;
    }


    void TaskPrintText::setConfiguration()
    {
        bool ok;
        while ( textToBePrinted.isEmpty() || !ok )
        {
            textToBePrinted = QInputDialog::getText( 0,
                                                     "Ti-Care",
                                                     "Testo da stampare:",
                                                     QLineEdit::Normal,
                                                     textToBePrinted,
                                                     &ok );
            if ( textToBePrinted.isEmpty() )
            {
                QMessageBox::information( 0,
                                          "Attenzione",
                                          "Non si può lasciare il testo vuoto!" );
            }
        }
    }

}



