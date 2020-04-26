#include "clgltask.h"

CLGLTask::CLGLTask()
{
}

CLGLTask::~CLGLTask()
{
    this->freeResources();
}


void CLGLTask::freeResources()
{

}

void CLGLTask::ComputeProteinLipidInteraction(GLuint vertexbufferid, GLuint colorbufferid, void *systemstructure, void *proteinspaces, void *proteinparticles,
                                unsigned int atomsnumber, float interactiondistance, unsigned int workitemssize, unsigned int localsize)
{
    cl_device_id device = NULL;
    cl_command_queue sharedCommand = NULL;
    cl_kernel sharedKernel = NULL;
    cl_mem positionMemoryObject = NULL;
    cl_mem sharedColorMemoryObject = NULL;
    cl_mem systemStructureMemoryObject = NULL;
    cl_mem proteinSpaceMemoryObject = NULL;
    cl_mem proteinParticleMemoryObject = NULL;
    size_t kernelGlobalSize;
    size_t kernelLocalSize;
    size_t workItemSize;
    long atomsNumber;
    long proteinsnumber;
    long proteinparticlesnumber;
    long rvecSize;
    long positionSize;
    long systemStructureSize;
    long proteinSpacesSize;
    long proteinParticlesSize;
    int err;
    QTime timer;
    bool timerState;

    timerState = this->getTimerState();

    if( timerState == true)
    {
        timer.start();
    }

    device = this->getCLDevice()->GetID();
    sharedCommand = this->getCLCommand()->GetSharedCommand();
    sharedKernel = this->getCLComputeInteractionKernel()->GetSharedKernel();

    atomsNumber = atomsnumber;
    proteinsnumber = PROTEINS_NUMBER;
    proteinparticlesnumber = PROTEIN_PARTICLES_NUMBER;
    rvecSize = RVEC_SIZE;
//    positionSize = atomsNumber * rvecSize;

    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLFrameIOBuffer()->CreateShared( vertexbufferid );

    positionMemoryObject = this->getCLFrameIOBuffer()->GetSharedMemoryObject();
//    err = clEnqueueWriteBuffer(sharedCommand ,positionMemoryObject, CL_TRUE, ZERO_OFFSET, positionSize, frame, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);
//    if(err != CL_SUCCESS)
//    {
//        qDebug() << "Error: write compute PL interaction Frame buffer" ;
//        return ;
//    }

    //Create a buffer if it hasn't created or if its size less than the required size.
//    colorSize = atomsNumber * VERTEX_COLOR_SIZE;
    this->getCLColorIOBuffer()->CreateShared( colorbufferid );

    sharedColorMemoryObject = this->getCLColorIOBuffer()->GetSharedMemoryObject();

    //Create a buffer if it hasn't created or if its size less than the required size.
    systemStructureSize = atomsNumber * SYSTEM_STRUCTURE_RECORD_SIZE;
    this->getCLSystemStructureBuffer()->Create( systemStructureSize, true );

    systemStructureMemoryObject = this->getCLSystemStructureBuffer()->GetSharedMemoryObject();
    err = clEnqueueWriteBuffer(sharedCommand ,systemStructureMemoryObject, CL_TRUE, ZERO_OFFSET, systemStructureSize, systemstructure, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction system structure buffer" ;
        return ;
    }

    proteinSpacesSize = proteinsnumber * GPU_PROTEIN_SPACE_SIZE;
    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLProteinSpaceIOBuffer()->Create( proteinSpacesSize, true );

    proteinSpaceMemoryObject = this->getCLProteinSpaceIOBuffer()->GetSharedMemoryObject();
    err = clEnqueueWriteBuffer(sharedCommand ,proteinSpaceMemoryObject, CL_TRUE, ZERO_OFFSET, proteinSpacesSize, proteinspaces, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction ProteinSpaceBuffer" ;
        return ;
    }

    proteinParticlesSize = proteinparticlesnumber * proteinsnumber * GPU_PROTEIN_PARTICLE_SIZE;
    this->getCLProteinAtomsBuffer()->Create( proteinParticlesSize, true );
    proteinParticleMemoryObject = this->getCLProteinAtomsBuffer()->GetSharedMemoryObject();

    err = clEnqueueWriteBuffer(sharedCommand ,proteinParticleMemoryObject, CL_TRUE, ZERO_OFFSET, proteinParticlesSize, proteinparticles,UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction ProteinParticlesBuffer" ;
        return ;
    }

     err  = clSetKernelArg( sharedKernel, 0, sizeof( cl_mem ), &positionMemoryObject);
     err  = clSetKernelArg( sharedKernel, 1, sizeof( cl_mem ), &sharedColorMemoryObject);
     err  = clSetKernelArg( sharedKernel, 2, sizeof( cl_mem ), &systemStructureMemoryObject);
     err  = clSetKernelArg( sharedKernel, 3, sizeof( cl_mem ), &proteinSpaceMemoryObject);
     err  = clSetKernelArg( sharedKernel, 4, sizeof( cl_mem ), &proteinParticleMemoryObject);
     err  = clSetKernelArg( sharedKernel, 5, sizeof( unsigned int ), &atomsnumber);
     err  = clSetKernelArg( sharedKernel, 6, sizeof( float ), &interactiondistance);


     if (err != CL_SUCCESS)
     {
         qDebug() << "Error: Failed to set kernel arguments! " ;
         return ;
     }


     if( localsize == UINT_ZERO )
     {
         err = clGetKernelWorkGroupInfo( sharedKernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof( size_t ), &kernelLocalSize, NULL);
         if (err != CL_SUCCESS) {
             qDebug() << "Error: Failed to retrieve compute Lip COM kernel work group info! " ;
             return ;
         }
     }
     else
     {
         kernelLocalSize = localsize;
     }

     workItemSize = 256;
     if( workitemssize != 0)
         workItemSize = workitemssize;

     kernelGlobalSize =  ( workItemSize / kernelLocalSize + UINT_ONE ) * kernelLocalSize;

     glFinish();
     clEnqueueAcquireGLObjects(sharedCommand, ONE_ENTRIE,  &sharedColorMemoryObject, UNSPECIFIED_EVENTS_LIST, NULL, NULL);

     err = clEnqueueNDRangeKernel(sharedCommand, sharedKernel, WORK1DIM, NULL, &kernelGlobalSize, &kernelLocalSize, UNSPECIFIED_EVENTS_LIST, NULL, NULL);
     if (err) {
         qDebug() << "Error: Failed to execute compute PL Interaction kernel on the fly!" ;
         return ;
     }


     clEnqueueReleaseGLObjects(sharedCommand, ONE_ENTRIE, &sharedColorMemoryObject, UNSPECIFIED_EVENTS_LIST, NULL, NULL);

     clFinish(sharedCommand);

}

