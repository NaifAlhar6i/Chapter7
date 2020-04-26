#include "clcontext.h"

CLContext::CLContext(CLDevice *cldevice, CLPlatform *clplatform) : m_CLDevice(cldevice), m_CLPlatform(clplatform)
{
}

CLContext::~CLContext()
{
    this->freeResources();
}

bool CLContext::Setup()
{
    bool result;

    result = setupContext();

    result |= setupSharedContext();

    return result;
}

bool CLContext::setupContext()
{
    int err;

    cl_device_id deviceID;
    cl_context_properties *properties;
    cl_context context;

    if( getContext() != NULL )
        return true;


    auto err_cb = [](const char* errinfo, const void* private_info, size_t cb, void* user_data) -> void {
        };

    deviceID = this->getDeviceID();
    properties = this->getContextProperties().data();

    context = clCreateContext(properties, ONE_ENTRIE, &deviceID, err_cb, NULL, &err);
    if (!context)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLContext).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Context!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_Context = NULL;
        return false;
    }


    this->setContext( context );
    return true;
}

bool CLContext::setupSharedContext()
{
    int err;

    cl_device_id deviceID;
    cl_context_properties *properties;
    cl_context context;

    if( getSharedContext() != NULL )
        return true;

    deviceID = this->getDeviceID();
    properties = this->getSharedContextProperties().data();

    auto err_cb = [](const char* errinfo, const void* private_info, size_t cb, void* user_data) -> void {
        qDebug() << "Shared Context error: " << errinfo ;
    };

    context = clCreateContext(properties, ONE_ENTRIE, &deviceID, err_cb, NULL, &err);

    if (!context)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLContext).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Shared Context!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_SharedContext = NULL;
        return false;
    }


    this->setSharedContext( context );
    return true;
}

void CLContext::freeResources()
{
    if( getContext() != NULL)
    {
        clReleaseContext( m_Context );
        m_Context = NULL;
    }

    if( getSharedContext() != NULL)
    {
        clReleaseContext( m_SharedContext );
        m_SharedContext = NULL;
    }

}
