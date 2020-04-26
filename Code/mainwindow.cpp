#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_IO(false), m_CL(false), m_GL(false),
    m_FrameIndex(0)
{
    ui->setupUi(this);

    connect(ui->openGLWidget, SIGNAL(GLinitialized()), this, SLOT( OnGLinitialized()));
}

MainWindow::~MainWindow()
{
    this->freeResources();
    delete ui;
}

void MainWindow::StartRendering(bool)
{
    QString caption;

    caption = "Start";
    if(ui->pushStart->text() == caption)
    {
        caption = "Stop";
        this->getTimer()->start();
        ui->pushStart->setText(caption);
    }
    else
    {
        this->getTimer()->stop();
        ui->pushStart->setText(caption);
    }
}

void MainWindow::UpdateParticle(void *particle)
{
    QString text;
    bool map;
    int timeElapsed;
    GLWidget *glWidget;


    glWidget = this->getGLWidget();
    map = this->getGL();

    timeElapsed = glWidget->UpdateParticles( particle, MemoryManager::getVertexColor(), map );

    text = QString("%1 ms").arg(timeElapsed );
    if( map )
    {
        ui->lblGLMapBuffer->setText( text);
    }
    else
    {
        ui->lblGLBufferData->setText( text);
    }

}

void MainWindow::LoadFrame()
{
    QString text;
    unsigned int frameIndex;
    int timeElapced;
    bool mmpIO;

    frameIndex = this->getFrameIndex();


    text = QString("Frame number: %1/1981").arg(frameIndex + UINT_ONE);

    ui->lblCurrentFrame->setText(text);

    mmpIO = this->getIO();

    if( mmpIO )
    {
        void *mmfFrame;
        timeElapced = this->getDataManager()->MMF::FetchFrame( frameIndex, mmfFrame);
        text = QString("%1 ms").arg(timeElapced);
        ui->lblMMF->setText( text );
        UpdateParticle( mmfFrame );
    }
    else
    {
        timeElapced = this->getDataManager()->STL::FetchFrame( frameIndex );
        text = QString("%1 ms").arg(timeElapced);
        ui->lblSTL->setText( text );
        UpdateParticle( MemoryManager::getVertexPosition() );

    }

    this->setFrameIndex( frameIndex );

}

void MainWindow::ComputeProteinLipidInteraction()
{
    unsigned int frameIndex;
    bool mapIO;
    bool clGlInter;
    GLuint vertexBufferID;
    GLuint colorBufferID;
    QString text;

    QOpenGLBuffer *vertexBuffer;

    frameIndex = this->getFrameIndex();

    text = QString("Frame number: %1/1981").arg(frameIndex + UINT_ONE);

    ui->lblCurrentFrame->setText(text);

    clGlInter = this->getCL();
    mapIO = this->getIO();

    if( !clGlInter )    //Old approach
    {
        this->getDataManager()->ComputeProteinLipidInteraction( frameIndex, mapIO );
    }
    else
    {
        vertexBuffer = this->getGLWidget()->GetParticle()->GetVertexBuffer();
        colorBufferID = this->getGLWidget()->GetParticle()->GetColorBufferID();
        this->getDataManager()->ComputeProteinLipidInteractionOnTheFly( frameIndex, vertexBuffer, colorBufferID, mapIO );
    }

    this->setFrameIndex( frameIndex );

}

void MainWindow::UpdateFrameRateLabel(int framerate)
{
    QString text;

    text = QString("Rendering rate: %1 FPS").arg(framerate );

    ui->lblRenderingRate->setText(text);
}

void MainWindow::ProteinLipidInteractionComputed(void *frame, void *color, int timeelapced)
{

    QString text;
    bool map;
    bool clInter;
    int timeElapsed;
    GLWidget *glWidget;


    glWidget = this->getGLWidget();
    map = this->getGL();
    clInter = this->getCL();

    timeElapsed = glWidget->UpdateParticles( frame, color, map );

    text = QString("%1 ms").arg(timeElapsed );
    if( map )
    {
        ui->lblGLMapBuffer->setText( text);
    }
    else
    {
        ui->lblGLBufferData->setText( text);
    }

    text = QString("%1 ms").arg(timeelapced );
    if( !clInter )
    {
        ui->lblCLDefault->setText( text);
    }
    else
    {
        ui->lblCLInteroperability->setText( text);
    }

}

