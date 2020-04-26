#include "boosthandler.h"

BoostHandler::BoostHandler()
{
    m_FrameIndex = RESTART_INDEX;
    m_PathIndex = RESTART_INDEX;
    m_GroupIndex[ DataType::MultiPath] = RESTART_INDEX;
    m_GroupIndex[ DataType::MultiIndices] = RESTART_INDEX;

    for( unsigned int index = UINT_ZERO; index < UINT_FIVE; index++)
    {
        m_FirstByte[index] = UINT_ZERO;
        m_LastByte[index] = UINT_ZERO;
        m_CurrentByte[index] = UINT_ZERO;
        m_BytePosition[index] = UINT_ZERO;
    }
}

void BoostHandler::SetPathFile(QString pathfile)
{
    if( this->getPathData().is_open() )
    {
        this->getPathData().close();
        for( unsigned int index = UINT_ZERO; index < UINT_FIVE; index++)
        {
            m_FirstByte[index] = UINT_ZERO;
            m_LastByte[index] = UINT_ZERO;
            m_CurrentByte[index] = UINT_ZERO;
            m_BytePosition[index] = UINT_ZERO;
        }
    }

    m_PathFile = pathfile ;
}

void BoostHandler::SetIndexFile(QString indexfile)
{
    if( this->getIndicesData().is_open() )
    {
        this->getIndicesData().close();
        for( unsigned int index = UINT_ZERO; index < UINT_FIVE; index++)
        {
            m_FirstByte[index] = UINT_ZERO;
            m_LastByte[index] = UINT_ZERO;
            m_CurrentByte[index] = UINT_ZERO;
            m_BytePosition[index] = UINT_ZERO;
        }
    }

    m_IndexFile = indexfile;
}

const char *BoostHandler::mapSphereData(unsigned int &frameindex, unsigned int &particlesnumber)
{
    long bufferSize;
    long firstByte;
    long bytePosition;
    unsigned int frameIndex;

    const char *data;
    frameIndex = this->getFrameIndex();

    if( frameIndex == frameindex)
    {
        data = this->getSphereData().data() + this->getFirstByte( DataType::Sphere);
        return data;
    }

    bufferSize = particlesnumber * RVEC_SIZE;

    this->computeSphereBytePosition( frameindex, bufferSize);

    firstByte    = this->getFirstByte( DataType::Sphere );
    bytePosition = this->getBytePosition( DataType::Sphere );


    if( ! this->getSphereData().is_open() )
    {
        this->getSphereData().open( this->getSphereFile().toStdString().c_str() , SPHERE_MAP_PAGE_SIZE , bytePosition );
    }


    if ( ( bytePosition + bufferSize ) > SPHERE_MAP_PAGE_SIZE || ( frameindex == UINT_ONE && this->getSphereData().is_open() ) ) // repage or reopen
    {
        this->getSphereData().close();
        this->getSphereData().open ( this->getSphereFile().toStdString().c_str(), SPHERE_MAP_PAGE_SIZE, bytePosition);
    }

    //Return the map from boost
    data = this->getSphereData().data() + firstByte;

    return data;
}

const char *BoostHandler::mapSinglePathData(unsigned int &pathindex, unsigned int framesnumber)
{
    long bufferSize;
    long firstByte;
    long bytePosition;

    const char *data;

    bufferSize = framesnumber * RVEC_SIZE;

    this->computeSinglePathBytePosition( pathindex, bufferSize);

    firstByte    = this->getFirstByte( DataType::SinglePath);
    bytePosition = this->getBytePosition( DataType::SinglePath );

//    qDebug() << " File mapSinglePathData" << this->getPathFile().toStdString().c_str();
    if( ! this->getPathData().is_open() )
    {
        this->getPathData().open( this->getPathFile().toStdString().c_str() , PATH_MAP_PAGE_SIZE, bytePosition );
    }


    if ( ( bytePosition + bufferSize ) > PATH_MAP_PAGE_SIZE || ( pathindex == UINT_ONE && this->getPathData().is_open() ) ) // repage or reopen
    {
        this->getPathData().close();
        this->getPathData().open ( this->getPathFile().toStdString().c_str(), PATH_MAP_PAGE_SIZE, bytePosition);
    }

//    qDebug() <<pathindex << " bytePosition -> " << bytePosition + firstByte;

//    qDebug() << " firstByte -> " << firstByte << " bytePosition -> " << bytePosition;

    //Return the map from boost
    data = this->getPathData().data() + firstByte;

    return data;
}

