#ifndef GLMANAGER_H
#define GLMANAGER_H

#include "Particle/sphereshader.h"
#include "Particle/spherevao.h"
#include "Particle/particle.h"

/**
 * @brief The GLManager class manages the OpenGL state
 */
class GLManager
{
public:
    /**
     * @brief GLManager class constructor
     */
    GLManager();

    /**
     * @brief InitializeGLObjects initilizes the Open gl objects
     */
    void InitializeGLObjects();

    /**
     * @brief FreeResources releases the assiocated object and clear the memory
     */
    void FreeResources();

    /**
     * @brief UpdateParticles updates the opengl vertex and color buffer
     * @param particle a void pointer to the particle data
     * @param color a void pointer to the color data
     * @param map specify the option of filling the vertex buffer and the color buffer
     * if true the glBuffeMap* functions will be used otherwise the glBufferData will be used to fill the buffer data
     * @return
     */
    int UpdateParticles(void *particle, void *color, bool map);

    /**
     * @brief UpdateParticles updates the opengl vertex buffer
     * @param particle a void pointer to the particle data
     * @param map specify the option of filling the vertex buffer
     * if true the glBuffeMap* functions will be used otherwise the glBufferData will be used to fill the buffer data
     * @return
     */
    int UpdateParticles(void *particle,bool map);

    /**
     * @brief Render renderes the current data-set
     * @param projection the projection matrex
     * @param view the view matrex
     * @param model the model matrex
     */
    void Render(QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model);

    /**
     * @brief GetParticle
     * @return
     */
    inline Particle *GetParticle() { return m_Particle;}

private:
    /**
     * @brief m_SphereVAO the vertex array object class
     */
    SphereVAO *m_SphereVAO = NULL;

    /**
     * @brief m_SphereShader the shared class
     */
    SphereShader *m_SphereShader = NULL;

    /**
     * @brief m_Particle the particle class
     */
    Particle *m_Particle = NULL;

    /**
     * @brief getSphereVAO accessor for the vertex array object class
     * @return a pointer to the vertex object class
     */
    inline SphereVAO *getSphereVAO() { return m_SphereVAO; }

    /**
     * @brief getSphereShader accessor for the shader class
     * @return a pointer to the shader class
     */
    inline SphereShader *getSphereShader() { return m_SphereShader; }

    /**
     * @brief getParticle accessor for the particle class
     * @return a pointer to the particle class
     */
    inline Particle *getParticle() { return m_Particle; }

    /**
     * @brief initializeGLObjects intilizes the openGL objects
     */
    void initializeGLObjects();

    /**
     * @brief freeResources release the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // GLMANAGER_H
