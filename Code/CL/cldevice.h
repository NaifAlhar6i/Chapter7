#ifndef CLDEVICE_H
#define CLDEVICE_H

#include "include/constdata.h"

/**
 * @brief The CLDevice class interfces the OpenCL device object.
 * The class provides two main functions: 1) setup and 2) GetID
 */
class CLDevice : public virtual Debugger
{
public:
    /**
     * @brief CLDevice class constructor
     */
    CLDevice();
    ~CLDevice();

    /**
     * @brief Setup creates an OpenCL device
     * @return true if device is created sucessully otherways it returns false
     */
    bool Setup();

    /**
     * @brief GetID: accessor for the device id
     * @return cl_device_id object
     */
    inline cl_device_id GetID() { return getDeviceID(); }
protected:
private:
    /**
     * @brief m_DeviceID an OpenCL device id
     */
    cl_device_id m_DeviceID = NULL;             // compute device id

    /**
     * @brief getDeviceID: private getter for OpenCL device id
     * @return
     */
    inline cl_device_id getDeviceID() { return m_DeviceID; }

    /**
     * @brief setDeviceID: private setter for OpenCL device id
     * @param deviceid cl_device_id
     */
    inline void setDeviceID(cl_device_id deviceid) { m_DeviceID = deviceid; }

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // CLDEVICE_H
