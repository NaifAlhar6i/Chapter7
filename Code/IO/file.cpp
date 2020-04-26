#include "file.h"
#include <QTime>
#include <vector>

namespace bio = boost::iostreams;
using namespace std;

File::File()
{
}

void File::AppendProteinSpace(void *data)
{
    FILE *proteinSpaceFile;
    QString fileName;

    fileName = DATA_DIRECTORY + CONFIGURATION_DIRECTORY + PROTEIN_SPACE_FILE;

    proteinSpaceFile = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, GPU_PROTEIN_SPACE_SIZE, PROTEINS_NUMBER, proteinSpaceFile);

    fclose(proteinSpaceFile);

}

void File::AppendCOMFrame(GPUProteinSpace *proteinspace)
{
    rvec *data;
    unsigned int bufferSize;
    FILE *comFrameFile;
    QString fileName;

    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_FRAME_FILE;
    bufferSize = PROTEINS_NUMBER * RVEC_SIZE;

    data = (rvec*)malloc( bufferSize );

    for(unsigned int proteinIndex = UINT_ZERO; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
    {
        memcpy( data + proteinIndex, &(proteinspace + proteinIndex)->ProteinCOM[0], RVEC_SIZE );
    }

    comFrameFile = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, PROTEINS_NUMBER, RVEC_SIZE, comFrameFile);

    fclose(comFrameFile);

}

void File::AppendCOMFrame(GPULipidSpace *lipidspace)
{
    rvec *data;
    unsigned int bufferSize;
    FILE *comFrameFile;
    QString fileName;

    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_FRAME_FILE;
    bufferSize = LIPIDS_NUMBER * RVEC_SIZE;

    data = (rvec*)malloc( bufferSize );

    for(unsigned int lipidIndex = UINT_ZERO; lipidIndex < LIPIDS_NUMBER; lipidIndex++)
    {
        memcpy( data + lipidIndex, &(lipidspace + lipidIndex)->LipidCOM[0], RVEC_SIZE );
    }

    comFrameFile = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, LIPIDS_NUMBER, RVEC_SIZE, comFrameFile);

    fclose(comFrameFile);
}

