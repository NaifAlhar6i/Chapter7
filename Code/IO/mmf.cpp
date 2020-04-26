#include "mmf.h"

bio::mapped_file_source MMF::m_VertexData;
bio::mapped_file_source MMF::m_PathData;
long MMF::m_VertexDataOffset;
long MMF::m_PathDataOffset;
long MMF::m_VertexDataTenthIndex;
long MMF::m_PathDataTenthIndex;

MMF::MMF()
{

}

void MMF::CopyData(unsigned int frameindex)
{
    bio::mapped_file_source outPathData;//(params);
    bio::mapped_file_source outFrameData;//(params);
    rvec *memoryFromPath ;
    long memoryFromPathBufferSize;
    QString pathFileName;
    QString frameFileName;
    unsigned int atomsNumber;
    atomsNumber = ATOMS_NUMBER;

    pathFileName = DATA_DIRECTORY + IND_DIRECTORY + IND_PATH_FILE;
    frameFileName = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;
    this->ReadFile(outFrameData, frameFileName, UINT_ZERO, RVEC_SIZE, atomsNumber , UINT_ONE);

    memoryFromPathBufferSize = ATOMS_NUMBER * RVEC_SIZE;
    memoryFromPath = (rvec *) malloc( memoryFromPathBufferSize );

    long srcVertexPosition;
    long dstVertexPosition;
    long srcVertexPositionByte;
    long dstVertexPositionByte;
    long requiredDataZize;
    long offset;
    requiredDataZize = FRAMES_NUMBER * ATOMS_NUMBER * RVEC_SIZE;

    rvec a;
    rvec b;
    unsigned int tenthIndex =1;
    //for( unsigned int tenthIndex = UINT_ZERO; tenthIndex < UINT_TEN; tenthIndex++)
    //{
        for(unsigned int atomIndex = UINT_ZERO ; atomIndex <  ATOMS_NUMBER; atomIndex++)
        {
            const char *data = this->readPathVerticesFile( pathFileName, atomIndex);

            offset = (atomIndex* RVEC_SIZE);

            dstVertexPosition = /*tenthIndex * ONE_TENTH_OF_ATOMS +*/ atomIndex ;
            srcVertexPosition = atomIndex * FRAMES_NUMBER;

            dstVertexPositionByte =/* offset + */atomIndex * RVEC_SIZE ;
            srcVertexPositionByte = (atomIndex % ONE_TENTH_OF_ATOMS) * FRAMES_NUMBER * RVEC_SIZE;

            //if(tenthIndex == 0 || tenthIndex == 9)
            //    qDebug() << memoryFromPathBufferSize - dstVertexPositionByte << " -> " << dstVertexPositionByte;
            memcpy( memoryFromPath + dstVertexPosition, data + srcVertexPositionByte, RVEC_SIZE);
            //memcpy( a, data + srcVertexPositionByte,  RVEC_SIZE);
            memcpy( b, outFrameData.data() + dstVertexPositionByte, RVEC_SIZE);

            if( memoryFromPath[dstVertexPosition][Z] != b[Z] )
                qDebug() << "Wrong!!!!!!!!" << dstVertexPosition << " " << memoryFromPath[dstVertexPosition][Z] << b[Z];
        }
    //}

    outPathData.close();
    outFrameData.close();
    free(memoryFromPath );
}

void MMF::FetchProteinParticles(unsigned int frameindex)
{
    QTime timer;
    QString frameFileName;
    const char *data;
    unsigned int atomsGroupStart;
    short proteinIndex;
    unsigned int proteinParticleIndex;
    long fileBytePosition;
    long atomsNumber;
    long framesNumber;
    long rvecSize;
    long frameIndex;

    rvecSize = RVEC_SIZE;
    atomsNumber = ATOMS_NUMBER;
    framesNumber =FRAMES_NUMBER;
    frameIndex = frameindex;

    frameFileName = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;

    timer.start();

    data = this->readAtomVerticesFile( frameFileName, frameindex );

    COMStructureRecord *comStructure;

    comStructure = DataStructure::getCOMStructure();

    proteinIndex = USHORT_ZERO;
    proteinParticleIndex = UINT_ZERO;

    for( unsigned int index = UINT_ZERO; index < COM_GROUPS_NUMBER; index++)
    {
        if((comStructure + index)->getMoleculeType() == PROTEIN_MOLECULE_0)
        {
            atomsGroupStart = (comStructure + index)->getFirstAtomIndex();
            fileBytePosition = atomsGroupStart * rvecSize;

            for(unsigned int particleIndex= UINT_ZERO; particleIndex < PROTEIN_PARTICLES_NUMBER; particleIndex++)
            {
                (MemoryManager::getProteinParticles() + proteinParticleIndex)->ProteinID = proteinIndex;
                (MemoryManager::getProteinParticles() + proteinParticleIndex)->ParticleID = atomsGroupStart + particleIndex;
                memcpy( (MemoryManager::getProteinParticles() + proteinParticleIndex)->Position , data + fileBytePosition, RVEC_SIZE );
                fileBytePosition += rvecSize;//To obtian the next particle starting byte!
                proteinParticleIndex ++;
            }

            proteinIndex ++;
        }
    }

}

