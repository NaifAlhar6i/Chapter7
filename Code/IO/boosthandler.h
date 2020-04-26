#ifndef BOOSTHANDLER_H
#define BOOSTHANDLER_H

#include <qDebug>
#include <QVector3D>
#include <QPair>
#include <boost/iostreams/device/mapped_file.hpp>
#include<boost/iostreams/stream.hpp>

#include "structure/structure.h"

using namespace boost;

class BoostHandler
{
public:
    BoostHandler();
    inline  int GetPathIndex()      { return m_PathIndex; }
    inline QString GetIndexFile() { return m_IndexFile; }

    inline void SetSphereFile( QString spherefile ) { m_SphereFile = spherefile ; }
    void SetPathFile( QString pathfile );
    void SetIndexFile(QString indexfile);
    inline void SetPathIndex( int value)    { m_PathIndex    = value   ; }

protected:
    inline boost::iostreams::mapped_file_source &getSphereData() { return m_SphereData; }
    inline boost::iostreams::mapped_file_source &getPathData() { return m_PathData; }
    inline boost::iostreams::mapped_file_source &getIndicesData() { return m_IndicesData; }

    const char *mapSinglePathData(unsigned int &pathindex , unsigned int framesnumber);
    const char *mapSphereData(unsigned int &frameindex , unsigned int &particlesnumber);
    const char *mapMultiPathData(unsigned int &pathgroupindex, unsigned int pathbasednumber, unsigned int pathsnumber, unsigned int framesnumber );
    const char *mapBulckPathData(unsigned int firstpathindex, unsigned int pathsnumber, unsigned int framesnumber);

//    const char *mapSphereData(unsigned int &frameindex , unsigned int &atomsnumber);
    const char *mapSinglePathIndicesData(unsigned int &pathindex , unsigned int framesnumber);
    const char *mapMultiPathIndicesData(unsigned int &pathgroupindex , unsigned int pathsbasednumber, unsigned int pathsnumber, unsigned int framesnumber);
//    const char *mapPathData(unsigned int &pathgroupindex, unsigned int pathsnumber );
    void mapFrameTest(unsigned int index);

private:
    long m_FirstByte[ UINT_FIVE ];
    long m_LastByte[ UINT_FIVE ];
    long m_CurrentByte[ UINT_FIVE ];
    long m_BytePosition[ UINT_FIVE ];
    QString m_SphereFile;
    QString m_PathFile;
    QString m_IndexFile;
    unsigned int m_FrameIndex;
    unsigned int m_PathIndex;
    unsigned int m_GroupIndex[ UINT_FIVE ];
    boost::iostreams::mapped_file_source m_SphereData;
    boost::iostreams::mapped_file_source m_PathData;
    boost::iostreams::mapped_file_source m_IndicesData;

    inline unsigned int getFrameIndex()      { return m_FrameIndex; }
    inline unsigned int getPathIndex()      { return m_PathIndex; }
    inline unsigned int getGroupIndex( DataType object)      { return m_GroupIndex[object]; }
    inline long getFirstByte( DataType object )      { return m_FirstByte[object];  }
    inline long getLastByte( DataType object )       { return m_LastByte[object];    }
    inline long getCurrentByte(DataType object)    { return   m_CurrentByte[object]; }
    inline long getBytePosition(DataType object)   { return   m_BytePosition[object]; }
    inline QString getSphereFile()   { return m_SphereFile; }
    inline QString getPathFile()   { return m_PathFile; }
    inline QString getIndexFile()   { return m_IndexFile; }

    inline void setFrameIndex(unsigned int value)    { m_FrameIndex    = value   ; }
    inline void setPathIndex(unsigned int value)    { m_PathIndex    = value   ; }
    inline void setGroupIndex(DataType object, unsigned int value)    { m_GroupIndex[object]    = value   ; }
    inline void setFirstByte(DataType object, long value)    { m_FirstByte[object]    = value   ; }
    inline void setLastByte(DataType object, long value)     { m_LastByte[object]     = value   ; }
    inline void setCurrentByte(DataType object, long value)  { m_CurrentByte[object]  = value   ; }
    inline void setBytePosition(DataType object, long value) { m_BytePosition[object] = value   ; }

    void computeSinglePathBytePosition(unsigned int pathindex, long buffersize);
    void computeSinglePathIndexBytePosition(unsigned int pathindex, long buffersize);
    void computeSphereBytePosition(unsigned int frameindex, long buffersize);
    void computeMultiPathBytePosition(unsigned int pathgroupindex, long basedbuffer, long buffersize);
    void computeMultiIndicesBytePosition(unsigned int pathgroupindex, long basedbuffer, long buffersize);


};

#endif // BOOSTHANDLER_H
