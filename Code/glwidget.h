#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QPoint>
#include <QMouseEvent>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "Helper/transformation.h"
#include "GL/glmanager.h"
#include <QTimer>
#include "Helper/framerate.h"

class MainWindow;

/**
 * @brief The GLWidget class the rendering canvas
 */
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions, public Transformation, public GLManager
{
    Q_OBJECT

public:
    /**
     * @brief GLWidget class constructor
     * @param parent specifies the parent
     */
    explicit GLWidget( QWidget *parent=0);
    ~GLWidget();

    /**
     * @brief UpdateParticles updates particles data
     * @param particle specifies the particle data
     * @param color specifies the vertices color data
     * @param map specifies the method to be used to update the OpenGL buffer
     * @return true if data updated otherwise return false
     */
    int UpdateParticles(void *particle, void *color, bool map = false);

    /**
     * @brief UpdateParticles updates particles data
     * @param particle specifies the particle data
     * @param map specifies the method to be used to update the OpenGL buffer
     * @return true if data updated otherwise return false
     */
    int UpdateParticles(void *particle, bool map = false);

protected:
    /**
     * @brief initializeGL initilizes OpenGL objects
     */
    void initializeGL() Q_DECL_OVERRIDE;

    /**
     * @brief resizeGL resizes viewport
     * @param w specifies the viewport widght
     * @param h specifies the viewport hight
     */
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;

    /**
     * @brief paintGL paints the OpenGL
     */
    void paintGL() Q_DECL_OVERRIDE;

public slots:

protected slots:
    /**
     * @brief zoom zoom in and out
     * @param value zooming value
     */
    void zoom( int value );

    /**
     * @brief mousePressEvent
     */
    virtual void mousePressEvent(QMouseEvent*);

    /**
     * @brief mouseMoveEvent
     */
    virtual void mouseMoveEvent(QMouseEvent*);

signals:
    /**
     * @brief FrameRateUpdated signals to be fired on frame is done
     */
    void FrameRateUpdated( int );

    /**
     * @brief GLinitialized signals to be fired on OpenGL objects initilized
     */
    void GLinitialized();
private:
    /**
     * @brief m_FrameRate
     */
    FrameRate m_FrameRate;

    /**
     * @brief m_RefereshTimer
     */
    QTimer m_RefereshTimer;

    /**
     * @brief getFrameRate gets a reference of the frame rate object FrameRate
     * @return a reference to FrameRate
     */
    inline FrameRate &getFrameRate() { return m_FrameRate; }

    /**
     * @brief getRefereshTimer gets a reference to the Widget referesing timer
     * @return a reference to a QTimer object
     */
    inline QTimer &getRefereshTimer() { return m_RefereshTimer; }
};

#endif // GLWIDGET_H
