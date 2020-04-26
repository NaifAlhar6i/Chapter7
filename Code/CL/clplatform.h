#ifndef CLPLATFORM_H
#define CLPLATFORM_H

#include "include/constdata.h"
#include <CGLCurrent.h>

/**
 * @brief The CLPlatform class interfaces te OpenCL platform object
 */
class CLPlatform: public virtual Debugger
{
public:
    /**
     * @brief CLPlatform class constructor
     */
    CLPlatform();

    /**
     * @brief Setup configurs the platform settings:1) platform id, 2) default context properties, and shared context properties
     * @return true if platform is configured sucessully otherways it returns false
     */
    bool Setup();

    /**
     * @brief GetID: getter for the platform id
     * @return platform id object
     */
    inline cl_platform_id GetID() { return getPlatformID(); }

    /**
     * @brief GetCLContextProperties accessor for a default cl_context_properties
     * @return list of cl context propertie in a QVector
     */
    inline QVector<cl_context_properties> GetCLContextProperties() { return m_CLContextProperties; }

    /**
     * @brief GetCLGLContextProperties  accessor for shared cl_context_properties
     * @return list of cl context propertie in a QVector
     */
    inline QVector<cl_context_properties> GetCLGLContextProperties() { return m_CLGLContextProperties; }

private:
    /**
     * @brief m_Platform_ID
     */
    cl_platform_id m_Platform_ID = NULL;

    /**
     * @brief m_CLContextProperties default context properties
     */
    QVector<cl_context_properties> m_CLContextProperties;

    /**
     * @brief m_CLGLContextProperties shared context properties
     */
    QVector<cl_context_properties> m_CLGLContextProperties;

    /**
     * @brief getPlatformID private accessor for platform id
     * @return
     */
    inline cl_platform_id getPlatformID() { return m_Platform_ID; }

    /**
     * @brief getCLContextProperties private accessor for a default cl_context_properties
     * @return list of cl context propertie in a QVector
     */
    inline QVector<cl_context_properties> &getCLContextProperties() { return m_CLContextProperties; }

    /**
     * @brief getCLGLContextProperties private accessor for a shared cl_context_properties
     * @return list of cl context propertie in a QVector
     */
    inline QVector<cl_context_properties> &getCLGLContextProperties() { return m_CLGLContextProperties; }

    /**
     * @brief setupCL configures platform by obtaining the platform id and setting the default context properties
     * @return true if platform is configured sucessully otherways it returns false
     */
    bool setupCL();

    /**
     * @brief setupCLGL configures platform by setting the shared context properties
     * @return true if shared context properties is configured sucessully otherways it returns false
     */
    bool setupCLGL();

    /**
     * @brief setPlatformID settet for platform id
     * @param id: the obtained platform id
     */
    void setPlatformID( cl_platform_id id ) { m_Platform_ID = id; }

};

#endif // CLPLATFORM_H