void File::AppendProteinLipidInteraction(unsigned int frameindex, GPUParticleInteraction *particlesinteraction)
{
    PLIRecord *pliRecord;
    short moleculeType;
    short interactionNumber;
    unsigned long pliRecordSize;
    unsigned int recorsNumber;
    unsigned int totalRecordsNumber;
    unsigned int interactParticlesNumber;

    unsigned short  frameIndex;
    unsigned char   proteinType;
    unsigned short  proteinIndex;
    unsigned char   proteinResidue;
    unsigned short  pResidueParticle;
    unsigned int    pParticleIndex;
    unsigned char   lipidType;
    unsigned short  lipidIndex;
    unsigned char   lipidResidue;
    unsigned short  lResidueParticle;
    unsigned int    lParticleIndex;

    recorsNumber = UINT_ZERO;
    totalRecordsNumber = recorsNumber;
    interactParticlesNumber = UINT_ZERO;
            //create file

//    FILE *pliFile;
//    QString fileName;
//    fileName = DATA_DIRECTORY + INTERACTION_DIRECTORY + PROTEINS_LIPIDS_INTERACTION_FILE;
//    pliFile = fopen(fileName.toStdString().c_str(), "a");

    pliRecord = (PLIRecord *)malloc( PLI_RECORD_SIZE );
    for(unsigned int index= UINT_ZERO; index < PARTICLES_NUMBER; index++)
    {
        interactionNumber = (particlesinteraction + index)->InteractionCounter;
        moleculeType = (particlesinteraction + index)->MoleculeType;
        pParticleIndex =  (particlesinteraction + index)->ParticleID;
        if( interactionNumber > SHORT_ZERO /* && moleculeType > SHORT_ZERO i.e. moleculeType == protein */)
        {
            frameIndex = (unsigned short)frameindex;
            proteinType = 0;
            proteinIndex = 0;
            proteinResidue = 0;
            pResidueParticle = 0;
            lipidType = 0;
            lipidIndex = 0;
            lipidResidue = 0;
            lResidueParticle = 0;

//            qDebug() << "moleculeType ->" << moleculeType << "Interaction Count ->" << interactionNumber;

            interactParticlesNumber++;

            for(short interactionIndex = SHORT_ZERO; interactionIndex < interactionNumber; interactionIndex++)
            {
                pliRecordSize = interactionIndex * PLI_RECORD_SIZE + PLI_RECORD_SIZE;
                PLIRecord *newPLIRecord = (PLIRecord *)realloc(pliRecord, pliRecordSize );

                if( newPLIRecord != NULL )
                {
                    pliRecord = newPLIRecord;
                }
                else
                {
                    qDebug() << "Buffer couldnt created!";
                    free( pliRecord );
                    return;
                }

                (pliRecord + interactionIndex)->FrameIndex = frameIndex;
                (pliRecord + interactionIndex)->ProteinType = proteinType;
                (pliRecord + interactionIndex)->ProteinIndex = proteinIndex;
                (pliRecord + interactionIndex)->ProteinResidue = proteinResidue;
                (pliRecord + interactionIndex)->PResidueParticle = pResidueParticle;
                (pliRecord + interactionIndex)->PParticleIndex = pParticleIndex;
                (pliRecord + interactionIndex)->LipidType = lipidType;
                (pliRecord + interactionIndex)->LipidIndex = lipidIndex;
                (pliRecord + interactionIndex)->LipidResidue = lipidResidue;
                (pliRecord + interactionIndex)->LResidueParticle = lResidueParticle;
                lParticleIndex = (particlesinteraction + index)->Interaction[interactionIndex];
                (pliRecord + interactionIndex)->LParticleIndex = lParticleIndex;

                //encrease the records number
                recorsNumber++;
            }

            totalRecordsNumber+=recorsNumber;
            recorsNumber = UINT_ZERO;
            //fwrite( pliRecord, pliRecordSize, UINT_ONE, pliFile);
            //fflush(pliFile);


        }

    }

    qDebug() <<"Time step->"<< "interacting paerticles number->" << interactParticlesNumber << "total interaction->" << totalRecordsNumber << "average interaction ber particle->" << totalRecordsNumber/ interactParticlesNumber;
    recorsNumber = UINT_ZERO;

//    fclose(pliFile);
//    free( pliRecord );
}

void File::AppendReferenceProtein(void *data)
{
    FILE *referenceProtein;
    QString fileName;

    fileName = DATA_DIRECTORY + INDIVIDUAL_DIRECTORY + REFERENCE_PROTEIN_FILE;

    referenceProtein = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, SHORT_SIZE, PARTICLES_NUMBER, referenceProtein);

    fclose(referenceProtein);
}

void File::AppendCOMReferenceProtein(void *data)
{
    FILE *referenceProtein;
    QString fileName;
    unsigned int particlesNumber;

    particlesNumber = LIPIDS_NUMBER + PROTEINS_NUMBER;

    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_FRAME_REFERENCE_PROTEIN_FILE;

    referenceProtein = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, SHORT_SIZE, particlesNumber , referenceProtein);

    fclose(referenceProtein);
}

void File::AppendTotalInteractionPerFrame(void *data)
{
    FILE *totalInteractionPerFrame;
    QString fileName;

    fileName = DATA_DIRECTORY + INDIVIDUAL_DIRECTORY + TOTAL_INTERACTION_PER_FRAME_FILE;

    totalInteractionPerFrame = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, SHORT_SIZE, PARTICLES_NUMBER, totalInteractionPerFrame);

    fclose(totalInteractionPerFrame);
}

void File::AppendCOMTotalInteractionPerFrame(void *data)
{
    FILE *totalInteractionPerFrame;
    QString fileName;
    unsigned int particlesNumber;

    particlesNumber = LIPIDS_NUMBER + PROTEINS_NUMBER;
    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_TOTAL_INTERACTION_PER_FRAME_FILE;

    totalInteractionPerFrame = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, SHORT_SIZE, particlesNumber, totalInteractionPerFrame);

    fclose(totalInteractionPerFrame);
}

