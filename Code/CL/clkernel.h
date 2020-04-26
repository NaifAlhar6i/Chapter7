#ifndef CLKERNEL_H
#define CLKERNEL_H

#include "clprogram.h"

/**
 * @brief The CLKernel class interfaces the OpenCL kernel object.
 * CLKernel requires a valid pointer to CLProgram.
 * The class provides three main fnctions: 1)Create, 2) GetKernel, and 3) GetSharedKernel
 */
class CLKernel : public virtual Debugger
{
public:
    /**
     * @brief CLKernel clas constructure
     * @param clprogram: a pointer to CLProgram
     */
    CLKernel(CLProgram *clprogram);
    ~CLKernel();

    /**
     * @brief Create creates two open cl kernels: 1) default kernel, and 2) shared kernel.
     * @param kernelname: the name of the default kernel to be created
     * @param sharedkernelname: the name of the shared kernel to be created.
     * By default there is no shared kernel.
     * If the sharedkernelname parameter is NULL only a default kernel is created.
     * @return true if required kernel(s) is created sucessully otherways it returns false
     */
    bool Create(QString kernelname, QString sharedkernelname = NULL);

    /**
     * @brief GetKernel: accessor for the defualt kernel
     * @return  default cl_kernel object
     */
    inline cl_kernel GetKernel() { return m_Kernel; }

    /**
     * @brief GetSharedKernel: accessor for shared kernel.
     * @return shared cl_kernel object
     */
    inline cl_kernel GetSharedKernel() { return m_SharedKernel; }

private:
    /**
     * @brief m_CLProgram
     */
    CLProgram *m_CLProgram = NULL;

    /**
     * @brief m_Kernel an OpenCL kernel
     */
    cl_kernel m_Kernel = NULL;

    /**
     * @brief m_SharedKernel a shared OpenCL kernel
     */
    cl_kernel m_SharedKernel = NULL;

    /**
     * @brief getCLPrograme: accessor for CLProgram
     * @return a pointer to CLProgram object
     */
    inline CLProgram *getCLPrograme() { return m_CLProgram; }

    /**
     * @brief getPrograme: accessor for OpenCL default cl_program
     * @return cl_program
     */
    inline cl_program getPrograme() { return this->getCLPrograme()->GetProgram();}

    /**
     * @brief getSharedPrograme: accessor for OpenCL shared cl_program
     * @return cl_program
     */
    inline cl_program getSharedPrograme() { return this->getCLPrograme()->GetSharedProgram();}

    /**
     * @brief getKernel: accessor for OpenCL default cl_kernel
     * @return cl_kernel
     */
    inline cl_kernel getKernel() { return m_Kernel; }

    /**
     * @brief getSharedKernel: accessor for OpenCL shared cl_kernel
     * @return cl_kernel
     */
    inline cl_kernel getSharedKernel() { return m_SharedKernel; }

    /**
     * @brief setKernel: setter for default cl_kernel
     * @param kernel cl_kernel
     */
    inline void setKernel( cl_kernel kernel ) { m_Kernel = kernel;}

    /**
     * @brief setSharedKernel: setter for shared cl_kernel
     * @param kernel cl_kernel
     */
    inline void setSharedKernel( cl_kernel kernel ) { m_SharedKernel = kernel;}

    /**
     * @brief createKernel creates a default kernel
     * @param kernelname a QString holds the kernel name to be created
     * @return true if kernel is created sucessully otherways it returns false
     */
    bool createKernel(QString kernelname);

    /**
     * @brief createSharedKernel creates a shared kernel
     * @param kernelname a QString holds the sharedkernel name to be created
     * @return true if sharedkernel is created sucessully otherways it returns false
     */
    bool createSharedKernel(QString kernelname);

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();
};

#endif // CLKERNEL_H
