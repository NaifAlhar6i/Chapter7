#ifndef CLTASK_H
#define CLTASK_H

#include "include/constdata.h"
#include "clmemory.h"
#include "clkernel.h"
#include <QTime>

/**
 * @brief The CLTask class provides the functionalities for configuring the our CL* classes
 */
class CLTask
{
public:
    /**
     * @brief CLTask class constructor
     */
    CLTask();
    ~CLTask();

    /**
     * @brief GetCLDevice accessor for CLDevice
     * @return a pointer to CLDevice object
     */
    inline CLDevice   *GetCLDevice() { return  m_CLDevice ;}

    /**
     * @brief GetCLPlatform accessor for CLPlatform
     * @return a pointer to CLPlatform object
     */
    inline CLPlatform *GetCLPlatform(){ return m_CLPlatform ; }

    /**
     * @brief GetCLContext accessor for CLContext
     * @return a pointer to CLContext object
     */
    inline CLContext  *GetCLContext(){ return m_CLContext ;}

    /**
     * @brief GetCLCommand accessor for CLCommand
     * @return a pointer to CLCommand
     */
    inline CLCommand  *GetCLCommand(){ return m_CLCommand ;}

    /**
     * @brief GetCLProgram accessor for CLProgram
     * @return a pointer to CLProgram
     */
    inline CLProgram  *GetCLProgram(){ return m_CLProgram ;}

    /**
     * @brief GetCLCentralizeFrameKernel accessor for CLKernel
     * @return a pointer to CentralizeFrameKernel object
     */
    inline CLKernel   *GetCLCentralizeFrameKernel(){ return m_CLCentralizeFrameKernel ; }

    /**
     * @brief GetCLComputeProteinCOMKernel accessor for CLKernel
     * @return a pointer to ComputeProteinCOMKernel object
     */
    inline CLKernel   *GetCLComputeProteinCOMKernel(){ return m_CLComputeProteinCOMKernel ; }

    /**
     * @brief GetCLComputeLipidCOMKernel accessor for CLKernel
     * @return a poiter to ComputeLipidCOMKernel object
     */
    inline CLKernel   *GetCLComputeLipidCOMKernel(){ return m_CLComputeLipidCOMKernel ;}

    /**
     * @brief GetCLComputeInteractionKernel accessor for CLKernel
     * @return a pointer to ComputeInteractionKernel object
     */
    inline CLKernel   *GetCLComputeInteractionKernel(){ return m_CLComputeInteractionKernel ; }

    /**
     * @brief GetCLComputeInteractionCOMKernel accessor for CLKernel
     * @return  a pointer to ComputeInteractionCOMKernel object
     */
    inline CLKernel   *GetCLComputeInteractionCOMKernel(){ return m_CLComputeInteractionCOMKernel ;}

    /**
     * @brief GetCLSystemStructureBuffer accessor for CLMemory
     * @return a pointer to SystemStructureBuffer
     */
    inline CLMemory   *GetCLSystemStructureBuffer(){ return m_CLSystemStructureBuffer ; }

    /**
     * @brief GetCLFirstFrameIOBuffer accessor for CLMemory
     * @return  a pointer to FirstFrameIOBuffer
     */
    inline CLMemory   *GetCLFirstFrameIOBuffer(){ return m_CLFirstFrameIOBuffer ; }

    /**
     * @brief GetCLFrameIOBuffer accessor for CLMemory
     * @return a pointer to FrameIOBuffer
     */
    inline CLMemory   *GetCLFrameIOBuffer(){ return m_CLFrameIOBuffer ; }

    /**
     * @brief GetCLCOMFrameIOBuffer accessor for CLMemory
     * @return a pointer to COMFrameIOBuffer
     */
    inline CLMemory   *GetCLCOMFrameIOBuffer(){ return m_CLCOMFrameIOBuffer ; }

    /**
     * @brief GetCLColorIOBuffer accessor for CLMemory
     * @return a pointer to ColorIOBuffer
     */
    inline CLMemory   *GetCLColorIOBuffer(){ return m_CLColorIOBuffer ; }

    /**
     * @brief GetCLCOMColorIOBuffer accessor for CLMemory
     * @return a pointer to COMColorIOBuffer
     */
    inline CLMemory   *GetCLCOMColorIOBuffer(){ return m_CLCOMColorIOBuffer ; }

