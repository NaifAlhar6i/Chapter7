#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QMap>
#include "include/constdata.h"

/**
 * @brief The DataStructure class manages data structure
 */
class DataStructure : public virtual Debugger
{
public:
    /**
     * @brief DataStructure class cunstructure
     */
    DataStructure();
    ~DataStructure();

    /**
     * @brief getVertexPosition gets vertex position
     * @return a pointer to the vertex position
     */
    inline static rvec *getVertexPosition() { return m_VertexPosition; }

    /**
     * @brief getVertexColor gets vertex color
     * @return
     */
    inline static VertexColor *getVertexColor() { return m_VertexColor; }

    /**
     * @brief getFirstFrame gets the first frame
     * @return a pointer to the first frame
     */
    inline static rvec *getFirstFrame() { return m_FirstFrame; }

protected:

    /**
     * @brief getSystemInformation gets the system information
     * @return a pointer to the system information data
     */
    inline static SystemInformationRecord *getSystemInformation() { return m_SystemInformation; }

    /**
     * @brief getSystemStructure gets the system structure
     * @return a pointer to the system structure
     */
    inline static SystemStructureRecord *getSystemStructure() { return m_SystemStructure; }

    /**
     * @brief getCOMStructure gets the center of mass structure
     * @return a pointer to the center of mass structure
     */
    inline static COMStructureRecord *getCOMStructure() { return m_COMStructure; }

    /**
     * @brief getProteinSpace gets the protein spapce
     * @return a pointer to the protein space
     */
    inline static GPUProteinSpace *getProteinSpace() { return m_ProteinSpace; }

    /**
     * @brief getLipidSpace gets the lipid space
     * @return a pointer to the lipid space
     */
    inline static GPULipidSpace *getLipidSpace() { return m_LipidSpace; }

    /**
     * @brief getProteinParticles gets protein particles
     * @return a pointer to the protein particles
     */
    inline static GPUProteinParticle *getProteinParticles() { return m_ProteinParticles; }

    /**
     * @brief getLipidParticles gets the lipid particle
     * @return a pointer to the lipid particles
     */
    inline static GPULipidParticle *getLipidParticles() { return m_LipidParticles; }

    /**
     * @brief getProteinResidueIdentifierTable gets the protein residue identifier table
     * @return a pointer to the protein residue identifier table
     */
    inline static QMap<unsigned short, QString> &getProteinResidueIdentifierTable() { return m_ProteinResidueIdentifierTable; }

    /**
     * @brief getLipidPOPEResidueIdentifierTable gets the POPE lipid type residue identifier table
     * @return a pointer to the lipid POPE type identifier table
     */
    inline static QMap<unsigned short, QString> &getLipidPOPEResidueIdentifierTable() { return m_LipidPOPEResidueIdentifierTable; }

    /**
     * @brief getLipidPOPGResidueIdentifierTable gets the POPG lipid type residue identifier table
     * @return a pointer to the lipid POPG type identifier table
     */
    inline static QMap<unsigned short, QString> &getLipidPOPGResidueIdentifierTable() { return m_LipidPOPGResidueIdentifierTable; }

    /**
     * @brief allocateSystemInformationSpace allocates the system information space in the heap
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateSystemInformationSpace();

    /**
     * @brief allocateSystemStructureSpace allocates the system structure space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateSystemStructureSpace(long time);

    /**
     * @brief allocateCOMStructureSpace allocates a space in the heap for the structure of the center of mass sysytem
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateCOMStructureSpace( long time);

    /**
     * @brief allocateProteinSpace allocates the protein space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateProteinSpace( long time);

    /**
     * @brief allocateProteinParticles allocates the protein particles space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateProteinParticles( long time);

    /**
     * @brief allocateLipidSpace allocates the lipid space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateLipidSpace( long time );

    /**
     * @brief allocateLipidParticles allocates the lipid particles space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateLipidParticles( long time);

    /**
     * @brief allocateVertexPosition allocates the vertices possition space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateVertexPosition( long time);

    /**
     * @brief allocateVertexColor allocates the vertices color space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateVertexColor( long time);

    /**
     * @brief allocateFirstFrame allocates the first frame space in the heap
     * @param time specifies the number of records (is used to determin the size of the memory needed)
     * @return true if the space is allocated otherwise return false
     */
    bool static allocateFirstFrame( long time);
private:

    /**
     * @brief m_SystemInformation system information object
     * this variable holds a pointer to the system information structure
     */
    static SystemInformationRecord *m_SystemInformation;

    /**
     * @brief m_SystemStructure system structure object
     * This variable holds a pointer to the system structure
     */
    static SystemStructureRecord *m_SystemStructure;

    /**
     * @brief m_COMStructure center of mass of the protein and the lipid
     * This variable holds a pointer to the center of  the mass of the protein and lipid
     */
    static COMStructureRecord *m_COMStructure;

    /**
     * @brief m_ProteinSpace the proteins space
     * This variable holds a pointer to the protein space
     * The protein space is updated for each time step
     */
    static GPUProteinSpace *m_ProteinSpace;

    /**
     * @brief m_ProteinParticles the proteins particles
     * This variable holds a pointer to the protein particle structure
     * The value is updated for each time step
     */
    static GPUProteinParticle *m_ProteinParticles;

    /**
     * @brief m_LipidSpace the lipids space
     * This variable holds a pointer to the lipids space structure
     * The value is updated for each time step
     */
    static GPULipidSpace *m_LipidSpace;

    /**
     * @brief m_LipidParticles the lipid particles
     * This variable holds a pointer to the lipid particles structure
     * The value is updated for each time step
     */
    static GPULipidParticle *m_LipidParticles;

    /**
     * @brief m_VertexPosition the vertices position
     * This variable holds a pointer to the current frame data (the position of the partiles in 3D)
     * The value is updated for each time step
     */
    static rvec *m_VertexPosition;

    /**
     * @brief m_VertexColor the vertices color
     * This variable holds a pointer to the vertices color
     * The value is updated
     * 1) each tome step. or
     * 2) once if we use the OpenCL-GL intero
     */
    static VertexColor *m_VertexColor;

    /**
     * @brief m_FirstFrame the first frame data
     * This variable holds a pointer to the first time step data
     * it will not be changed ever
     */
    static rvec *m_FirstFrame;

    /**
     * @brief m_ProteinResidueIdentifierTable protein residue identifier table
     * This table is used to make sure we have a unique protein residue names
     */
    static QMap<unsigned short, QString> m_ProteinResidueIdentifierTable;

    /**
     * @brief m_LipidPOPEResidueIdentifierTable lipid POPE type residue identifier table
     * This table is used to make sure we have a unique POPE residue names
     */
    static QMap<unsigned short, QString> m_LipidPOPEResidueIdentifierTable;

    /**
     * @brief m_LipidPOPGResidueIdentifierTable lipid POPG type residue identifier table
     * This table is used to make sure we have a unique POPG residue names
     */
    static QMap<unsigned short, QString> m_LipidPOPGResidueIdentifierTable;

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // DATASTRUCTURE_H
