#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "gromanager.h"
#include "xtcmanager.h"
#include "stl.h"
#include "mmf.h"
#include "CL/clmanager.h"

/**
 * @brief The DataManager class manages the data
 */
class DataManager : public QObject, public virtual STL, public virtual MMF
{
    Q_OBJECT
public:
    /**
     * @brief DataManager class constructore
     * @param clmanager specifies the Open cl manager CLManager
     */
    DataManager(CLManager *clmanager);

    /**
     * @brief SetProcessingState sets the processing state
     * @param state specifies the processing state
     * if true the processing will take place otherwise no processing will performed on the data
     */
    inline void SetProcessingState(bool state) { m_ProcessingState = state; }

    // GRO and XTC file (used once!)
    /**
     * @brief FetchGROData fetches the system info from the GRO file
     */
    void FetchGROData();

    /**
     * @brief FetchXTCFrames fetches frames from the XTC file
     * @param start specifies the first frame to be fetched
     * @param end specifies the last frame to be fetched
     * @param stride specified the number of time tepes to be skiped
     */
    void FetchXTCFrames(unsigned int start, unsigned int end, short stride = 0);

    /**
     * @brief ComputeProteinCOM computes the center of mass of protein
     * @param frameindex specifies the frame index or the time step number to be computed
     */
    void ComputeProteinCOM(unsigned int frameindex);

    /**
     * @brief ComputeLipidCOM computes the center of mass of lipid
     * @param frameindex specifies the frame index or the time step number to be computed
     */
    void ComputeLipidCOM(unsigned int frameindex);

    /**
     * @brief ComputeProteinLipidInteraction computes the protein lipid interaction
     * @param frameindex specifies the frame index or the time step number to be computed
     * @param mmf specifies the method to be used to read data from the disk
     * if true then the MMF method will be used otherwise the STL method will be used
     */
    void ComputeProteinLipidInteraction(unsigned int frameindex, bool mmf = false);

    /**
     * @brief ComputeProteinLipidInteractionOnTheFly computes the protein lipid interaction on the fly
     * @param frameindex specifies the frame index or the time step number to be computed
     * @param vertex specifies the
     * @param colorbufferid
     * @param mmf
     */
    void ComputeProteinLipidInteractionOnTheFly(unsigned int frameindex, QOpenGLBuffer *&vertex, GLuint colorbufferid, bool mmf = false);

    /**
     * @brief GenerateAtomsPathFile generates atom path file
     * @param typesize specifies the size of the data
     * @param atomsnumber specifies the number of atoms
     * @param framesnumber specifies the current time step number
     */
    void GenerateAtomsPathFile(long typesize, long atomsnumber, long framesnumber);

    /**
     * @brief GenerateCOMAtomsPathFile generates the center of mass of atoms path
     * @param typesize specifies the size of the data
     * @param atomsnumber specifies the number of atoms
     * @param framesnumber specifies the current time step number
     */
    void GenerateCOMAtomsPathFile(long typesize, long atomsnumber, long framesnumber);

signals:

    /**
     * @brief CentralizeFrameComputed signal to be invoked on the frame centrized is computed
     * @param frame a valid pointer to the computed frame
     */
    void CentralizeFrameComputed(void *frame );

    /**
     * @brief ProteinSpaceComputed signal to be invoked on the protein space computed
     * @param proteinspace a valid pointer to the computed protein space
     */
    void ProteinSpaceComputed(void *proteinspace );

    /**
     * @brief LipidSpaceComputed signal to be computed on the lipid space computed
     * @param lipidspace a valid poiner to the lipid space
     */
    void LipidSpaceComputed( void *lipidspace );

    /**
     * @brief ProteinLipidInteractionComputed signal to be computed  on the protein lipid interaction computed
     * @param frame a valid pointer to the frame data
     * @param color a valid poiter to the vertex color data
     * @param frameindex specifies the current frame index (time step
     */
    void ProteinLipidInteractionComputed( void *frame, void *color, int frameindex);

    /**
     * @brief ProteinLipidInteractionComputed signal to be invoked on the protein lipid interaction computed
     * @param frame a valid pointer to the frame (time step) data
     * @param frameindex specifies the current frame (time step)
     */
    void ProteinLipidInteractionComputed( void *frame, int frameindex);

    /**
     * @brief FrameFixed signal to be involked on time step (frame) PBC fixed
     * @param frame a valid pointer to the current frame data (time step)
     */
    void FrameFixed(void *frame);

    /**
     * @brief FileDataRead signal to be involke on the file data read
     */
    void FileDataRead(int);
public slots:

    /**
     * @brief CentralizeFrame centrizes the frame data
     * @param index specifies the current time step nimber
     * @param frame a pointer to the current frame data (time step)
     * @param dimentions specifies the simulation box dimentions
     * @param mindimentions specifies the minimum x, y, and z value of the dimention of the simulation box
     * @param maxdimentions specifies the maximum x, y, and z value of the dimentions of the simulation box
     */
    void CentralizeFrame(unsigned int index, void *frame, QVector3D dimentions, QVector3D mindimentions, QVector3D maxdimentions);

