#include "cltask.h"

CLDevice *CLTask::m_CLDevice = NULL;
CLPlatform *CLTask::m_CLPlatform = NULL;
CLContext *CLTask::m_CLContext = NULL;
CLCommand *CLTask::m_CLCommand = NULL;
CLProgram *CLTask::m_CLProgram = NULL;

CLKernel  *CLTask::m_CLCentralizeFrameKernel = NULL;
CLKernel  *CLTask::m_CLComputeProteinCOMKernel = NULL;
CLKernel  *CLTask::m_CLComputeLipidCOMKernel = NULL;
CLKernel  *CLTask::m_CLComputeInteractionKernel = NULL;
CLKernel  *CLTask::m_CLComputeInteractionCOMKernel = NULL;

CLMemory *CLTask::m_CLSystemStructureBuffer = NULL;

CLMemory *CLTask::m_CLFirstFrameIOBuffer = NULL;
CLMemory *CLTask::m_CLFrameIOBuffer = NULL;
CLMemory *CLTask::m_CLCOMFrameIOBuffer = NULL;
CLMemory *CLTask::m_CLColorIOBuffer = NULL;
CLMemory *CLTask::m_CLCOMColorIOBuffer = NULL;

CLMemory *CLTask::m_CLProteinSpaceIOBuffer = NULL;
CLMemory *CLTask::m_CLProteinAtomsBuffer = NULL;
CLMemory *CLTask::m_CLLipidSpaceInOutBuffer = NULL;
CLMemory *CLTask::m_CLLipidParticlesBuffer = NULL;

CLMemory *CLTask::m_CLParticlesIdentityBuffer =  NULL;
CLMemory *CLTask::m_CLParticlesInteractionInOutBuffer = NULL;
CLMemory *CLTask::m_CLReferenceProteinIBuffer = NULL;
CLMemory *CLTask::m_CLInteractionCountIOBuffer = NULL;

size_t CLTask::m_WorkItemSize = 0;
size_t CLTask::m_KernelGlobalSize = 0;
size_t CLTask::m_KernelLocalSize = 0;

bool CLTask::m_TimerState = false;


CLTask::CLTask()
{
    this->initialObjects();
}

CLTask::~CLTask()
{
    this->freeResources();
}

bool CLTask::InstallOpenCL()
{
    bool installed;

    installed = this->getCLDevice()->Setup();
    installed &= this->getCLPlatform()->Setup();
    installed &= this->getCLContext()->Setup();
    installed &= this->getCLCommand()->Setup();
    installed &= this->getCLProgram()->Create( KERNELS_FILE );
    installed &= this->GetCLCentralizeFrameKernel()->Create( CENTRALIZE_FRAME_KERNEL );
    installed &= this->GetCLComputeProteinCOMKernel()->Create( PROTEIN_COM_KERNEL );
    installed &= this->GetCLComputeLipidCOMKernel()->Create( LIPID_COM_KERNEL );
    installed &= this->GetCLComputeInteractionKernel()->Create( INTERACTION_KERNEL, INTERACTION_KERNEL );

    qDebug() << "CL installed" << installed;
    return installed;
}

void CLTask::initialObjects()
{
    m_CLDevice = new CLDevice;
    m_CLPlatform = new CLPlatform;
    m_CLContext = new CLContext( m_CLDevice, m_CLPlatform );
    m_CLCommand = new CLCommand( m_CLContext );
    m_CLProgram = new CLProgram( m_CLContext );

    m_CLCentralizeFrameKernel = new CLKernel( m_CLProgram );
    m_CLComputeProteinCOMKernel = new CLKernel( m_CLProgram );
    m_CLComputeLipidCOMKernel = new CLKernel( m_CLProgram );
    m_CLComputeInteractionKernel = new CLKernel( m_CLProgram );
    m_CLComputeInteractionCOMKernel = new CLKernel( m_CLProgram );

    m_CLSystemStructureBuffer = new CLMemory(m_CLContext );        //Task1 & 4

    m_CLFirstFrameIOBuffer = new CLMemory(m_CLContext );        //Task1 & 4
    m_CLFrameIOBuffer = new CLMemory(m_CLContext );        //Task1 & 4
    m_CLCOMFrameIOBuffer = new CLMemory(m_CLContext );        //Task1 & 4
    m_CLColorIOBuffer = new CLMemory(m_CLContext );        //Task1 & 4
    m_CLCOMColorIOBuffer = new CLMemory(m_CLContext );        //Task1 & 4

    m_CLProteinSpaceIOBuffer = new CLMemory(m_CLContext );    //Task2 & 4
    m_CLProteinAtomsBuffer = new CLMemory(m_CLContext );      //Task2 & 4
    m_CLLipidSpaceInOutBuffer = new CLMemory(m_CLContext );   //Task3
    m_CLLipidParticlesBuffer = new CLMemory(m_CLContext );    //Task3

    m_CLParticlesIdentityBuffer = new CLMemory(m_CLContext );         //Task4
    m_CLParticlesInteractionInOutBuffer = new CLMemory(m_CLContext ); //Task4
    m_CLReferenceProteinIBuffer = new CLMemory(m_CLContext );         //Task4
    m_CLInteractionCountIOBuffer = new CLMemory(m_CLContext );        //Task4
}