    /**
     * @brief GetCLProteinSpaceIOBuffer acccessor for CLMemory
     * @return a pointer to ProteinSpaceIOBuffer
     */
    inline CLMemory   *GetCLProteinSpaceIOBuffer(){ return m_CLProteinSpaceIOBuffer ; }

    /**
     * @brief GetCLProteinAtomsBuffer accessor for CLmemory
     * @return a pointer to ProteinAtomsBuffer
     */
    inline CLMemory   *GetCLProteinAtomsBuffer(){ return m_CLProteinAtomsBuffer ; }

    /**
     * @brief GetCLLipidSpaceInOutBuffer accessor for CLMemory
     * @return a pointer to LipidSpaceInOutBuffer
     */
    inline CLMemory   *GetCLLipidSpaceInOutBuffer(){ return m_CLLipidSpaceInOutBuffer ; }

    /**
     * @brief GetCLLipidParticlesBuffer accesor for CLMemory
     * @return a pointer to LipidParticlesBuffer
     */
    inline CLMemory   *GetCLLipidParticlesBuffer(){ return m_CLLipidParticlesBuffer ; }

    /**
     * @brief GetCLParticlesIdentityBuffer accessor for CLMemory
     * @return a pointer to ParticlesIdentityBuffer
     */
    inline CLMemory   *GetCLParticlesIdentityBuffer(){ return m_CLParticlesIdentityBuffer ; }

    /**
     * @brief GetCLParticlesInteractionInOutBuffer accessor for CLMemory
     * @return a pointer to ParticlesInteractionInOutBuffer
     */
    inline CLMemory   *GetCLParticlesInteractionInOutBuffer(){ return m_CLParticlesInteractionInOutBuffer ; }

    /**
     * @brief GetCLReferenceProteinIBuffer accessor for CLMemory
     * @return a pointer to ReferenceProteinIBuffer
     */
    inline CLMemory   *GetCLReferenceProteinIBuffer(){ return m_CLReferenceProteinIBuffer ;  }

    /**
     * @brief GetCLInteractionCountIOBuffer accessor for CLMemory
     * @return a pointer to InteractionCountIOBuffer
     */
    inline CLMemory   *GetCLInteractionCountIOBuffer(){ return m_CLInteractionCountIOBuffer ; }

    /**
     * @brief SetTimerState specifying the time calculation state
     * @param state true to calculate the processing time. If the parameter is false then no time calculation is done.
     */
    inline void SetTimerState( bool state ) { m_TimerState = state; }

    /**
     * @brief InstallOpenCL installing the essential OpenCL objects (device, platform, context, command, program, and kernel)
     * @return true if they installed sucessull otherways returns false.
     */
    bool InstallOpenCL();

    /**
     * @brief CentralizeFrame
     * @param frame
     * @param boxdimensionsX
     * @param boxdimensionsY
     * @param boxdimensionsZ
     * @param minboxdimensionsX
     * @param minboxdimensionsY
     * @param minboxdimensionsZ
     * @param maxboxdimensionsX
     * @param maxboxdimensionsY
     * @param maxboxdimensionsZ
     * @param atomsnumber
     * @param workitemssize
     * @param localsize
     */
    void CentralizeFrame(void *frame, float boxdimensionsX, float boxdimensionsY, float boxdimensionsZ
                         , float minboxdimensionsX, float minboxdimensionsY, float minboxdimensionsZ
                         , float maxboxdimensionsX, float maxboxdimensionsY, float maxboxdimensionsZ,unsigned int atomsnumber, unsigned int workitemssize = 0, unsigned int localsize = 0);

    /**
     * @brief ComputeProteinCOM computes the proteins center of mass.
     * @param proteinSpaces a void pointer to the structure of protein space.
     * @param proteinParticles  a void pointer to the structure of protein particles.
     * @param proteinsnumber the number of protein.
     * @param proteinparticlesnumber the number of protein particles.
     * @param workitemssize the size of the work items to be excuted, we use the number of protein.
     * @param localsize the number of items per group.
     */
    void ComputeProteinCOM(void *proteinSpaces, void *proteinParticles, unsigned int proteinsnumber, unsigned int proteinparticlesnumber, unsigned int workitemssize = 256, unsigned int localsize = 0);

