#include "datamanager.h"

DataManager::DataManager(CLManager *clmanager) :
    m_CLManager( clmanager ),
    m_ProcessingState(false)
{
    m_GROManager = new GROManager;

    m_XTCManager = new XTCManager( m_GROManager);

    this->initializeSignalsAndSlots();
    this->initializeMinMaxDimention();

}

void DataManager::FetchGROData()
{

    this->getGROManager()->FetchData();
    this->getGROManager()->FetchStructure();
    qDebug() << this->getGROManager()->getSystemInformation()->getDimentions();

    unsigned int index = (MemoryManager::getCOMStructure() + 281)->getFirstAtomIndex();
    QString filename = "/Users/naif/Dropbox/PhD/MDSProject/Data/COM/COMPath.data";

    //for( unsigned int index = UINT_ZERO; index < 336260; index++)
    //    STL::PrintOutPath(filename,  index, 1981 );
    //STL::PrintOutPath(filename,  51, 1981 );

//    QString filename = "/Users/naif/Dropbox/PhD/MDSProject/Data/IND/INDParticle.data";
    //for( unsigned int index = UINT_ZERO; index < 1981; index++)
    //    STL::PrintOutFrame(filename,  index, 336260 );

}

void DataManager::FetchXTCFrames(unsigned int start, unsigned int end, short stride)
{
    this->getXTCManager()->FetchFrames( start, end, stride );
}

void DataManager::ComputeProteinCOM(unsigned int frameindex)
{
    GPUProteinSpace *proteinSpace;
    GPUProteinParticle *proteinParticles;
    unsigned int proteinsNumber;
    unsigned int proteinParticlesNumber;

    proteinSpace = MemoryManager::getProteinSpace();

    this->fetchProteinParticles( frameindex );
    proteinParticles = MemoryManager::getProteinParticles();

    proteinsNumber = PROTEINS_NUMBER;
    proteinParticlesNumber = PROTEIN_PARTICLES_NUMBER;


    ((GPUProteinSpace *)proteinSpace )->ProteinCOM[ X ] = 0;
    ((GPUProteinSpace *)proteinSpace )->ProteinCOM[ Y ] = 0;
    ((GPUProteinSpace *)proteinSpace )->ProteinCOM[ Z ] = 0;

    this->getCLManager()->ComputeProteinCOM( proteinSpace, proteinParticles, proteinsNumber, proteinParticlesNumber );

    emit ProteinSpaceComputed( proteinSpace );

}

void DataManager::ComputeLipidCOM(unsigned int frameindex)
{
    GPULipidSpace *lipidSpace;
    GPULipidParticle *lipidParticles;
    unsigned int lipidsNumber;
    unsigned int lipidParticlesNumber;

    lipidSpace = MemoryManager::getLipidSpace();

    this->fetchLipidParticles( frameindex );
    lipidParticles = MemoryManager::getLipidParticles();

    lipidsNumber = LIPIDS_NUMBER;
    lipidParticlesNumber = LIPID_PARTICLES_NUMBER;


    this->getCLManager()->ComputeLipidCOM( lipidSpace, lipidParticles, lipidsNumber, lipidParticlesNumber, lipidsNumber );


    emit LipidSpaceComputed( lipidSpace );
}

void DataManager::ComputeProteinLipidInteraction(unsigned int frameindex, bool mmf)
{

    void *frame;
    void *color;
    SystemStructureRecord *systemStructure;
    GPUProteinSpace *proteinSpace;
    GPUProteinParticle *proteinParticles;
    unsigned int proteinsNumber;
    unsigned int proteinParticlesNumber;
    int timeElapced;

    QTime time;


    proteinsNumber = PROTEINS_NUMBER;
    proteinParticlesNumber = PROTEIN_PARTICLES_NUMBER;

    proteinSpace = MemoryManager::getProteinSpace();

    time.start();
    if( mmf )
    {
        MMF::FetchFrame( frameindex, frame );
        this->fetchProteinParticles( frameindex );
        timeElapced = time.restart();
    }
    else
    {
        STL::FetchFrame( frameindex );
        this->fetchProteinParticlesSTL( frameindex );
        timeElapced = time.restart();
    }

    frame = (void*)MemoryManager::getVertexPosition();

    emit FileDataRead( timeElapced );


    color = (void *)MemoryManager::getVertexColor();

    systemStructure = MemoryManager::getSystemStructure();

    proteinParticles = MemoryManager::getProteinParticles();

    this->getCLManager()->ComputeProteinCOM( proteinSpace, proteinParticles, proteinsNumber, proteinParticlesNumber );

    this->getCLManager()->CLTask::ComputeProteinLipidInteraction( frame, color, systemStructure,  proteinSpace, proteinParticles, ATOMS_NUMBER, 0, ATOMS_NUMBER );

    timeElapced = time.restart();

    emit ProteinLipidInteractionComputed( frame, color, timeElapced );
}