void File::WriteMaxInteraction(void *data)
{
    FILE *maxInteraction;
    QString fileName;

    fileName = DATA_DIRECTORY + CONFIGURATION_DIRECTORY + MAX_INTERACTION_FILE;

    maxInteraction = fopen(fileName.toStdString().c_str(), "wb");
//    fseek( maxInteraction, 0L, SEEK_SET );
    fwrite(data, SHORT_SIZE, UINT_ONE, maxInteraction);
    fflush(maxInteraction);
    fclose(maxInteraction);
}

void File::WriteCOMMaxInteraction(void *data)
{
    FILE *maxInteraction;
    QString fileName;

    fileName = DATA_DIRECTORY + CONFIGURATION_DIRECTORY + COM_MAX_INTERACTION_FILE;

    maxInteraction = fopen(fileName.toStdString().c_str(), "wb");
//    fseek( maxInteraction, 0L, SEEK_SET );
    fwrite(data, SHORT_SIZE, UINT_ONE, maxInteraction);
    fflush(maxInteraction);
    fclose(maxInteraction);
}

void File::AppendINDFrame(void *data)
{
    FILE *individualFrame;
    QString fileName;

    fileName = DATA_DIRECTORY + INDIVIDUAL_DIRECTORY + IND_FRAME_FILE;

    individualFrame = fopen(fileName.toStdString().c_str(), "a");

    fwrite(data, RVEC_SIZE, PARTICLES_NUMBER, individualFrame);

    fclose(individualFrame);
}

void File::ReadProteinsLipidsInteraction()
{

    QVector<unsigned int> interactionCounter;
    unsigned short frameIndex;
    unsigned short lastFrameIndex;
    QString fileName;
    bio::mapped_file_source outData;//(params);

    fileName = DATA_DIRECTORY + INTERACTION_DIRECTORY + PROTEINS_LIPIDS_INTERACTION_FILE;

    bio::mapped_file_params params;
    params.path = fileName.toStdString();
    //params.length = typesize * particlesnumber * framesnumber; 3,642,411,136
    params.flags = bio::mapped_file::mapmode::readonly;

    outData.open(params);

    lastFrameIndex = 60000;
    for(unsigned int index = 0 ; index <  130086112  ; index++)
    {
        frameIndex = ((PLIRecord *)outData.data() + index)->FrameIndex;
        if( lastFrameIndex != frameIndex )
        {
            lastFrameIndex = frameIndex;
            interactionCounter.append(index);
//            qDebug() << "Frame Index " << frameIndex << " Value " <<  index;
        }
    }

    for(unsigned int index = 0 ; index <  interactionCounter.size()  ; index++)
    {
            qDebug() << "Frame Index " << interactionCounter.value(index);
    }
    qDebug() << "Done!" << interactionCounter.size() << " record Number " << 3642411136/PLI_RECORD_SIZE;

    outData.close();

}

void File::ReadCOMFrame(rvec *&frame, unsigned int frameindex, unsigned int framesize)
{
    FILE *comFrame;
    QString fileName;
    unsigned int position;
    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_FRAME_FILE;

    comFrame = fopen(fileName.toStdString().c_str(), "rb");

    position = frameindex * framesize;
    fseek(comFrame, position, SEEK_SET );

    fread(frame, framesize, UINT_ONE, comFrame);

    fclose(comFrame);

}

const char *File::MapEntirePathsFile( unsigned int buffersize)
{
    const char *data;
    QString fileName;

    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_PATH_FILE;

    bio::mapped_file_params params;
    params.path = fileName.toStdString();
    params.length = buffersize;
    params.flags = bio::mapped_file::mapmode::readonly;

    this->getEntireFile().open(params);

    data = this->getEntireFile().data();

    return data;


}

const char *File::MapEntireIndicesFile( unsigned int buffersize)
{
    const char *data;
    QString fileName;

    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_PATH_INDEX_FILE;

    bio::mapped_file_params params;
    params.path = fileName.toStdString();
    params.length = buffersize;
    params.flags = bio::mapped_file::mapmode::readonly;

    if( this->getEntireFile().is_open() )
        this->getEntireFile().close();

    this->getEntireFile().open(params);

    data = this->getEntireFile().data();

    return data;
}

