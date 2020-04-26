#ifndef PROCESSING_H
#define PROCESSING_H

#include <QObject>
#include "include/constdata.h"
#include "IO/datamanager.h"

/**
 * @brief The Processing class interfaces the processing functualities
 */
class Processing : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Processing class constrtucture
     * @param datamanager specifies the DataManager object
     */
    Processing( DataManager *datamanager);
public slots:
    /**
     * @brief FetchXTCData fetches the frames from the XTC file
     */
    void FetchXTCData(bool);

    /**
     * @brief GenerateAtomsPath generated atoms path
     */
    void GenerateAtomsPath(bool);

    /**
     * @brief ComputeCenterOfMass comptes the center of mass of proteins aand lipids
     */
    void ComputeCenterOfMass(bool);

    /**
     * @brief GenerateCOMAtomsPath generates the center of mass of atoms path
     */
    void GenerateCOMAtomsPath(bool);

    /**
     * @brief ComputeProteinLipidInteractionSingleFrame computes proteins lipids interactions per frame
     */
    void ComputeProteinLipidInteractionSingleFrame(bool);

private:

    /**
     * @brief m_DataManager DataManager object
     */
    DataManager *m_DataManager;

    /**
     * @brief getDataManager gets a pointer to the DataManager object
     * @return
     */
    inline DataManager *getDataManager() { return m_DataManager; }

};

#endif // PROCESSING_H
