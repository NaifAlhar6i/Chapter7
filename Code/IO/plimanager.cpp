#include "plimanager.h"
#include "unistd.h"
PLIManager::PLIManager()
{
    this->initialPLIManager();
}

PLIManager::~PLIManager()
{
    this->freeResoures();
}

void PLIManager::initialPLIManager()
{
    PLIFileHeader pliFileHeader;
    unsigned int recodesCount;
    unsigned int lookUpBufferSize;
    unsigned long recourdBufferSize;
    unsigned int headerOffset;
    unsigned long fileSize;

    QString interactionFileName;

    lookUpBufferSize = PLI_LOOKUP_TABLE_SIZE * FRAMES_NUMBER;
    recourdBufferSize = PLI_RECORD_SIZE;
    interactionFileName = DATA_DIRECTORY + INTERACTION_DIRECTORY + INTERACTION_FILE;

    this->setFileName( interactionFileName );


    headerOffset = PLI_FILE_HEADER_SIZE + lookUpBufferSize;
    fileSize = headerOffset;

    if( m_PLILookUpTable == NULL )
    {
        m_PLILookUpTable = ( PLILookUpTable *)malloc( lookUpBufferSize );
    }

    if( m_PLIRecords != NULL )
    {
        m_PLIRecords = ( PLIRecord *)malloc( recourdBufferSize ); // initial size
    }

    this->setHeaderOffset( headerOffset );

    if( this->isFileExist() )
    {
        //Load header and lookup table
        this->loadHeaders();
        pliFileHeader = this->getPLIFileHeader();
        recodesCount = pliFileHeader.RecordCount;
        fileSize+= PLI_RECORD_SIZE * recodesCount;
    }
    else
    {
        this->initialHeader();
        this->initialLookUpTable();
    }

    this->setFileSize( fileSize );

}

void PLIManager::updateHeader()
{

}

void PLIManager::loadHeaders()
{
    FILE *interactionFile;
    QString interactionFileName;

    interactionFileName = this->getFileName();

    interactionFile = fopen( interactionFileName.toStdString().c_str(), "rb");

    this->loadHeader( interactionFile );
    this->loadLookUpTable( interactionFile );

    fclose( interactionFile );
}

void PLIManager::UpdateLookUpTable(unsigned short frameindex, unsigned int firstrecordindex, unsigned int recorsnumber)
{

}

void PLIManager::UpdateRecord(unsigned short frameindex, unsigned int recordindex, PLIRecord plirecord)
{

}

void PLIManager::InsertRecord(unsigned short frameindex, unsigned char proteintype, unsigned short proteinindex, unsigned char proteinresidue, unsigned short presidueparticle, unsigned int pparticleindex, unsigned char lipidtype, unsigned short lipidindex, unsigned char lipidresidue, unsigned short lresidueparticle, unsigned int lparticleindex)
{

}

void PLIManager::PrintOut()
{
    PLILookUpTable *pliLookUpTable;
    unsigned short framesNumber;

    framesNumber = FRAMES_NUMBER;

    pliLookUpTable = this->getPLILookUpTable();

    for( unsigned short frameIndex= UINT_ZERO; frameIndex < framesNumber; frameIndex++)
    {
       qDebug() << (pliLookUpTable + frameIndex)->FrameIndex ;
    }

}

void PLIManager::initialHeader()
{
    PLIFileHeader pliFileHeader;
    unsigned short framesNumber;
    unsigned int headersOffset;

    framesNumber = FRAMES_NUMBER;
    headersOffset = this->getHeaderOffset();

    pliFileHeader.FramesNumber = framesNumber;
    pliFileHeader.HeadersOffset = headersOffset;

    this->setPLIFileHeader( pliFileHeader );
}

void PLIManager::initialLookUpTable()
{
    PLILookUpTable *pliLookUpTable;
    unsigned short framesNumber;

    framesNumber = FRAMES_NUMBER;

    pliLookUpTable = this->getPLILookUpTable();

    for( unsigned short frameIndex= UINT_ZERO; frameIndex < framesNumber; frameIndex++)
    {
         (pliLookUpTable + frameIndex)->FrameIndex = frameIndex;
         (pliLookUpTable + frameIndex)->FirstRecordIndex = UINT_ZERO;
         (pliLookUpTable + frameIndex)->RecordsNumber = UINT_ZERO;
    }
}

void PLIManager::loadHeader(FILE *file)
{
    PLIFileHeader pliFileHeader;
    fseek(file, UINT_ZERO, SEEK_SET );
    fread(&pliFileHeader, PLI_FILE_HEADER_SIZE, UINT_ONE, file);

    this->setPLIFileHeader( pliFileHeader );

}

void PLIManager::loadLookUpTable(FILE *file)
{
    PLILookUpTable *pliLookUpTable;

    pliLookUpTable = this->getPLILookUpTable();

    fseek(file, PLI_FILE_HEADER_SIZE, SEEK_SET );
    fread( pliLookUpTable, PLI_LOOKUP_TABLE_SIZE, FRAMES_NUMBER, file);

}

void PLIManager::loadProteinRecords(unsigned short proteinindex)
{

}

void PLIManager::loadFrameProteinsRecords(unsigned short frameindex)
{

}

void PLIManager::loadFrameProteinRecords(unsigned short frameindex, unsigned short proteinindex)
{

}

void PLIManager::writeHeader(PLIFileHeader pliheader)
{

}

void PLIManager::writeLookUpTable(PLILookUpTable plilookuptable)
{

}

void PLIManager::writeRecord(PLIRecord plirecord)
{

}

void PLIManager::freeResoures()
{
    if( m_PLILookUpTable != NULL )
    {
        free( m_PLILookUpTable );
    }

    if( m_PLIRecords != NULL )
    {
        free( m_PLIRecords );
    }
}

bool PLIManager::isFileExist()
{
    QString interactionFileName;

    interactionFileName = this->getFileName();

    if( access( interactionFileName.toStdString().c_str(), F_OK ) != -1 ) {
        return true;
    } else {
        return false;
    }
}