    /**
     * @brief SaveCentralizeFrameToFile saves the centrized frame to a file
     * @param frame a valid pointer to the centrized frame data
     */
    void SaveCentralizeFrameToFile(void *frame);

    /**
     * @brief SaveProteinParticlesCOMToFile saves the center of the mass of the protein data
     * @param proteinspace a pointer to the protein space
     */
    void SaveProteinParticlesCOMToFile( void *proteinspace);

    /**
     * @brief SaveLipidParticlesCOMToFile saves the center of mass of lipid particles
     * @param lipidspace a valid pointer to the lipid space
     */
    void SaveLipidParticlesCOMToFile( void *lipidspace);

    /**
     * @brief SaveProteinSpace saves protein space
     * @param proteinspace a valid pointer to the protein space
     */
    void SaveProteinSpace( void *proteinspace);

private:
    /**
     * @brief m_ProcessingState the processing state
     * if true this class wil perform the processing otherwise no processing will be performed
     */
    bool m_ProcessingState;

    /**
     * @brief m_GROManager the gro file manager GROManager
     */
    GROManager *m_GROManager = NULL;

    /**
     * @brief m_XTCManager the xtc file manager XTCManager
     */
    XTCManager *m_XTCManager = NULL;

    /**
     * @brief m_CLManager the cl manager CLManager
     */
    CLManager *m_CLManager = NULL;

    /**
     * @brief m_MinDimentions the minimum valus of the simulation box dimentions
     */
    QVector3D m_MinDimentions = QVector3D(0,0,0);

    /**
     * @brief m_MaxDimentions the maximum values of the simulation box dimentions
     */
    QVector3D m_MaxDimentions = QVector3D(0,0,0);

    /**
     * @brief getProcessingState gets a pointer to the processing state
     * @return the processing state
     */
    inline bool getProcessingState() { return m_ProcessingState ; }

    /**
     * @brief getGROManager gets a pointer to the GROManager file object
     * @return  the gro file object
     */
    GROManager *getGROManager() { return m_GROManager;}

    /**
     * @brief getXTCManager gets a pointer to the XTCManager object
     * @return  the xtc object
     */
    XTCManager *getXTCManager() { return m_XTCManager;}

    /**
     * @brief getCLManager gets the cl manager
     * @return a pointer to the CLManager object
     */
    CLManager *getCLManager() { return m_CLManager;}

    /**
     * @brief getMinDimentions gets the minimum values of the simulation box dimentions
     * @return the minimum values of the simulation box dimention
     */
    QVector3D getMinDimentions() { return m_MinDimentions; }

    /**
     * @brief getMaxDimentions gets the maximum values of the simulation box
     * @return the maximum values of the simulation box
     */
    QVector3D getMaxDimentions() { return m_MaxDimentions; }

    /**
     * @brief setMinDimentions sets the minimum values of the simulation box
     * @param min specifies the minmum values to be set
     */
    void setMinDimentions(QVector3D min ) {  m_MinDimentions = min; }

    /**
     * @brief setMaxDimentions sets the maximum values of the simulation box
     * @param max specifies the maximum values of the simulation box
     */
    void setMaxDimentions(QVector3D max ) {  m_MaxDimentions = max; }

    /**
     * @brief initializeSignalsAndSlots initilizes the signals and slots
     */
    void initializeSignalsAndSlots();

    /**
     * @brief initializeMinMaxDimention initlizes the minimum and maximum dimention
     */
    void initializeMinMaxDimention();

    /**
     * @brief fetchProteinParticlesSTL fetches protein particles using the STL method
     * @param frameindex specifies the frame index (time step) to be fetched
     */
    void fetchProteinParticlesSTL( unsigned int frameindex);

    /**
     * @brief fetchLipidParticlesSTL fetches lipid particles using the STL method
     * @param frameindex specifies the frame index (time step) to be fetched
     */
    void fetchLipidParticlesSTL( unsigned int frameindex );

    /**
     * @brief fetchProteinSpaceSTL fetches proteins spaces using the STL method
     * @param frameindex specifies the frame index (time step) to be fetched
     */
    void fetchProteinSpaceSTL(unsigned int frameindex);

    /**
     * @brief fetchProteinParticles fetches the protein particles using the MMF method
     * @param frameindex specifies the frame index (time step) to be fetched
     */
    void fetchProteinParticles(unsigned int frameindex);

    /**
     * @brief fetchLipidParticles fetches the lipid particles using thr MMf method
     * @param frameindex specifies the frame index (time step) to be fetched
     */
    void fetchLipidParticles( unsigned int frameindex );

    /**
     * @brief fetchProteinSpace fetches the protein spaces using the MMF method
     * @param frameindex specifies the frame index (time step) to be fetched
     */
    void fetchProteinSpace(unsigned int frameindex);


    /**
     * @brief testMinMaxDimentions tests the min and max x, y and z values of the simulation box
     * @param frameindex specifies the frame index (time step) to be fetched
     * @param frame a void pointer to the frame data
     */
    void testMinMaxDimentions(unsigned int frameindex, void *frame );

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

#endif // DATAMANAGER_H
