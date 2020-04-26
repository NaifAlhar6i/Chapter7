#include "comframehandler.h"

COMFrameHandler::COMFrameHandler() : m_FrameIndex(FRAMES_NUMBER), m_FirstByte(UINT_ZERO)
{

}

const char *COMFrameHandler::mapFrame(unsigned int frameindex, unsigned int buffersize)
{
    const char *data;
    QString comFrameFile;
    long firstByte = UINT_ZERO;
    long bytePosition;
    unsigned int frameIndex;

    comFrameFile = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_FRAME_FILE;
    frameIndex = this->getFrameIndex();

    if( frameIndex == frameindex)
    {
        data = this->getFrameStream().data() + this->getFirstByte();
        return data;
    }

    this->computeFrameBytePosition( frameindex, buffersize);

    firstByte    = this->getFirstByte(  );
    bytePosition = this->getBytePosition( );




    if( ! this->getFrameStream().is_open() )
    {
        this->getFrameStream().open( comFrameFile.toStdString().c_str() , COM_FRAME_MAP_PAGE_SIZE , bytePosition );
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
