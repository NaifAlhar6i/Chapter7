#include "gromanager.h"

QStringList GROManager::m_GROData;

GROManager::GROManager()
{

}

void GROManager::FetchData()
{
    unsigned int atomsNumber;
    unsigned int comGroupsNumber;

    setupSystemInformation();

    fetchData();

    atomsNumber = DataStructure::getSystemInformation()->getAtomsNumber();

    setupSystemStructure( atomsNumber );

    comGroupsNumber = COM_GROUPS_NUMBER;

    setupCOMStructure( comGroupsNumber );

}

void GROManager::FetchStructure()
{
    fetchStructure();
}

void GROManager::setGROData(QString &data)
{
    m_GROData = data.split(QString(NEW_LINE));
}

void GROManager::computeProteinResidueID(unsigned short currentMoleculeType, unsigned int &proteinsParticlesNumber, unsigned short &proteinResidueID, unsigned int residueNumber)
{

    if( currentMoleculeType == PROTEIN_MOLECULE_0 ) {
        proteinsParticlesNumber++;
        proteinResidueID = (unsigned short)residueNumber;

        SystemStructureRecord *systemStructure;
        systemStructure  = DataStructure::getSystemStructure();
    }
}

void GROManager::computeLipidResidueID(unsigned short currentMoleculeType, unsigned int &lipidsParticlesNumber, unsigned short &lipidResidueID)
{
    if( currentMoleculeType != PROTEIN_MOLECULE_0 )
    {
       lipidsParticlesNumber++;
       /* We use special lipid residue counter as the GRO file provide us with different value*/
       lipidResidueID ++;
    }
}

void GROManager::checkProteinCounter(COMStructureRecord *comstructure, unsigned int atomindex, unsigned short currentMoleculeType, unsigned int &proteinsParticlesNumber, unsigned int &proteinIndexCOM)
{
    unsigned int firstAtom;

    if( currentMoleculeType == PROTEIN_MOLECULE_0 ) {

        if( proteinsParticlesNumber % PROTEIN_PARTICLES_NUMBER  == UINT_ZERO)
        {

            //This condition just to start the proteins index @ ZERO
            if(atomindex >= PROTEIN_PARTICLES_NUMBER )
            {
                proteinIndexCOM++;
            }
            firstAtom = atomindex - PROTEIN_PARTICLES_UPPER_BOUNDARY;
            updateCOMStructureProteinRecord(comstructure, proteinIndexCOM, currentMoleculeType, firstAtom, PROTEIN_PARTICLES_NUMBER);
        }
    }
}

void GROManager::checkLipidCounter( COMStructureRecord *comstructure, unsigned int atomindex, unsigned short currentMoleculeType, unsigned int &lipidsParticlesNumber, unsigned short &lipidResidueID, unsigned int &lipidIndexCOM)
{
    unsigned int firstAtom;

    if( currentMoleculeType != PROTEIN_MOLECULE_0 )
    {
       //The lipids index in the COM file start @ 256.
       if( lipidsParticlesNumber % LIPID_PARTICLES_NUMBER  == UINT_ZERO)
       {
           lipidResidueID = UINT_ZERO;
           lipidIndexCOM++;
           firstAtom = atomindex - LIPID_PARTICLES_UPPER_BOUNDARY;
           updateCOMStructureLipidRecord(comstructure, lipidIndexCOM, currentMoleculeType, firstAtom, LIPID_PARTICLES_NUMBER);
//           qDebug() << "Atom Index->" << atomindex << "Lipid COM index- >" << lipidIndexCOM;
       }
    }
}

void GROManager::fetchData()
{
    QFile groFileIO( DATA_DIRECTORY + GRO_FILE );
    QString groFileData;

    if(groFileIO.open(QIODevice::ReadOnly))
    {

        groFileData = groFileIO.readAll();
        groFileIO.close();

        setGROData( groFileData );

        removeGROHeader();  //First line
        fetchAtomsNumber();
        removeGROHeader();  //First line
        removeGROFooter();
        fetchSystemDimentions();
    }
}

void GROManager::fetchSystemInformation()
{

}

void GROManager::fetchSystemStructure()
{

}

void GROManager::removeGROHeader()
{
    getGROData().removeFirst();
}

void GROManager::removeGROFooter()
{
    while(getGROData().last() == EMPTY_STRING )
        getGROData().removeLast();  //Footer
}