const char *File::MapEntireProteinReferenceFile(unsigned int buffersize, bool framebased)
{
    const char *data;
    QString fileName;

    if( framebased == true )
    {
        fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_FRAME_REFERENCE_PROTEIN_FILE;
    }
    else
    {
        fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_PATH_REFERENCE_PROTEIN_FILE;
    }

    bio::mapped_file_params params;
    params.path = fileName.toStdString();
    params.length = buffersize;
    params.flags = bio::mapped_file::mapmode::readonly;

    if( this->getEntireFile().is_open() )
        this->getEntireFile().close();

    this->getEntireFile().open(params);

    data = this->getEntireFile().data();

    return data;
}

void File::UnmapEntireFile()
{
    if( this->getEntireFile().is_open() )
        this->getEntireFile().close();
}

void File::CreatTestFile(QString filename)
{




    QTime  time;

    time.start();

    FILE *file;

    unsigned int *data = (unsigned int *)malloc( 336260 * 1981 * sizeof(unsigned int));

    unsigned int index(0);
    for(unsigned int vertexIndex =  0; vertexIndex <  1981; vertexIndex++)
    {
        for(unsigned int pathIndex = 0; pathIndex < 336260; pathIndex++)
        {
            index = vertexIndex * 336260 + pathIndex;
            *(data + index  ) = pathIndex;
        }
    }

    file = fopen(filename.toStdString().c_str(), "wb");


    fwrite(data, sizeof(unsigned int), 336260 * 1981, file);


    free(data);
    fclose(file);

    qDebug() << " Done" << time.elapsed();


}

void File::ReadTestFile()
{
    bio::mapped_file_source outData;//(params);
    QString fileName;
    unsigned int particlesNumber;
    particlesNumber = LIPIDS_NUMBER + PROTEINS_NUMBER;

    fileName = DATA_DIRECTORY + CENTER_OF_MASS_DIRECTORY + COM_PATH_INDEX_FILE;
    this->readFile(outData, fileName, UNSIGNED_INT_SIZE, particlesNumber ,FRAMES_NUMBER);

    for(unsigned int index = 256 * FRAMES_NUMBER ; index <  256 * FRAMES_NUMBER + FRAMES_NUMBER ; index++)
    {
        qDebug() << "Index " << index << " Value " << *((unsigned int *)outData.data() + index) ;
    }

    outData.close();

}

void File::PrintOutTypesInfo()
{
    qDebug() << "Bool" << sizeof (bool);
    qDebug() << "Char" << sizeof (char);
    qDebug() << "Unsigned Char" << sizeof (unsigned char);
    qDebug() << "short" << sizeof ( short);
    qDebug() << "Unsigned short" << sizeof (unsigned short);
    qDebug() << "Int" << sizeof ( int);
    qDebug() << "Unsigned Int" << sizeof (unsigned int);
    qDebug() << "Long" << sizeof ( long );
    qDebug() << "Unsigned Long" << sizeof (unsigned long);
    qDebug() << "Float" << sizeof ( float );
    qDebug() << "Double" << sizeof (double);
}


void File::CreateFrame()
{
    this->createFrame();
}

void File::FrameToPath(QString framesfile, QString pathsfile, unsigned int typesize, unsigned int particlesnumber, unsigned int framesnumber)
{
    this->frameToPath(framesfile, pathsfile, typesize, particlesnumber, framesnumber);
}

void File::GenerateIndices(QString interactionsfile, QString pathsfile, unsigned int particlesnumber, unsigned int framesnumber)
{
    this->generateIndices( interactionsfile, pathsfile, particlesnumber, framesnumber );
}

