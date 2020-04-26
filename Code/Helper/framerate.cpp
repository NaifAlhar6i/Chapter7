#include "framerate.h"

FrameRate::FrameRate()
{

}

void FrameRate::Calculate()
{

    int fpsCounter;
    int fpsNumber;

    fpsCounter = this->getFPSCounter();

    if (const int elapsed = this->getFPSTimer().elapsed())
    {
        fpsNumber = fpsCounter / (elapsed / THOUSAND);
        this->setFPSNumber( fpsNumber );
    }


    if (!(fpsCounter % HANDRED))
    {
        this->getFPSTimer().start();
        fpsCounter = UINT_ZERO;
    }

    fpsCounter++;
    this->setFPSCounter( fpsCounter );

}


int FrameRate::getTickCount()
{
    int timeElapxed;

    timeElapxed = this->getFPSTimer().elapsed();
    return timeElapxed;
}
