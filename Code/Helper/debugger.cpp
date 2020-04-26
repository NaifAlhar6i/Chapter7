#include "debugger.h"

QTime Debugger::m_Time;

Debugger::Debugger()
{

}

void Debugger::Debug(QString debug)
{
    qDebug() << debug;
}

void Debugger::Debug(QVector<QString> messages)
{
    unsigned int messagesNumber;
    QString messagesContainer;

    messagesNumber = messages.size();
    messagesContainer = "==Start Message==\n";
    messagesContainer += "Class:" + messages.at( UINT_ZERO) +"\nMessage(s):\n";
    for(unsigned int messageIndex= UINT_ONE; messageIndex < messagesNumber; messageIndex++)
    {
        messagesContainer+= messages.at( messageIndex ) + "\n";
    }
    messagesContainer+= "==End message==";
    qDebug().noquote() << messagesContainer;

}

void Debugger::TimerStart(QString tasktitle)
{
    qDebug() << tasktitle << " Started!";
    getTime().start();
}

void Debugger::TimerEnd(QString tasktitle)
{
    qDebug() << tasktitle << " Has been done in " << getTime().elapsed();
}