    /**
     * @brief ComputeLipidCOM computes
     * @param lipidSpaces
     * @param lipidParticles
     * @param lipidsnumber
     * @param lipidparticlesnumber
     * @param workitemssize
     * @param localsize
     */
    void ComputeLipidCOM(void *lipidSpaces, void *lipidParticles, unsigned int lipidsnumber, unsigned int lipidparticlesnumber, unsigned int workitemssize = 256, unsigned int localsize = 0);

    /**
     * @brief ComputeProteinLipidInteraction computes the protein-lipid interaction based on the interactiondistance.
     * @param frame a void pointer to the frame data
     * @param color a void pointer to the color data
     * @param systemstructure a void pointer to the system structure.
     * @param proteinspaces a void pointer to the protein space.
     * @param proteinparticles a void pointer to the protein particles
     * @param atomsnumber the number of system atoms
     * @param interactiondistance the maximum distance to be used in the interaction test
     * @param workitemssize the size of the work items to be excuted, we use the number of syatem atoms.
     * @param localsize the number of items per group.
     */
    void ComputeProteinLipidInteraction(void *frame, void *color, void *systemstructure, void *proteinspaces, void *proteinparticles,
                            unsigned int atomsnumber, float interactiondistance,  unsigned int workitemssize = 0, unsigned int localsize = 0);

protected:
    /**
     * @brief getCLDevice private accessor for CLDevice
     * @return a pointer to the CLDevice object
     */
    inline CLDevice   *getCLDevice() { return m_CLDevice ;}

    /**
     * @brief getCLPlatform private accessor for CLPlatform
     * @return  a pointer to the CLPlatform object
     */
    inline CLPlatform *getCLPlatform(){ return m_CLPlatform ; }

    /**
     * @brief getCLContext private accessor for CLContext
     * @return a pointer to the CLContext object
     */
    inline CLContext  *getCLContext(){ return m_CLContext ;}

    /**
     * @brief getCLCommand pivate accessor for CLCommand
     * @return a pointer to the CLCommand object
     */
    inline CLCommand  *getCLCommand(){ return m_CLCommand ;}

    /**
     * @brief getCLProgram private accessor for CLProgram
     * @return a pointer to the CLProgram object
     */
    inline CLProgram  *getCLProgram(){ return m_CLProgram ;}

    /**
     * @brief getCLCentralizeFrameKernel private accessor for CLKernel
     * @return a pointer to the CentralizeFrame Kernel
     */
    inline CLKernel   *getCLCentralizeFrameKernel(){ return m_CLCentralizeFrameKernel ; }

    /**
     * @brief getCLComputeProteinCOMKernel private accessor for CLKernel
     * @return a pointer to the ComputeProteinCOM Kernel
     */
    inline CLKernel   *getCLComputeProteinCOMKernel(){ return m_CLComputeProteinCOMKernel ; }

    /**
     * @brief getCLComputeLipidCOMKernel privare accessor for CLKernel
     * @return a pointer to the ComputeLipidCOM Kernel
     */
    inline CLKernel   *getCLComputeLipidCOMKernel(){ return m_CLComputeLipidCOMKernel ;}

    /**
     * @brief getCLComputeInteractionKernel private accessor for CLKernel
     * @return a pointer to the ComputeInteraction Kernel
     */
    inline CLKernel   *getCLComputeInteractionKernel(){ return m_CLComputeInteractionKernel ; }

    /**
     * @brief getCLComputeInteractionCOMKernel private accessor for CLKernel
     * @return a pointer to the ComputeInteractionCOM Kernel
     */
    inline CLKernel   *getCLComputeInteractionCOMKernel(){ return m_CLComputeInteractionCOMKernel ;}

    /**
     * @brief getCLSystemStructureBuffer private accessor for CLMemory
     * @return a pointer to the SystemStructure memory object
     */
    inline CLMemory   *getCLSystemStructureBuffer(){ return m_CLSystemStructureBuffer ; }

