#ifndef STL_H
#define STL_H

#include "Memory/memorymanager.h"

/**
 * @brief The STL class interfaces the STL method
 */
class STL : public virtual MemoryManager
{
public:
    /**
     * @brief STL class constructure
     */
    STL();

    /**
     * @brief FetchProteinParticles fetches proteins particles
     * @param frameindex specifies the frame index to be fetched
     */
    void FetchProteinParticles( unsigned int frameindex );

    /**
     * @brief FetchLipidParticles fetches lipid particles
     * @param frameindex specifies the frame index to be fetched
     */
    void FetchLipidParticles( unsigned int frameindex);

    /**
     * @brief FetchFrame fetches frame
     * @param frameindex specifies the frame index to be fetched
     * @return time elapced for reading the data
     */
    int FetchFrame(unsigned int frameindex );

    /**
     * @brief ReadFile reads file
     */
    void ReadFile();

    /**
     * @brief PrintOutPath
     * @param filename
     * @param pathindex
     * @param atomsnumber
     */
    void PrintOutPath( QString filename, long pathindex, long atomsnumber);

    /**
     * @brief PrintOutFrame
     * @param filename
     * @param frameindex
     * @param atomsnumber
     */
    void PrintOutFrame( QString filename, long frameindex, long atomsnumber);

private:


    /**
     * @brief min finds the min value by comparing two inputs
     * @param value1 a reference to the first value. it will hold the min value
     * @param value2 specifies the second value to be compared with
     */
    void min(float &value1, float value2);

    /**
     * @brief max finds the max value by comparing two inputs
     * @param value1 a reference to the first value. it will hold the max value
     * @param value2 specifies the second value to be compared with
     */
    void max(float &value1, float value2);

};

#endif // STL_H
