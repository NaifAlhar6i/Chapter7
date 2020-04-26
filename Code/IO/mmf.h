#ifndef MMF_H
#define MMF_H

#include <boost/iostreams/device/mapped_file.hpp>
#include<boost/iostreams/stream.hpp>

#include "Memory/memorymanager.h"
namespace bio = boost::iostreams;

/**
 * @brief The MMF class interfaces the boost MMF functions
 */
class MMF : public virtual MemoryManager
{
public:
    /**
     * @brief MMF class constructure
     */
    MMF();

    /**
     * @brief GetVertexData gets the vertex data
     * @return a reference to mapped_file_source object
     */
    inline bio::mapped_file_source &GetVertexData() { return m_VertexData;}

    /**
     * @brief CopyData
     * @param frameindex
     */
    void CopyData(unsigned int frameindex);

    /**
     * @brief FetchProteinParticles fetches protein particles
     * @param frameindex specifies the frame index (time step)
     */
    void FetchProteinParticles( unsigned int frameindex );

    /**
     * @brief FetchLipidParticles fetches partices number
     * @param frameindex specifies the frame index (time step)
     */
    void FetchLipidParticles( unsigned int frameindex);

    /**
     * @brief FetchFrame fecthes frame data
     * @param frameindex  specifies the frame index to be fetched
     * @param mapframe (we don't use this for now)
     * @return the time elapced for reading the frame data
     */
    int FetchFrame(unsigned int frameindex, void *&mapframe);

    /**
     * @brief ReadFile
     */
    void ReadFile();

    /**
     * @brief ReadFile
     * @param out
     * @param name
     * @param frameindex
     * @param typesize
     * @param atomsnumber
     * @param framesnumber
     */
    void ReadFile(bio::mapped_file_source &out, QString name, unsigned int frameindex, long typesize, long atomsnumber, long framesnumber = 1);

private:

    /**
     * @brief m_VertexData
     */
    static bio::mapped_file_source m_VertexData;

    /**
     * @brief m_PathData
     */
    static bio::mapped_file_source m_PathData;

    /**
     * @brief m_VertexDataOffset
     */
    static long m_VertexDataOffset;

    /**
     * @brief m_PathDataOffset
     */
    static long m_PathDataOffset;

    /**
     * @brief m_VertexDataTenthIndex
     */
    static long m_VertexDataTenthIndex;

    /**
     * @brief m_PathDataTenthIndex
     */
    static long m_PathDataTenthIndex;

    /**
     * @brief getVertexData gets a refernce to the vertex data object
     * @return a pointer to the vertex data object
     */
    inline bio::mapped_file_source &getVertexData() { return m_VertexData;}

    /**
     * @brief getPathData gets a reference to the path data object
     * @return a pointer to the path data object
     */
    inline bio::mapped_file_source &getPathData() { return m_PathData;}

    /**
     * @brief getVertexDataOffset gets the offset of the vertex data object
     * @return the offcet of the vertex data
     */
    inline long getVertexDataOffset() { return m_VertexDataOffset;}

    /**
     * @brief getPathDataOffset gets the offcet of teh path data
     * @return the offcet of the path data
     */
    inline long getPathDataOffset() { return m_PathDataOffset;}

    /**
     * @brief getVertexDataTenthIndex gets the tenth index of the vertex data
     * @return the tenth index o fthe vertex data
     */
    inline long getVertexDataTenthIndex() { return m_VertexDataTenthIndex; }

    /**
     * @brief getPathDataTenthIndex gets the tenth index of the path data
     * @return the tenth index of the path data
     */
    inline long getPathDataTenthIndex() { return m_PathDataTenthIndex; }

    /**
     * @brief setVertexDataOffset sets the offcet of the  ertex data
     * @param offset specifies the offcet value
     */
    inline void setVertexDataOffset( long offset) { m_VertexDataOffset = offset;}

    /**
     * @brief setPathDataOffset sets the offcet of the path data
     * @param offset specifies the offcet vale
     */
    inline void setPathDataOffset( long offset) { m_PathDataOffset = offset;}

    /**
     * @brief setVertexDataTenthIndex sets the tenth index of the vertex data
     * @param index specifies the index value
     */
    inline void setVertexDataTenthIndex( long index ) { m_VertexDataTenthIndex = index; }

    /**
     * @brief setPathDataTenthIndex sets the tenth index of the path data
     * @param index specifies th eindex value
     */
    inline void setPathDataTenthIndex( long index ) { m_PathDataTenthIndex = index; }

    /**
     * @brief readPathVerticesFile reads the vertices path file
     * @param name specifies the file name
     * @param atomindex specifies the index
     * @return a const char pointer to the opened file
     */
    const char *readPathVerticesFile(QString name, unsigned int atomindex);

    /**
     * @brief readAtomVerticesFile reads the vertex atom file
     * @param name specifies the file name
     * @param frameindex specifies the frame index
     * @return a const char pointer to the opend file
     */
    const char *readAtomVerticesFile(QString name, unsigned int frameindex);

    /**
     * @brief readAtomVerticesFile2 reads the vertex atom file
     * @param name specifies the file name
     * @param frameindex specifies the frame index
     * @return a const char pointer to the opend file
     */
    const char *readAtomVerticesFile2(QString name, unsigned int frameindex);

    /**
     * @brief readAtomIndicesFile reads the index  file
     * @param name specifies the file name
     * @param frameindex specifies the frame index
     * @return a const char pointer to the opend file
     */
    const char *readAtomIndicesFile(QString name, unsigned int atomindex);

    /**
     * @brief readAtomAttributesFile reads the attribute  file
     * @param name specifies the file name
     * @param frameindex specifies the frame index
     * @return a const char pointer to the opend file
     */
    const char *readAtomAttributesFile(QString name, unsigned int atomindex);
};

#endif // MMF_H