void CLTask::freeResources()
{
    if(this->getCLCentralizeFrameKernel() != NULL )
    {
        delete m_CLCentralizeFrameKernel;
        m_CLCentralizeFrameKernel = NULL;
    }

    if(this->getCLComputeProteinCOMKernel() != NULL)
    {
        delete m_CLComputeProteinCOMKernel;
        m_CLComputeProteinCOMKernel = NULL;
    }

    if(this->getCLComputeLipidCOMKernel() != NULL)
    {
        delete m_CLComputeLipidCOMKernel;
        m_CLComputeLipidCOMKernel = NULL;
    }

    if(this->getCLComputeInteractionCOMKernel() != NULL)
    {
        delete m_CLComputeInteractionCOMKernel;
        m_CLComputeInteractionCOMKernel =NULL;
    }

    if(this->getCLComputeInteractionKernel() != NULL)
    {
        delete m_CLComputeInteractionKernel;
        m_CLComputeInteractionKernel=NULL;
    }

    if(this->getCLProgram() != NULL)
    {
        delete m_CLProgram;
        m_CLProgram = NULL;
    }

    if(this->getCLSystemStructureBuffer() != NULL)
    {
        delete m_CLSystemStructureBuffer;
        m_CLSystemStructureBuffer = NULL;
    }

    if(this->getCLFirstFrameIOBuffer() != NULL)
    {
        delete m_CLFirstFrameIOBuffer;
        m_CLFirstFrameIOBuffer = NULL;
    }

    if(this->getCLFrameIOBuffer() != NULL)
    {
        delete m_CLFrameIOBuffer;
        m_CLFrameIOBuffer = NULL;
    }

    if(this->getCLCOMFrameIOBuffer() != NULL)
    {
        delete m_CLCOMFrameIOBuffer;
        m_CLCOMFrameIOBuffer = NULL;
    }

    if(this->getCLColorIOBuffer() != NULL)
    {
        delete m_CLColorIOBuffer;
        m_CLColorIOBuffer = NULL;
    }

    if(this->getCLCOMColorIOBuffer() != NULL)
    {
        delete m_CLCOMColorIOBuffer;
        m_CLCOMColorIOBuffer = NULL;
    }


    if(this->getCLCOMFrameIOBuffer() != NULL)
    {
        delete m_CLCOMFrameIOBuffer;
        m_CLCOMFrameIOBuffer = NULL;
    }

    if(this->getCLProteinSpaceIOBuffer() != NULL)
    {
        delete m_CLProteinSpaceIOBuffer;
        m_CLProteinSpaceIOBuffer = NULL;
    }

    if(this->getCLProteinAtomsBuffer() != NULL)
    {
        delete m_CLProteinAtomsBuffer;
        m_CLProteinAtomsBuffer = NULL;
    }

    if(this->getCLLipidSpaceInOutBuffer() != NULL)
    {
        delete m_CLLipidSpaceInOutBuffer;
        m_CLLipidSpaceInOutBuffer = NULL;
    }

    if(this->getCLLipidParticlesBuffer() != NULL)
    {
        delete m_CLLipidParticlesBuffer;
        m_CLLipidParticlesBuffer = NULL;
    }

    if(this->getCLParticlesIdentityBuffer() != NULL)
    {
        delete m_CLParticlesIdentityBuffer;
        m_CLParticlesIdentityBuffer = NULL;
    }

    if(this->getCLParticlesInteractionInOutBuffer() != NULL)
    {
        delete m_CLParticlesInteractionInOutBuffer;
        m_CLParticlesInteractionInOutBuffer = NULL;
    }

    if(this->getCLReferenceProteinIBuffer() != NULL)
    {
        delete m_CLReferenceProteinIBuffer;
        m_CLReferenceProteinIBuffer = NULL;
    }

    if(this->getCLInteractionCountIOBuffer() != NULL)
    {
        delete m_CLInteractionCountIOBuffer;
        m_CLInteractionCountIOBuffer = NULL;
    }

    if(this->getCLCommand() != NULL)
    {
        delete m_CLCommand;
        m_CLCommand = NULL;
    }

    if(this->getCLContext() != NULL)
    {
        delete m_CLContext;
        m_CLContext = NULL;
    }

    if(this->getCLPlatform() != NULL)
    {
        delete m_CLPlatform;
        m_CLPlatform = NULL;
    }

    if(this->getCLDevice() != NULL)
    {
        delete m_CLDevice;
        m_CLDevice = NULL;
    }

}

