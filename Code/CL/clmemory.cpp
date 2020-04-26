#include "clmemory.h"

CLMemory::CLMemory(CLContext *clcontext) : m_CLContext( clcontext )
{

}

CLMemory::~CLMemory()
{
    this->freeResources();
}

bool CLMemory::Create(size_t buffersize, bool usesharedcontext)
{
    bool result;
    if( !usesharedcontext )
    {
        result = this->createMemoryFromCLContext( buffersize );
    }
    else
    {
        result = this->createMemoryFromSharedContext( buffersize );
    }

    return result;
}

bool CLMemory::CreateShared(GLuint glbufferid)
{
    cl_context sharedContext;
    cl_mem sharedMemoryObject;

    if(this->getSharedMemoryObject() == NULL)
    {

        sharedContext = this->getSharedContext();

        sharedMemoryObject = clCreateFromGLBuffer(sharedContext, CL_MEM_READ_WRITE, glbufferid, NULL);

        if( sharedMemoryObject == NULL )
        {
            QVector<QString> errorMessages;
            QString className;
            className = typeid(CLMemory).name();
            errorMessages.append( className );
            errorMessages.append( "Field to create Shared Memory Object!" );
            Debug( errorMessages );
            m_SharedMemoryObject = NULL;
            return false;
        }

        this->setSharedMemoryObject( sharedMemoryObject );

        return true;
    }

}

bool CLMemory::createMemoryFromCLContext(size_t buffersize)
{
    cl_context context;
    cl_mem memoryObject;
    bool sharingState;

    sharingState = this->getSharingState();

    this->setBufferSize( buffersize );

    size_t currentBufferSize;

    if(this->getMemoryObject() != NULL)
    {
        currentBufferSize = this->getBufferSize();
        if( currentBufferSize >= buffersize )
        {
            return true;    //No need to create a buffer
        }
        else
        {
            //release the memory to create a new buffer!
            if( this->getMemoryObject() != NULL )
            {
                clReleaseMemObject( m_MemoryObject );
                m_MemoryObject = NULL;
                Debug(" New Mem object is going to be generated!");
            }
        }
    }

    this->setSharingState( false );
    context = this->getContext();


    memoryObject = clCreateBuffer( context, CL_MEM_READ_WRITE, buffersize, NULL, NULL);
    if( memoryObject == NULL )
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLMemory).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Memory Object!");
        Debug( errorMessages );
        m_MemoryObject = NULL;
        return false;
    }

    this->setMemoryObject( memoryObject );

    return true;
}

bool CLMemory::createMemoryFromSharedContext(size_t buffersize)
{
    cl_context context;
    cl_mem sharedMemoryObject;
    bool sharingState;

    sharingState = this->getSharingState();

    this->setBufferSize( buffersize );

    size_t currentBufferSize;

    if(this->getSharedMemoryObject() != NULL)
    {
        currentBufferSize = this->getBufferSize();
        if( currentBufferSize >= buffersize && sharingState )
        {
            return true;    //No need to create a buffer
        }
        else
        {
            //release the memory to create a new buffer!
            if( this->getSharedMemoryObject() != NULL )
            {
                clReleaseMemObject( m_SharedMemoryObject );
                m_SharedMemoryObject = NULL;
                Debug(" New Shared Mem object is going to be generated!");
            }
        }
    }

    this->setSharingState( true );

    context = this->getSharedContext();


    sharedMemoryObject = clCreateBuffer( context, CL_MEM_READ_WRITE, buffersize, NULL, NULL);
    if( sharedMemoryObject == NULL )
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLMemory).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create shared Memory Object!");
        Debug( errorMessages );
        m_SharedMemoryObject = NULL;
        return false;
    }

    this->setSharedMemoryObject( sharedMemoryObject );

    return true;
}

void CLMemory::freeResources()
{
    if( this->getMemoryObject() != NULL )
    {
        clReleaseMemObject( m_MemoryObject );
        m_MemoryObject = NULL;
    }

    if( this->getSharedMemoryObject() != NULL )
    {
        clReleaseMemObject( m_SharedMemoryObject );
        m_SharedMemoryObject = NULL;
    }
}
