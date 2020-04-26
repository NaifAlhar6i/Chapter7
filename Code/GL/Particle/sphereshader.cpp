#include "sphereshader.h"

SphereShader::SphereShader()
{

}

SphereShader::~SphereShader()
{
    freeResources();
}

void SphereShader::Create()
{
    if( this->getSphereShader() == NULL )
    {
        m_SphereShader = new QOpenGLShaderProgram();

        this->getSphereShader()->addShaderFromSourceFile(QOpenGLShader::Vertex, SHADER_DIRECTORY + SPHERE_VERTEX_SHADER_FILE );
        //this->getSphereShader()->addShaderFromSourceFile(QOpenGLShader::Geometry, SHADER_DIRECTORY + SPHERE_GEOMETRY_SHADER_FILE);
        this->getSphereShader()->addShaderFromSourceFile(QOpenGLShader::Fragment, SHADER_DIRECTORY + SPHERE_FRAGMENT_SHADER_FILE);
        this->getSphereShader()->link();
        qDebug() << "Frame Shader error " << this->getSphereShader()->log();
    }
}

void SphereShader::freeResources()
{
    if( this->getSphereShader()   != NULL)
    {
        this->getSphereShader()->release();
        m_SphereShader = NULL;
    }
}