void CLTask::CentralizeFrame(void *frame, float boxdimensionsX, float boxdimensionsY, float boxdimensionsZ, float minboxdimensionsX, float minboxdimensionsY, float minboxdimensionsZ, float maxboxdimensionsX, float maxboxdimensionsY, float maxboxdimensionsZ, unsigned int atomsnumber, unsigned int workitemssize, unsigned int localsize)
{
    int err;
    cl_device_id device = NULL;
    cl_command_queue command = NULL;
    cl_kernel kernel = NULL;
    cl_mem memoryObject = NULL;
    size_t kernelGlobalSize;
    size_t kernelLocalSize;
    size_t workItemSize;
    size_t bufferSize;

    QTime timer;
    bool timerState;

    timerState = this->getTimerState();

    if( timerState == true)
    {
        timer.start();
    }

    bufferSize = atomsnumber * RVEC_SIZE;

    //set a default work item size
    workItemSize = atomsnumber;


    device = this->getCLDevice()->GetID();
    command = this->getCLCommand()->GetCommand();
    kernel = this->getCLCentralizeFrameKernel()->GetKernel();

    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLFrameIOBuffer()->Create( bufferSize );

    memoryObject = this->getCLFrameIOBuffer()->GetMemoryObject();
    err = clEnqueueWriteBuffer( command ,memoryObject, CL_TRUE, ZERO_OFFSET, bufferSize, frame, UNSPECIFIED_EVENTS_LIST ,NULL, NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write centralize FrameInOutBuffer";
        return ;
    }

    err  = clSetKernelArg( kernel, 0, sizeof( cl_mem ), &memoryObject);
    err |= clSetKernelArg( kernel, 1, sizeof( float ) , &boxdimensionsX);
    err |= clSetKernelArg( kernel, 2, sizeof( float ) , &boxdimensionsY);
    err |= clSetKernelArg( kernel, 3, sizeof( float ) , &boxdimensionsZ);
    err |= clSetKernelArg( kernel, 4, sizeof( float ) , &minboxdimensionsX);
    err |= clSetKernelArg( kernel, 5, sizeof( float ) , &minboxdimensionsY);
    err |= clSetKernelArg( kernel, 6, sizeof( float ) , &minboxdimensionsZ);
    err |= clSetKernelArg( kernel, 7, sizeof( float ) , &maxboxdimensionsX);
    err |= clSetKernelArg( kernel, 8, sizeof( float ) , &maxboxdimensionsY);
    err |= clSetKernelArg( kernel, 9, sizeof( float ) , &maxboxdimensionsZ);
    err |= clSetKernelArg( kernel, 10, sizeof(unsigned int), &atomsnumber);

    if (err != CL_SUCCESS)
    {
        qDebug() << "Error: Failed to set centralize kernel arguments! " << err ;
        return ;
    }

    if( localsize == UINT_ZERO )
    {
        err = clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof( size_t ), &kernelLocalSize, NULL);
        if (err != CL_SUCCESS) {
            qDebug() << "Error: Failed to retrieve centralize kernel work group info! " << err ;
            return ;
        }
    }
    else
    {
        kernelLocalSize = localsize;
    }

    if( workitemssize != 0)
        workItemSize = workitemssize;

    kernelGlobalSize =  ( workItemSize / kernelLocalSize + UINT_ONE ) * kernelLocalSize;

    err = clEnqueueNDRangeKernel(command, kernel, WORK1DIM, NULL, &kernelGlobalSize, &kernelLocalSize, UNSPECIFIED_EVENTS_LIST, NULL, NULL);
    if (err) {
        qDebug() << "Error: Failed to execute centralize kernel!";
        return ;
    }


    clEnqueueReadBuffer( command, memoryObject, CL_TRUE, ZERO_OFFSET, bufferSize, frame, UNSPECIFIED_EVENTS_LIST, NULL, NULL);

    //clFlush(command);
    clFinish(command);

    if( timerState == true)
    {
        qDebug() << " CentralizeFrame done in " << timer.elapsed() << "ms!";
    }
}

