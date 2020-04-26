#include "spherevao.h"

SphereVAO::SphereVAO()
{

}

SphereVAO::~SphereVAO()
{
    freeResources();
}

void SphereVAO::Create()
{
    if( this->getSphereVAO() == NULL)
    {
        m_SphereVAO = new QOpenGLVertexArrayObject;
        this->getSphereVAO()->create();
    }
}

void SphereVAO::Bind()
{
    getSphereVAO()->bind();
}

void SphereVAO::Release()
{
    getSphereVAO()->release();
}

void SphereVAO::freeResources()
{
    if( this->getSphereVAO() != NULL)
    {
        this->getSphereVAO()->destroy();
        m_SphereVAO = NULL;
    }
}
