#ifndef COMPATHHANDLER_H
#define COMPATHHANDLER_H


#include "structure/structure.h"
#include <boost/iostreams/device/mapped_file.hpp>
#include<boost/iostreams/stream.hpp>

class COMPathHandler
{
public:
    COMPathHandler();
protected:
    const char *mapPath(unsigned int frameindex , unsigned int buffersize);
    inline boost::iostreams::mapped_file_source &getPathStream() { return m_PathStream; }
    const char *mapSinglePathData(unsigned int &pathindex , unsigned int framesnumber);
    const char *mapMultiPathData(unsigned int &pathgroupindex, unsigned int pathbasednumber, unsigned int pathsnumber, unsigned int framesnumber );

private:
    boost::iostreams::mapped_file_source m_PathStream;
    unsigned int m_PathIndex;
    long m_FirstByte;
    long m_LastByte;
    long m_CurrentByte;
    long m_BytePosition;

    inline unsigned int getPathIndex()  { return m_PathIndex; }
    inline long getFirstByte()  { return m_FirstByte;  }
    inline long getLastByte()       { return m_LastByte;    }
    inline long getCurrentByte()    { return   m_CurrentByte; }
    inline long getBytePosition()   { return   m_BytePosition; }

    inline void setPathIndex(unsigned int value)    { m_PathIndex    = value   ; }
    inline void setFirstByte(long value)    { m_FirstByte = value   ; }
    inline void setLastByte(long value)     { m_LastByte = value   ; }
    inline void setCurrentByte( long value)  { m_CurrentByte = value   ; }
    inline void setBytePosition(long value) { m_BytePosition = value   ; }

    void computePathBytePosition(unsigned int frameindex, unsigned int buffersize);


};

#endif // COMPATHHANDLER_H
