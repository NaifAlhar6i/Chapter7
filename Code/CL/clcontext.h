#ifndef CLCONTEXT_H
#define CLCONTEXT_H

#include "cldevice.h"
#include "clplatform.h"

/**
 * @brief The CLContext class interfaces th OpenCL cl_context object
 * CLContext requires a valid pointers to CLDevice and CLPlatform class.
 * The class provides four main function: Setup, GetContext, GetSharedContext and GetDeviceID.
 *
 */
class CLContext : public virtual Debugger
{
public:
    /**
     * @brief CLContext class constructor
     * @param cldevice: a pointer to CLDevice object
     * @param clplatform: a pointer to CLPlatform object
     */
    CLContext(CLDevice *cldevice, CLPlatform *clplatform);
    ~CLContext();

    /**
     * @brief Setup creates two OpenCL contexts: 1) a default context (non-shareable), and 2) shared context.
     * @return true if booth context are created sucessully otherways it returns false
     */
    bool Setup();

    /**
     * @brief GetContext accessor for default context
     * @return cl_context object
     */
    inline cl_context GetContext() { return m_Context; }

    /**
     * @brief GetSharedContext accesor for shared context
     * @return shared cl_context object
     */
    inline cl_context GetSharedContext() { return m_SharedContext; }

    /**
     * @brief GetDeviceID accessor for device id
     * @return cl_device_id
     */
    inline cl_device_id GetDeviceID() { return this->getDeviceID(); }
protected:

private:
    /**
     * @brief m_CLDevice: a poiner to CLDevice
     */
    CLDevice *m_CLDevice = NULL;

    /**
     * @brief m_CLPlatform: a pointer to CLPlatform
     */
    CLPlatform *m_CLPlatform = NULL;

    /**
     * @brief m_Context: a default OpenCL context
     */
    cl_context m_Context = NULL;

    /**
     * @brief m_SharedContext: a shared OpenCL context
     */
    cl_context m_SharedContext = NULL;

    /**
     * @brief getCLDevice: privste accessor for CLDevice object
     * @return a pointer to CLDevice
     */
    inline CLDevice   *getCLDevice() { return m_CLDevice; }

    /**
     * @brief getCLPlatform: private accessor for CLPlatform object
     * @return a pointer to CLPlatform
     */
    inline CLPlatform *getCLPlatform() { return m_CLPlatform; }

    /**
     * @brief getContext: private accessor for defualt cl_context
     * @return cl_context object
     */
    inline cl_context getContext() { return m_Context; }

    /**
     * @brief getSharedContext: private accessor for shared cl_context
     * @return cl_context
     */
    inline cl_context getSharedContext() { return m_SharedContext; }

    /**
     * @brief getDeviceID: private accessor for OpenCL device ID
     * @return cl_device_id
     */
    inline cl_device_id getDeviceID() { return this->getCLDevice()->GetID(); }

    /**
     * @brief getContextProperties: private accessor for a default cl_context_properties
     * @return list of cl context propertie in a QVector
     */
    inline QVector<cl_context_properties> getContextProperties() { return this->getCLPlatform()->GetCLContextProperties(); }

    /**
     * @brief getSharedContextProperties: private accessor for a shared cl_context_properties
     * @return list of cl context propertie in a QVector
     */
    inline QVector<cl_context_properties> getSharedContextProperties() { return this->getCLPlatform()->GetCLGLContextProperties(); }

    /**
     * @brief setContext: setter for default opencl context
     * @param context a default cl_context object
     */
    inline void setContext(cl_context context) { m_Context = context; }

    /**
     * @brief setSharedContext: setter for shared opencl context
     * @param context a shared cl_context object
     */
    inline void setSharedContext(cl_context context) { m_SharedContext = context; }

    /**
     * @brief setupContext creates a default OpenCL context
     * @return true if the context is succeffuly created
     */
    bool setupContext();

    /**
     * @brief setupSharedContext creates a shared OpenCL context
     * @return true if the context is succeffuly created
     */
    bool setupSharedContext();

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();
};

#endif // CLCONTEXT_H
