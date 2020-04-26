#include "glwidget.h"
#include <QTime>
#include <gl.h>
#include <glu.h>
#include <QThread>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget( parent )
{

    getRefereshTimer().setInterval( 0 );

    connect(&getRefereshTimer(), SIGNAL(timeout()), this, SLOT(update()));

    getRefereshTimer().start();

}

GLWidget::~GLWidget()
{
    //    delete m_Renderer;
    GLManager::FreeResources();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint lastPosition;
    lastPosition = event->pos();

    Transformation::setLastPosition( lastPosition );

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QRect viewPort;
    QPoint currentPosition;

    viewPort = rect();
    currentPosition = event->pos();

    if (event->buttons() & Qt::LeftButton)
    {
        Transformation::Translate(currentPosition, viewPort);
    }else if (event->buttons() & Qt::RightButton) {
        Transformation::Rotate(currentPosition);
    }

    Transformation::setLastPosition( currentPosition );

    this->update();
}

int GLWidget::UpdateParticles(void *particle, void *color, bool map)
{
    int timeElapced;

    timeElapced = GLManager::UpdateParticles( particle, color, map );

    //this->update();

    return timeElapced;
}

int GLWidget::UpdateParticles(void *particle, bool map)
{
    int timeElapced;

    timeElapced = GLManager::UpdateParticles( particle, map );

    //this->update();

    return timeElapced;
}

void GLWidget::initializeGL()
{
    qDebug() << "OpenGL start";
    initializeOpenGLFunctions();
    makeCurrent();

    GLManager::InitializeGLObjects();
    qDebug() << "OpenGL initilized";

    Transformation::updateProjection( width(), height() );

    Transformation::LookAtCenter();

    this->update();

    emit GLinitialized();


}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    Transformation::updateProjection(w, h );
    this->update();
}

void GLWidget::paintGL()
{
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    int frameRate;

    this->getFrameRate().Calculate();

    projection = Transformation::getProjection();
    view = Transformation::getView();
    model = Transformation::getModel();

    GLManager::Render( projection, view, model );

    frameRate = this->getFrameRate().GetRate();

    emit FrameRateUpdated( frameRate );
}


void GLWidget::zoom(int value)
{

    Transformation::Zoom( value );
    this->update();
}
