#include "stl.h"

STL::STL()
{

}

void STL::FetchLipidParticles(unsigned int frameindex)
{
    QTime timer;
    QString frameFileName;
    unsigned int atomsGroupStart;
    short lipidIndex;
    unsigned int lipidParticleIndex;
    long groupAtomSize;
    long fileBytePosition;
    long offset;
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

    FILE *comFrame;

    comFrame = fopen(frameFileName.toStdString().c_str(), "rb");

    COMStructureRecord *systemStructure;

    systemStructure = DataStructure::getCOMStructure();

    lipidIndex = UINT_ZERO;
    lipidParticleIndex = UINT_ZERO;
    groupAtomSize = LIPIDS_NUMBER * LIPID_PARTICLES_NUMBER * rvecSize;

    offset = frameIndex * FRAME_SIZE;
    for( unsigned int index = UINT_ZERO; index < COM_GROUPS_NUMBER; index++)
    {
        if((systemStructure + index)->getMoleculeType() != PROTEIN_MOLECULE_0)
        {
            atomsGroupStart = (systemStructure + index)->getFirstAtomIndex();
            fileBytePosition = offset +  atomsGroupStart * rvecSize;
            for(unsigned int particleIndex = UINT_ZERO; particleIndex < LIPID_PARTICLES_NUMBER; particleIndex++)
            {
                (MemoryManager::getLipidParticles() + lipidParticleIndex)->LipidID = lipidIndex;
                (MemoryManager::getLipidParticles() + lipidParticleIndex)->ParticleID = atomsGroupStart + particleIndex;
                fseek(comFrame, fileBytePosition, SEEK_SET );
                fread( (MemoryManager::getLipidParticles() + lipidParticleIndex)->Position, RVEC_SIZE, UINT_ONE, comFrame);
                fileBytePosition += rvecSize;
                lipidParticleIndex ++;
            }
            lipidIndex ++;
        }
    }

    fclose(comFrame);

}

int STL::FetchFrame(unsigned int frameindex)
{
    QTime timer;
    QString frameFileName;
    long fileBytePosition;
    long atomsNumber;
    long framesNumber;
    long rvecSize;
    long frameIndex;
    int timeElapced;

    rvecSize = RVEC_SIZE;
    atomsNumber = ATOMS_NUMBER;
    framesNumber =FRAMES_NUMBER;
    frameIndex = frameindex;
    frameFileName = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;

    timer.start();

    FILE *comFrame;

    comFrame = fopen(frameFileName.toStdString().c_str(), "rb");

    fileBytePosition = frameIndex * FRAME_SIZE;

    fseek(comFrame, fileBytePosition, SEEK_SET );
    fread( MemoryManager::getVertexPosition(), FRAME_SIZE, UINT_ONE, comFrame);

    fclose(comFrame);

    timeElapced = timer.elapsed();

    return timeElapced;

}

void STL::ReadFile()
{
    QTime timer;
    QString frameFileName;
    long position;
    long atomsNumber;
    long framesNumber;
    long rvecSize;
    rvecSize = RVEC_SIZE;
    atomsNumber = ATOMS_NUMBER;
    framesNumber =FRAMES_NUMBER;

    frameFileName = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;

    timer.start();



    FILE *comFrame;

    comFrame = fopen(frameFileName.toStdString().c_str(), "rb");


    for(long frameindex= 0; frameindex < FRAMES_NUMBER; frameindex ++)
    {
        for(long atomsnumber = 0; atomsnumber < ATOMS_NUMBER; atomsnumber++)
        {
            position = (frameindex * atomsNumber + atomsnumber) * rvecSize ;

            if(frameindex == 211 && (atomsnumber == 0 || atomsnumber == 170000 || atomsnumber == 336259))
            {
                rvec data;
                fseek(comFrame, position, SEEK_SET );
                fread( data, rvecSize, UINT_ONE, comFrame);
                qDebug() << frameindex << data[0] << data[1] << data[2];
            }

        }
    }


    fclose(comFrame);

}

void STL::PrintOutPath(QString filename, long pathindex, long atomsnumber)
{
    long position;
    long atomsNumber;
    long framesNumber;
    long rvecSize;
    rvec *data;



    rvecSize = RVEC_SIZE;
    atomsNumber = atomsnumber;
    framesNumber =FRAMES_NUMBER;


    FILE *comFrame;
    data = (rvec*)malloc( rvecSize * framesNumber );
    comFrame = fopen(filename.toStdString().c_str(), "rb");

    position = pathindex * framesNumber * rvecSize ;
    fseek(comFrame, position, SEEK_SET );
    fread( data, rvecSize, framesNumber, comFrame);

    float minX =200;
    float minY =200;
    float minZ =200;

    float maxX =-200;
    float maxY =-200;
    float maxZ =-200;

    float comX = 0.0;
    float comY = 0.0;
    float comZ = 0.0;


    for(long frameindex= 0; frameindex < FRAMES_NUMBER; frameindex ++)
    {
        //116.019, 116.019, 10.1359
        float newXPosition =  *((*(data + frameindex)) + X);
        float newYPosition =  *((*(data + frameindex)) + Y);
        float newZPosition =  *((*(data + frameindex)) + Z);

        comX += newXPosition;
        comY += newYPosition;
        comZ += newZPosition;

        min( minX, newXPosition );
        min( minY, newYPosition );
        min( minZ, newZPosition );

        max( maxX, newXPosition );
        max( maxY, newYPosition );
        max( maxZ, newZPosition );
        qDebug() << frameindex << newXPosition << newYPosition << newZPosition;
    }

    comX /= 1981.0;
    comY /= 1981.0;
    comZ /= 1981.0;


//    if(( maxX - minX > 50) || ( maxY - minY > 50) || ( maxZ - minZ > 5) )
//    {
    qDebug() << "PathIndex" << pathindex;
    qDebug() << "Min" << minX << minY << minZ;
    qDebug() << "Max" << maxX << maxY << maxZ;
//    }
    //for(long frameindex= 0; frameindex < FRAMES_NUMBER; frameindex ++)
    //{
    //    //116.019, 116.019, 10.1359
    //    float newXPosition =  *((*(data + frameindex)) + X);
    //    float newYPosition =  *((*(data + frameindex)) + Y);
    //    float newZPosition =  *((*(data + frameindex)) + Z);
    //
    //    if( comX < 16 )
    //    {
    //        if( newXPosition > 115/2)
    //            newXPosition = 116.019 - newXPosition;
    //    }
    //    //qDebug() << frameindex << newXPosition << newYPosition << newZPosition;
    //}

    fclose(comFrame);
    free(data );

}

