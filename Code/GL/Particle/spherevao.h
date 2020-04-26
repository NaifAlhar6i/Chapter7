#ifndef SPHEREVAO_H
#define SPHEREVAO_H

#include "include/glheaders.h"

/**
 * @brief The SphereVAO class interfaces the QOpenGL vertex array object class
 */
class SphereVAO
{
public:
    /**
     * @brief SphereVAO class constructor
     */
    SphereVAO();
    ~SphereVAO();

    /**
     * @brief Create creates the QOpenGL vertex array object
     */
    void Create();

    /**
     * @brief Bind binds the QOpenGL vertex array object
     */
    void Bind();

    /**
     * @brief Release releases the QOpenGL vertex array object
     */
    void Release();
private:
    /**
     * @brief m_SphereVAO the QOpenGL vertex array object
     */
    QOpenGLVertexArrayObject *m_SphereVAO = NULL;

    /**
     * @brief getSphereVAO getter for the QOpenGL vertex array object
     * @return a pointer to the QOpenGL vertex array object
     */
    inline QOpenGLVertexArrayObject *getSphereVAO() { return m_SphereVAO ;}

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // SPHEREVAO_H