void GROManager::fetchAtomsNumber()
{
    SystemInformationRecord *systemInformation;
    QString atomsNumber;

    systemInformation = DataStructure::getSystemInformation();

    atomsNumber = getGROData().first();
    systemInformation->setAtomsNumber( atomsNumber.toUInt() );
}

void GROManager::fetchSystemDimentions()
{
    QStringList dataStringList;
    QString boxDimenssions;

    float xDimention;
    float yDimention;
    float zDimention;

    boxDimenssions = getGROData().last();

    dataStringList = boxDimenssions.split( SINGLE_SPACE );

    for(unsigned short lineIndex= USHORT_ZERO; lineIndex < dataStringList.size(); lineIndex++)
    {
        if (dataStringList.at( lineIndex ) == EMPTY_STRING )
        {
            dataStringList.removeOne( dataStringList.at( lineIndex ) );
        }
    }

    xDimention = dataStringList.at( X ).toFloat();
    yDimention = dataStringList.at( Y ).toFloat();
    zDimention = dataStringList.at( Z ).toFloat();

    updateSystemDimentions( xDimention, yDimention, zDimention );

    dataStringList.clear();
    getGROData().removeLast();
}

void GROManager::fetchStructure()
{
    SystemStructureRecord *systemStructure;
    COMStructureRecord *comStructure;

    unsigned short lastMoleculeType;
    unsigned int particlesNumber;
    QString lastResidueName ;
    QString currentMoleculeName;
    short moleculeIdentifier[ UINT_THREE ] = { -1, -1, -1 }; // to start by ZERO
    unsigned int residueParticlesCounter[ UINT_THREE ] = { UINT_ONE, UINT_ONE, UINT_ONE };
    bool isNewMolecule[ UINT_THREE ] = {false, false, false};
    short residueCounter[ UINT_THREE ] = { 0, 0, 0 };
    unsigned int residueNumber;
    QString residueName;
    unsigned int particleNumber;
    QString particleName;
    QString residueTag;

    unsigned int proteinsParticlesNumber(UINT_ZERO);
    unsigned short proteinResidueID(UINT_ZERO );
    unsigned short lipidResidueID(UINT_ZERO );

    unsigned int lipidsParticlesNumber(UINT_ZERO);
    unsigned int proteinIndexCOM(UINT_ZERO);
    unsigned int lipidIndexCOM( PROTEIN_INDEX_UPPER_BOUNDARY );
    lastResidueName = EMPTY_STRING;
    lastMoleculeType = MOLECULE_UNDEFINED;

    particlesNumber = ATOMS_NUMBER ;

    systemStructure = DataStructure::getSystemStructure();
    comStructure = DataStructure::getCOMStructure();

    for( unsigned int atomIndex = UINT_ZERO; atomIndex < particlesNumber; atomIndex++)
    {
        const QString detail = getGROData().at( atomIndex );
        unsigned short currentMoleculeType;
        short currentMoleculeID;

        fetchAtomInfo( detail, residueNumber, residueName, particleNumber, particleName, residueTag );

        fetchCurrentMoleculeInfo( lastResidueName, residueName, lastMoleculeType, currentMoleculeType, currentMoleculeName,
                                           currentMoleculeID, moleculeIdentifier, residueParticlesCounter, isNewMolecule, residueCounter );


        //computing the correct Protein Residue ID and return the protein Index in the COM file.
        computeProteinResidueID(currentMoleculeType, proteinsParticlesNumber, proteinResidueID , residueNumber);
        //computing the correct Lipid residue ID and return the lipid index in the COM file.
        computeLipidResidueID(currentMoleculeType, lipidsParticlesNumber, lipidResidueID);

        //Update lookup table
        updateProteinResidueNameidentifierTable(currentMoleculeType, residueNumber, residueName );
        //residue name here is either POPE or POPG and particle name is the real residue :)
        updateLipidPOPEResidueNameidentifierTable(residueName, lipidResidueID, particleName );
        updateLipidPOPGResidueNameidentifierTable(residueName, lipidResidueID, particleName );

        //Update system structure records
        updateSystemStructureProteinRecord( systemStructure, comStructure, atomIndex, currentMoleculeID, proteinResidueID, currentMoleculeType, proteinsParticlesNumber, proteinIndexCOM );
        updateSystemStructureLipidRecord( systemStructure, comStructure, atomIndex, currentMoleculeID, currentMoleculeType, lipidsParticlesNumber, lipidResidueID , lipidIndexCOM );

        lastMoleculeType = currentMoleculeType;
    }

    //for(unsigned int index = UINT_ZERO; index< PARTICLES_NUMBER; index++)
    //{
    //    if(index < PARTICLES_NUMBER)
    //        qDebug() << "AtomIndex ->" << (systemStructure+index)->getAtomIndex() << " Molecule index ->" << (systemStructure+index)->getMoleculeIndex() << " Residue Index ->" << (systemStructure+index)->getMoleculeResidueIndex();
    //}

    //for(unsigned int index = UINT_ZERO; index< COM_GROUPS_NUMBER; index++)
    //{
    //        qDebug() << "Group Index ->" << (comStructure+index)->getCOMGroupIndex() << " First Atom Index ->" << (comStructure+index)->getFirstAtomIndex() << " Group Atoms Number ->" << (comStructure+index)->getCOMGroupAtomsNumber();
    //}

    getGROData().clear();
}

