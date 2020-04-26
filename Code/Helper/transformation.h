#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QPoint>
#include <QMatrix4x4>
#include <QVector3D>
#include <QRect>
#include "include/constdata.h"

/**
 * @brief The Transformation class interface the transformation transactions
 */
class Transformation
{
public:
    /**
     * @brief Transformation class constructor
     */
    Transformation();

    /**
     * @brief Translate translate translate the current position based on the new delta X and Y
     * @param currentposition specifies the curent position
     * @param viewport specifies the viewport.
     * It is used to unproject from th screen coordinates to the object coordinates
     */
    void Translate(QPoint currentposition, QRect viewport);

    /**
     * @brief Rotate rotates the current position
     * @param currentposition specifies the current position
     */
    void Rotate(QPoint currentposition);

    /**
     * @brief LookAtCenter sets the trasformations matries to the default configration
     */
    void LookAtCenter();

    /**
     * @brief Zoom Zoom in an out
     * @param value specifies the zooming value
     */
    void Zoom( int value );
protected:

    /**
     * @brief getProjection gets the projection matrix
     * @return the projection matrix
     */
    inline QMatrix4x4 &getProjection() {return m_Projection;}

    /**
     * @brief getView gets the view matrix
     * @return the view matrix
     */
    inline QMatrix4x4 &getView() {return m_View;}

    /**
     * @brief getModel gets the Model matrix
     * @return the Model matrix
     */
    inline QMatrix4x4 &getModel() { return m_Model;}

    /**
     * @brief getRotation get the rotation matrix
     * @return the rotation matrix
     */
    inline QMatrix4x4 &getRotation() {return m_Rotation;}

    /**
     * @brief getLastPosition gets the last position
     * @return the last position
     */
    inline QPoint getLastPosition() { return m_LastPosition;}

    /**
     * @brief setLastPosition sets the last position
     * @param lastposition specifies the last position
     */
    inline void setLastPosition(QPoint lastposition) { m_LastPosition = lastposition;}

    /**
     * @brief updateModel updates the model
     */
    void updateModel();

    /**
     * @brief updateProjection updates the projection matrix
     * @param width specifies the width of the viewport
     * @param height specifies the height of the viewport
     */
    void updateProjection(int width, int height);


private:
    /**
     * @brief m_Projection the projection matrix
     */
    QMatrix4x4 m_Projection;

    /**
     * @brief m_View the view matrix
     */
    QMatrix4x4 m_View;

    /**
     * @brief m_Model the model matrix
     */
    QMatrix4x4 m_Model;

    /**
     * @brief m_Rotation the Rotation matrix
     */
    QMatrix4x4 m_Rotation;

    /**
     * @brief m_ZoomField the zoom field
     */
    float m_ZoomField = 201.0;

    /**
     * the rotation field
     */
    float m_FieldRotation = 0.0;

    /**
     * @brief m_XRotation the X rotation
     */
    float m_XRotation = 0.0;

    /**
     * @brief m_YRotation the Y rotation
     */
    float m_YRotation = 0.0;

    /**
     * @brief m_ZRotation the Z rotation
     */
    float m_ZRotation = 0.0;

    /**
     * @brief m_DeltaX the X delta
     * It is the distance between the old X position and the new X position
     */
    float m_DeltaX = 0.0;

    /**
     * @brief m_DeltaY the Y dalta
     * It is the distance between the old Y position and the new Y position
     */
    float m_DeltaY = 0.0;

    /**
     * @brief m_LastPosition the last position
     */
    QPoint m_LastPosition;

    /**
     * @brief getZoomField gets the zoom feild
     * @return the zoom feild
     */
    inline float getZoomField( ) {return m_ZoomField;}

    /**
     * @brief getFieldRotation gets the field rotation
     * @return  the feild rotation
     */
    inline float getFieldRotation( ) {return m_FieldRotation;}

    /**
     * @brief getXRotation gets the X rotation
     * @return  the x rotation
     */
    inline float getXRotation( ) {return m_XRotation;}

    /**
     * @brief getYRotation gets the Y rotation
     * @return the Y rotation
     */
    inline float getYRotation( ) { return m_YRotation;}

    /**
     * @brief getZRotation gets the Z rotation
     * @return the Z rotation
     */
    inline float getZRotation() {return m_ZRotation;}

    /**
     * @brief getDeltaX gets delta X
     * @return the X delta
     */
    inline float getDeltaX() {return m_DeltaX;}

    /**
     * @brief getDeltaY gets delta Y
     * @return  the Y delta
     */
    inline float getDeltaY() {return m_DeltaY;}

    /**
     * @brief setProjection sets the projection matrix
     * @param projection specifies the projection matrix
     */
    inline void setProjection(QMatrix4x4 projection) {m_Projection = projection;}

    /**
     * @brief setView sets the view matrix
     * @param view specifies the view matrix
     */
    inline void setView(QMatrix4x4 view) { m_View = view;}

    /**
     * @brief setModel sets the model matrix
     * @param model specifies the model matrix
     */
    inline void setModel(QMatrix4x4 model) { m_Model = model;}

    /**
     * @brief setZoomField sets the zoom field
     * @param zoomfield specifies the zoom field
     */
    inline void setZoomField(float zoomfield) { m_ZoomField = zoomfield;}

    /**
     * @brief setFieldRotation sets the rotation field
     * @param fieldrotation specifies the rotation field
     */
    inline void setFieldRotation( float fieldrotation) { m_FieldRotation = fieldrotation;}

    /**
     * @brief setXRotation sets the X rotation
     * @param xrotation specifies the X rotation
     */
    inline void setXRotation( float xrotation) { m_XRotation = xrotation;}

    /**
     * @brief setYRotation sets the Y rotation
     * @param yrotation specifies the Y rotation
     */
    inline void setYRotation( float yrotation) { m_YRotation = yrotation;}

    /**
     * @brief setZRotation sets the z rotation
     * @param zrotation specifies the Z rotation
     */
    inline void setZRotation( float zrotation) { m_ZRotation = zrotation;}

    /**
     * @brief setDeltaX sets the X delta
     * @param deltax specifies the x delta
     */
    inline void setDeltaX(float deltax) { m_DeltaX = deltax;}

    /**
     * @brief setDeltaY sets the Y delta
     * @param deltay specifies the y delta
     */
    inline void setDeltaY(float deltay) { m_DeltaY = deltay;}
};

#endif // TRANSFORMATION_H