const char *BoostHandler::mapMultiPathData(unsigned int &pathgroupindex, unsigned int pathbasednumber, unsigned int pathsnumber, unsigned int framesnumber)
{
    long basedBufferSize;
    long bufferSize;
    long firstByte;
    long bytePosition;
    unsigned int pathGroupIndex;
    const char *data;

    pathGroupIndex = this->getGroupIndex( DataType::MultiPath );

    if( pathGroupIndex == pathgroupindex)
    {
        data = this->getPathData().data() + this->getFirstByte( DataType::MultiPath );
        return data;
    }

    basedBufferSize = pathbasednumber * framesnumber * RVEC_SIZE;
    bufferSize = pathsnumber * framesnumber * RVEC_SIZE;
    this->computeMultiPathBytePosition( pathgroupindex, basedBufferSize, bufferSize);

    firstByte    = this->getFirstByte( DataType::MultiPath  );
    bytePosition = this->getBytePosition( DataType::MultiPath  );

//    qDebug() << " File mapMultiPathData " << this->getPathFile().toStdString().c_str();

    if( ! this->getPathData().is_open() )
    {
        this->getPathData().open( this->getPathFile().toStdString().c_str() , PATH_MAP_PAGE_SIZE , bytePosition );
    }


    if ( ( bytePosition + bufferSize ) > PATH_MAP_PAGE_SIZE || ( pathgroupindex == UINT_ONE && this->getPathData().is_open() ) ) // repage or reopen
    {
        this->getPathData().close();
        this->getPathData().open ( this->getPathFile().toStdString().c_str(), PATH_MAP_PAGE_SIZE, bytePosition);
    }

    //Return the map from boost
    data = this->getPathData().data() + firstByte;

    return data;
}

const char *BoostHandler::mapBulckPathData(unsigned int firstpathindex, unsigned int pathsnumber, unsigned int framesnumber)
{

}

const char *BoostHandler::mapSinglePathIndicesData(unsigned int &pathindex, unsigned int framesnumber)
{
    long bufferSize;
    long firstByte;
    long bytePosition;

    const char *data;

    bufferSize = framesnumber * UNSIGNED_INT_SIZE;

    this->computeSinglePathIndexBytePosition( pathindex, bufferSize);

    firstByte    = this->getFirstByte( DataType::Index );
    bytePosition = this->getBytePosition( DataType::Index );

    if( ! this->getIndicesData().is_open() )
    {
        this->getIndicesData().open( this->getIndexFile().toStdString().c_str() , PATH_MAP_PAGE_SIZE , bytePosition );
    }

//    qDebug() << " File mapSinglePathIndicesData" << this->getPathFile().toStdString().c_str();

    if ( ( bytePosition + bufferSize ) > PATH_MAP_PAGE_SIZE || ( pathindex == UINT_ONE && this->getIndicesData().is_open() ) ) // repage or reopen
    {
        this->getIndicesData().close();
        this->getIndicesData().open ( this->getIndexFile().toStdString().c_str(), PATH_MAP_PAGE_SIZE, bytePosition);
    }

    //Return the map from boost
    data = this->getIndicesData().data() + firstByte;

    return data;
}

