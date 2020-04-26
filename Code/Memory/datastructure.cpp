#include "datastructure.h"

SystemInformationRecord *DataStructure::m_SystemInformation = NULL;
SystemStructureRecord *DataStructure::m_SystemStructure = NULL;
COMStructureRecord *DataStructure::m_COMStructure = NULL;
GPUProteinSpace *DataStructure::m_ProteinSpace = NULL;
GPUProteinParticle *DataStructure::m_ProteinParticles = NULL;
GPULipidSpace *DataStructure::m_LipidSpace = NULL;
GPULipidParticle *DataStructure::m_LipidParticles = NULL;
rvec *DataStructure::m_VertexPosition = NULL;
VertexColor *DataStructure::m_VertexColor = NULL;
rvec *DataStructure::m_FirstFrame = NULL;

QMap<unsigned short, QString> DataStructure::m_ProteinResidueIdentifierTable;
QMap<unsigned short, QString> DataStructure::m_LipidPOPEResidueIdentifierTable;
QMap<unsigned short, QString> DataStructure::m_LipidPOPGResidueIdentifierTable;

DataStructure::DataStructure()
{
    long proteinParticlesNumber;
    long lipidParticlesNumber;
    proteinParticlesNumber = PROTEINS_NUMBER * PROTEIN_PARTICLES_NUMBER;
    lipidParticlesNumber = LIPIDS_NUMBER * LIPID_PARTICLES_NUMBER;

    allocateProteinSpace( PROTEINS_NUMBER );
    allocateProteinParticles( proteinParticlesNumber );
    allocateLipidSpace( LIPIDS_NUMBER );
    allocateLipidParticles( lipidParticlesNumber );
    allocateVertexPosition( ATOMS_NUMBER );
    allocateVertexColor( ATOMS_NUMBER );
    allocateFirstFrame( ATOMS_NUMBER );
}

DataStructure::~DataStructure()
{
    this->freeResources();
}

