#ifndef PLIMANAGER_H
#define PLIMANAGER_H

#include "structure/structure.h"
#include <boost/iostreams/device/mapped_file.hpp>
#include<boost/iostreams/stream.hpp>

using namespace boost;

class PLIManager
{
public:
    PLIManager();
    ~PLIManager();
    void initialPLIManager();

    void UpdateLookUpTable(unsigned short frameindex, unsigned int firstrecordindex, unsigned int recorsnumber);
    void UpdateRecord(unsigned short frameindex, unsigned int recordindex, PLIRecord plirecord);
    void InsertRecord( unsigned short frameindex, unsigned char proteintype, unsigned short proteinindex, unsigned char proteinresidue,
                        unsigned short presidueparticle, unsigned int pparticleindex,
                        unsigned char lipidtype, unsigned short lipidindex, unsigned char lipidresidue, unsigned short lresidueparticle, unsigned int lparticleindex);

    void PrintOut();
private :

    unsigned long m_FileSize;
    QString m_FileName;
    unsigned int m_HeaderOffset;
    PLIFileHeader m_PLIHeader;
    PLILookUpTable *m_PLILookUpTable = NULL;
    PLIRecord *m_PLIRecords = NULL;
    PLIRecord m_PLIRecord;

    boost::iostreams::mapped_file m_FileData;

    inline QString getFileName() { return m_FileName; }
    inline PLIFileHeader getPLIFileHeader() { return m_PLIHeader; }
    inline PLILookUpTable *&getPLILookUpTable() { return m_PLILookUpTable; }
    inline PLIRecord *&getPLIRecords() { return m_PLIRecords; }
    inline PLIRecord getPLIRecord() { return m_PLIRecord; }
    inline unsigned int getHeaderOffset() { return m_HeaderOffset; }
    inline unsigned long getFileSize() { return m_FileSize; }

    inline boost::iostreams::mapped_file getFileData() { return m_FileData; }

    inline void setPLIFileHeader(PLIFileHeader plifileheader) { m_PLIHeader = plifileheader; }
    inline void setHeaderOffset( unsigned int headeroffset ) { m_HeaderOffset = headeroffset; }
    inline void setFileSize( unsigned long filesize) { m_FileSize = filesize; }
    inline void setFileName( QString filename ) { m_FileName = filename; }

    void initialHeader();
    void initialLookUpTable();
    void updateHeader();

    void loadHeaders();
    void loadHeader(FILE *file);
    void loadLookUpTable(FILE *file);
    void loadProteinRecords(unsigned short proteinindex);
    void loadFrameProteinsRecords( unsigned short frameindex);
    void loadFrameProteinRecords( unsigned short frameindex, unsigned short proteinindex);
    void writeHeader(PLIFileHeader pliheader);
    void writeLookUpTable(PLILookUpTable plilookuptable);
    void writeRecord( PLIRecord plirecord);

    void freeResoures();
    bool isFileExist();

};

#endif // PLIMANAGER_H