void MMF::FetchLipidParticles(unsigned int frameindex)
{
    QTime timer;
    QString frameFileName;
    const char *data;
    unsigned int atomsGroupStart;
    short lipidIndex;
    unsigned int lipidParticleIndex;
    long groupAtomSize;
    long fileBytePosition;
    long atomsNumber;
    long framesNumber;
    long rvecSize;
    long frameIndex;

    rvecSize = RVEC_SIZE;
    atomsNumber = ATOMS_NUMBER;
    framesNumber =FRAMES_NUMBER;
    frameIndex = frameindex;

    frameFileName =  DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;

    timer.start();

    data = this->readAtomVerticesFile( frameFileName, frameindex );

    COMStructureRecord *comStructure;

    comStructure = DataStructure::getCOMStructure();

    lipidIndex = USHORT_ZERO;
    lipidParticleIndex = UINT_ZERO;
    groupAtomSize = LIPIDS_NUMBER * LIPID_PARTICLES_NUMBER * rvecSize;

    for( unsigned int index = UINT_ZERO; index < COM_GROUPS_NUMBER; index++)
    {
        if((comStructure + index)->getMoleculeType() != PROTEIN_MOLECULE_0)
        {
            atomsGroupStart = (comStructure + index)->getFirstAtomIndex();
            fileBytePosition = atomsGroupStart * rvecSize;

            for(unsigned int particleIndex= UINT_ZERO; particleIndex < LIPID_PARTICLES_NUMBER; particleIndex++)
            {
                (MemoryManager::getLipidParticles() + lipidParticleIndex)->LipidID = lipidIndex;
                (MemoryManager::getLipidParticles() + lipidParticleIndex)->ParticleID = atomsGroupStart + particleIndex;
                memcpy( (MemoryManager::getLipidParticles() + lipidParticleIndex)->Position , data + fileBytePosition, RVEC_SIZE );
                fileBytePosition += rvecSize;//To obtian the next particle starting byte!
                lipidParticleIndex ++;
            }

            lipidIndex ++;
        }
    }

}

int MMF::FetchFrame(unsigned int frameindex, void *&mapframe)
{
    rvec *frame;
    QTime timer;
    QString frameFileName;
    long frameIndex;
    int timeElapced;

    frameIndex = frameindex;

    frameFileName = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;

    timer.start();

    frame = (rvec *)this->readAtomVerticesFile( frameFileName, frameindex );

    memcpy( MemoryManager::getVertexPosition(), frame, FRAME_SIZE );

    timeElapced=timer.elapsed();

    return timeElapced;
}

void MMF::ReadFile()
{
    bio::mapped_file_source inFile;
    QString name ;
    long fileLength;
    long position;
    long atomsNumber;
    long framesNumber;
    long rvecSize;
    rvecSize = RVEC_SIZE;
    atomsNumber = ATOMS_NUMBER;
    framesNumber =FRAMES_NUMBER;

    name = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;
    fileLength = rvecSize * atomsNumber * framesNumber;

    bio::mapped_file_params params;
    params.path = name.toStdString();
    params.length = fileLength;
    params.flags = bio::mapped_file::mapmode::readonly;

    inFile.open(params);

    for(long frameindex= 0; frameindex < FRAMES_NUMBER; frameindex ++)
    {
        for(long atomsnumber = 0; atomsnumber < ATOMS_NUMBER; atomsnumber++)
        {
            position = (frameindex * atomsNumber + atomsnumber) * rvecSize ;

            if( frameindex == 211 && (atomsnumber == 0 || atomsnumber == 170000 || atomsnumber == 336259))
            {
                rvec data;
                memcpy(data, inFile.data() + position, rvecSize );
                qDebug() << frameindex << data[0] << data[1] << data[2];
            }

        }
    }

    inFile.close();
}