const char *BoostHandler::mapMultiPathIndicesData(unsigned int &pathgroupindex, unsigned int pathsbasednumber, unsigned int pathsnumber, unsigned int framesnumber)
{
    long basedBufferSize;
    long bufferSize;
    long firstByte;
    long bytePosition;
    unsigned int pathGroupIndex;

    const char *data;

    pathGroupIndex = this->getGroupIndex( DataType::MultiIndices);

    if( pathGroupIndex == pathgroupindex)
    {
        data = this->getIndicesData().data() + this->getFirstByte( DataType::MultiIndices );
        return data;
    }


    basedBufferSize = pathsbasednumber * framesnumber * UNSIGNED_INT_SIZE;
    bufferSize = pathsnumber * framesnumber * UNSIGNED_INT_SIZE;

    this->computeMultiIndicesBytePosition( pathgroupindex, basedBufferSize, bufferSize);

    firstByte    = this->getFirstByte( DataType::MultiIndices  );
    bytePosition = this->getBytePosition( DataType::MultiIndices  );

    if( ! this->getIndicesData().is_open() )
    {
        this->getIndicesData().open( this->getIndexFile().toStdString().c_str() , INDEX_MAP_PAGE_SIZE , bytePosition );
    }

//    qDebug() << " File mapMultiPathIndicesData " << this->getPathFile().toStdString().c_str();

    if ( ( bytePosition + bufferSize ) > INDEX_MAP_PAGE_SIZE || ( pathgroupindex == UINT_ONE && this->getIndicesData().is_open() ) ) // repage or reopen
    {
        this->getIndicesData().close();
        this->getIndicesData().open ( this->getIndexFile().toStdString().c_str(), INDEX_MAP_PAGE_SIZE, bytePosition);
    }

    //Return the map from boost
    data = this->getIndicesData().data() + firstByte;

    return data;
}

void BoostHandler::mapFrameTest(unsigned int index)
{
    long bufferSize;
    unsigned int atomsnumber = 336260;
    long firstByte;
    long lastByte;
    long currentByte;
    long bytePosition;

    unsigned int frameIndex;

    frameIndex = this->getFrameIndex();

    if( index == frameIndex )
        return;

    bufferSize = atomsnumber * RVEC_SIZE;

    this->computeSphereBytePosition( index, bufferSize);

//    firstByte    = this->getFirstByte();
//    lastByte     = this->getLastByte();
//    currentByte  = this->getCurrentByte();
//    bytePosition = this->getBytePosition();

    if( index == UINT_ZERO )
        qDebug() << " Index " << index << " firstByte " << firstByte << " lastByte " << lastByte << " currentByte " << currentByte << " bytePosition " << bytePosition << " is open" << this->getSphereData().is_open();

    if( ! this->getPathData().is_open() )
    {
        this->getPathData().open( this->getSphereFile().toStdString().c_str() , SPHERE_MAP_PAGE_SIZE , bytePosition );
    }

    if ( ( bytePosition + bufferSize ) >  SPHERE_MAP_PAGE_SIZE || bytePosition == UINT_ZERO) // repage
    {
        this->getPathData().close();

        this->getPathData().open ( this->getSphereFile().toStdString().c_str(), SPHERE_MAP_PAGE_SIZE, bytePosition );
    }


    const char *m_Data = this->getPathData().data()+ firstByte;

    qDebug() << "System " << index
             << "Position - " << *(*((rvec *)m_Data))
             << " - "  << *(*((rvec *)m_Data)+1)
             << " - " << *(*((rvec *)m_Data)+2);

    //Generate pathes
//    for(unsigned int byteIndex=0; byteIndex< 8000; byteIndex++)
//    {

//    }

    //memcpy( data, m_SphereFile.data() + start, frameSize);
}

void BoostHandler::computeSphereBytePosition(unsigned int frameindex, long buffersize)
{
    long firstByte;
    long bytePosition;

    firstByte    = this->getFirstByte( DataType::Sphere);
    bytePosition = this->getBytePosition( DataType::Sphere );

    if( frameindex == UINT_ZERO  )
    {
        firstByte = bytePosition = frameindex = UINT_ZERO;
    }
    else
    {
        firstByte = frameindex * buffersize;
    }

    this->setFrameIndex( frameindex );

    if( firstByte > SPHERE_MAP_PAGE_SIZE || ( firstByte + buffersize ) > SPHERE_MAP_PAGE_SIZE  )
    {
        bytePosition = ( firstByte / MAP_PAGE_PARTITION_SIZE ) * MAP_PAGE_PARTITION_SIZE;
        firstByte = firstByte - bytePosition;
    }

    this->setFirstByte( DataType::Sphere, firstByte );
    this->setBytePosition( DataType::Sphere, bytePosition );
}