void GROManager::fetchAtomInfo(const QString &detail, unsigned int &residuenumber, QString &residuename, unsigned int &particlenumber, QString &particlename, QString &residuetag)
{
    residuenumber = detail.mid( START_AT_00 , LENGHT_5 ).trimmed().toUInt();
    residuename = detail.mid( START_AT_05 , LENGHT_5 ).trimmed();
    particlename = detail.mid( START_AT_10, LENGHT_5 ).trimmed();
    particlenumber = detail.mid( START_AT_15, LENGHT_5 ).trimmed().toUInt();
    residuetag = QString("%1-%2").arg( residuename.trimmed() ).arg( residuenumber );
}

void GROManager::fetchCurrentMoleculeInfo(QString &lastresiduename, QString residuename, unsigned short &lastmoleculetype, unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                                          short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[])
{
    if( residuename.trimmed() == POPE_NAME || residuename.trimmed() == POPG_NAME)
    {
        fetchPOPEInfo( lastmoleculetype, currentmoleculetype, currentmoleculename, currentmoleculeid, identifier, residueparticlescounter, isnewmolecule );
    }
    else if(residuename.trimmed() == POPG_NAME) // It should be removed
    {
        fetchPOPGInfo( lastmoleculetype, currentmoleculetype, currentmoleculename, currentmoleculeid, identifier, residueparticlescounter, isnewmolecule);
    }
    else
    {
        fetchPROTEINInfo( lastresiduename, residuename, lastmoleculetype, currentmoleculetype, currentmoleculename, currentmoleculeid, identifier, residueparticlescounter, isnewmolecule, residuecounter );
    }

}

void GROManager::fetchPROTEINInfo(QString &lastresiduename, QString residuename, unsigned short &lastmoleculetype, unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid, short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[])
{
    currentmoleculetype = PROTEIN_MOLECULE_0;

    if( lastmoleculetype != PROTEIN_MOLECULE_0 )
    {
        identifier[PROTEIN_MOLECULE_0]++;
        residueparticlescounter[PROTEIN_MOLECULE_0] = UINT_ONE;
        residuecounter[PROTEIN_MOLECULE_0] = 0;
        lastresiduename = EMPTY_STRING;

    }
    else
    {
        if( residueparticlescounter[PROTEIN_MOLECULE_0] >= PROTEIN_PARTICLES_NUMBER )
        {
            residueparticlescounter[PROTEIN_MOLECULE_0] = UINT_ONE;
            identifier[PROTEIN_MOLECULE_0]++;
            residuecounter[PROTEIN_MOLECULE_0] = 0;
            lastresiduename =EMPTY_STRING;

        }
        else
        {
            residueparticlescounter[PROTEIN_MOLECULE_0]++;

        }
    }

    if( lastresiduename != residuename )
    {
        residuecounter[PROTEIN_MOLECULE_0] ++;
        lastresiduename = residuename;
    }

    currentmoleculename = QString("PROTEIN%1").arg( identifier[PROTEIN_MOLECULE_0] );
    currentmoleculeid = identifier[PROTEIN_MOLECULE_0];
    isnewmolecule[PROTEIN_MOLECULE_0] = false;
    isnewmolecule[LIPID_MOLECULE_POPE] = true;
    isnewmolecule[LIPID_MOLECULE_POPG] = true;
}

