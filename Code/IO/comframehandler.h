#ifndef COMFRAMEHANDLER_H
#define COMFRAMEHANDLER_H

#include "structure/structure.h"
#include <boost/iostreams/device/mapped_file.hpp>
#include<boost/iostreams/stream.hpp>

class COMFrameHandler
{
public:
    COMFrameHandler();
protected:
    const char *mapFrame(unsigned int frameindex , unsigned int buffersize);
    inline boost::iostreams::mapped_file_source &getFrameStream() { return m_FrameStream; }

private:
    boost::iostreams::mapped_file_source m_FrameStream;
    unsigned int m_FrameIndex;
    long m_FirstByte;
    long m_LastByte;
    long m_CurrentByte;
    long m_BytePosition;

    inline unsigned int getFrameIndex()  { return m_FrameIndex; }
    inline long getFirstByte()  { return m_FirstByte;  }
    inline long getLastByte()       { return m_LastByte;    }
    inline long getCurrentByte()    { return   m_CurrentByte; }
    inline long getBytePosition()   { return   m_BytePosition; }

    inline void setFrameIndex(unsigned int value)    { m_FrameIndex    = value   ; }
    inline void setFirstByte(long value)    { m_FirstByte = value   ; }
    inline void setLastByte(long value)     { m_LastByte = value   ; }
    inline void setCurrentByte( long value)  { m_CurrentByte = value   ; }
    inline void setBytePosition(long value) { m_BytePosition = value   ; }

    void computeFrameBytePosition(unsigned int frameindex, unsigned int buffersize);


};

#endif // COMFRAMEHANDLER_H
