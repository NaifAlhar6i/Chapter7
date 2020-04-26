#include "cldevice.h"

//cl_device_id CLDevice::m_Device_ID = NULL;

CLDevice::CLDevice()
{
}

CLDevice::~CLDevice()
{
    this->freeResources();
}

bool CLDevice::Setup()
{
    cl_device_id deviceID;
    int err;

    if( this->getDeviceID() != NULL )
        return true;

    err = clGetDeviceIDs(NULL, GPU_DEVICE ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, ONE_ENTRIE, &deviceID, NULL);
    if (err != CL_SUCCESS)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLDevice).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Device!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_DeviceID = NULL;
        return false;
    }


    this->setDeviceID( deviceID );
    return true;

}

void CLDevice::freeResources()
{
    if( getDeviceID() != NULL)
    {
        clReleaseDevice( m_DeviceID );
        m_DeviceID = NULL;
    }
}