void BoostHandler::computeSinglePathBytePosition(unsigned int pathindex, long buffersize)
{
    long firstByte;
    long bytePosition;

    firstByte    = this->getFirstByte( DataType::SinglePath);
    bytePosition = this->getBytePosition(  DataType::SinglePath );

    if( pathindex == UINT_ZERO  )
    {
        firstByte = bytePosition = pathindex = UINT_ZERO;
    }
    else
    {
        firstByte = pathindex * buffersize;
    }

    this->setPathIndex( pathindex );

    if( firstByte > PATH_MAP_PAGE_SIZE || ( firstByte + buffersize ) > PATH_MAP_PAGE_SIZE  )
    {

        bytePosition = ( firstByte / MAP_PAGE_PARTITION_SIZE ) * MAP_PAGE_PARTITION_SIZE;
        firstByte = firstByte - bytePosition;

    }

    this->setFirstByte(  DataType::SinglePath, firstByte );
    this->setBytePosition(  DataType::SinglePath, bytePosition );
}

void BoostHandler::computeSinglePathIndexBytePosition(unsigned int pathindex, long buffersize)
{
    long firstByte;
    long bytePosition;

    firstByte    = this->getFirstByte( DataType::Index);
    bytePosition = this->getBytePosition(  DataType::Index );

    if( pathindex == UINT_ZERO  )
    {
        firstByte = bytePosition = pathindex = UINT_ZERO;
    }
    else
    {
        firstByte = pathindex * buffersize;
    }

    this->setPathIndex( pathindex );

    if( firstByte > PATH_MAP_PAGE_SIZE || ( firstByte + buffersize ) > PATH_MAP_PAGE_SIZE  )
    {
        bytePosition = ( firstByte / MAP_PAGE_PARTITION_SIZE ) * MAP_PAGE_PARTITION_SIZE;
        firstByte = firstByte - bytePosition;
    }

    this->setFirstByte(  DataType::Index, firstByte );
    this->setBytePosition(  DataType::Index, bytePosition );
}

void BoostHandler::computeMultiPathBytePosition(unsigned int pathgroupindex, long basedbuffer, long buffersize)
{
    long firstByte;
    long bytePosition;

    firstByte    = this->getFirstByte( DataType::MultiPath);
    bytePosition = this->getBytePosition( DataType::MultiPath);

    if( pathgroupindex == UINT_ZERO  )
    {
        firstByte = bytePosition = pathgroupindex = UINT_ZERO;
    }
    else
    {
        firstByte = pathgroupindex * basedbuffer;
    }

    this->setGroupIndex( DataType::MultiPath, pathgroupindex );

    if( firstByte > PATH_MAP_PAGE_SIZE || ( firstByte + buffersize ) > PATH_MAP_PAGE_SIZE  )
    {
        bytePosition = ( firstByte / MAP_PAGE_PARTITION_SIZE ) * MAP_PAGE_PARTITION_SIZE;
        firstByte = firstByte - bytePosition;
    }

    this->setFirstByte(  DataType::MultiPath, firstByte );
    this->setBytePosition(  DataType::MultiPath, bytePosition );
}

void BoostHandler::computeMultiIndicesBytePosition(unsigned int pathgroupindex, long basedbuffer, long buffersize)
{
    long firstByte;
    long bytePosition;

    firstByte    = this->getFirstByte( DataType::MultiIndices);
    bytePosition = this->getBytePosition( DataType::MultiIndices);

    if( pathgroupindex == UINT_ZERO  )
    {
        firstByte = bytePosition = pathgroupindex = UINT_ZERO;
    }
    else
    {
        firstByte = pathgroupindex * basedbuffer;
    }


    this->setGroupIndex( DataType::MultiIndices, pathgroupindex );

    if( firstByte > INDEX_MAP_PAGE_SIZE || ( firstByte + buffersize ) > INDEX_MAP_PAGE_SIZE  )
    {
        bytePosition = ( firstByte / MAP_PAGE_PARTITION_SIZE ) * MAP_PAGE_PARTITION_SIZE;
        firstByte = firstByte - bytePosition;
    }

//    qDebug() << "pathgroupindex " << pathgroupindex << "bytePosition " << bytePosition << " firstByte" <<  firstByte;

    this->setFirstByte(  DataType::MultiIndices, firstByte );
    this->setBytePosition(  DataType::MultiIndices, bytePosition );
}