void DataManager::ComputeProteinLipidInteractionOnTheFly(unsigned int frameindex, QOpenGLBuffer *& vertex, GLuint colorbufferid, bool mmf)
{
    void *frame;
    GLuint vertexBufferID;
    SystemStructureRecord *systemStructure;
    GPUProteinSpace *proteinSpace;
    GPUProteinParticle *proteinParticles;
    unsigned int proteinsNumber;
    unsigned int proteinParticlesNumber;
    int timeElapced;
    size_t vertexBufferSize;

    QTime time;

    time.start();

    proteinsNumber = PROTEINS_NUMBER;
    proteinParticlesNumber = PROTEIN_PARTICLES_NUMBER;

    proteinSpace = MemoryManager::getProteinSpace();

    if( mmf )
    {
        MMF::FetchFrame( frameindex, frame );
        this->fetchProteinParticles( frameindex );
        timeElapced = time.restart();
    }
    else
    {
        STL::FetchFrame( frameindex );
        this->fetchProteinParticlesSTL( frameindex );
        timeElapced = time.restart();
    }

    frame = (void*)MemoryManager::getVertexPosition();

    emit FileDataRead( timeElapced );

    vertex->bind();
    vertexBufferSize = vertex->size();
    void *data = vertex->map(QOpenGLBuffer::ReadWrite);
    memcpy( data, frame, vertexBufferSize );
    vertexBufferID = vertex->bufferId();
    vertex->unmap();

    systemStructure = MemoryManager::getSystemStructure();

    proteinParticles = MemoryManager::getProteinParticles();

    this->getCLManager()->ComputeProteinCOM( proteinSpace, proteinParticles, proteinsNumber, proteinParticlesNumber );

    this->getCLManager()->CLGLTask::ComputeProteinLipidInteraction( vertexBufferID, colorbufferid, systemStructure,  proteinSpace, proteinParticles, ATOMS_NUMBER, 0, ATOMS_NUMBER );

    timeElapced = time.restart();

    emit ProteinLipidInteractionComputed( frame, timeElapced );
}

void DataManager::fetchProteinParticlesSTL(unsigned int frameindex)
{
    STL::FetchProteinParticles( frameindex );
}

void DataManager::fetchLipidParticlesSTL(unsigned int frameindex)
{
    STL::FetchLipidParticles( frameindex );
}

void DataManager::fetchProteinSpaceSTL(unsigned int frameindex)
{

}

void DataManager::fetchProteinParticles( unsigned int frameindex)
{
    MMF::FetchProteinParticles( frameindex );
}

void DataManager::fetchLipidParticles(unsigned int frameindex)
{
    MMF::FetchLipidParticles( frameindex );
}

void DataManager::fetchProteinSpace(unsigned int frameindex)
{

}

void DataManager::testMinMaxDimentions(unsigned int frameindex, void *frame)
{
    QVector3D minDimentions;
    QVector3D maxDimentions;

    float newXDimention;
    float newYDimention;
    float newZDimention;

    float minXDimention;
    float minYDimention;
    float minZDimention;
    float maxXDimention;
    float maxYDimention;
    float maxZDimention;

    minDimentions = getMinDimentions();
    maxDimentions = getMaxDimentions();

    minXDimention = getMinDimentions().x();
    minYDimention = getMinDimentions().y();
    minZDimention = getMinDimentions().z();
    maxXDimention = getMaxDimentions().x();
    maxYDimention = getMaxDimentions().y();
    maxZDimention = getMaxDimentions().z();

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

    minDimentions.setX( minXDimention );
    minDimentions.setY( minYDimention );
    minDimentions.setZ( minZDimention );
    setMinDimentions( minDimentions );

    maxDimentions.setX( maxXDimention );
    maxDimentions.setY( maxYDimention );
    maxDimentions.setZ( maxZDimention );
    setMaxDimentions( maxDimentions );

    qDebug() << frameindex << "Min " << minDimentions << "Max " << maxDimentions;

}

void DataManager::min(float &value1, float value2)
{
    if( value1 > value2)
    {
        value1 = value2;
    }
}

void DataManager::max(float &value1, float value2)
{
    if( value1 < value2)
    {
        value1 = value2;
    }
}