void GROManager::fetchPOPEInfo(unsigned short &lastmoleculetype, unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid, short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[])
{
    currentmoleculetype = LIPID_MOLECULE_POPE;

    if( lastmoleculetype != LIPID_MOLECULE_POPE )
    {
        identifier[LIPID_MOLECULE_POPE]++;
        residueparticlescounter[LIPID_MOLECULE_POPE] = UINT_ONE;
    }
    else
    {
        if( residueparticlescounter[LIPID_MOLECULE_POPE] >= LIPID_PARTICLES_NUMBER )
        {
            residueparticlescounter[LIPID_MOLECULE_POPE] = UINT_ONE;
            identifier[LIPID_MOLECULE_POPE]++;
        }
        else
        {
            residueparticlescounter[LIPID_MOLECULE_POPE]++;
        }
    }

    currentmoleculename = QString("POPE%1").arg( identifier[LIPID_MOLECULE_POPE] );
    currentmoleculeid = identifier[LIPID_MOLECULE_POPE];
    isnewmolecule[PROTEIN_MOLECULE_0] = true;
    isnewmolecule[LIPID_MOLECULE_POPE] = false;
    isnewmolecule[LIPID_MOLECULE_POPG] = true;
}

void GROManager::fetchPOPGInfo(unsigned short &lastmoleculetype, unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid, short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[])
{
    currentmoleculetype = LIPID_MOLECULE_POPG;

    if( lastmoleculetype != LIPID_MOLECULE_POPG )
    {
        identifier[LIPID_MOLECULE_POPG]++;
        residueparticlescounter[LIPID_MOLECULE_POPG] = UINT_ONE;
    }
    else
    {
        if( residueparticlescounter[LIPID_MOLECULE_POPG] >= LIPID_PARTICLES_NUMBER )
        {
            residueparticlescounter[LIPID_MOLECULE_POPG] = UINT_ONE;
            identifier[LIPID_MOLECULE_POPG]++;
        }
        else
        {
            residueparticlescounter[LIPID_MOLECULE_POPG]++;
        }
    }

    currentmoleculename = QString("POPG%1").arg( identifier[LIPID_MOLECULE_POPG] );
    currentmoleculeid = identifier[LIPID_MOLECULE_POPG];
    isnewmolecule[PROTEIN_MOLECULE_0] = true;
    isnewmolecule[LIPID_MOLECULE_POPE] = true;
    isnewmolecule[LIPID_MOLECULE_POPG] = false;
}

void GROManager::setupSystemInformation()
{
    bool allocated;

    // Allocate system information space
    allocated = DataStructure::allocateSystemInformationSpace();

    if( !allocated )
    {
        qDebug() << "Memory allocation error";
        return;
    }
}

void GROManager::setupSystemStructure(unsigned int atomsnumber)
{
    bool allocated;
    //Allocate system structure space
    allocated = DataStructure::allocateSystemStructureSpace( atomsnumber );
    if( !allocated )
    {
        qDebug() << "Memory allocation error";
        return;
    }
}

void GROManager::setupCOMStructure(unsigned int comgroupsnumber)
{
    bool allocated;
    //Allocate COM Structure space
    allocated = DataStructure::allocateCOMStructureSpace( comgroupsnumber );
    if(!allocated)
    {
        qDebug() << " COM Memory allocated error!";
        return;
    }
}

void GROManager::updateSystemDimentions(float xDimention, float yDimention, float zDimention)
{
    QVector3D dimentions;

    dimentions.setX( xDimention );
    dimentions.setY( yDimention );
    dimentions.setZ( zDimention );

    SystemInformationRecord *systemInformation;
    systemInformation = DataStructure::getSystemInformation();
    systemInformation->setDimentions( dimentions );
}

