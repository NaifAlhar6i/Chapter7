#include "clcommand.h"

//cl_command_queue CLCommand::m_Command = NULL;          // compute command queue

CLCommand::CLCommand(CLContext *clcontext) : m_CLContext(clcontext)
{
}

CLCommand::~CLCommand()
{
    this->freeResources();
}

bool CLCommand::Setup()
{

    bool result;

    result = setupCommand();
    result |= setupSharedCommand();

    return result;

}

bool CLCommand::setupCommand()
{
    cl_device_id deviceID;
    cl_context context;
    cl_command_queue command;
    int err;


    if(this->getCommand() != NULL)
        return true;

    deviceID = this->getDeviceID();
    context = this->getContext();
    command = clCreateCommandQueue(context, deviceID, UNSPECIFIED_QUEUE_LIST, &err);
    if (!command)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLCommand).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Command!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_Command = NULL;
        return false;
    }

    this->setCommand( command );
    return true;
}

bool CLCommand::setupSharedCommand()
{
    cl_device_id deviceID;
    cl_context context;
    cl_command_queue command;
    int err;


    if(this->getSharedCommand() != NULL)
        return true;

    deviceID = this->getDeviceID();
    context = this->getSharedContext();
    command = clCreateCommandQueue(context, deviceID, UNSPECIFIED_QUEUE_LIST, &err);
    if (!command)
    {
        QVector<QString> errorMessages;
        QString className;
        className = typeid(CLCommand).name();
        errorMessages.append( className );
        errorMessages.append( "Field to create Shared Command!" );
        errorMessages.append( "Eroor Code:" + err );
        Debug( errorMessages );
        m_SharedCommand = NULL;
        return false;
    }

    this->setSharedCommand( command );

    return true;
}

void CLCommand::freeResources()
{
    if( this->getCommand() != NULL)
    {
        clReleaseCommandQueue( m_Command );
        m_Command = NULL;

    }

    if( this->getSharedCommand() != NULL)
    {
        clReleaseCommandQueue( m_SharedCommand );
        m_SharedCommand = NULL;

    }
}
