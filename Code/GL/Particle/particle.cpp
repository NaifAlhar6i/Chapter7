#include "particle.h"

Particle::Particle(SphereVAO *vao, SphereShader *shader):
    m_VAO(vao), m_Shader(shader)
{
    this->createBuffers();
    this->initialize();
}

void Particle::createBuffers()
{
    this->createVertexBuffer(  );
    this->createColorBuffer(  );
    this->createIndexBuffer(  );
}

void Particle::Render(QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model)
{
    QMatrix4x4 mvp;

    mvp = projection * view * model;

    this->getVAO()->Bind();
    //this->printGlError("initialCOMProteinCylinderVAO !!!->");
    this->getShader()->GetShader()->bind();
    this->getShader()->GetShader()->setUniformValue("uniMVP", mvp );

    this->render();

    this->getShader()->GetShader()->release();
    this->getVAO()->Release();

}

int Particle::Update(void *particle, void *color, bool map)
{
    QTime time;
    int timeElapced;

    time.start();

    if( map )
    {
        mapBuffer( particle, color);
    }
    else
    {
        dataBuffer( particle, color );
    }

    timeElapced = time.elapsed();

    return timeElapced;
}

int Particle::Update(void *particle, bool map)
{
    QTime time;
    int timeElapced;

    time.start();

    if( map )
    {
        mapBuffer( particle);
    }
    else
    {
        dataBuffer( particle );
    }

    timeElapced = time.elapsed();

    return timeElapced;
}



void Particle::mapBuffer(void *particle, void *color)
{
    void *positionBuffer;
    void *colorBuffer;
    int vertexBufferSize;
    int colorBufferSize;

    vertexBufferSize = ATOMS_NUMBER * QVECTOR3D_SIZE;
    this->getVertexBuffer()->bind();
    positionBuffer = this->getVertexBuffer()->map(QOpenGLBuffer::WriteOnly);
    memcpy(positionBuffer, particle, vertexBufferSize);
    this->getVertexBuffer()->unmap();
    this->getVertexBuffer()->release();

    colorBufferSize = ATOMS_NUMBER * QVECTOR4D_SIZE;
    this->getColorBuffer()->bind();
    colorBuffer = this->getColorBuffer()->map(QOpenGLBuffer::WriteOnly);
    memcpy(colorBuffer, color, colorBufferSize);
    this->getColorBuffer()->unmap();
    this->getColorBuffer()->release();
}

void Particle::mapBuffer(void *particle)
{
    void *positionBuffer;
    int vertexBufferSize;

    vertexBufferSize = ATOMS_NUMBER * QVECTOR3D_SIZE;
    this->getVertexBuffer()->bind();
    positionBuffer = this->getVertexBuffer()->map(QOpenGLBuffer::WriteOnly);
    memcpy(positionBuffer, particle, vertexBufferSize);
    this->getVertexBuffer()->unmap();
    this->getVertexBuffer()->release();

}

void Particle::dataBuffer(void *particle, void *color)
{

    int vertexBufferSize;
    int colorBufferSize;

    vertexBufferSize = ATOMS_NUMBER * QVECTOR3D_SIZE;
    this->getVertexBuffer()->bind();
    this->getVertexBuffer()->allocate( particle, vertexBufferSize);
    this->getVertexBuffer()->release();

    colorBufferSize = ATOMS_NUMBER * QVECTOR4D_SIZE;
    this->getColorBuffer()->bind();
    this->getColorBuffer()->allocate( color, colorBufferSize );
    this->getColorBuffer()->release();

}

void Particle::dataBuffer(void *particle)
{
    int vertexBufferSize;

    vertexBufferSize = ATOMS_NUMBER * QVECTOR3D_SIZE;
    this->getVertexBuffer()->bind();
    this->getVertexBuffer()->allocate( particle, vertexBufferSize);
    this->getVertexBuffer()->release();

}

void Particle::createVertexBuffer()
{
    int vertexBufferSize;
    vertexBufferSize = ATOMS_NUMBER * QVECTOR3D_SIZE;

    if(this->getVertexBuffer() == NULL)
    {
        m_VertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        this->getVertexBuffer()->setUsagePattern(QOpenGLBuffer::DynamicDraw);
        this->getVertexBuffer()->create();
        this->getVertexBuffer()->bind();
        this->getVertexBuffer()->allocate( vertexBufferSize );
        this->getVertexBuffer()->release();
    }
}

void Particle::createColorBuffer()
{
    int colorBufferSize;
    colorBufferSize = ATOMS_NUMBER * QVECTOR4D_SIZE;
    if(this->getColorBuffer() == NULL)
    {
        m_ColorBuffer = new QOpenGLBuffer( QOpenGLBuffer::VertexBuffer );
        this->getColorBuffer()->setUsagePattern(QOpenGLBuffer::DynamicDraw);
        this->getColorBuffer()->create();
        this->getColorBuffer()->bind();
        this->getColorBuffer()->allocate( colorBufferSize );
        this->getColorBuffer()->release();
    }
}

void Particle::createIndexBuffer()
{
    if(this->getIndexBuffer() == NULL)
    {
        m_IndexBuffer = new QOpenGLBuffer( QOpenGLBuffer::IndexBuffer);
        this->getIndexBuffer()->create();
    }
}

void Particle::render()
{
    if(!glIsEnabled( GL_PROGRAM_POINT_SIZE ))
    {
        glEnable( GL_PROGRAM_POINT_SIZE);
    }

    glDrawArrays( GL_POINTS, UINT_ZERO , ATOMS_NUMBER );
}

void Particle::initialize()
{
    this->getVAO()->Bind();
        this->getShader()->GetShader()->bind();
            this->getVertexBuffer()->bind();
            this->getShader()->GetShader()->enableAttributeArray(0);
            this->getShader()->GetShader()->setAttributeBuffer(0, GL_FLOAT, 0, 3, QVECTOR3D_SIZE);
            this->getColorBuffer()->bind();
            this->getShader()->GetShader()->enableAttributeArray(1);
            this->getShader()->GetShader()->setAttributeBuffer(1, GL_FLOAT, 0, 4, QVECTOR4D_SIZE);
        this->getShader()->GetShader()->release();
    this->getVAO()->Release();
    this->getColorBuffer()->release();
    this->getVertexBuffer()->release();
}
