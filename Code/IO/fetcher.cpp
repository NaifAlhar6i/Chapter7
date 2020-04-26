#include <QFile>
#include "fetcher.h"

Fetcher::Fetcher()
{

}

void Fetcher::setGROData(const QString &data)
{
    m_GROData = data.split(QString("\n"));
}

void Fetcher::removeGROHeader()
{
    getGRODataRef().removeFirst(); //Description
    getGRODataRef().removeFirst(); //Details
}

void Fetcher::removeGROFooter()
{
    QString boxDimenssion;

    while(getGRODataRef().last() == "" )
        getGRODataRef().removeLast();  //Footer

    boxDimenssion = getGRODataRef().last();

    readBoxDimentions( boxDimenssion );

    getGRODataRef().removeLast();
}

void Fetcher::closeXTC()
{
    xdrfile_close( getXDRFileRef() );

}

void Fetcher::openXTC()
{
    m_XTC_Read = xdrfile_open( getXTCFilePath().data(), "r");
}

void Fetcher::fetchParticleInfo(const QString &detail, unsigned int &residuenumber, QString &residuename, unsigned int &particlenumber, QString &particlename, QString &residuetag)
{
    residuenumber = detail.mid( START_AT_00 , LENGHT_5 ).trimmed().toUInt();
    residuename = detail.mid( START_AT_05 , LENGHT_5 ).trimmed();
    particlename = detail.mid( START_AT_10, LENGHT_5 ).trimmed();
    particlenumber = detail.mid( START_AT_15, LENGHT_5 ).trimmed().toUInt();
    residuetag = QString("%1-%2").arg( residuename.trimmed() ).arg( residuenumber );
}

void Fetcher::fetchPROTEINInfo(QString &lastresiduename, QString residuename, MoleculeType &lastmoleculetype, MoleculeType &currentmoleculetype, QString &currentmoleculename,
                               short &currentmoleculeid, short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[])
{
    currentmoleculetype = PROTEIN;

    if( lastmoleculetype != PROTEIN )
    {
        identifier[PROTEIN]++;
        residueparticlescounter[PROTEIN] = Y;
        residuecounter[PROTEIN] = 0;
        lastresiduename ="";

    }
    else
    {
        if( residueparticlescounter[PROTEIN] >= PROTEIN_PARTICLES_NUMBER )
        {
            residueparticlescounter[PROTEIN] = Y;
            identifier[PROTEIN]++;
            residuecounter[PROTEIN] = 0;
            lastresiduename ="";

        }
        else
        {
            residueparticlescounter[PROTEIN]++;

        }
    }

    if( lastresiduename != residuename )
    {
        residuecounter[PROTEIN] ++;
        lastresiduename = residuename;

    }



    currentmoleculename = QString("PROTEIN%1").arg( identifier[PROTEIN] );
    currentmoleculeid = identifier[PROTEIN];
    isnewmolecule[PROTEIN] = false;
    isnewmolecule[POPE] = true;
    isnewmolecule[POPG] = true;
}

void Fetcher::fetchPOPEInfo(MoleculeType &lastmoleculetype,
                             MoleculeType &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                             short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[])
{

    currentmoleculetype = POPE;

    if( lastmoleculetype != POPE )
    {
        identifier[POPE]++;
        residueparticlescounter[POPE] = Y;
    }
    else
    {
        if( residueparticlescounter[POPE] >= LIPID_PARTICLES_NUMBER )
        {
            residueparticlescounter[POPE] = Y;
//            identifier[POPE]++;
//            qDebug()<< QString("POPE%1").arg( identifier[POPE] ) << " - >" << residueindex[POPE];

        }
        else
        {
            residueparticlescounter[POPE]++;
//            qDebug()<< QString("POPE%1").arg( identifier[POPE] ) << " - >" << residueindex[POPE];
        }
    }

    currentmoleculename = QString("POPE%1").arg( identifier[POPE] );
    currentmoleculeid = identifier[POPE];
    isnewmolecule[PROTEIN] = true;
    isnewmolecule[POPG] = true;
    isnewmolecule[POPE] = false;



}

void Fetcher::fetchPOPGInfo(MoleculeType &lastmoleculetype,
                            MoleculeType &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                            short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[])
{

    currentmoleculetype = POPG;


    if( lastmoleculetype != POPG )
    {
        identifier[POPG]++;
        residueparticlescounter[POPG] = Y;
    }
    else
    {
        if( residueparticlescounter[POPG] >= LIPID_PARTICLES_NUMBER )
        {
            residueparticlescounter[POPG] = Y;
//            identifier[POPE]++;
//            qDebug()<< QString("POPG%1").arg( identifier[POPG] ) << " - >" << residueindex[POPG];

        }
        else
        {
            residueparticlescounter[POPG]++;
//            qDebug()<< QString("POPG%1").arg( identifier[POPG] ) << " - >" << residueindex[POPG];
        }
    }
    currentmoleculename = QString("POPG%1").arg( identifier[POPG] );
    currentmoleculeid = identifier[POPG];
    isnewmolecule[PROTEIN] = true;
    isnewmolecule[POPE] = true;
    isnewmolecule[POPG] = false;

}

void Fetcher::FetchGRO()
{

    QFile groFileIO( getStrGROFilePath() );
    QString groFileData;

    if(groFileIO.open(QIODevice::ReadOnly))
    {

        groFileData = groFileIO.readAll();
        groFileIO.close();

        setGROData( groFileData );

        removeGROHeader();
        removeGROFooter();

    }
}

void Fetcher::FetchFrame(rvec *&frame, unsigned int frameindex)
{

}

void Fetcher::FetchPaths(rvec *&paths, unsigned &lastPathsNumber, QList<unsigned int> particleslist)
{

}

void Fetcher::readBoxDimentions(const QString &data)
{
    QStringList dataStringList= data.split(" ");

    for(unsigned int lineIndex= UINT_ZERO; lineIndex < dataStringList.size(); lineIndex++)
    {

        if (dataStringList.at( lineIndex ) == "")
        {
            dataStringList.removeOne( dataStringList.at( lineIndex ) );
        }
    }

    this->getTrajectoryInfoRef().BoxDimensions[ X ] = dataStringList.at( UINT_ZERO ).toFloat();
    this->getTrajectoryInfoRef().BoxDimensions[ Y ] = dataStringList.at( UINT_ONE ).toFloat();
    this->getTrajectoryInfoRef().BoxDimensions[ Z ] = dataStringList.at( UINT_TWO ).toFloat();

    dataStringList.clear();
}

void Fetcher::fetchCurrentMoleculeInfo(QString &lastresiduename, QString residuename, MoleculeType &lastmoleculetype, MoleculeType &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                                       short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[])
{

    if( residuename.trimmed() == POPE_NAME )
    {
        this->fetchPOPEInfo( lastmoleculetype, currentmoleculetype, currentmoleculename, currentmoleculeid, identifier, residueparticlescounter, isnewmolecule );
    }
    else if(residuename.trimmed() == POPG_NAME)
    {
        this->fetchPOPGInfo( lastmoleculetype, currentmoleculetype, currentmoleculename, currentmoleculeid, identifier, residueparticlescounter, isnewmolecule );
    }
    else
    {

        this->fetchPROTEINInfo( lastresiduename, residuename, lastmoleculetype,
                                currentmoleculetype, currentmoleculename, currentmoleculeid,
                                identifier, residueparticlescounter, isnewmolecule, residuecounter );
    }

}
