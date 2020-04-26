#ifndef SPHERESHADER_H
#define SPHERESHADER_H

#include "include/constdata.h"
#include "include/glheaders.h"

/**
 * @brief The SphereShader class interfaces the QOpenGL shader progrsm class
 */
class SphereShader
{
public:
    /**
     * @brief SphereShader class constructor
     */
    SphereShader();
    ~SphereShader();

    /**
     * @brief Create creates the QOpenGL shader program
     */
    void Create();

    /**
     * @brief GetShader getter for the QOpenGL shader program
     * @return the QOpenGL shader program
     */
    inline QOpenGLShaderProgram *GetShader() {return m_SphereShader;}

private:
    /**
     * @brief m_SphereShader QOpenGL shader program
     */
    QOpenGLShaderProgram *m_SphereShader = NULL;

    /**
     * @brief getSphereShader accessor for the QOpenGL shader program
     * @return
     */
    inline QOpenGLShaderProgram *getSphereShader() {return m_SphereShader;}

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();



};

#endif // SPHERESHADER_H
