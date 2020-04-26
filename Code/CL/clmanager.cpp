#include "clmanager.h"

CLManager::CLManager()
{
    //this->initializeCLTask();
}

CLManager::~CLManager()
{
    //this->freeResources();
    //Debug( "CLManager freed");
}

/*
void CLManager::SetTimerState(bool state)
{
    this->getCLTask()->SetTimerState( state );
}

void CLManager::InstallCL()
{
    this->getCLTask()->InstallOpenCL();
}

void CLManager::CentralizeFrame(void *frame, float boxdimensionsX, float boxdimensionsY, float boxdimensionsZ, float minboxdimensionsX, float minboxdimensionsY, float minboxdimensionsZ, float maxboxdimensionsX, float maxboxdimensionsY, float maxboxdimensionsZ, unsigned int atomsnumber, unsigned int workitemssize, unsigned int localsize)
{
    this->getCLTask()->SetTimerState( true );
    this->getCLTask()->CentralizeFrame(frame
                                       , boxdimensionsX, boxdimensionsY, boxdimensionsZ
                                       , minboxdimensionsX, minboxdimensionsY, minboxdimensionsZ
                                       , maxboxdimensionsX, maxboxdimensionsY, maxboxdimensionsZ
                                       , atomsnumber, workitemssize, localsize );
    this->getCLTask()->SetTimerState( false );
}

void CLManager::ComputeProteinCOM(void *proteinspaces, void *proteinparticles, unsigned int proteinsnumber, unsigned int proteinparticlesnumber, unsigned int workitemssize, unsigned int localsize)
{
    this->getCLTask()->SetTimerState( true );
    this->getCLTask()->ComputeProteinCOM( proteinspaces, proteinparticles, proteinsnumber, proteinparticlesnumber, workitemssize, localsize );
    this->getCLTask()->SetTimerState( false );
}

void CLManager::ComputeLipidCOM(void *lipidspaces, void *lipidparticles, unsigned int lipidsnumber, unsigned int lipidparticlesnumber, unsigned int workitemssize, unsigned int localsize)
{
    this->getCLTask()->SetTimerState( true );
    this->getCLTask()->ComputeLipidCOM( lipidspaces, lipidparticles, lipidsnumber, lipidparticlesnumber, workitemssize, localsize );
    this->getCLTask()->SetTimerState( false );
}

void CLManager::ComputeProteinLipidInteraction(void *&frame, void *color, void *systemstructure, void *proteinspaces, void *proteinparticles, unsigned int atomsnumber, float interactiondistance, unsigned int workitemssize, unsigned int localsize)
{
    this->getCLTask()->SetTimerState( true );
    this->getCLTask()->ComputeProteinLipidInteraction( frame, color, systemstructure, proteinspaces, proteinparticles, atomsnumber, interactiondistance,  workitemssize, localsize );
    this->getCLTask()->SetTimerState( false );
}

void CLManager::ComputeProteinLipidInteractionOnTheFly(GLuint vertexbufferid, GLuint colorbufferid, void *systemstructure, void *proteinspaces, void *proteinparticles, unsigned int atomsnumber, float interactiondistance, unsigned int workitemssize, unsigned int localsize)
{
    this->getCLGLTask()->SetTimerState( true );
    this->getCLGLTask()->ComputeProteinLipidInteraction( vertexbufferid, colorbufferid, systemstructure, proteinspaces, proteinparticles, atomsnumber, interactiondistance,  workitemssize, localsize );
    this->getCLGLTask()->SetTimerState( false );
}

void CLManager::initializeCLTask()
{
    if( this->getCLTask() == NULL)
    {
        m_CLTask = new CLTask();
    }
}

void CLManager::initializeCLGLTask()
{

}

void CLManager::freeResources()
{
    if(this->getCLTask() != NULL )
    {
        delete m_CLTask;
        m_CLTask = NULL;
    }

    if(this->getCLGLTask() != NULL )
    {
        delete m_CLGLTask;
        m_CLGLTask = NULL;
    }
}
*/
