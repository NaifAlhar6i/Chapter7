#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "CL/clmanager.h"
#include "IO/datamanager.h"
#include "Helper/processing.h"

namespace Ui {
class MainWindow;
}

class GLWidget;

/**
 * @brief The MainWindow class the main window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow class constructor
     * @param parent specifies the parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    /**
     * @brief StartRendering starts rendering the data set
     */
    void StartRendering(bool);

    /**
     * @brief UpdateParticle updates the particles
     * @param particle specifies the new particles
     */
    void UpdateParticle(void *particle);

    /**
     * @brief SetIOSTL sets the I/O STL method state
     * @param state specifies the state true==on and false == off
     */
    inline void SetIOSTL(bool state) { m_IO = false;}

    /**
     * @brief SetIOMMF sets the I/O MMF method state
     * @param state specifies the state true==on and false == off
     */
    inline void SetIOMMF(bool state) { m_IO = true;}

    /**
     * @brief SetCLDefault sets CL to default (dont use Interoperability)
     * @param state specifies the state true==on and false == off
     */
    inline void SetCLDefault(bool state) { m_CL = false;}

    /**
     * @brief SetCLInteroperability sets CL to CL-GL Interoperability
     * @param state specifies the state true==on and false == off
     */
    inline void SetCLInteroperability(bool state) { m_CL = true;}

    /**
     * @brief SetGLBufferData sets uploading data to GPU using buffer data method
     * @param state specifies the state true==on and false == off
     */
    inline void SetGLBufferData(bool state) { m_GL = false;}

    /**
     * @brief SetGLMapBuffer sets uploading data to GPU using map buffer method
     * @param state specifies the state true==on and false == off
     */
    inline void SetGLMapBuffer(bool state) { m_GL = true;}

    /**
     * @brief LoadFrame loads frame
     */
    void LoadFrame();

    /**
     * @brief ComputeProteinLipidInteraction computes protein lipid interaction
     */
    void ComputeProteinLipidInteraction();

    /**
     * @brief UpdateFrameRateLabel updates frame rate lable
     * @param framerate specifies the frame rate value
     */
    void UpdateFrameRateLabel(int framerate);

    /**
     * @brief ProteinLipidInteractionComputed slot to be invoked on protein lipid interaction is done
     * @param frame specifies the frame data
     * @param color specifies the color data
     * @param timeelapced specicfies the time elapced
     */
    void ProteinLipidInteractionComputed( void *frame, void *color, int timeelapced );

    /**
     * @brief ProteinLipidInteractionComputed slot to be invoked on protein lipid interaction is done
     * @param frame specifies the frame data
     * @param timeelapced specicfies the time elapced
     */
    void ProteinLipidInteractionComputed( void *frame, int timeelapced );

    /**
     * @brief OnFileDataRead slot to be invoked on file data is read
     * @param timeelapced specicfies the time elapced
     */
    void OnFileDataRead(int timeelapced);

    /**
     * @brief OnGLinitialized slot to be invoked on the OpenGL is intilized
     */
    void OnGLinitialized();
private:

    /**
     * @brief ui
     */
    Ui::MainWindow *ui;

    /**
     * @brief m_Timer
     */
    QTimer *m_Timer = new QTimer;

    /**
     * @brief m_DataManager
     */
    DataManager *m_DataManager;

    /**
     * @brief m_CLManager
     */
    CLManager *m_CLManager;

    /**
     * @brief m_Processing
     */
    Processing *m_Processing;

    /**
     * @brief m_FrameIndex
     */
    unsigned int m_FrameIndex;

    /**
     * @brief m_IO
     */
    bool m_IO;

    /**
     * @brief m_CL
     */
    bool m_CL;

    /**
     * @brief m_GL
     */
    bool m_GL;

    /**
     * @brief getGLWidget gets the OpenGL widget GLWidget
     * @return a pointer to the the OpenGL widget
     */
    GLWidget *getGLWidget();

    /**
     * @brief getDataManager gets the data manager object DataManager
     * @return a pointer to the data manager
     */
    inline DataManager *getDataManager() { return m_DataManager; }

    /**
     * @brief getCLManager gets the CL manager CLManager
     * @return a pointer to the CL manager
     */
    inline CLManager *getCLManager() { return m_CLManager; }

    /**
     * @brief getProcessing gets the processing object Processing
     * @return a pointer to the processing object
     */
    inline Processing *getProcessing() { return m_Processing; }

    /**
     * @brief getIO gets the I/O method state
     * @return the I/O method state
     */
    inline bool getIO() {return m_IO; }

    /**
     * @brief getCL gets the CL intero state
     * @return  the CL intero state
     */
    inline bool getCL() {return m_CL; }

    /**
     * @brief getGL gets the CPU-GPU data transfer method
     * @return the CPU-GPU transfeer method
     */
    inline bool getGL() {return m_GL; }

    /**
     * @brief getTimer gets the timer object
     * @return
     */
    inline QTimer *getTimer() { return m_Timer; }

    /**
     * @brief getFrameIndex gets the frame index
     * @return the current frame index
     */
    unsigned int getFrameIndex();

    /**
     * @brief setFrameIndex sets the current frame index
     * @param index specifies the current frame index
     */
    inline void setFrameIndex(unsigned int index) {m_FrameIndex = index; }

    /**
     * @brief initializeSignalsAndSlots initilizes the signals and slots
     */
    void initializeSignalsAndSlots();

    /**
     * @brief initializeCLObjects initializes the CLObjects
     */
    void initializeCLObjects();

    /**
     * @brief initializeObjects initializes the class Objects
     */
    void initializeObjects();

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // MAINWINDOW_H
