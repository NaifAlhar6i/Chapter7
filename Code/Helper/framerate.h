#ifndef FRAMERATE_H
#define FRAMERATE_H

#include <QTime>
#include "include/constdata.h"

/**
 * @brief The FrameRate class provides the functulity for calculating the rendering frame rate
 */
class FrameRate
{
public:
    /**
     * @brief FrameRate class constructor
     */
    FrameRate();

    /**
     * @brief Calculate calculates the frame rate
     */
    void Calculate();

    /**
     * @brief GetRate gets the current frame rate
     * @return the frame rate value
     */
    inline int GetRate() { return this->getFPSNumber(); }
private:
    /**
     * @brief m_FPSTimer frame rate time object
     */
    QTime m_FPSTimer;

    /**
     * @brief m_FPSCounter the counter of the frame rate
     */
    int m_FPSCounter ;

    /**
     * @brief m_FPSNumber number of frames per second
     */
    int m_FPSNumber ;

//    int m_FPSPreviousTime ;

    /**
     * @brief setFPSCounter sets the current FPS value
     * @param newcount specifies the FPS new value
     */
    inline void setFPSCounter( int newcount) {  m_FPSCounter = newcount; }

    /**
     * @brief setFPSNumber sets the current FPS number science the current calculation
     * @param number specifies the FPS number
     */
    inline void setFPSNumber( int number) { m_FPSNumber = number; }
//    inline void setFPSPreviousTime( int previoustime) { m_FPSPreviousTime = previoustime; }

    /**
     * @brief getFPSTimer accessor for the timer object
     * @return a reference of the timer object
     */
    inline QTime &getFPSTimer() { return m_FPSTimer; }

    /**
     * @brief getFPSCounter getter for the FPS counter
     * @return  the FPS counter
     */
    inline int getFPSCounter() { return m_FPSCounter; }
//    inline int getFPSPreviousTime() { return m_FPSPreviousTime; }

    /**
     * @brief getFPSNumber gets the current FPS number
     * @return
     */
    inline int getFPSNumber() { return m_FPSNumber; }

    /**
     * @brief getTickCount gets the time elapced since the last frame
     * @return the time elapced
     */
    int getTickCount();
};

#endif // FRAMERATE_H