/*
 *
void CLGLTask::computeInteractionCOM(float interactionspace, unsigned int lipidsnumber, unsigned int proteinsnumber, rvec *&frame, GPUProteinSpace *&proteinspaces, short *&referenceprotein, short *interactioncount, unsigned int workitemssize, unsigned int localsize)
{
    unsigned int proteinSpacesSize;
    unsigned int bufferSize;
    unsigned int referenceProteinSize;
    unsigned int interactionCountSize;
    unsigned int lpParticlesNumber;

    int err ;

    lpParticlesNumber =  lipidsnumber + proteinsnumber;
    bufferSize = lpParticlesNumber * RVEC_SIZE;
    proteinSpacesSize = proteinsnumber * GPU_PROTEIN_SPACE_SIZE;

    referenceProteinSize =  lpParticlesNumber * SHORT_SIZE;
    interactionCountSize =  lpParticlesNumber * SHORT_SIZE;

    err = clEnqueueWriteBuffer( m_Commands ,m_COMFrameInOutBuffer, CL_TRUE, 0, bufferSize, (void *)frame, 0 ,NULL, NULL);

    if(err != CL_SUCCESS)
    {
           std::cerr << "Error: write centralize COMFrameInOutBuffer" << std::endl;
           return ;
    }


    err = clEnqueueWriteBuffer(m_Commands ,m_ProteinSpaceInOutBuffer, CL_TRUE, 0, proteinSpacesSize,(void*)proteinspaces,0,NULL,NULL);

    if(err != CL_SUCCESS)
    {
           std::cerr << "Protein In -> OpenCL Errror!!" << std::endl;
           return ;
    }

    err  = clSetKernelArg(m_InteractionCOMKernel, 0, sizeof( cl_mem ), &m_COMFrameInOutBuffer);
    err  = clSetKernelArg(m_InteractionCOMKernel, 1, sizeof( cl_mem ), &m_ProteinSpaceInOutBuffer);
    err  = clSetKernelArg(m_InteractionCOMKernel, 2, sizeof( cl_mem ), &m_COMReferenceProteinInOutBuffer);
    err  = clSetKernelArg(m_InteractionCOMKernel, 3, sizeof( cl_mem ), &m_COMInteractionCountInOutBuffer);

    err |= clSetKernelArg(m_InteractionCOMKernel, 4, sizeof(unsigned int), &lpParticlesNumber);
    err |= clSetKernelArg(m_InteractionCOMKernel, 5, sizeof(float), &interactionspace);

    if (err != CL_SUCCESS)
    {
        std::cerr << "Error: Failed to set kernel arguments! " << err << std::endl;
        return ;
    }


    if( localsize == UINT_ZERO )
    {
        err = clGetKernelWorkGroupInfo(m_InteractionCOMKernel, m_Device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof( KernelLocalSize ), &KernelLocalSize, NULL);
        if (err != CL_SUCCESS) {
            std::cerr << "Error: Failed to retrieve kernel work group info! " << err << std::endl;
            return ;
        }
    }
    else
    {
        KernelLocalSize = localsize;
    }

    if( workitemssize != 0)
        m_WorkItemSize = workitemssize;

    KernelGlobalSize =  ( m_WorkItemSize / KernelLocalSize + Y ) * KernelLocalSize;


    err = clEnqueueNDRangeKernel(m_Commands, m_InteractionCOMKernel, WORK1DIM, NULL, &KernelGlobalSize, &KernelLocalSize, 0, NULL, NULL);
    if (err) {
        std::cerr << "Error: Failed to execute kernel!" << std::endl;
        return ;
    }


    clEnqueueReadBuffer(m_Commands, m_COMReferenceProteinInOutBuffer, CL_TRUE, 0, referenceProteinSize, referenceprotein, 0, NULL, NULL);
    clEnqueueReadBuffer(m_Commands, m_COMInteractionCountInOutBuffer, CL_TRUE, 0, interactionCountSize, interactioncount, 0, NULL, NULL);

    clFlush(m_Commands);
    clFinish(m_Commands);

}

void CLGLTask::computeInteractionCOMOnTheFly(float interactionspace, unsigned int lipidsnumber, unsigned int proteinsnumber, GPUProteinSpace *&proteinspaces, short *&referenceprotein, short *interactioncount, unsigned int workitemssize, unsigned int localsize)
{
    unsigned int proteinSpacesSize;
    unsigned int referenceProteinSize;
    unsigned int interactionCountSize;
    unsigned int lpParticlesNumber;
    int err ;

    proteinSpacesSize = proteinsnumber * GPU_PROTEIN_SPACE_SIZE;
    lpParticlesNumber = lipidsnumber + proteinsnumber;

    referenceProteinSize =  lpParticlesNumber * SHORT_SIZE;
    interactionCountSize =  lpParticlesNumber * SHORT_SIZE;

    err = clEnqueueWriteBuffer(m_SharedCommands ,m_SharedProteinSpaceInOutBuffer, CL_TRUE, 0, proteinSpacesSize,(void*)proteinspaces,0,NULL,NULL);

    if(err != CL_SUCCESS)
    {
           std::cerr << "Protein In -> OpenCL Errror!!" << std::endl;
           return ;
    }

    err  = clSetKernelArg(m_SharedInteractionCOMKernel, 0, sizeof( cl_mem ), &m_SharedCOMFrameInOutBuffer);
    err  = clSetKernelArg(m_SharedInteractionCOMKernel, 1, sizeof( cl_mem ), &m_SharedCOMFrameColorInOutBuffer);
    err  = clSetKernelArg(m_SharedInteractionCOMKernel, 2, sizeof( cl_mem ), &m_SharedProteinSpaceInOutBuffer);
    err  = clSetKernelArg(m_SharedInteractionCOMKernel, 3, sizeof( cl_mem ), &m_SharedCOMReferenceProteinInOutBuffer);
    err  = clSetKernelArg(m_SharedInteractionCOMKernel, 4, sizeof( cl_mem ), &m_SharedCOMInteractionCountInOutBuffer);

    err |= clSetKernelArg(m_SharedInteractionCOMKernel, 5, sizeof(unsigned int), &lpParticlesNumber);
    err |= clSetKernelArg(m_SharedInteractionCOMKernel, 6, sizeof(float), &interactionspace);

    if (err != CL_SUCCESS)
    {
        std::cerr << "Error: Failed to set kernel arguments! " << err << std::endl;
        return ;
    }


    if( localsize == UINT_ZERO )
    {
        err = clGetKernelWorkGroupInfo(m_SharedInteractionCOMKernel, m_Device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof( KernelLocalSize ), &KernelLocalSize, NULL);
        if (err != CL_SUCCESS) {
            std::cerr << "Error: Failed to retrieve kernel work group info! " << err << std::endl;
            return ;
        }
    }
    else
    {
        KernelLocalSize = localsize;
    }

    if( workitemssize != 0)
        m_WorkItemSize = workitemssize;

    KernelGlobalSize =  ( m_WorkItemSize / KernelLocalSize + UINT_ONE ) * KernelLocalSize;


    err = clEnqueueNDRangeKernel(m_SharedCommands, m_SharedInteractionCOMKernel, WORK1DIM, NULL, &KernelGlobalSize, &KernelLocalSize, 0, NULL, NULL);
    if (err) {
        std::cerr << "Error: Failed to execute kernel!" << std::endl;
        return ;
    }

    clEnqueueAcquireGLObjects(m_SharedCommands, 1,  &m_SharedCOMFrameInOutBuffer, 0, 0, NULL);
    clEnqueueAcquireGLObjects(m_SharedCommands, 1,  &m_SharedCOMFrameColorInOutBuffer, 0, 0, NULL);

    clEnqueueReadBuffer(m_SharedCommands, m_SharedCOMReferenceProteinInOutBuffer, CL_TRUE, 0, referenceProteinSize, referenceprotein, 0, NULL, NULL);
    clEnqueueReadBuffer(m_SharedCommands, m_SharedCOMInteractionCountInOutBuffer, CL_TRUE, 0, interactionCountSize, interactioncount, 0, NULL, NULL);

    clFlush(m_SharedCommands);
    clFinish(m_SharedCommands);

    clEnqueueReleaseGLObjects(m_SharedCommands, 1,  &m_SharedCOMFrameInOutBuffer, 0, 0, NULL);
    clEnqueueReleaseGLObjects(m_SharedCommands, 1,  &m_SharedCOMFrameColorInOutBuffer, 0, 0, NULL);

}

*/