    /**
     * @brief getCLFirstFrameIOBuffer private accessor for CLMemory
     * @return a pointer to the FirstFrameIO memory object
     */
    inline CLMemory   *getCLFirstFrameIOBuffer(){ return m_CLFirstFrameIOBuffer ; }

    /**
     * @brief getCLFrameIOBuffer private accessor for CLMemory
     * @return  a pointer to the FrameIO memory object
     */
    inline CLMemory   *getCLFrameIOBuffer(){ return m_CLFrameIOBuffer ; }

    /**
     * @brief getCLCOMFrameIOBuffer private accessor for CLMemory
     * @return a pointer to the COMFrameIO memory object
     */
    inline CLMemory   *getCLCOMFrameIOBuffer(){ return m_CLCOMFrameIOBuffer ; }

    /**
     * @brief getCLColorIOBuffer private accessor for CLMemory
     * @return a pointer to the ColorIO memory object
     */
    inline CLMemory   *getCLColorIOBuffer(){ return m_CLColorIOBuffer ; }

    /**
     * @brief getCLCOMColorIOBuffer private accessor for CLMemory
     * @return a pointer to the COMColorIO memory object
     */
    inline CLMemory   *getCLCOMColorIOBuffer(){ return m_CLCOMColorIOBuffer ; }

    /**
     * @brief getCLProteinSpaceIOBuffer private accessor for CLMemory
     * @return a pointer to the ProteinSpaceIO memory object
     */
    inline CLMemory   *getCLProteinSpaceIOBuffer(){ return m_CLProteinSpaceIOBuffer ; }

    /**
     * @brief getCLProteinAtomsBuffer private accessor for CLMemory
     * @return a pointer to the ProteinAtoms memory object
     */
    inline CLMemory   *getCLProteinAtomsBuffer(){ return m_CLProteinAtomsBuffer ; }

    /**
     * @brief getCLLipidSpaceInOutBuffer private accessor for CLMemory
     * @return a pointer to the LipidSpaceInOut memory object
     */
    inline CLMemory   *getCLLipidSpaceInOutBuffer(){ return m_CLLipidSpaceInOutBuffer ; }

    /**
     * @brief getCLLipidParticlesBuffer private accessor for CLMemory
     * @return a pointer to the LipidParticles memory object
     */
    inline CLMemory   *getCLLipidParticlesBuffer(){ return m_CLLipidParticlesBuffer ; }

    /**
     * @brief getCLParticlesIdentityBuffer  private accessor for CLMemory
     * @return a pointer to the ParticlesIdentity memory object
     */
    inline CLMemory   *getCLParticlesIdentityBuffer(){ return m_CLParticlesIdentityBuffer ; }

    /**
     * @brief getCLParticlesInteractionInOutBuffer private accessor for CLMemory
     * @return a pointer to the ParticlesInteractionInOut memory object
     */
    inline CLMemory   *getCLParticlesInteractionInOutBuffer(){ return m_CLParticlesInteractionInOutBuffer ; }

    /**
     * @brief getCLReferenceProteinIBuffer private accessor for CLMemory
     * @return a pointer to the ReferenceProteinI memory object
     */
    inline CLMemory   *getCLReferenceProteinIBuffer(){ return m_CLReferenceProteinIBuffer ;  }

    /**
     * @brief getCLInteractionCountIOBuffer private accessor for CLMemory
     * @return a pointer to the InteractionCountIO memory object
     */
    inline CLMemory   *getCLInteractionCountIOBuffer(){ return m_CLInteractionCountIOBuffer ; }

    /**
     * @brief getKernelGlobalSize private accessor for kernel global size
     * @return  the kernel global size
     */
    inline size_t getKernelGlobalSize() { return m_KernelGlobalSize;}

    /**
     * @brief getWorkItemSize private accessor for work items size
     * @return the work item size
     */
    inline size_t getWorkItemSize() { return m_WorkItemSize;}

    /**
     * @brief getKernelLocalSize private accessor for kernel local size
     * @return the local kernel size
     */
    inline size_t getKernelLocalSize() { return m_KernelLocalSize;}

    /**
     * @brief getTimerState accessor for teimer state
     * @return the timer state
     */
    inline bool getTimerState() { return m_TimerState;}

    /**
     * @brief setKernelGlobalSize setter for the kernel global size
     * @param size the global size of the kernel
     */
    inline void setKernelGlobalSize(size_t size) { m_KernelGlobalSize = size;}

