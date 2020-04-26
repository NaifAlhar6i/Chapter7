#ifndef FETCHER_H
#define FETCHER_H

#include <QStringList>
#include <QLinkedList>


#include "include/constdata.h"

class Fetcher
{
public:
    Fetcher();

    inline TrajectoryInformation &GetTrajectoryInfoRef() { return m_TrajectoryInfo; }

    /**
     * @brief setGROFilePath
     * @param gro
     */
    inline void SetGROFilePath(const QString &gro) { m_GROFilePath = gro;}

    /**
     * @brief setXTCFilePath
     * @param xtc
     */
    inline void SetXTCFilePath(const QString &xtc) { m_XTCFilePath = xtc;}

    void FetchGRO();

    void FetchFrame( rvec *&frame, unsigned int frameindex );
    void FetchPaths(rvec *&paths, unsigned &lastPathsNumber, QList<unsigned int> particleslist);


protected:

    inline XDRFILE *getXDRFileRef() { return m_XTC_Read; }

    /**
     * @brief getGROFilePath
     * @return
     */
    inline QByteArray getGROFilePath() {
        QByteArray ba = m_GROFilePath.toLatin1();
        return ba;
    }

    inline TrajectoryInformation &getTrajectoryInfoRef() { return m_TrajectoryInfo; }

    /**
     * @brief getXTCFilePath
     * @return
     */
    inline QByteArray getXTCFilePath() {
        QByteArray ba = m_XTCFilePath.toLatin1();
        return ba;
    }

    /**
     * @brief getStrGROFilePath
     * @return
     */
    inline const QString getStrGROFilePath( void ) { return m_GROFilePath; }

    /**
     * @brief getStrXTCFilePath
     * @return
     */
    inline const QString getStrXTCFilePath( void ) { return m_XTCFilePath; }

    /**
     * @brief getGROData accessor
     * @return the GRO file string list.
     */
    inline QStringList &getGRODataRef() { return m_GROData; }


    /**
     * @brief setGROData accessor to update the m_GROData variable
     * @param data reference to the gro data
     */
    void setGROData(const QString &data);

    /**
     * @brief removeGROHeader removes the gro file's header
     */
    void removeGROHeader();

    /**
     * @brief removeGROFooter removes the gro file's footer
     */
    void removeGROFooter();

    /**
     * @brief closeXTC
     */
    void closeXTC();
    /**
     * @brief openXTC
     */
    void openXTC();

    void fetchParticleInfo(const QString &detail, unsigned int &residuenumber, QString &residuename,
                           unsigned int &particlenumber, QString &particlename,
                           QString &residuetag);

    void fetchCurrentMoleculeInfo(QString &lastresiduename, QString residuename, MoleculeType &lastmoleculetype,
                              MoleculeType &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                              short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[]);

    void fetchPROTEINInfo(QString &lastresiduename, QString residuename, MoleculeType &lastmoleculetype,
                          MoleculeType &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                          short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[]);

    void fetchPOPEInfo(MoleculeType &lastmoleculetype,
                          MoleculeType &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                          short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[]);

    void fetchPOPGInfo(MoleculeType &lastmoleculetype,
                          MoleculeType &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                          short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[]);
private:
    const int ONE = 1 ;
    const int TWO = 2 ;
    const int THREE = 3 ;

    const int START_AT_00=0;
    const int START_AT_05=5;
    const int START_AT_10=10;
    const int START_AT_15=15;
    const int LENGHT_5=5;

    TrajectoryInformation m_TrajectoryInfo;

    /**
     * @brief m_GROFilePath
     */
    QString m_GROFilePath;

    /**
     * @brief m_XTCFilePath
     */
    QString m_XTCFilePath;

    /**
     * @brief m_GROData
     */
    QStringList m_GROData;

    /**
     * @brief m_XTC_Read
     */
    XDRFILE *m_XTC_Read;

    /**
     * @brief readBoxDimentions
     * @param data
     */
    void readBoxDimentions( const QString &data );

};


#endif // FETCHER_H