void GROManager::updateSystemStructureProteinRecord(SystemStructureRecord *systemstructure, COMStructureRecord *comstructure, unsigned int atomindex, unsigned short proteinmoleculeid, unsigned short proteinresidueid, unsigned short currentmoleculetype, unsigned int &proteinsparticlesnumber, unsigned int &proteinindexcom)
{
    unsigned short molecularResidueIndex;

    if(currentmoleculetype == PROTEIN_MOLECULE_0)
    {
        molecularResidueIndex = proteinresidueid - USHORT_ONE;// We need zero-based IDs

        ( systemstructure + atomindex )->setAtomIndex( atomindex );
        ( systemstructure + atomindex )->setMoleculeIndex( proteinmoleculeid);
        ( systemstructure + atomindex )->setMoleculeType( currentmoleculetype );
        ( systemstructure + atomindex )->setMoleculeResidueIndex( molecularResidueIndex );

        checkProteinCounter(comstructure, atomindex, currentmoleculetype, proteinsparticlesnumber, proteinindexcom);

    }

}

void GROManager::updateSystemStructureLipidRecord(SystemStructureRecord *systemstructure, COMStructureRecord *comstructure, unsigned int atomindex, unsigned short lipidmoleculeid, unsigned short currentmoleculetype, unsigned int &lipidsparticlesnumber, unsigned short &lipidresidueid, unsigned int &lipidindexcom)
{
    unsigned short molecularResidueIndex;

    if(currentmoleculetype != PROTEIN_MOLECULE_0)
    {

        molecularResidueIndex = lipidresidueid - USHORT_ONE;// We need zero-based IDs

        (systemstructure + atomindex )->setAtomIndex( atomindex );
        (systemstructure + atomindex )->setMoleculeIndex( lipidmoleculeid);
        (systemstructure + atomindex )->setMoleculeType( currentmoleculetype );
        (systemstructure + atomindex )->setMoleculeResidueIndex( molecularResidueIndex );

        //Reset the residue counters
        checkLipidCounter( comstructure, atomindex, currentmoleculetype, lipidsparticlesnumber, lipidresidueid , lipidindexcom);

    }

}

void GROManager::updateCOMStructureProteinRecord(COMStructureRecord *comstructure, unsigned int comgroupindex, unsigned short moleculetype, unsigned int firstatom, unsigned int comgroupatomsnumber)
{

    (comstructure + comgroupindex)->setCOMGroupIndex( comgroupindex );
    (comstructure + comgroupindex)->setMoleculeType( moleculetype );
    (comstructure + comgroupindex)->setFirstAtomIndex( firstatom );
    (comstructure + comgroupindex)->setCOMGroupAtomsNumber( comgroupatomsnumber );

}

void GROManager::updateCOMStructureLipidRecord(COMStructureRecord *comstructure, unsigned int comgroupindex, unsigned short moleculetype, unsigned int firstatom, unsigned int comgroupatomsnumber)
{
    (comstructure + comgroupindex)->setCOMGroupIndex( comgroupindex );
    (comstructure + comgroupindex)->setMoleculeType( moleculetype );
    (comstructure + comgroupindex)->setFirstAtomIndex( firstatom );
    (comstructure + comgroupindex)->setCOMGroupAtomsNumber( comgroupatomsnumber );
}

void GROManager::updateProteinResidueNameidentifierTable(unsigned short currentmoleculetype, unsigned short residueid, QString residuename)
{
    unsigned short residueIndex;
    if(currentmoleculetype == PROTEIN_MOLECULE_0)
    {
        residueIndex = residueid - USHORT_ONE;
        if( !DataStructure::getProteinResidueIdentifierTable().contains( residueIndex ) )
        {
            DataStructure::getProteinResidueIdentifierTable().insert( residueIndex, residuename );
        }
    }
}

void GROManager::updateLipidPOPEResidueNameidentifierTable(QString residuename, unsigned short residueid, QString particlename)
{
    unsigned short residueIndex;

    if(residuename == POPE_NAME)
    {
        residueIndex = residueid - USHORT_ONE;
        if( !DataStructure::getLipidPOPEResidueIdentifierTable().contains( residueIndex ) )
        {
            DataStructure::getLipidPOPEResidueIdentifierTable().insert( residueIndex, particlename );
        }
    }
}

void GROManager::updateLipidPOPGResidueNameidentifierTable(QString residuename, unsigned short residueid, QString particlename)
{
    unsigned short residueIndex;

    if(residuename == POPG_NAME)
    {
        residueIndex = residueid - USHORT_ONE;

        if( !DataStructure::getLipidPOPGResidueIdentifierTable().contains( residueIndex ) )
        {
            DataStructure::getLipidPOPGResidueIdentifierTable().insert( residueIndex, particlename );
        }
    }
}