void CLTask::ComputeProteinCOM(void *proteinSpaces, void *proteinParticles, unsigned int proteinsnumber, unsigned int proteinparticlesnumber, unsigned int workitemssize, unsigned int localsize)
{
    cl_device_id device = NULL;
    cl_command_queue command = NULL;
    cl_kernel kernel = NULL;
    cl_mem proteinSpaceMemoryObject = NULL;
    cl_mem proteinParticleMemoryObject = NULL;
    size_t kernelGlobalSize;
    size_t kernelLocalSize;
    size_t workItemSize;
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
    command = this->getCLCommand()->GetCommand();
    kernel = this->getCLComputeProteinCOMKernel()->GetKernel();

    proteinSpacesSize = proteinsnumber * GPU_PROTEIN_SPACE_SIZE;
    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLProteinSpaceIOBuffer()->Create( proteinSpacesSize );

    proteinSpaceMemoryObject = this->getCLProteinSpaceIOBuffer()->GetMemoryObject();
    err = clEnqueueWriteBuffer(command ,proteinSpaceMemoryObject, CL_TRUE, ZERO_OFFSET, proteinSpacesSize, proteinSpaces, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);


    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute COM ProteinSpaceBuffer" ;
        return ;
    }

    proteinParticlesSize = proteinparticlesnumber * proteinsnumber * GPU_PROTEIN_PARTICLE_SIZE;
    this->getCLProteinAtomsBuffer()->Create( proteinParticlesSize );
    proteinParticleMemoryObject = this->getCLProteinAtomsBuffer()->GetMemoryObject();

    err = clEnqueueWriteBuffer(command ,proteinParticleMemoryObject, CL_TRUE, ZERO_OFFSET, proteinParticlesSize, proteinParticles,UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute COM ProteinParticlesBuffer" ;
        return ;
    }

    err  = clSetKernelArg(kernel, 0, sizeof( cl_mem ), &proteinSpaceMemoryObject);
    err |= clSetKernelArg(kernel, 1, sizeof( cl_mem ), &proteinParticleMemoryObject);
    err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &proteinsnumber);

    if (err != CL_SUCCESS)
    {
        qDebug() << "Error: Failed to set Compute COM kernel arguments! ";
        return ;
    }

    if( localsize == UINT_ZERO )
    {
        err = clGetKernelWorkGroupInfo( kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof( size_t ), &kernelLocalSize, NULL);
        if (err != CL_SUCCESS) {
            qDebug() << "Error: Failed to retrieve centralize kernel work group info! ";
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

    err = clEnqueueNDRangeKernel(command, kernel, WORK1DIM, NULL, &kernelGlobalSize, &kernelLocalSize, UNSPECIFIED_QUEUE_LIST, NULL, NULL);
    if (err) {
        qDebug() << "Error: Failed to execute centralize kernel!" ;
        return ;
    }

    clEnqueueReadBuffer(command, proteinSpaceMemoryObject, CL_TRUE, ZERO_OFFSET, proteinSpacesSize, proteinSpaces, UNSPECIFIED_EVENTS_LIST, NULL, NULL);

    //clFlush(command);
    clFinish(command);

}



void CLTask::ComputeLipidCOM(void *lipidSpaces, void *lipidParticles, unsigned int lipidsnumber, unsigned int lipidparticlesnumber, unsigned int workitemssize, unsigned int localsize)
{

    cl_device_id device = NULL;
    cl_command_queue command = NULL;
    cl_kernel kernel = NULL;
    cl_mem lipidSpaceMemoryObject = NULL;
    cl_mem lipidParticleMemoryObject = NULL;
    size_t kernelGlobalSize;
    size_t kernelLocalSize;
    size_t workItemSize;
    unsigned int lipidSpacesSize;
    unsigned int lipidParticlesSize;


    int err;
    QTime timer;
    bool timerState;

    timerState = this->getTimerState();

    if( timerState == true)
    {
        timer.start();
    }

    device = this->getCLDevice()->GetID();
    command = this->getCLCommand()->GetCommand();
    kernel = this->getCLComputeLipidCOMKernel()->GetKernel();

    lipidSpacesSize = lipidsnumber * GPU_LIPID_SPACE_SIZE;
    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLLipidSpaceInOutBuffer()->Create( lipidSpacesSize );

    lipidSpaceMemoryObject = this->getCLLipidSpaceInOutBuffer()->GetMemoryObject();

    err = clEnqueueWriteBuffer(command ,lipidSpaceMemoryObject, CL_TRUE, ZERO_OFFSET, lipidSpacesSize, lipidSpaces, UNSPECIFIED_EVENTS_LIST,NULL,NULL);


    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute COM LipidSpaceBuffer" ;
        return ;
    }

    lipidParticlesSize = lipidsnumber * lipidparticlesnumber * GPU_LIPID_PARTICLE_SIZE;
    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLLipidParticlesBuffer()->Create( lipidParticlesSize );

    lipidParticleMemoryObject = this->getCLLipidParticlesBuffer()->GetMemoryObject();

    err = clEnqueueWriteBuffer(command ,lipidParticleMemoryObject, CL_TRUE, ZERO_OFFSET, lipidParticlesSize, lipidParticles, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute COM LipidParticlesBuffer" ;
        return ;
    }

    err  = clSetKernelArg(kernel, 0, sizeof( cl_mem ), &lipidSpaceMemoryObject);
    err  = clSetKernelArg(kernel, 1, sizeof( cl_mem ), &lipidParticleMemoryObject);
    err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &lipidsnumber);

    if (err != CL_SUCCESS)
    {
        qDebug() << "Error: Failed to set Compute Lipid COM kernel arguments! " ;
        return ;
    }

    if( localsize == UINT_ZERO )
    {
        err = clGetKernelWorkGroupInfo( kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof( size_t ), &kernelLocalSize, NULL);
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

    err = clEnqueueNDRangeKernel(command, kernel, WORK1DIM, NULL, &kernelGlobalSize, &kernelLocalSize, 0, NULL, NULL);
    if (err) {
        qDebug() << "Error: Failed to execute compute Lipid COM kernel!" ;
        return ;
    }

    clEnqueueReadBuffer(command, lipidSpaceMemoryObject, CL_TRUE, ZERO_OFFSET, lipidSpacesSize, lipidSpaces, UNSPECIFIED_EVENTS_LIST, NULL, NULL);

    //clFlush(command);
    clFinish(command);
}

