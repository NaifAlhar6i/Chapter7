#include "transformation.h"

Transformation::Transformation()
{

}

void Transformation::Translate(QPoint currentposition, QRect viewport)
{
    QMatrix4x4 tmpScaleModel;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QPoint lastPosition;
    float deltaX;
    float deltaY;
    float zoomField;

    projection = this->getProjection();
    view = this->getView();
    zoomField = this->getZoomField();
    lastPosition = this->getLastPosition();

    /*
     * Construct a temporary model scale matrix
     */
    tmpScaleModel.setToIdentity();
    tmpScaleModel.scale( zoomField );

    QVector3D v3d1(0, 0, 0);//3D vector at origin
    QVector3D v3d2(1, 0, 0);//3D vector of unit vector along positive x-axis
    QVector3D v3d3(0, 1, 0);//3D vector of unit vector along positive y-axis

    /*
     * unproject from screen coordinates to object coordiniates
     * (screen coordinates) = m_proj * m_view * m_model * (object coordinates)
     */
    v3d1 = v3d1.project(tmpScaleModel, projection * view, viewport);
    v3d2 = v3d2.project(tmpScaleModel, projection * view, viewport);
    v3d3 = v3d3.project(tmpScaleModel, projection * view, viewport);

    /*
     * dx : mouse translation value along the x-axis converted to object coordinates
     * dy : mouse translation value along the y-axis converted to object coordinates
     * qt : positive x-> right, positive y->down
     * opengl : positive x-> right, positive y->up
     */

    deltaX = this->getDeltaX();
    deltaY = this->getDeltaY();

    deltaX += ((float)(currentposition.x() - lastPosition.x())) / (v3d2.x() - v3d1.x());
    deltaY += -((float)(currentposition.y() - lastPosition.y())) / (v3d3.y() - v3d1.y());

    this->setDeltaX( deltaX );
    this->setDeltaY( deltaY );

    this->updateModel();
}

void Transformation::Rotate(QPoint currentposition)
{
    QPoint lastPosition;
    float yRotation;
    float xRotation;
    /*
     * x displacement corresponds to y-rotation
     * y displacement corresponds to x-rotation
     * (pixel to degrees)
     */

    lastPosition = this->getLastPosition();
    yRotation = this->getYRotation();
    xRotation = this->getXRotation();

    yRotation += (currentposition.x() - lastPosition.x());
    xRotation += (currentposition.y() - lastPosition.y());

    this->setYRotation( yRotation);
    this->setXRotation( xRotation);

    this->updateModel();
}

void Transformation::LookAtCenter()
{
    QVector3D eye;
    QVector3D center;
    QVector3D up;

    this->getView().setToIdentity();
    eye = QVector3D(0.0f, 0.0f,  2);
    center = QVector3D(0.0f, 0.0f, 0.0f);
    up = QVector3D(0.0f, 1.0f, 0.0f);
    this->getView().lookAt(eye, center, up);

    this->updateModel();
}

void Transformation::Zoom(int value)
{
    float zoomField;
    zoomField = ( value + UINT_ONE) / ZOOM_QUANTIFIER;

    this->setZoomField( zoomField );
    this->updateModel();
}

void Transformation::updateModel()
{
    float zoomField;
    float xRotation;
    float yRotation;
    float zRotation;
    float deltaX;
    float deltaY;

    zoomField = this->getZoomField();
    xRotation = this->getXRotation();
    yRotation = this->getYRotation();
    zRotation = this->getZRotation();
    deltaX = this->getDeltaX();
    deltaY = this->getDeltaY();

    this->getModel().setToIdentity();
    this->getRotation().setToIdentity();
    /*
     * apply scaling factor controlled by horizontalScrollBar
     */
    this->getModel().scale(zoomField);
    this->getRotation().scale( zoomField );

    /*
     * apply translation given by mouse left button drag and drop
     */
    this->getModel().translate(deltaX, deltaY, 0.0);
    /*
     * apply rotation given by mouse right button drag and drop
     * along x-axis, y-axis. (z-axis rotation added for future use)
     */
    this->getModel().rotate(xRotation, 1.0f, 0.0f, 0.0f);
    this->getModel().rotate(yRotation, 0.0f, 1.0f, 0.0f);
    this->getModel().rotate(zRotation, 0.0f, 0.0f, 1.0f);

    this->getRotation().rotate(xRotation, 1.0f, 0.0f, 0.0f);
    this->getRotation().rotate(yRotation, 0.0f, 1.0f, 0.0f);
    this->getRotation().rotate(zRotation, 0.0f, 0.0f, 1.0f);

}

void Transformation::updateProjection(int width, int height)
{
    this->getProjection().setToIdentity();
    this->getProjection().perspective(FIELD_ANGLE , width / (float)height,NEAR_PLANE, FAR_PLANE);
}