void STL::PrintOutFrame(QString filename, long frameindex, long atomsnumber)
{
    long position;
    long atomsNumber;
    long framesNumber;
    long rvecSize;
    rvec *data;

    qDebug() << "frameindex" << frameindex;


    rvecSize = RVEC_SIZE;
    atomsNumber = atomsnumber;
    framesNumber =FRAMES_NUMBER;



    FILE *comFrame;
    data = (rvec*)malloc( rvecSize * atomsNumber );
    comFrame = fopen(filename.toStdString().c_str(), "rb");

    position = frameindex * atomsNumber * rvecSize ;
    fseek(comFrame, position, SEEK_SET );
    fread( data, rvecSize, atomsNumber, comFrame);

    float minX =200;
    float minY =200;
    float minZ =200;

    float maxX =-200;
    float maxY =-200;
    float maxZ =-200;

    float comX = 0.0;
    float comY = 0.0;
    float comZ = 0.0;


    for(long atomsindex= 0; atomsindex < atomsNumber; atomsindex ++)
    {
        //116.019, 116.019, 10.1359
        float newXPosition =  *((*(data + atomsindex)) + X);
        float newYPosition =  *((*(data + atomsindex)) + Y);
        float newZPosition =  *((*(data + atomsindex)) + Z);

        comX += newXPosition;
        comY += newYPosition;
        comZ += newZPosition;

        min( minX, newXPosition );
        min( minY, newYPosition );
        min( minZ, newZPosition );

        max( maxX, newXPosition );
        max( maxY, newYPosition );
        max( maxZ, newZPosition );
        if( newXPosition ==0 || newYPosition ==0 || newZPosition ==0)
            qDebug() << atomsindex << newXPosition << newYPosition << newZPosition;
    }

    comX /= 1981.0;
    comY /= 1981.0;
    comZ /= 1981.0;

    qDebug() << "COM" << comX << comY << comZ;
    qDebug() << "Min" << minX << minY << minZ;
    qDebug() << "Max" << maxX << maxY << maxZ;

    for(long atomsindex= 0; atomsindex < 300; atomsindex ++)
    {
        //116.019, 116.019, 10.1359
        float newXPosition =  *((*(data + atomsindex)) + X);
        float newYPosition =  *((*(data + atomsindex)) + Y);
        float newZPosition =  *((*(data + atomsindex)) + Z);

        if( comX < 16 )
        {
            if( newXPosition > 115/2)
                newXPosition = 116.019 - newXPosition;
        }
        //qDebug() << atomsindex << newXPosition << newYPosition << newZPosition;
    }

    fclose(comFrame);
    free(data );
}

void STL::min(float &value1, float value2)
{
    if(value1 > value2 )
        value1 = value2;
}

void STL::max(float &value1, float value2)
{
    if(value1 < value2 )
        value1 = value2;
}

void STL::FetchProteinParticles(unsigned int frameindex)
{
    QTime timer;
    QString frameFileName;
    unsigned int atomsGroupStart;
    short proteinIndex;
    unsigned int proteinParticleIndex;
    long groupAtomSize;
    long fileBytePosition;
    long offset;
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

    FILE *comFrame;

    comFrame = fopen(frameFileName.toStdString().c_str(), "rb");

    COMStructureRecord *systemStructure;

    systemStructure = DataStructure::getCOMStructure();

    proteinIndex = UINT_ZERO;
    proteinParticleIndex = UINT_ZERO;
    groupAtomSize = PROTEINS_NUMBER * PROTEIN_PARTICLES_NUMBER * rvecSize;

    offset = frameIndex * FRAME_SIZE;
    for( unsigned int index = UINT_ZERO; index < COM_GROUPS_NUMBER; index++)
    {
        if((systemStructure + index)->getMoleculeType() == PROTEIN_MOLECULE_0)
        {
            atomsGroupStart = (systemStructure + index)->getFirstAtomIndex();
            fileBytePosition = offset +  atomsGroupStart * rvecSize;
            for(unsigned int particleIndex = UINT_ZERO; particleIndex < PROTEIN_PARTICLES_NUMBER; particleIndex++)
            {
                (MemoryManager::getProteinParticles() + proteinParticleIndex)->ProteinID = proteinIndex;
                (MemoryManager::getProteinParticles() + proteinParticleIndex)->ParticleID = atomsGroupStart + particleIndex;
                fseek(comFrame, fileBytePosition, SEEK_SET );
                fread( (MemoryManager::getProteinParticles() + proteinParticleIndex)->Position, RVEC_SIZE, UINT_ONE, comFrame);
                fileBytePosition += rvecSize;
                proteinParticleIndex ++;
            }
            proteinIndex ++;
        }
    }

    fclose(comFrame);

}