void CLTask::ComputeProteinLipidInteraction(void *frame, void *color, void *systemstructure, void *proteinspaces, void *proteinparticles,
                                unsigned int atomsnumber, float interactiondistance, unsigned int workitemssize, unsigned int localsize)
{
    cl_device_id device = NULL;
    cl_command_queue command = NULL;
    cl_kernel kernel = NULL;
    cl_mem positionMemoryObject = NULL;
    cl_mem colorMemoryObject = NULL;
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
    long colorSize;
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
    command = this->getCLCommand()->GetCommand();
    kernel = this->getCLComputeInteractionKernel()->GetKernel();

    atomsNumber = atomsnumber;
    proteinsnumber = PROTEINS_NUMBER;
    proteinparticlesnumber = PROTEIN_PARTICLES_NUMBER;
    rvecSize = RVEC_SIZE;
    positionSize = atomsNumber * rvecSize;

    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLFrameIOBuffer()->Create( positionSize );

    positionMemoryObject = this->getCLFrameIOBuffer()->GetMemoryObject();
    err = clEnqueueWriteBuffer(command ,positionMemoryObject, CL_TRUE, ZERO_OFFSET, positionSize, frame, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);
    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction Frame buffer" ;
        return ;
    }

    //Create a buffer if it hasn't created or if its size less than the required size.
    colorSize = atomsNumber * VERTEX_COLOR_SIZE;
    this->getCLColorIOBuffer()->Create( colorSize );

    colorMemoryObject = this->getCLColorIOBuffer()->GetMemoryObject();
    err = clEnqueueWriteBuffer(command ,colorMemoryObject, CL_TRUE, ZERO_OFFSET, colorSize, color, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);
    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction color buffer" ;
        return ;
    }

    //Create a buffer if it hasn't created or if its size less than the required size.
    systemStructureSize = atomsNumber * SYSTEM_STRUCTURE_RECORD_SIZE;
    this->getCLSystemStructureBuffer()->Create( systemStructureSize );

    systemStructureMemoryObject = this->getCLSystemStructureBuffer()->GetMemoryObject();
    err = clEnqueueWriteBuffer(command ,systemStructureMemoryObject, CL_TRUE, ZERO_OFFSET, systemStructureSize, systemstructure, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction system structure buffer" ;
        return ;
    }

    proteinSpacesSize = proteinsnumber * GPU_PROTEIN_SPACE_SIZE;
    //Create a buffer if it hasn't created or if its size less than the required size.
    this->getCLProteinSpaceIOBuffer()->Create( proteinSpacesSize );

    proteinSpaceMemoryObject = this->getCLProteinSpaceIOBuffer()->GetMemoryObject();
    err = clEnqueueWriteBuffer(command ,proteinSpaceMemoryObject, CL_TRUE, ZERO_OFFSET, proteinSpacesSize, proteinspaces, UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction ProteinSpaceBuffer" ;
        return ;
    }

    proteinParticlesSize = proteinparticlesnumber * proteinsnumber * GPU_PROTEIN_PARTICLE_SIZE;
    this->getCLProteinAtomsBuffer()->Create( proteinParticlesSize );
    proteinParticleMemoryObject = this->getCLProteinAtomsBuffer()->GetMemoryObject();

    err = clEnqueueWriteBuffer(command ,proteinParticleMemoryObject, CL_TRUE, ZERO_OFFSET, proteinParticlesSize, proteinparticles,UNSPECIFIED_EVENTS_LIST ,NULL,NULL);

    if(err != CL_SUCCESS)
    {
        qDebug() << "Error: write compute PL interaction ProteinParticlesBuffer" ;
        return ;
    }

     err  = clSetKernelArg( kernel, 0, sizeof( cl_mem ), &positionMemoryObject);
     err  = clSetKernelArg( kernel, 1, sizeof( cl_mem ), &colorMemoryObject);
     err  = clSetKernelArg( kernel, 2, sizeof( cl_mem ), &systemStructureMemoryObject);
     err  = clSetKernelArg( kernel, 3, sizeof( cl_mem ), &proteinSpaceMemoryObject);
     err  = clSetKernelArg( kernel, 4, sizeof( cl_mem ), &proteinParticleMemoryObject);
     err  = clSetKernelArg( kernel, 5, sizeof( unsigned int ), &atomsnumber);
     err  = clSetKernelArg( kernel, 6, sizeof( float ), &interactiondistance);


     if (err != CL_SUCCESS)
     {
         qDebug() << "Error: Failed to set kernel arguments! " ;
         return ;
     }


     if( localsize == UINT_ZERO )
     {
         err = clGetKernelWorkGroupInfo( kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof( size_t ), &kernelLocalSize, NULL);
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

     err = clEnqueueNDRangeKernel(command, kernel, WORK1DIM, NULL, &kernelGlobalSize, &kernelLocalSize, UNSPECIFIED_EVENTS_LIST, NULL, NULL);
     if (err) {
         qDebug() << "Error: Failed to execute compute PL Interaction kernel!" ;
         return ;
     }

     clEnqueueReadBuffer(command, colorMemoryObject, CL_TRUE, ZERO_OFFSET, colorSize, color, UNSPECIFIED_EVENTS_LIST, NULL, NULL);

     clFlush(command);

}

/*
 *
void CLTask::computeInteractionCOM(float interactionspace, unsigned int lipidsnumber, unsigned int proteinsnumber, rvec *&frame, GPUProteinSpace *&proteinspaces, short *&referenceprotein, short *interactioncount, unsigned int workitemssize, unsigned int localsize)
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

void CLTask::computeInteractionCOMOnTheFly(float interactionspace, unsigned int lipidsnumber, unsigned int proteinsnumber, GPUProteinSpace *&proteinspaces, short *&referenceprotein, short *interactioncount, unsigned int workitemssize, unsigned int localsize)
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
