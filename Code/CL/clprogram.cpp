#include <QFile>
#include "clprogram.h"

//cl_program CLProgram::m_Program = NULL;

CLProgram::CLProgram(CLContext *clcontext) : m_CLContext( clcontext)
{
}

CLProgram::~CLProgram()
{
    this->freeResources();
}

bool CLProgram::Create(QString filename)
{

    bool result;

    result = createProgram( filename);

    result |= buildPrograme();

    result |= createSharedProgram( filename);

    result |= buildSharedPrograme();

    return result;

}

bool CLProgram::createProgram(QString filename)
{
    cl_device_id deviceID;
    cl_context context;
    cl_program program;
    int err;

    deviceID = this->getDeviceID();
    context = this->getContext();
    program = NULL;
    const char *source_code = fetchSource(filename).toLatin1().data();

    if( this->getProgram() != NULL)
        return true;

    program = clCreateProgramWithSource(context, ONE_ENTRIE, &source_code, NULL, &err);
    if (!program)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLProgram).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Program from source!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_Program = NULL;
        return false;
    }

    this->setProgram( program );

    return true;
}

bool CLProgram::buildPrograme()
{
    cl_device_id deviceID;
    cl_program program;
    int err;

    program = this->getProgram();
    deviceID = this->getDeviceID();
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];

        clGetProgramBuildInfo(program, deviceID, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLProgram).name();
        errorMessages.append( className );
        errorMessages.append( "Field to build Program!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_Program = NULL;
        return false;
    }

    return true;
}

bool CLProgram::createSharedProgram(QString filename)
{
    cl_device_id deviceID;
    cl_context context;
    cl_program sharedProgram;
    int err;

    deviceID = this->getDeviceID();
    context = this->getSharedContext();
    sharedProgram = NULL;
    const char *source_code = fetchSource(filename).toLatin1().data();

    if( this->getSharedProgram() != NULL)
        return true;

    sharedProgram = clCreateProgramWithSource(context, ONE_ENTRIE, &source_code, NULL, &err);
    if (!sharedProgram)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLProgram).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Shared Program from source!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_SharedProgram = NULL;
        return false;
    }

    this->setSharedProgram( sharedProgram );

    return true;
}

bool CLProgram::buildSharedPrograme()
{
    cl_device_id deviceID;
    cl_program sharedProgram;
    int err;

    sharedProgram = this->getSharedProgram();
    deviceID = this->getDeviceID();
    err = clBuildProgram(sharedProgram, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];

        clGetProgramBuildInfo(sharedProgram, deviceID, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLProgram).name();
        errorMessages.append( className );
        errorMessages.append( "Field to build Shared Program!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_SharedProgram = NULL;
        return false;
    }

    return true;
}

void CLProgram::freeResources()
{
    if( getProgram() != NULL)
    {
        clReleaseProgram( m_Program );
        m_Program = NULL;
    }

    if( getSharedProgram() != NULL)
    {
        clReleaseProgram( m_SharedProgram );
        m_SharedProgram = NULL;
    }
}

QString CLProgram::fetchSource(QString filename)
{
    QString resourceData;

    QFile resourceFile(filename);
        if(!resourceFile.open(QFile::ReadOnly |
                      QFile::Text))
        {
            Debug(" Could not open the program file!");
            return "";
        }

        QTextStream inResource(&resourceFile);
        resourceData = inResource.readAll();

        resourceFile.close();

        return resourceData;
}

