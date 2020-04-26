#include "processing.h"

Processing::Processing(DataManager *datamanager): m_DataManager(datamanager)
{

}

void Processing::FetchXTCData(bool)
{
    qDebug() << "FetchXYC";
    return;

    this->getDataManager()->SetProcessingState( true );

    this->getDataManager()->FetchXTCFrames(0, 3 /*FRAMES_NUMBER*/, 0);

    this->getDataManager()->SetProcessingState( false );
}

void Processing::GenerateAtomsPath(bool)
{
    qDebug() << "GenerateAtomsPath";
    return;
    this->getDataManager()->SetProcessingState( true );

    this->getDataManager()->GenerateAtomsPathFile(RVEC_SIZE, ATOMS_NUMBER, FRAMES_NUMBER);

    this->getDataManager()->SetProcessingState( false );
}

void Processing::ComputeCenterOfMass(bool)
{
    qDebug() << "ComputeCenterOfMass";
    return;
    this->getDataManager()->SetProcessingState( true );
    for(unsigned int frameIndex = UINT_ZERO; frameIndex < FRAMES_NUMBER; frameIndex++)
    {
        this->getDataManager()->ComputeProteinCOM( frameIndex );
        this->getDataManager()->ComputeLipidCOM( frameIndex );
    }

    this->getDataManager()->SetProcessingState( false );
}

void Processing::GenerateCOMAtomsPath(bool)
{
    qDebug() << "GenerateCOMAtomsPath";
    return;
    this->getDataManager()->SetProcessingState( true );

    this->getDataManager()->GenerateCOMAtomsPathFile(RVEC_SIZE, COM_GROUPS_NUMBER, FRAMES_NUMBER);

    this->getDataManager()->SetProcessingState( false );
}

void Processing::ComputeProteinLipidInteractionSingleFrame(bool)
{
    qDebug() << " Compute protein lipid interaction!";
    return;
    this->getDataManager()->ComputeProteinLipidInteraction( 0, false );
}

