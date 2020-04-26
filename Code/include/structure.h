#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QVector3D>

/**

  */
typedef struct STRUCT_SystemInformation
{
    unsigned int m_AtomsNumber;
    unsigned int m_FramesNumber;
    QVector3D m_Dimentions;

    inline unsigned int getAtomsNumber() { return m_AtomsNumber; }
    inline unsigned int getFramesNumber() { return m_FramesNumber; }
    inline QVector3D getDimentions() { return m_Dimentions; }
    inline void setAtomsNumber(unsigned int atomsnumber) {  m_AtomsNumber = atomsnumber; }
    inline void setFramesNumber(unsigned int framesnumber) { m_FramesNumber = framesnumber; }
    inline void setDimentions(QVector3D dimentions) { m_Dimentions = dimentions; }
} SystemInformationRecord;
const size_t SYSTEM_INFORMATION_RECORD_SIZE = sizeof( STRUCT_SystemInformation );

typedef struct STRUCT_SystemStructure
{
    unsigned int m_AtomIndex;
    unsigned short m_MoleculeType;
    unsigned short m_MoleculeIndex;
    unsigned short m_MoleculeResidueIndex;

    STRUCT_SystemStructure lookup(unsigned int index)
    {
        return *(this + index);
    }

    STRUCT_SystemStructure *lookupRef(unsigned int index)
    {
        return this + index;
    }

    inline unsigned int getAtomIndex() { return m_AtomIndex; }
    inline unsigned short getMoleculeType() { return m_MoleculeType; }
    inline unsigned short getMoleculeIndex() { return m_MoleculeIndex; }
    inline unsigned short getMoleculeResidueIndex() { return m_MoleculeResidueIndex; }
    inline void setAtomIndex(unsigned int index) { m_AtomIndex = index; }
    inline void setMoleculeType( unsigned short type) {  m_MoleculeType = type; }
    inline void setMoleculeIndex(unsigned short index) { m_MoleculeIndex = index; }
    inline void setMoleculeResidueIndex( unsigned short index) { m_MoleculeResidueIndex = index; }
} SystemStructureRecord;
const size_t SYSTEM_STRUCTURE_RECORD_SIZE = sizeof( STRUCT_SystemStructure );


typedef struct STRUCT_COMStructure
{
    unsigned int m_COMGroupIndex;
    unsigned short m_MoleculeType;
    unsigned int m_FirstAtomIndex;
    unsigned int m_COMGroupAtomsNumber;
    QVector3D m_FTRPosition;
    QVector3D m_NBLPosition;

    STRUCT_COMStructure lookup(unsigned int index)
    {
        return *(this + index);
    }

    STRUCT_COMStructure *lookupRef(unsigned int index)
    {
        return this + index;
    }

    inline unsigned int getCOMGroupIndex() { return m_COMGroupIndex; }
    inline unsigned short getMoleculeType() { return m_MoleculeType; }
    inline unsigned int getFirstAtomIndex() { return m_FirstAtomIndex; }
    inline unsigned int getCOMGroupAtomsNumber() { return m_COMGroupAtomsNumber; }
    inline QVector3D getFTRPosition() { return m_FTRPosition; }
    inline QVector3D getNBLPosition() { return m_NBLPosition;}

    inline void setCOMGroupIndex(unsigned int index) { m_COMGroupIndex = index; }
    inline void setMoleculeType( unsigned short type) {  m_MoleculeType = type; }
    inline void setFirstAtomIndex(unsigned int index) { m_FirstAtomIndex = index; }
    inline void setCOMGroupAtomsNumber( unsigned int number) { m_COMGroupAtomsNumber = number; }
    inline void setFTRPosition(QVector3D position) { m_FTRPosition = position; }
    inline void setNBLPosition(QVector3D position) { m_NBLPosition = position; }

} COMStructureRecord;
const size_t COM_STRUCTURE_RECORD_SIZE = sizeof( STRUCT_COMStructure );

class QVector4D;
typedef struct STRUCT_GPUProteinSpace
{
    unsigned short ProteinID     ;    //2
    float ProteinCOM[3] ;    //12
    float ZAxis[2]      ;   //Fra  => Near
    float Radius        ;    //4
    float avgProteinCOM[3];
    float avgZAxis[2];
    float avgRadius;
} GPUProteinSpace;          //18->32
const size_t GPU_PROTEIN_SPACE_SIZE = sizeof( GPUProteinSpace );

typedef struct STRUCT_GPUProteinParticle
{
    short ProteinID         ;   //2
    unsigned int ParticleID ;   //4
    float Position[3]       ;   //12
} GPUProteinParticle;
const size_t GPU_PROTEIN_PARTICLE_SIZE = sizeof( GPUProteinParticle );

typedef struct STRUCT_GPULipidSpace
{
    short LipidID        ;    //2
    float LipidCOM[3]  ;    //12
    float Radius          ;    //4
} GPULipidSpace;                              //18->32
const size_t GPU_LIPID_SPACE_SIZE = sizeof( GPULipidSpace );

typedef struct STRUCT_GPULipidParticle
{
    short LipidID         ;   //2
    unsigned int ParticleID ;   //4
    float Position[3]       ;   //12
} GPULipidParticle;
const size_t GPU_LIPID_PARTICLE_SIZE = sizeof( GPULipidParticle );


typedef struct STRUCT_GPUProteinSpaceAverage
{
    short ProteinID     ;    //2
    float ProteinCOM[3] ;    //12
    float ProteinFirstPosition[3] ;    //12
    float ProteinAveragePosition[3] ;    //12
    float ProteinEndPosition[3] ;    //12
    float ZAxis[2]      ;               //8
    float Radius        ;    //4
    float AverageRadius        ;    //4
} GPUProteinSpaceAverage;
const size_t GPU_PROTEIN_SPACE_AVERAGE_SIZE = sizeof( GPUProteinSpaceAverage );

typedef struct STRUCT_VetexColor
{
    float R;
    float G;
    float B;
    float A;
} VertexColor;
const size_t VERTEX_COLOR_SIZE = sizeof( VertexColor );
#endif // STRUCTURE_H
