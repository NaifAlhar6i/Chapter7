#include "clkernel.h"

CLKernel::CLKernel(CLProgram *clprogram) : m_CLProgram(clprogram)
{

}

CLKernel::~CLKernel()
{
    this->freeResources();
}

bool CLKernel::Create(QString kernelname, QString sharedkernelname)
{

    bool result;

    result = createKernel(kernelname);

    if(sharedkernelname != NULL)
    {
        result |= createSharedKernel(sharedkernelname);
    }

    return result;

}

bool CLKernel::createKernel(QString kernelname)
{
    cl_program program;
    cl_kernel kernel;
    int err;

    if( this->getKernel() != NULL )
        return true;

    program = this->getPrograme();
    kernel = clCreateKernel(program, kernelname.toStdString().data(), &err);
    if (!kernel || err != CL_SUCCESS)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLKernel).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Kernel!" + kernelname );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_Kernel = NULL;
        return false;
    }


    this->setKernel( kernel );
    return true;

}

bool CLKernel::createSharedKernel(QString kernelname)
{
    cl_program sharedProgram;
    cl_kernel sharedKernel;
    int err;

    if( this->getSharedKernel() != NULL )
        return true;

    sharedProgram = this->getSharedPrograme();
    sharedKernel = clCreateKernel(sharedProgram, kernelname.toStdString().data(), &err);
    if (!sharedKernel || err != CL_SUCCESS)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLKernel).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Shared Kernel!" + kernelname );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_SharedKernel = NULL;
        return false;
    }


    this->setSharedKernel( sharedKernel );
    return true;
}

void CLKernel::freeResources()
{
    if( this->getKernel() != NULL)
    {
        clReleaseKernel( m_Kernel );
        m_Kernel = NULL;
    }

    if( this->getSharedKernel() != NULL)
    {
        clReleaseKernel( m_SharedKernel );
        m_SharedKernel = NULL;
    }

}
