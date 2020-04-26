#include "clplatform.h"

CLPlatform::CLPlatform()
{
}

bool CLPlatform::Setup()
{

    bool result;

    result = setupCL();
    result |= setupCLGL();

    return result;

}

bool CLPlatform::setupCL()
{
    int err;

    cl_platform_id platformID = NULL;
    cl_uint retPlatformsNumber;

    //Get platform/device information
    err = clGetPlatformIDs( ONE_ENTRIE, &platformID, &retPlatformsNumber );

    if( err != CL_SUCCESS )
    {
        return false;
    }

    this->setPlatformID( platformID );

    this->getCLContextProperties().append( CL_CONTEXT_PLATFORM );
    this->getCLContextProperties().append( (cl_context_properties)platformID );
    this->getCLContextProperties().append( PROPERTIES_LIST_TERMINATOR );

    return true;
}

bool CLPlatform::setupCLGL()
{

    CGLContextObj    gl_ctx        = CGLGetCurrentContext();
    CGLShareGroupObj gl_sharegroup = CGLGetShareGroup(gl_ctx);

    this->getCLGLContextProperties().append( CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE );
    this->getCLGLContextProperties().append( (cl_context_properties)gl_sharegroup );
    this->getCLGLContextProperties().append( PROPERTIES_LIST_TERMINATOR );

    return true;

}

