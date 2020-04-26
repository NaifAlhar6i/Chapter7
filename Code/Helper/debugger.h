#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QDebug>
#include <QTime>
#include "include/constdata.h"

/**
 * @brief The Debugger class provides debugging functionallities
 */
class Debugger
{
public:
    /**
     * @brief Debugger class constructor
     */
    Debugger();

    /**
     * @brief Debug printout the error data
     * @param debug specifies the error data
     */
    void Debug( QString debug );

    /**
     * @brief Debug printout the error details
     * @param messages specifies the error details including the class name .. etc
     */
    void Debug(QVector<QString> messages);

    /**
     * @brief TimerStart fires the timer
     * @param tasktitle specifies the task name
     */
    void TimerStart(QString tasktitle);

    /**
     * @brief TimerEnd stop the timer and printout the time elapced
     * @param tasktitle specifies the task name
     */
    void TimerEnd(QString tasktitle);
private:

    /**
     * @brief m_Time timer object
     */
    static QTime m_Time;

    /**
     * @brief getTime accessor for the timer object
     * @return a reference to the timer object
     */
    QTime &getTime() { return m_Time;}

};

#endif // DEBUGGER_H
