#ifndef FILE_H
#define FILE_H

//#include <boost/iostreams/device/mapped_file.hpp>
//#include <boost/iostreams/stream.hpp>
#include <QDebug>
#include <QFile>
#include "boosthandler.h"


class File: public BoostHandler
{
public:
    File();
    void AppendProteinSpace(void *data);
    void AppendCOMFrame(GPUProteinSpace *proteinspace );
    void AppendCOMFrame(GPULipidSpace *proteinspace );

    void AppendProteinLipidInteraction( unsigned int frameindex, GPUParticleInteraction *particlesinteraction);
    void AppendReferenceProtein(void *data);
    void AppendCOMReferenceProtein(void *data);
    void AppendTotalInteractionPerFrame(void *data);
    void AppendCOMTotalInteractionPerFrame(void *data);
    void WriteMaxInteraction(void *data);
    void WriteCOMMaxInteraction(void *data);

    void AppendINDFrame(void *data);

    void ReadProteinsLipidsInteraction();
    void ReadCOMFrame(rvec *&frame, unsigned int frameindex, unsigned int framesize);

    const char *MapEntirePathsFile(unsigned int buffersize);
    const char *MapEntireIndicesFile(unsigned int buffersize);
    const char *MapEntireProteinReferenceFile(unsigned int buffersize, bool framebased = true);
    void UnmapEntireFile();

    void CreatTestFile(QString filename);
    void ReadTestFile();
    void PrintOutTypesInfo();
    void CreateFrame();
    void FrameToPath(QString framesfile, QString pathsfile, unsigned int typesize, unsigned int particlesnumber, unsigned int framesnumber);
    void GenerateIndices(QString interactionsfile, QString pathsfile, unsigned int particlesnumber, unsigned int framesnumber);

    void AppendAverageToProteinCOMFile();
    void ReadProteinSpaceAverage();
    void GetPaths(iostreams::mapped_file_source &out);
protected:
    bool isProteinSpaceExist(GPUProteinSpace *data);
private:
    boost::iostreams::mapped_file_source m_EntireFile;

    inline boost::iostreams::mapped_file_source getEntireFile() { return m_EntireFile; }

    void readFile(boost::iostreams::mapped_file_source &out, QString name, unsigned int typesize, unsigned int particlesnumber, unsigned int framesnumber);
    void createFrame();
    void frameToPath(QString framesfile, QString pathsfile, unsigned int typesize, unsigned int particlesnumber, unsigned int framesnumber);
    void generateIndices(QString interactionsfile, QString pathsfile, unsigned int particlesnumber, unsigned int framesnumber);

};

#endif // FILE_H
