#ifndef PARTICLE_H
#define PARTICLE_H

#include "spherevao.h"
#include "sphereshader.h"
/**
 * @brief The Particle class
 */
class Particle
{
public:
    /**
     * @brief Particle class constructure
     * @param vao a pointer to vertex array object
     * @param shader a pointer to particle shader
     */
    Particle( SphereVAO *vao, SphereShader *shader);

    /**
     * @brief Render render the particles object
     * @param projection the projection matrex
     * @param view the view matrex
     * @param model the model matrex
     */
    void Render(QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model);

    /**
     * @brief Update updates the particle vertex buffer
     * @param particle a void pointer to the particle data
     * @param color a void pointer to the vertx color data
     * @param map specify the option of filling the vertex buffer and the color buffer
     * if true the glBuffeMap* functions will be used otherwise the glBufferData will be used to fill the buffer data
     * @return true if the buffer is filled sucessully otherwise returns false.
     */
    int Update( void *particle, void *color, bool map = false);

    /**
     * @brief Update updates the particle vertex buffer
     * @param particle a void pointer to the particle data
     * @param map specify the option of filling the vertex buffer
     * if true the glBuffeMap* functions will be used otherwise the glBufferData will be used to fill the buffer data
     * @return true if the buffer is filled sucessully otherwise returns false.
     */
    int Update( void *particle, bool map = false);

    /**
     * @brief GetVertexBufferID accessor for the vertex buffer id
     * @return the vertex buffer ID
     */
    inline GLuint GetVertexBufferID() { return getVertexBuffer()->bufferId(); }

    /**
     * @brief GetColorBufferID accessor for the color buffer id
     * @return  the color buffer ID
     */
    inline GLuint GetColorBufferID() { return getColorBuffer()->bufferId(); }

    /**
     * @brief GetVertexBuffer accessor for the vertex buffer object
     * @return a pointer to the vertex buffer object
     */
    inline QOpenGLBuffer *GetVertexBuffer() { return m_VertexBuffer; }

private:

    /**
     * @brief m_VAO vertex array object
     */
    SphereVAO *m_VAO = NULL;
    /**
     * @brief m_Shader shared object
     */
    SphereShader *m_Shader = NULL;

    /**
     * @brief m_VertexBuffer the openGL vertex array buffer
     */
    QOpenGLBuffer *m_VertexBuffer = NULL;

    /**
     * @brief m_ColorBuffer the openGL color buffer
     */
    QOpenGLBuffer *m_ColorBuffer = NULL;

    /**
     * @brief m_IndexBuffer the openGL index buffer
     */
    QOpenGLBuffer *m_IndexBuffer = NULL;

    /**
     * @brief getVAO accessor for the vertex array object
     * @return
     */
    inline SphereVAO *getVAO() { return m_VAO; }

    /**
     * @brief getShader accessor for the sphere shader
     * @return
     */
    inline SphereShader *getShader() { return m_Shader; }

    /**
     * @brief getVertexBuffer getter for the openGL vertex buffer
     * @return a pinter to the openGL vertex buffer
     */
    inline QOpenGLBuffer *getVertexBuffer() { return m_VertexBuffer; }

    /**
     * @brief getColorBuffer getter for the openGL color buffer
     * @return a pointer to the openGL color buffer
     */
    inline QOpenGLBuffer *getColorBuffer() { return m_ColorBuffer; }

    /**
     * @brief getIndexBuffer getter for the openGL index buffer
     * @return a pointer to the openGL index buffer
     */
    inline QOpenGLBuffer *getIndexBuffer() { return m_IndexBuffer; }

    /**
     * @brief dataBuffer allocates the openGL vertex and color buffer utilizing glBufferData
     * @param particle a pointer to the data to be filled into the openGL vertex buffer
     * @param color a pointer to the data to be filled into the openGL color buffer
     */
    void dataBuffer(void *particle, void *color);

    /**
     * @brief dataBuffer allocates the openGL vertex buffer utilizing glBufferData
     * @param particle a pointer to the data to be filled into the openGL vertex buffer
     */
    void dataBuffer(void *particle);

    /**
     * @brief mapBuffer mapping the openGL vertex and color buffer to memory utilizing glBufferMap
     * @param particle a pointer to the data to be mapped
     * @param color a pointer to the data to be mapped
     */
    void mapBuffer(void *particle, void *color);

    /**
     * @brief mapBuffer mapping the openGL vertex buffer to memory utilizing glBufferMap
     * @param particle a pointer to the data to be mapped
     */
    void mapBuffer(void *particle);

    /**
     * @brief createBuffers creates openGL vertex, volor and index buffer.
     */
    void createBuffers();

    /**
     * @brief createVertexBuffer creates the openGL vertex buffer
     */
    void createVertexBuffer();

    /**
     * @brief createColorBuffer creates the openGL color buffer
     */
    void createColorBuffer();

    /**
     * @brief createIndexBuffer create the openGL index buffer
     */
    void createIndexBuffer();

    /**
     * @brief render render the updated data-set
     */
    void render();

    /**
     * @brief initialize initilizes the openGL objectes
     */
    void initialize();

};

#endif // PARTICLE_H