    /**
     * @brief setWorkItemSize setter for the work items size
     * @param size the work item size
     */
    inline void setWorkItemSize(size_t size) { m_WorkItemSize = size;}

    /**
     * @brief setKernelLocalSize setter for the kernel local size
     * @param size the kernel local size
     */
    inline void setKernelLocalSize(size_t size) { m_KernelLocalSize = size;}
private:
    /**
     * @brief m_CLDevice
     */
    static CLDevice *m_CLDevice;

    /**
     * @brief m_CLPlatform
     */
    static CLPlatform *m_CLPlatform;

    /**
     * @brief m_CLContext
     */
    static CLContext *m_CLContext;

    /**
     * @brief m_CLCommand
     */
    static CLCommand *m_CLCommand;

    /**
     * @brief m_CLProgram
     */
    static CLProgram *m_CLProgram;

    /**
     * @brief m_CLCentralizeFrameKernel
     */
    static CLKernel  *m_CLCentralizeFrameKernel;

    /**
     * @brief m_CLComputeProteinCOMKernel
     */
    static CLKernel  *m_CLComputeProteinCOMKernel;

    /**
     * @brief m_CLComputeLipidCOMKernel
     */
    static CLKernel  *m_CLComputeLipidCOMKernel;

    /**
     * @brief m_CLComputeInteractionKernel
     */
    static CLKernel  *m_CLComputeInteractionKernel;

    /**
     * @brief m_CLComputeInteractionCOMKernel
     */
    static CLKernel  *m_CLComputeInteractionCOMKernel;

    /**
     * @brief m_CLSystemStructureBuffer
     */
    static CLMemory *m_CLSystemStructureBuffer;

    /**
     * @brief m_CLFirstFrameIOBuffer
     */
    static CLMemory *m_CLFirstFrameIOBuffer;

    /**
     * @brief m_CLFrameIOBuffer
     */
    static CLMemory *m_CLFrameIOBuffer;

    /**
     * @brief m_CLCOMFrameIOBuffer
     */
    static CLMemory *m_CLCOMFrameIOBuffer;

    /**
     * @brief m_CLColorIOBuffer
     */
    static CLMemory *m_CLColorIOBuffer;

    /**
     * @brief m_CLCOMColorIOBuffer
     */
    static CLMemory *m_CLCOMColorIOBuffer;

    /**
     * @brief m_CLProteinSpaceIOBuffer
     */
    static CLMemory *m_CLProteinSpaceIOBuffer;

    /**
     * @brief m_CLProteinAtomsBuffer
     */
    static CLMemory *m_CLProteinAtomsBuffer;

    /**
     * @brief m_CLLipidSpaceInOutBuffer
     */
    static CLMemory *m_CLLipidSpaceInOutBuffer;

    /**
     * @brief m_CLLipidParticlesBuffer
     */
    static CLMemory *m_CLLipidParticlesBuffer;

    /**
     * @brief m_CLParticlesIdentityBuffer
     */
    static CLMemory *m_CLParticlesIdentityBuffer;

    /**
     * @brief m_CLParticlesInteractionInOutBuffer
     */
    static CLMemory *m_CLParticlesInteractionInOutBuffer;

    /**
     * @brief m_CLReferenceProteinIBuffer
     */
    static CLMemory *m_CLReferenceProteinIBuffer;

    /**
     * @brief m_CLInteractionCountIOBuffer
     */
    static CLMemory *m_CLInteractionCountIOBuffer;

    /**
     * @brief m_WorkItemSize
     */
    static size_t m_WorkItemSize;

    /**
     * @brief m_KernelGlobalSize specifies the total number of items to be excuted in the kernel.
     */
    static size_t m_KernelGlobalSize;

    /**
     * @brief m_KernelLocalSize specifies the number of itemes per group.
     * We obtain the groups number by calling clGetKernelWorkGroupInfo
     */
    static size_t m_KernelLocalSize;

    /**
     * @brief m_TimerState specifies the timer state.
     */
    static bool m_TimerState;

    /**
     * @brief initialObjects initializes the CL* classes
     */
    void initialObjects();

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // CLTASK_H