bool DataStructure::allocateSystemInformationSpace()
{
    bool allocated;
    size_t size;
    size = SYSTEM_INFORMATION_RECORD_SIZE;
    if( getSystemInformation() == NULL )
    {
        m_SystemInformation = (SystemInformationRecord*)malloc( size );
        if( m_SystemInformation == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        SystemInformationRecord *newLocation = (SystemInformationRecord*)malloc( size );
        if( newLocation != NULL )
        {
            m_SystemInformation = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateSystemStructureSpace( long time)
{
    bool allocated;
    size_t size;

    size= SYSTEM_STRUCTURE_RECORD_SIZE * time;
    if( getSystemStructure() == NULL )
    {
        m_SystemStructure = (SystemStructureRecord*)malloc( size );
        if( m_SystemStructure == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        SystemStructureRecord *newLocation = (SystemStructureRecord*)malloc( size );
        if( newLocation != NULL )
        {
            m_SystemStructure = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateCOMStructureSpace( long time)
{
    bool allocated;
    size_t size;

    size= COM_STRUCTURE_RECORD_SIZE * time;
    if( getCOMStructure() == NULL )
    {
        m_COMStructure = (COMStructureRecord*)malloc( size );
        if( m_COMStructure == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        COMStructureRecord *newLocation = (COMStructureRecord*)malloc( size );
        if( newLocation != NULL )
        {
            m_COMStructure = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateProteinSpace( long time)
{
    bool allocated;
    size_t size;

    size= GPU_PROTEIN_SPACE_SIZE * time;
    if( getProteinSpace() == NULL )
    {
        m_ProteinSpace = (GPUProteinSpace*)malloc( size );
        if( m_ProteinSpace == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        GPUProteinSpace *newLocation = (GPUProteinSpace*)malloc( size );
        if( newLocation != NULL )
        {
            m_ProteinSpace = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    for(unsigned short proteinIndex = USHORT_ZERO; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
    {
        (m_ProteinSpace + proteinIndex )->ProteinID = proteinIndex;
    }
    return allocated;
}

bool DataStructure::allocateProteinParticles( long time)
{
    bool allocated;
    size_t size;

    size= GPU_PROTEIN_PARTICLE_SIZE * time;

    if( getProteinParticles() == NULL )
    {
        m_ProteinParticles = (GPUProteinParticle*)malloc( size );
        if( m_ProteinParticles == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        GPUProteinParticle *newLocation = (GPUProteinParticle*)malloc( size );
        if( newLocation != NULL )
        {
            m_ProteinParticles = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateLipidSpace(long time)
{
    bool allocated;
    size_t size;

    size= GPU_LIPID_SPACE_SIZE * time;
    if( getLipidSpace() == NULL )
    {
        m_LipidSpace = (GPULipidSpace*)malloc( size );
        if( m_LipidSpace == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        GPULipidSpace *newLocation = (GPULipidSpace*)malloc( size );
        if( newLocation != NULL )
        {
            m_LipidSpace = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateLipidParticles( long time)
{
    bool allocated;
    size_t size;

    size= GPU_LIPID_PARTICLE_SIZE * time;

    if( getLipidParticles() == NULL )
    {
        m_LipidParticles = (GPULipidParticle*)malloc( size );
        if( m_LipidParticles == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        GPULipidParticle *newLocation = (GPULipidParticle*)malloc( size );
        if( newLocation != NULL )
        {
            m_LipidParticles = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateVertexPosition(long time)
{
    bool allocated;
    size_t size;

    size= RVEC_SIZE * time;

    if( getVertexPosition() == NULL )
    {
        m_VertexPosition = (rvec*)malloc( size );
        if( m_VertexPosition == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        rvec *newLocation = (rvec*)malloc( size );
        if( newLocation != NULL )
        {
            m_VertexPosition = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateVertexColor(long time)
{
    bool allocated;
    size_t size;

    size= VERTEX_COLOR_SIZE * time;

    if( getVertexColor() == NULL )
    {
        m_VertexColor = (VertexColor*)malloc( size );
        if( m_VertexColor == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        VertexColor *newLocation = (VertexColor*)malloc( size );
        if( newLocation != NULL )
        {
            m_VertexColor = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

bool DataStructure::allocateFirstFrame(long time)
{
    bool allocated;
    size_t size;

    size= RVEC_SIZE * time;

    if( getFirstFrame() == NULL )
    {
        m_FirstFrame = (rvec*)malloc( size );
        if( m_FirstFrame == NULL )
        {
            allocated = false;
        }
        else
        {
            allocated = true;
        }
    }
    else
    {
        rvec *newLocation = (rvec*)malloc( size );
        if( newLocation != NULL )
        {
            m_FirstFrame = newLocation;
            allocated = true;
        }
        else
        {
            allocated = false;
        }
    }

    return allocated;
}

void DataStructure::freeResources()
{
    if(getSystemInformation() != NULL )
    {
        free(m_SystemInformation);
        m_SystemInformation =NULL;
    }

    if(getSystemStructure() != NULL )
    {
        free(m_SystemStructure);
        m_SystemStructure =NULL;
    }

    if(getCOMStructure() != NULL )
    {
        free(m_COMStructure);
        m_COMStructure =NULL;
    }

    if(getProteinSpace() != NULL )
    {
        free( m_ProteinSpace );
        m_ProteinSpace = NULL;
    }

    if(getProteinParticles() != NULL )
    {
        free( m_ProteinParticles );
        m_ProteinParticles = NULL;
    }

    if(getLipidSpace() != NULL )
    {
        free( m_LipidSpace );
        m_LipidSpace = NULL;
    }

    if(getLipidParticles() != NULL )
    {
        free( m_LipidParticles );
        m_LipidParticles = NULL;
    }

    if(getVertexPosition() != NULL )
    {
        free( m_VertexPosition );
        m_VertexPosition = NULL;
    }

    if(getVertexColor() != NULL )
    {
        free( m_VertexColor );
        m_VertexColor = NULL;
    }

    if(this->getFirstFrame() != NULL )
    {
        free( m_FirstFrame );
        m_FirstFrame = NULL;
    }

    getProteinResidueIdentifierTable().clear();
    getLipidPOPEResidueIdentifierTable().clear();
    getLipidPOPGResidueIdentifierTable().clear();

    qDebug()<<"Data structure Memorry Freed!";

}