void File::AppendAverageToProteinCOMFile()
{

    ReadProteinSpaceAverage();

    return;

    QTime time;

    time.start();

    QString proteinSpaceFileName;
    QString proteinSpaceAverageFileName;
    short proteinID;
    float radius;
    float xPosition;
    float yPosition;
    float zPosition;
    float zFar;
    float zNear;

    float minRadius;
    float maxRadius;
    float averageRadius[256];

    unsigned int index;
    float xAveragePosition[256];
    float yAveragePosition[256];
    float zAveragePosition[256];

    float xStartPosition[256];
    float yStartPosition[256];
    float zStartPosition[256];

    float xEndPosition[256];
    float yEndPosition[256];
    float zEndPosition[256];

    GPUProteinSpaceAverage proteinSpaceAverage;


    proteinSpaceFileName =DATA_DIRECTORY + CONFIGURATION_DIRECTORY + PROTEIN_SPACE_FILE;
    proteinSpaceAverageFileName =DATA_DIRECTORY + CONFIGURATION_DIRECTORY + PROTEIN_SPACE_AVERAGE_FILE;


    bio::mapped_file_params params;
    params.path = proteinSpaceAverageFileName.toStdString();
    params.new_file_size = GPU_PROTEIN_SPACE_AVERAGE_SIZE * PROTEINS_NUMBER * FRAMES_NUMBER;
    params.flags = bio::mapped_file::mapmode::readwrite;
    bio::mapped_file_sink inData;//(params);

    inData.open(params);


    minRadius = 10;
    maxRadius = 0;
    bio::mapped_file_source outData;//(params);
    this->readFile( outData, proteinSpaceFileName, GPU_PROTEIN_SPACE_SIZE, PROTEINS_NUMBER, FRAMES_NUMBER);

    for(unsigned int proteinIndex = UINT_ZERO; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
    {
        averageRadius[proteinIndex] = 0.0;
        xAveragePosition[proteinIndex] = 0.0;
        yAveragePosition[proteinIndex] = 0.0;
        zAveragePosition[proteinIndex] = 0.0;
    }

    for(unsigned int frameIndex =  UINT_ZERO ; frameIndex < FRAMES_NUMBER ; frameIndex++)
    {

        for(unsigned int proteinIndex = UINT_ZERO; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
        {
            index = frameIndex * PROTEINS_NUMBER + proteinIndex;
            proteinID = ((GPUProteinSpace *)outData.data() + index  )->ProteinID;
            xPosition = ((GPUProteinSpace *)outData.data() + index  )->ProteinCOM[X];
            yPosition = ((GPUProteinSpace *)outData.data() + index  )->ProteinCOM[Y];
            zPosition = ((GPUProteinSpace *)outData.data() + index  )->ProteinCOM[Z];
            zFar =  ((GPUProteinSpace *)outData.data() + index  )->ZAxis[X];
            zNear =  ((GPUProteinSpace *)outData.data() + index  )->ZAxis[Y];
            radius = ((GPUProteinSpace *)outData.data() + index  )->Radius;

            averageRadius[proteinIndex] += radius;
            xAveragePosition[proteinIndex] += xPosition;
            yAveragePosition[proteinIndex] += yPosition;
            zAveragePosition[proteinIndex] += zPosition;

            if(frameIndex == UINT_ZERO )
            {
                xStartPosition[proteinIndex] = xPosition;
                yStartPosition[proteinIndex] = yPosition;
                zStartPosition[proteinIndex] = zPosition;
            }
            else if ( frameIndex == 1980  )
            {
                xEndPosition[proteinIndex] = xPosition;
                yEndPosition[proteinIndex] = yPosition;
                zEndPosition[proteinIndex] = zPosition;
            }



            proteinSpaceAverage.ProteinID = proteinID;
            proteinSpaceAverage.ProteinCOM[X] = xPosition;
            proteinSpaceAverage.ProteinCOM[Y] = yPosition;
            proteinSpaceAverage.ProteinCOM[Z] = zPosition;
            proteinSpaceAverage.ZAxis[X] = zFar;
            proteinSpaceAverage.ZAxis[Y] = zNear;
            proteinSpaceAverage.Radius = radius;

            *((GPUProteinSpaceAverage *)inData.data() + index  ) = proteinSpaceAverage;
        }

        //radius = ((GPUProteinSpace *)outData.data() + index  )->Radius;


    }

    for(unsigned int proteinIndex = UINT_ZERO; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
    {
        averageRadius[proteinIndex] /= 1981.0;
        xAveragePosition[proteinIndex] /= 1981.0;
        yAveragePosition[proteinIndex] /= 1981.0;
        zAveragePosition[proteinIndex] /= 1981.0;
        qDebug() << "Radius ->" << averageRadius[proteinIndex];
    }

    for(unsigned int frameIndex =  UINT_ZERO ; frameIndex < FRAMES_NUMBER ; frameIndex++)
    {

        for(unsigned int proteinIndex = UINT_ZERO; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
        {
            index = frameIndex * PROTEINS_NUMBER + proteinIndex;


            ((GPUProteinSpaceAverage *)inData.data() + index  )->AverageRadius = averageRadius[proteinIndex];
            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinFirstPosition[X] = xStartPosition[proteinIndex];
            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinFirstPosition[Y] = yStartPosition[proteinIndex];
            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinFirstPosition[Z] = zStartPosition[proteinIndex];

            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinAveragePosition[X] = xAveragePosition[proteinIndex];
            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinAveragePosition[Y] = yAveragePosition[proteinIndex];
            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinAveragePosition[Z] = zAveragePosition[proteinIndex];

            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinEndPosition[X] = xEndPosition[proteinIndex];
            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinEndPosition[Y] = yEndPosition[proteinIndex];
            ((GPUProteinSpaceAverage *)inData.data() + index  )->ProteinEndPosition[Z] = zEndPosition[proteinIndex];
        }

        //radius = ((GPUProteinSpace *)outData.data() + index  )->Radius;


    }
    inData.close();
    outData.close();

    qDebug() << "Write done ! " << time.elapsed();
}

void File::ReadProteinSpaceAverage()
{
    QTime time;

    time.start();

    QString proteinSpaceAverageFileName;

    proteinSpaceAverageFileName =DATA_DIRECTORY + CONFIGURATION_DIRECTORY + PROTEIN_SPACE_AVERAGE_FILE;


    bio::mapped_file_source outData;//(params);
    this->readFile( outData, proteinSpaceAverageFileName, GPU_PROTEIN_SPACE_AVERAGE_SIZE , PROTEINS_NUMBER, FRAMES_NUMBER);

    for(unsigned int index = 255; index< FRAMES_NUMBER * PROTEINS_NUMBER; index+=PROTEINS_NUMBER)
    {
        qDebug() << ((GPUProteinSpaceAverage *)outData.data() + index )->AverageRadius;
    }

    outData.close();
}

void File::GetPaths(bio::mapped_file_source &out)
{
    bio::mapped_file_params params;
    params.path = "/Users/Naif/Dropbox/PhD/MDSProject/Data/Individual/INDFrame.data";
//    params.length = typesize * particlesnumber * framesnumber;
    params.flags = bio::mapped_file::mapmode::readonly;

    out.open(params);
}

bool File::isProteinSpaceExist(GPUProteinSpace *data)
{
    bool isExisit;
    unsigned int time;
    FILE *proteinSpace;
    QString proteinSpaceFile;

    proteinSpaceFile = DATA_DIRECTORY + CONFIGURATION_DIRECTORY + PROTEIN_SPACE_FILE ;
    QFile file(proteinSpaceFile);
    isExisit = file.exists();

    if( isExisit )
    {
        time = PROTEINS_NUMBER * FRAMES_NUMBER;
        proteinSpace = fopen( proteinSpaceFile.toStdString().c_str(), "r" );
        fseek(proteinSpace, 0L, SEEK_SET );
        fread( data, GPU_PROTEIN_SPACE_SIZE, time , proteinSpace );

        fclose(proteinSpace);
    }
    return isExisit;
}

void File::readFile(boost::iostreams::mapped_file_source &out, QString name, unsigned int typesize, unsigned int particlesnumber, unsigned int framesnumber)
{

    bio::mapped_file_params params;
    params.path = name.toStdString();
    params.length = typesize * particlesnumber * framesnumber;
    params.flags = bio::mapped_file::mapmode::readonly;

    out.open(params);
}

void File::createFrame()
{
    QTime time;

    time.start();

    bio::mapped_file_params params;
    params.path = "/Users/naif/Documents/textFrame.txt";
    params.new_file_size = sizeof(unsigned int ) * 336260 * 1981;
    params.flags = bio::mapped_file::mapmode::readwrite;
    bio::mapped_file_sink inData;//(params);

    inData.open(params);

    unsigned int index(0);
    for(unsigned int vertexIndex =  0; vertexIndex <  1981; vertexIndex++)
    {
        for(unsigned int pathIndex = 0; pathIndex < 336260; pathIndex++)
        {
            index = vertexIndex * 336260 + pathIndex;
//            memcpy( out.data() + index * sizeof(unsigned int ), &pathIndex, sizeof(unsigned int ));
            *((unsigned int *)inData.data() + index  ) = pathIndex;
        }
    }

    inData.close();

    bio::mapped_file_source outData;//(params);
    this->readFile(outData, "/Users/naif/Documents/textFrame.txt",0,0,0);
    for(unsigned int index =  0; index < 1981 * 3; index++)
    {
        qDebug() << "value" << *((unsigned int *)outData.data() + index  );
    }
    outData.close();

    qDebug() << "Write done ! " << time.elapsed();
}

void File::frameToPath(QString framesfile, QString pathsfile, unsigned int typesize, unsigned int particlesnumber, unsigned int framesnumber)
{
    QTime time;

    time.start();

    bio::mapped_file_source outData;//(params);

    bio::mapped_file_params params;
    params.path = pathsfile.toStdString();
    params.new_file_size = typesize * particlesnumber * framesnumber;
    params.flags = bio::mapped_file::mapmode::readwrite;
    params.offset = 0;
    bio::mapped_file_sink inData;//(params);

    inData.open(params);

    this->readFile(outData, framesfile, typesize, particlesnumber, framesnumber);

    unsigned int index(0);
    for(unsigned int pathIndex = UINT_ZERO; pathIndex < particlesnumber ; pathIndex ++)
    {
        for(unsigned int frameIndex = UINT_ZERO; frameIndex < framesnumber; frameIndex++)
        {
            memcpy( inData.data() + (index * typesize), outData.data() + ((frameIndex * particlesnumber + pathIndex) * typesize) , typesize);
//            *((rvec *)inData.data() + index  ) = *((rvec *)outData.data() + frameIndex * particlesnumber + pathIndex  );
            index++;
        }
     }

    inData.close();
    outData.close();

//    this->readFile(outData, "/Users/naif/Documents/textPath.txt");

//    for(unsigned int frameIndex = 0; frameIndex < 1981 * 3; frameIndex++)
//    {
//        qDebug() << " New Order" << *((unsigned int *)outData.data() + frameIndex );
//    }

//    outData.close();

    qDebug() << "Write done ! " << time.elapsed();
}

void File::generateIndices(QString interactionsfile, QString pathsfile, unsigned int particlesnumber, unsigned int framesnumber)
{
    QTime time;

    unsigned int totalVerticesNumber;
    unsigned int typeSize;
    unsigned int index;
    unsigned int lastIndex;
    short interactProtein;
    bool interaction;
    bool travel;

    qDebug() << "Start!";

    time.start();

    bio::mapped_file_source outData;//(params);

    bio::mapped_file_params params;
    params.path = pathsfile.toStdString();
    params.new_file_size = UNSIGNED_INT_SIZE * particlesnumber * framesnumber ;
    params.flags = bio::mapped_file::mapmode::readwrite;
    params.offset = 0;
    bio::mapped_file_sink inData;//(params);

    inData.open(params);

    typeSize = SHORT_SIZE;
    this->readFile(outData, interactionsfile, typeSize, particlesnumber, framesnumber);

    index = UINT_ZERO;

    totalVerticesNumber = particlesnumber * framesnumber;

    for(unsigned int pathIndex = UINT_ZERO; pathIndex < particlesnumber ; pathIndex ++)
    {
        interaction = false;
        travel = false;
        for(unsigned int frameIndex = UINT_ZERO; frameIndex < framesnumber; frameIndex++)
        {
            index = pathIndex * FRAMES_NUMBER + frameIndex;

            interactProtein = *( (short *)outData.data() + index ) ;

            if( interactProtein > SHORT_ZERO )
            {
                if( interaction == false )
                {
                    lastIndex = index;
                    interaction = true;
                    travel= false;
                }

                *((unsigned int *)inData.data() + index  ) = lastIndex;
            }
            else
            {
                if( travel == false )
                {
                    lastIndex = index;
                    interaction = false;
                    travel = true;
                }

                *((unsigned int *)inData.data() + index  ) = lastIndex;
            }
        }
     }


     for(unsigned int frameIndex = 1981; frameIndex < 1981 * 2; frameIndex++)
     {
         qDebug() << " New Order" << *((unsigned int *)inData.data() + frameIndex );
     }

    inData.close();
    outData.close();

    qDebug() << "Write done ! " << time.elapsed();
}