void MainWindow::ProteinLipidInteractionComputed(void *frame, int timeelapced)
{
    QString text;
    bool map;
    bool clInter;
    int timeElapsed;
    GLWidget *glWidget;


    glWidget = this->getGLWidget();
    map = this->getGL();
    clInter = this->getCL();

    //timeElapsed = glWidget->UpdateParticles( frame, map );

    text = QString("%1 ms").arg( 0 );
    if( map )
    {
        ui->lblGLMapBuffer->setText( text);
    }
    else
    {
        ui->lblGLBufferData->setText( text);
    }


    text = QString("%1 ms").arg(timeelapced );
    if( !clInter )
    {
        ui->lblCLDefault->setText( text);
    }
    else
    {
        ui->lblCLInteroperability->setText( text);
    }

}

void MainWindow::OnFileDataRead(int timeelapced)
{
    QString text;
    bool mmfIO;

    mmfIO = this->getIO();

    text = QString("%1 ms").arg(timeelapced );
    if( mmfIO )
    {
        ui->lblMMF->setText( text);
    }
    else
    {
        ui->lblSTL->setText( text);
    }

}

void MainWindow::OnGLinitialized()
{
    this->initializeCLObjects();
}

GLWidget *MainWindow::getGLWidget()
{
    return ui->openGLWidget;
}

unsigned int MainWindow::getFrameIndex()
{
    unsigned int frameIndex;

    frameIndex = m_FrameIndex;

    if(frameIndex >= FRAMES_NUMBER )
    {
        frameIndex = UINT_ZERO;
    }
    else
    {
        frameIndex++;
    }

    return frameIndex;
}

void MainWindow::initializeSignalsAndSlots()
{

    connect( this->getDataManager(), SIGNAL(CentralizeFrameComputed(void*)), this, SLOT(UpdateParticle( void*)));
    connect( this->getDataManager(), SIGNAL(ProteinLipidInteractionComputed(void*,void*, int)), this, SLOT(ProteinLipidInteractionComputed(void*,void*, int)));
    connect( this->getDataManager(), SIGNAL(ProteinLipidInteractionComputed(void*, int)), this, SLOT(ProteinLipidInteractionComputed(void*, int)));
    connect( this->getDataManager(), SIGNAL(FileDataRead(int)), this, SLOT(OnFileDataRead(int)));

    connect(ui->hrzZoom, SIGNAL(valueChanged(int)), ui->openGLWidget,SLOT(zoom(int)));
    connect(ui->pushStart, SIGNAL(clicked(bool)), this,SLOT(StartRendering(bool)));

    connect(ui->optSTL, SIGNAL(clicked(bool)), this, SLOT( SetIOSTL(bool)));
    connect(ui->optMMF, SIGNAL(clicked(bool)), this, SLOT( SetIOMMF(bool)));
    connect(ui->optCLDefault, SIGNAL(clicked(bool)), this, SLOT( SetCLDefault(bool)));
    connect(ui->optCLInteroperability, SIGNAL(clicked(bool)), this, SLOT( SetCLInteroperability(bool)));
    connect(ui->optGLBufferData, SIGNAL(clicked(bool)), this, SLOT( SetGLBufferData(bool)));
    connect(ui->optGLMapBuffer, SIGNAL(clicked(bool)), this, SLOT( SetGLMapBuffer(bool)));
    connect(ui->openGLWidget, SIGNAL(FrameRateUpdated(int)), this, SLOT( UpdateFrameRateLabel(int)));

    connect( this->getTimer(), SIGNAL(timeout()), this, SLOT(ComputeProteinLipidInteraction()) );

}

void MainWindow::initializeCLObjects()
{
    CLManager *clManager;

    m_CLManager = new CLManager;

    clManager = this->getCLManager();
    clManager->CLTask::InstallOpenCL();
    clManager->CLTask::SetTimerState( true );
    m_DataManager = new DataManager( clManager );

    this->getDataManager()->FetchGROData();

    m_Processing = new Processing( m_DataManager );

    this->initializeSignalsAndSlots();

    this->getTimer()->setInterval( 75 );


}

void MainWindow::initializeObjects()
{



}


void MainWindow::freeResources()
{
    if( this->getCLManager() != NULL )
    {
        delete m_CLManager;
        m_CLManager = NULL;
    }

    if(this->getDataManager() != NULL)
    {
        delete m_DataManager;
        m_DataManager = NULL;
    }

    if(this->getProcessing() != NULL)
    {
        delete m_Processing;
        m_Processing = NULL;
    }
    delete m_Timer;
}