void DataManager::CentralizeFrame(unsigned int index, void *frame, QVector3D dimentions, QVector3D mindimentions, QVector3D maxdimentions)
{

    float xDimention;
    float yDimention;
    float zDimention;
    float xMinDimention;
    float yMinDimention;
    float zMinDimention;
    float xMaxDimention;
    float yMaxDimention;
    float zMaxDimention;
    QVector3D point;
    bool processingState;

    processingState = this->getProcessingState();

    if( !processingState )
    {
        return;
    }

    xDimention = dimentions.x();
    yDimention = dimentions.y();
    zDimention = dimentions.z();
    xMinDimention = mindimentions.x();
    yMinDimention = mindimentions.y();
    zMinDimention = mindimentions.z();
    xMaxDimention = maxdimentions.x();
    yMaxDimention = maxdimentions.y();
    zMaxDimention = maxdimentions.z();

   this->getCLManager()->CentralizeFrame( frame, xDimention, yDimention, zDimention
                                          ,xMinDimention
                                          ,yMinDimention
                                          ,zMinDimention
                                          ,xMaxDimention
                                          ,yMaxDimention
                                          ,zMaxDimention
                                          ,ATOMS_NUMBER);

    //point = QVector3D(*((*((rvec *)frame + 3)) + X) , *((*((rvec *)frame + 3)) + Y) , *((*((rvec *)frame + 3)) + Z) );
    //qDebug() << index <<  point << dimentions << mindimentions << maxdimentions;
    //return;

    emit CentralizeFrameComputed( frame );
}

void DataManager::SaveCentralizeFrameToFile(void *frame)
{

    QString centralizeFrameFileName;
    FILE *centralizeFrameFile;

    centralizeFrameFileName = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;

    centralizeFrameFile = fopen( centralizeFrameFileName.toStdString().c_str(), "a");

    fwrite(frame, FRAME_SIZE, UINT_ONE, centralizeFrameFile) ;

    fclose(centralizeFrameFile);

}

void DataManager::SaveProteinParticlesCOMToFile(void *proteinspace)
{
    rvec *data;
    QString comParticleFileName;
    FILE *comParticleFile;
    bool processingState;
    unsigned int dataSize;


    processingState = this->getProcessingState();

    if( !processingState )
    {
        return;
    }

    dataSize = RVEC_SIZE * PROTEINS_NUMBER;
    data = (rvec*)malloc( dataSize );

    comParticleFileName = DATA_DIRECTORY + COM_DIRECTORY + COM_PARTICLE_FILE;

    comParticleFile = fopen( comParticleFileName.toStdString().c_str(), "a");

    for( unsigned int index = UINT_ZERO; index < PROTEINS_NUMBER; index++)
    {
        memcpy(data + index, ((GPUProteinSpace *)proteinspace + index)->ProteinCOM , RVEC_SIZE) ;
    }

    fwrite(data, dataSize, UINT_ONE, comParticleFile) ;

    fclose(comParticleFile);
    free(data);

}

void DataManager::SaveLipidParticlesCOMToFile(void *lipidspace)
{
    rvec *data;
    QString comParticleFileName;
    FILE *comParticleFile;
    bool processingState;
    unsigned int dataSize;


    processingState = this->getProcessingState();

    if( !processingState )
    {
        return;
    }

    dataSize = RVEC_SIZE * LIPIDS_NUMBER;

    data = (rvec*)malloc( dataSize );

    comParticleFileName = DATA_DIRECTORY + COM_DIRECTORY + COM_PARTICLE_FILE;

    comParticleFile = fopen( comParticleFileName.toStdString().c_str(), "a");

    for( unsigned int index = UINT_ZERO; index < LIPIDS_NUMBER; index++)
    {
        memcpy(data + index, ((GPULipidSpace *)lipidspace + index)->LipidCOM, RVEC_SIZE) ;
    }

    fwrite(data, dataSize, UINT_ONE, comParticleFile) ;

    fclose(comParticleFile);
    free(data);

}

void DataManager::SaveProteinSpace(void *proteinspace)
{
    QTime time;
    QString proteinSpaceFileName;
    FILE *proteinSpaceFile;
    bool processingState;

    processingState = this->getProcessingState();

    if( !processingState )
    {
        return;
    }

    time.start();

    proteinSpaceFileName = DATA_DIRECTORY + COM_DIRECTORY + PROTEIN_SPACE_FILE;

    proteinSpaceFile = fopen( proteinSpaceFileName.toStdString().c_str(), "a");

    fwrite( proteinspace, GPU_PROTEIN_SPACE_SIZE, PROTEINS_NUMBER, proteinSpaceFile) ;

    fclose(proteinSpaceFile);

    qDebug() << "Write done ! " << time.elapsed();

}