void MMF::ReadFile(bio::mapped_file_source &out, QString name, unsigned int frameindex, long typesize, long atomsnumber, long framesnumber)
{
    long fileLength;
    long offset;
    long frameIndex;

    frameIndex = frameindex;
    fileLength = typesize * atomsnumber * framesnumber;

    offset = ((frameIndex * typesize * atomsnumber) / SYSTEME_ALIGNMENT)  * SYSTEME_ALIGNMENT;

    bio::mapped_file_params params;
    params.path = name.toStdString();
    params.length = fileLength;
    params.flags = bio::mapped_file::mapmode::readonly;
    params.offset = offset;

    out.open(params);
}

const char *MMF::readPathVerticesFile(QString name, unsigned int atomindex)
{
    long fileOffset;
    long currentByte;;
    long pageOffset;
    long tenthIndex;
    long paging;

    tenthIndex = atomindex / ONE_TENTH_OF_ATOMS;
    paging = atomindex % ONE_TENTH_OF_ATOMS;
    fileOffset = (((tenthIndex * ONE_TENTH_PATH_SIZE) / SYSTEME_ALIGNMENT) * SYSTEME_ALIGNMENT);
    currentByte = tenthIndex * ONE_TENTH_PATH_SIZE;

    pageOffset = currentByte - fileOffset;

    if( !getVertexData().is_open() )
    {
        getVertexData().open ( name.toStdString().c_str(), PATH_MAP_PAGE_SIZE, fileOffset);
    }

    if( paging == UINT_ZERO)
    {
        //qDebug() << "How? ->" << atomindex << tenthIndex;
        //qDebug() << fileOffset << currentByte << pageOffset  ;
        getVertexData().close();
        getVertexData().open ( name.toStdString().c_str(), PATH_MAP_PAGE_SIZE, fileOffset);
    }


    return getVertexData().data() + pageOffset;
}

const char *MMF::readAtomVerticesFile(QString name,  unsigned int frameindex)
{

    long fileOffset;
    long currentByte;;
    long pageOffset;
    long tenthIndex;
    long paging;
    long frameIndex;

    frameIndex =  frameindex;

    tenthIndex = frameIndex / ONE_TENTH_OF_FRAMES;
    paging = frameIndex % ONE_TENTH_OF_FRAMES; // to know when reopen the file
    fileOffset = (((tenthIndex * ONE_TENTH_FRAME_SIZE) / SYSTEME_ALIGNMENT) * SYSTEME_ALIGNMENT);
    currentByte = frameIndex * FRAME_SIZE;


    pageOffset = currentByte - fileOffset;

    if( !getVertexData().is_open() )
    {
        getVertexData().open ( name.toStdString().c_str(), FRAME_MAP_PAGE_SIZE, fileOffset);
    }

    if( tenthIndex != getVertexDataTenthIndex() )
    {
        getVertexData().close();
        getVertexData().open ( name.toStdString().c_str(), FRAME_MAP_PAGE_SIZE, fileOffset);
        setVertexDataTenthIndex( tenthIndex );
        //qDebug() << "tenthIndex" << tenthIndex << "paging" << paging << "fileOffset" << fileOffset << "currentByte" << currentByte << "pageOffset" << pageOffset;
    }

    return getVertexData().data() + pageOffset;
}

const char *MMF::readAtomVerticesFile2(QString name, unsigned int frameindex)
{

    size_t fileSize;
    size_t framesNumber;
    size_t frameIndex;
    size_t frameOffset;
    bio::mapped_file_params params;

    framesNumber= FRAMES_NUMBER;
    fileSize = FRAME_SIZE * framesNumber;
    params.path = name.toStdString();
    params.length = fileSize;
    params.flags = bio::mapped_file::mapmode::readonly;

    frameIndex = frameindex;
    frameOffset = frameIndex * FRAME_SIZE;

    if( !getVertexData().is_open() )
    {
        getVertexData().open( params);
    }


    return getVertexData().data() + frameOffset;
}

const char *MMF::readAtomIndicesFile(QString name, unsigned int atomindex)
{

}

const char *MMF::readAtomAttributesFile(QString name, unsigned int atomindex)
{

}
