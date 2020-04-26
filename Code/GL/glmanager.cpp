#include "glmanager.h"

GLManager::GLManager()
{

}

void GLManager::InitializeGLObjects()
{
    initializeGLObjects();
}

void GLManager::FreeResources()
{
    freeResources();
}

int GLManager::UpdateParticles(void *particle, void *color, bool map)
{
    int timeElapced;

    timeElapced = this->getParticle()->Update( particle, color, map);

    return timeElapced;

}

int GLManager::UpdateParticles(void *particle, bool map)
{
    int timeElapced;

    timeElapced = this->getParticle()->Update( particle, map);

    return timeElapced;
}

void GLManager::Render(QMatrix4x4 projection, QMatrix4x4 view, QMatrix4x4 model)
{
    this->getParticle()->Render( projection, view, model );
}

void GLManager::initializeGLObjects()
{
    qDebug() << " Initialize!";
    //    glPrimitiveRestartIndex(RESTART_INDEX);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
        //glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT); //can also use GL_BACK GL_FRONT, or GL_FRONT_AND_BACK
        //glFrontFace(GL_CW);
        //glEnable(GL_DEPTH_TEST);
    //    glEnable(GL_LIGHTING);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_SphereVAO = new SphereVAO;
        m_SphereShader = new SphereShader;

        this->getSphereVAO()->Create();
        this->getSphereShader()->Create();

        m_Particle = new Particle( m_SphereVAO, m_SphereShader );




}

void GLManager::freeResources()
{
    delete m_Particle;
    delete m_SphereShader;
    delete m_SphereVAO;
}