void DataManager::initializeSignalsAndSlots()
{
    connect( this->getXTCManager(), SIGNAL(FrameFetched(uint, void*, QVector3D, QVector3D, QVector3D)), this, SLOT(CentralizeFrame(uint, void*,QVector3D, QVector3D, QVector3D)) );
    //connect( this, SIGNAL(CentralizeFrameComputed(void*)), this, SLOT(SaveCentralizeFrameToFile(void*)) );
    connect( this, SIGNAL(ProteinSpaceComputed(void*)), this, SLOT(SaveProteinSpace(void*)) );
    connect( this, SIGNAL(ProteinSpaceComputed(void*)), this, SLOT(SaveProteinParticlesCOMToFile(void*)) );
    connect( this, SIGNAL(LipidSpaceComputed(void*)), this, SLOT(SaveLipidParticlesCOMToFile(void*)) );
}

void DataManager::initializeMinMaxDimention()
{
    QVector3D minDimentions;
    QVector3D maxDimentions;

    float minXDimention;
    float minYDimention;
    float minZDimention;
    float maxXDimention;
    float maxYDimention;
    float maxZDimention;


    minXDimention = 200.0f;
    minYDimention = 200.0f;
    minZDimention = 200.0f;
    maxXDimention = -200.0f;
    maxYDimention = -200.0f;
    maxZDimention = -200.0f;

    minDimentions.setX( minXDimention );
    minDimentions.setY( minYDimention );
    minDimentions.setZ( minZDimention );
    setMinDimentions( minDimentions );

    maxDimentions.setX( maxXDimention );
    maxDimentions.setY( maxYDimention );
    maxDimentions.setZ( maxZDimention );
    setMaxDimentions( maxDimentions );
}

void DataManager::GenerateAtomsPathFile(long typesize, long atomsnumber, long framesnumber)
{
    QTime time;
    QString particlesFile;
    QString pathsfile;
    bool processingState;

    processingState = this->getProcessingState();

    if( !processingState )
    {
        return;
    }


    time.start();

    particlesFile = DATA_DIRECTORY + IND_DIRECTORY + IND_PARTICLE_FILE;
    pathsfile = DATA_DIRECTORY + IND_DIRECTORY + IND_PATH_FILE;

    bio::mapped_file_source outData;//(params);

    bio::mapped_file_params params;
    params.path = pathsfile.toStdString();
    params.new_file_size = typesize * atomsnumber * framesnumber;
    params.flags = bio::mapped_file::mapmode::readwrite;
    params.offset = 0;
    bio::mapped_file_sink inData;//(params);

    inData.open(params);

    MMF::ReadFile(outData, particlesFile, 0, typesize, atomsnumber, framesnumber);

    long index(0);
    for(long atomIndex = UINT_ZERO; atomIndex < atomsnumber ; atomIndex ++)
    {
        for(long frameIndex = UINT_ZERO; frameIndex < framesnumber; frameIndex++)
        {
            memcpy( inData.data() + (index * typesize), outData.data() + ((frameIndex * atomsnumber + atomIndex) * typesize) , typesize);
            index++;
        }

        if(atomIndex %1000 == 0 )
            qDebug() << "Path Index" << atomIndex;
     }

    inData.close();
    outData.close();

    qDebug() << "Write done ! " << time.elapsed();
}

void DataManager::GenerateCOMAtomsPathFile(long typesize, long atomsnumber, long framesnumber)
{
    QTime time;
    QString particlesFile;
    QString pathsfile;
    bool processingState;

    processingState = this->getProcessingState();

    if( !processingState )
    {
        return;
    }


    time.start();

    particlesFile = DATA_DIRECTORY + COM_DIRECTORY + COM_PARTICLE_FILE;
    pathsfile = DATA_DIRECTORY + COM_DIRECTORY + COM_PATH_FILE;

    bio::mapped_file_source outData;//(params);

    bio::mapped_file_params params;
    params.path = pathsfile.toStdString();
    params.new_file_size = typesize * atomsnumber * framesnumber;
    params.flags = bio::mapped_file::mapmode::readwrite;
    params.offset = 0;
    bio::mapped_file_sink inData;//(params);

    inData.open(params);

    MMF::ReadFile(outData, particlesFile, 0, typesize, atomsnumber, framesnumber);

    long index(0);
    for(long pathIndex = UINT_ZERO; pathIndex < atomsnumber ; pathIndex ++)
    {
        for(long frameIndex = UINT_ZERO; frameIndex < framesnumber; frameIndex++)
        {
            memcpy( inData.data() + (index * typesize), outData.data() + ((frameIndex * atomsnumber + pathIndex) * typesize) , typesize);
            index++;
        }
        qDebug() << pathIndex;
     }

    inData.close();
    outData.close();

    qDebug() << "Write COM done ! " << time.elapsed();
}

