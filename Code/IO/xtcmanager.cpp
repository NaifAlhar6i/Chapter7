#include "xtcmanager.h"

XTCManager::XTCManager( GROManager *gromanager) :
    m_GROManager(gromanager)
{
}

void XTCManager::FetchFrames(const unsigned int start, const unsigned int end, short stride)
{
    this->readFrames( start, end, stride );
}

void XTCManager::readFrames(const unsigned int &start, const unsigned int &end, short stride)
{
    unsigned int framesNumber(0);
    int currentFrameNumber(0);
    int xtcResult(0);


    this->openXTC();

    //Move to first frame if the user select to start from frame other than frame number 1.
    currentFrameNumber = this->moveToFirstFrame( start, ATOMS_NUMBER );

    xtcResult = 0;

    if (stride == 0)
    {
       framesNumber = this->readSequencedFrames( ATOMS_NUMBER, currentFrameNumber, end );
    }
    else
    {
       framesNumber = this->readUnSequenceFrames( ATOMS_NUMBER, currentFrameNumber, end, stride );
    }

    //Fetcher::getTrajectoryInfoRef().FramesNumber = framesNumber;


    this->closeXTC();
}

int XTCManager::readFrame(unsigned int atomsnumber, unsigned int &frameindex)
{
    matrix box_xtc;
    int state;
    int xtcStep;
    float xtcTime;
    QVector3D systemDimentions;
    QVector3D minDimentions;
    QVector3D maxDimentions;
    float dimentionX;
    float dimentionY;
    float dimentionZ;

    rvec *frame = (rvec*)calloc( atomsnumber, RVEC_SIZE );

    state = read_xtc( this->getXDRFile(), atomsnumber, &xtcStep, &xtcTime,
            box_xtc, frame, &PREC_XTC );

    dimentionX = box_xtc[0][0];
    dimentionY = box_xtc[1][1];
    dimentionZ = box_xtc[2][2];

    //Copy the first frame to be areference
    if( frameindex == UINT_ZERO )
    {
        memcpy( DataStructure::getFirstFrame(), frame, FRAME_SIZE );
    }

    systemDimentions = QVector3D( dimentionX , dimentionY, dimentionZ);

    computeFrameMinMaxBoundaries( minDimentions, maxDimentions, frame);

    emit FrameFetched(frameindex, frame, systemDimentions, minDimentions, maxDimentions );

    free( frame );

    return state;
}

int XTCManager::readUnSequenceFrames(unsigned int atomsnumber, int &currentframenumber, int end, int stride)
{
    int xtcResult(0);
    unsigned int frameIndex(0);

    while (xtcResult == exdrOK)
    {
        if (currentframenumber % stride == 0 && currentframenumber <= end)
        {
            xtcResult = this->readFrame( atomsnumber, frameIndex );
            frameIndex++;
            ++currentframenumber;
        }
        else
        {
            ++currentframenumber;
            xtcResult = this->skipFrame( atomsnumber );
        }


        if (currentframenumber >= end || xtcResult == exdrENDOFFILE)
        {
            currentframenumber--;
            break;
        }
    }

    return frameIndex;
}

int XTCManager::readSequencedFrames(unsigned int atomsnumber, int &currentframenumber, int end)
{
    unsigned int frameIndex(0);
    int xtcResult(0);

    while (xtcResult == exdrOK  && currentframenumber < end)
    {
        xtcResult = this->readFrame( atomsnumber, frameIndex );


        if(xtcResult == exdrENDOFFILE)
        {
            frameIndex--;
            break;
        }

        frameIndex++;
        ++currentframenumber;
    }

    return frameIndex;
}

int XTCManager::skipFrame(unsigned int atomsnumber)
{
    matrix box_xtc;
    int state;
    int xtcStep;
    float xtcTime;
    rvec frame[atomsnumber];

    state = read_xtc( this->getXDRFile(), atomsnumber, &xtcStep, &xtcTime,
                     box_xtc, &frame[0], &PREC_XTC );


    return state;
}

void XTCManager::computeFrameMinMaxBoundaries(QVector3D &minDimentions, QVector3D &maxDimentions, rvec *frame)
{

    float newXDimention;
    float newYDimention;
    float newZDimention;

    float minXDimention = 200.0;
    float minYDimention = 200.0;
    float minZDimention = 200.0;
    float maxXDimention = -200.0;
    float maxYDimention = -200.0;
    float maxZDimention = -200.0;

    for( unsigned int atomsIndex = UINT_ZERO; atomsIndex < ATOMS_NUMBER; atomsIndex++ )
    {
        newXDimention =  *((*((rvec *)frame + atomsIndex)) + X);
        newYDimention =  *((*((rvec *)frame + atomsIndex)) + Y);
        newZDimention =  *((*((rvec *)frame + atomsIndex)) + Z);

        min(minXDimention, newXDimention);
        min(minYDimention, newYDimention);
        min(minZDimention, newZDimention);

        max(maxXDimention, newXDimention);
        max(maxYDimention, newYDimention);
        max(maxZDimention, newZDimention);

    }

    minXDimention = fAbs(minXDimention);
    minYDimention = fAbs(minYDimention);
    minZDimention = fAbs(minZDimention);

    minDimentions.setX( minXDimention );
    minDimentions.setY( minYDimention );
    minDimentions.setZ( minZDimention );

    maxDimentions.setX( maxXDimention );
    maxDimentions.setY( maxYDimention );
    maxDimentions.setZ( maxZDimention );

}

void XTCManager::min(float &value1, float value2)
{
    if( value1 > value2)
    {
        value1 = value2;
    }
}

void XTCManager::max(float &value1, float value2)
{
    if( value1 < value2)
    {
        value1 = value2;
    }
}

float XTCManager::fAbs(float value)
{
    float absoluteValue;

    absoluteValue = value;
    if( value < 0.0f )
    {
        absoluteValue = value * -1.0f;
    }

    return absoluteValue;
}

int XTCManager::moveToFirstFrame(unsigned int start, unsigned int atomsnumber)
{
    int index(0);
    int xtcResult;

    for (unsigned int frameIndex = 1; frameIndex < start; frameIndex++)
    {
        xtcResult = this->skipFrame(  atomsnumber );

        if(xtcResult != exdrOK)
        {
            break;
        }

        ++index;
    }

    return index;
}

void XTCManager::closeXTC()
{
    xdrfile_close( getXDRFile() );
}

void XTCManager::openXTC()
{
    QString xtcFile;

    xtcFile = DATA_DIRECTORY + XTC_FILE;
    m_XTC_Read = xdrfile_open( xtcFile.toStdString().c_str(), "r");
}
