#include "compathhandler.h"

COMPathHandler::COMPathHandler() : m_PathIndex(FRAMES_NUMBER), m_FirstByte(UINT_ZERO)
{

}

const char *COMPathHandler::mapPath(unsigned int frameindex, unsigned int buffersize)
{
    const char *data;
    QString comPathFile;
    long firstByte = UINT_ZERO;
    long bytePosition;
    unsigned int frameIndex;

    comPathFile = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_PATH_FILE;
    frameIndex = this->getFrameIndex();

    if( frameIndex == frameindex)
    {
        data = this->getPathStream().data() + this->getFirstByte();
        return data;
    }

    this->computePathBytePosition( frameindex, buffersize);

    firstByte    = this->getFirstByte(  );
    bytePosition = this->getBytePosition( );




    if( ! this->getPathStream().is_open() )
    {
        this->getPathStream().open( comPathFile.toStdString().c_str() , COM_PATH_MAP_PAGE_SIZE , bytePosition );
    }

    if ( ( bytePosition + buffersize ) > COM_FRAME_MAP_PAGE_SIZE ||
         ( frameindex == UINT_ONE && this->getFrameStream().is_open() ) ) // repage or reopen
    {
        this->getFrameStream().close();
        this->getFrameStream().open ( comFrameFile.toStdString().c_str() , COM_FRAME_MAP_PAGE_SIZE, bytePosition);
    }

    //Return pointer with offset
    data = this->getFrameStream().data() + firstByte;

    return data;
}

const char *COMPathHandler::mapSinglePathData(unsigned int &pathindex, unsigned int framesnumber)
{
    long bufferSize;
    long firstByte;
    long bytePosition;

    const char *data;

    bufferSize = framesnumber * RVEC_SIZE;

    this->computeSinglePathBytePosition( pathindex, bufferSize);

    firstByte    = this->getFirstByte( );
    bytePosition = this->getBytePosition(  );

//    qDebug() << " File mapSinglePathData" << this->getPathFile().toStdString().c_str();
    if( ! this->getPathData().is_open() )
    {
        this->getPathData().open( this->getPathFile().toStdString().c_str() , PATH_MAP_PAGE_SIZE , bytePosition );
    }


    if ( ( bytePosition + bufferSize ) > PATH_MAP_PAGE_SIZE || ( pathindex == UINT_ONE && this->getPathData().is_open() ) ) // repage or reopen
    {
        this->getPathData().close();
        this->getPathData().open ( this->getPathFile().toStdString().c_str(), PATH_MAP_PAGE_SIZE, bytePosition);
    }

    //qDebug() << " firstByte " << firstByte;

    //Return the map from boost
    data = this->getPathData().data() + firstByte;

    return data;
}

void COMFrameHandler::computeFrameBytePosition(unsigned int frameindex, unsigned int buffersize)
{
    long firstByte;
    long bytePosition;

    firstByte    = this->getFirstByte( );
    bytePosition = this->getBytePosition(  );

    if( frameindex == UINT_ZERO  )
    {
        firstByte = bytePosition = frameindex = UINT_ZERO;
    }
    else
    {
        firstByte = frameindex * buffersize;
    }

    this->setFrameIndex( frameindex );

    if( firstByte > COM_FRAME_MAP_PAGE_SIZE || ( firstByte + buffersize ) > COM_FRAME_MAP_PAGE_SIZE  )
    {
        bytePosition = ( firstByte / MAP_PAGE_PARTITION_SIZE ) * MAP_PAGE_PARTITION_SIZE;
        firstByte = firstByte - bytePosition;
    }

    this->setFirstByte(  firstByte );
    this->setBytePosition( bytePosition );
}
