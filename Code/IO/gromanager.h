#ifndef GROMANAGER_H
#define GROMANAGER_H

#include "Memory/memorymanager.h"
#include <QFile>

/**
 * @brief The GROManager class handles the GRO file data
 * we deal with the gro file data as a a text line by line
 * So the data will be stored in QStringList object
 */
class GROManager : public virtual MemoryManager
{
public:
    /**
     * @brief GROManager class constructor
     */
    GROManager();

    /**
     * @brief FetchData fetches gro file data
     */
    void FetchData();

    /**
     * @brief FetchStructure fetches the molecules structure
     */
    void FetchStructure();

protected:

private:

    /**
     * @brief START_AT_00
     */
    static const int START_AT_00=0;

    /**
     * @brief START_AT_05
     */
    static const int START_AT_05=5;

    /**
     * @brief START_AT_10
     */
    static const int START_AT_10=10;

    /**
     * @brief START_AT_15
     */
    static const int START_AT_15=15;

    /**
     * @brief LENGHT_5
     */
    static const int LENGHT_5=5;

    /**
     * @brief m_GROData
     */
    static  QStringList m_GROData;

    /**
     * @brief getGROData gets a reference to the gro data
     * @return a reference to the gro data
     */
    inline static QStringList &getGROData() { return m_GROData; }

    /**
     * @brief setGROData sets the gro data
     * @param data specifies the gro data
     */
    static void setGROData(QString &data );

    /**
     * @brief computeProteinResidueID computes the protein residue ID
     * This function is responsible for computing the protein identity based on the apearnce of the protein in the data
     * @param currentMoleculeType specifies the current molecule type
     * @param proteinsParticlesNumber specifies the protein particle number
     * @param proteinResidueID specifies the protein residu number
     * @param residueNumber the residue number from the gro file
     */
    static void computeProteinResidueID(unsigned short currentMoleculeType, unsigned int &proteinsParticlesNumber, unsigned short &proteinResidueID , unsigned int residueNumber);

    /**
     * @brief computeLipidResidueID computes the lipid resideue identity based on the appearince of the lipid in the gro file
     * @param currentMoleculeType specifies the current mlecule type
     * @param lipidsParticlesNumber specifies the lipid particle number
     * @param lipidResidueID specifies the lipid residue id
     */
    static void computeLipidResidueID(unsigned short currentMoleculeType, unsigned int &lipidsParticlesNumber, unsigned short &lipidResidueID );

    /**
     * @brief checkProteinCounter chekes the protein counter
     * @param comstructure specifies the center of the massstructure
     * @param atomindex specifies the atom index
     * @param currentMoleculeType specifies the current molecule type
     * @param proteinsParticlesNumber specifies the protein particles number
     * @param proteinIndexCOM specifies the protein index in the center of mass structure
     */
    static void checkProteinCounter( COMStructureRecord *comstructure, unsigned int atomindex, unsigned short currentMoleculeType, unsigned int &proteinsParticlesNumber, unsigned int &proteinIndexCOM);

    /**
     * @brief checkLipidCounter checks the lipid counter
     * @param comstructure specifies the center of the massstructure
     * @param atomindex specifies the atom index
     * @param currentMoleculeType specifies the current molecule type
     * @param lipidsParticlesNumber specifies the lipid particle number
     * @param lipidResidueID specifies the lipid residue idenetity
     * @param lipidIndexCOM specifies the index of the lipid in the structure of the center of mass
     */
    static void checkLipidCounter(COMStructureRecord *comstructure, unsigned int atomindex, unsigned short currentMoleculeType, unsigned int &lipidsParticlesNumber, unsigned short &lipidResidueID , unsigned int &lipidIndexCOM);

    /**
     * @brief fetchData fetches the data from the gro file
     */
    static void fetchData();

    /**
     * @brief fetchSystemInformation fetches the system information
     */
    void fetchSystemInformation();

    /**
     * @brief fetchSystemStructure fetches the systen structure
     */
    void fetchSystemStructure();

    /**
     * @brief fetchAtomsNumber fetches the atoms nummbr
     */
    static void fetchAtomsNumber();

    /**
     * @brief fetchSystemDimentions fetches the system dimentions
     */
    static void fetchSystemDimentions();

    /**
     * @brief fetchStructure fetches the system structures
     */
    static void fetchStructure();

    /**
     * @brief fetchAtomInfo fetches curent atom info
     * @param detail specifies the atome detail
     * @param residuenumber a reference to the residue number. It will hold the residue number.
     * @param residuename a reference to  the residue name. It will hold the residue name
     * @param particlenumber a reference to the particle number. It will hold the particle number
     * @param particlename a reference to the particle name. It will hold the particle name
     * @param residuetag a reference to the residue tag.
     * I t will hold  aspecial tag (a combanation of residue name and residue number)
     */
    static void fetchAtomInfo(const QString &detail, unsigned int &residuenumber, QString &residuename,
                           unsigned int &particlenumber, QString &particlename,
                           QString &residuetag);


    /**
     * @brief fetchCurrentMoleculeInfo fetches the current molecule info.
     * @param lastresiduename specifies the name of the latest fetched residue
     * @param residuename specifies the current residue name
     * @param lastmoleculetype specifies the type of the latest fetched molecule
     * @param currentmoleculetype specifies the current molecule type
     * @param currentmoleculename specifies the current molecule name
     * @param currentmoleculeid specifies the current molecule id
     * @param identifier specifies a special identifier that is used to identifies the current molecule
     * @param residueparticlescounter specifies the counter of the current rasidue
     * @param isnewmolecule specifies the state of the input molecule whether it is new or we atill deal with the previous one.
     * @param residuecounter specifies the residue counter
     */
    static void fetchCurrentMoleculeInfo(QString &lastresiduename, QString residuename, unsigned short &lastmoleculetype,
                              unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                              short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[]);

    /**
     * @brief fetchPROTEINInfo fetches the protein info
     * @param lastresiduename specifies the lastes residue name
     * @param residuename specifies the current residue name
     * @param lastmoleculetype specifies the type of lates molecule
     * @param currentmoleculetype specifies the type of the current molecule
     * @param currentmoleculename specifies the name of the current molecule
     * @param currentmoleculeid specifies the id of the current molecule
     * @param identifier specifies a special identifier that is used to identifie the current molecule
     * @param residueparticlescounter specifies the counter of the residue particle
     * @param isnewmolecule specifies the state of the input molecule whether it is new or we atill deal with the previous one.
     * @param residuecounter specifies the residue counter
     */
    static void fetchPROTEINInfo(QString &lastresiduename, QString residuename, unsigned short &lastmoleculetype,
                          unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                          short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[], short residuecounter[]);

    /**
     * @brief fetchPOPEInfo fetches the POPE type info
     * @param lastmoleculetype specifies the type of the lates molecule of the input
     * @param currentmoleculetype specifies the type of the current molecule
     * @param currentmoleculename specifies the name of the current molecule
     * @param currentmoleculeid specifies the id of the current molecule
     * @param identifier specifies a special identifier that is used to identifie the current molecule
     * @param residueparticlescounter specifies the counter of the residue particle
     * @param isnewmolecule specifies the state of the input molecule whether it is new or we atill deal with the previous one.
     */
    static void fetchPOPEInfo(unsigned short &lastmoleculetype,
                          unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                          short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[]);

    /**
     * @brief fetchPOPGInfo fetches the POPG type info
     * @param lastmoleculetype specifies the type of the lates molecule of the input
     * @param currentmoleculetype specifies the type of the current molecule
     * @param currentmoleculename specifies the name of the current molecule
     * @param currentmoleculeid specifies the id of the current molecule
     * @param identifier specifies a special identifier that is used to identifie the current molecule
     * @param residueparticlescounter specifies the counter of the residue particle
     * @param isnewmolecule specifies the state of the input molecule whether it is new or we atill deal with the previous one.
     */
    static void fetchPOPGInfo(unsigned short &lastmoleculetype,
                          unsigned short &currentmoleculetype, QString &currentmoleculename, short &currentmoleculeid,
                          short identifier[], unsigned int residueparticlescounter[], bool isnewmolecule[]);

    /**
     * @brief setupSystemInformation sets up system information space by allocating a memory for
     * the SystemInformationRecord structure
     */
    static void setupSystemInformation();

    /**
     * @brief setupSystemStructure  sets up the system strcucture space by allocatin a memory for
     * the SystemStructureRecord structure
     * @param atomsnumber specifies the number of atom in the system
     * It is used to find the size of the structure in bytes
     */
    static void setupSystemStructure( unsigned int atomsnumber);

    /**
     * @brief setupCOMStructure  sets up the center of mass strcucture space by allocatin a memory for
     * the COMStructureRecord structure
     * @param comgroupsnumber specifies the number of groups in the center of mass  structure
     * It is used to find the size of the structure in bytes
     */
    static void setupCOMStructure( unsigned int comgroupsnumber );

    /**
     * @brief updateSystemDimentions updates the system dimentions
     * @param xDimention specifies the x dimention value
     * @param yDimention specifies the y dimention value
     * @param zDimention specifies the z dimention value
     */
    static void updateSystemDimentions(float xDimention, float yDimention, float zDimention);

    /**
     * @brief updateSystemStructureProteinRecord updates the protein recores in the system structure
     * @param systemstructure specifies the systm strcucture
     * @param comstructure specifies the center of mass structure
     * @param atomindex specifies the particle index
     * @param proteinmoleculeid specifies the id of the protein molecule
     * @param proteinresidueid specifies the id of the prptein residue
     * @param currentmoleculetype specifies the type of the current  molecule
     * @param proteinsparticlesnumber specifies the number of the protein particle
     * @param proteinindexcom specifies the index of the protein in the center of the mass structure
     */
    static void updateSystemStructureProteinRecord(SystemStructureRecord *systemstructure, COMStructureRecord *comstructure, unsigned int atomindex, unsigned short proteinmoleculeid, unsigned short proteinresidueid, unsigned short currentmoleculetype, unsigned int &proteinsparticlesnumber, unsigned int &proteinindexcom);

    /**
     * @brief updateSystemStructureLipidRecord updates the lipd record in the system structure
     * @param systemstructure specifies the system structure
     * @param comstructure specicfies the center of mass system structure
     * @param atomindex specifies the atom index
     * @param lipidmoleculeid specifies the id of the lipid molecule
     * @param currentmoleculetype specifies the type of the current molecule
     * @param lipidsparticlesnumber specifies the number of lipid particle
     * @param lipidresidueid specifies the id of the lipid residue
     * @param lipidindexcom specifies the index of the lipid in the center of mass structure
     */
    static void updateSystemStructureLipidRecord(SystemStructureRecord *systemstructure, COMStructureRecord *comstructure, unsigned int atomindex, unsigned short lipidmoleculeid, unsigned short currentmoleculetype, unsigned int &lipidsparticlesnumber, unsigned short &lipidresidueid , unsigned int &lipidindexcom);

    /**
     * @brief updateCOMStructureProteinRecord updates the protein record in the center of mass structure
     * @param comstructure specifies the center of mass structure
     * @param comgroupindex specifies the index of the protein the the center of mass structure
     * @param moleculetype specifies the type of the molecule
     * @param firstatom specifies the first atom index
     * @param comgroupatomsnumber specifies the number of particles per group
     */
    static void updateCOMStructureProteinRecord(COMStructureRecord *comstructure, unsigned int comgroupindex, unsigned short moleculetype, unsigned int firstatom, unsigned int comgroupatomsnumber);

    /**
     * @brief updateCOMStructureLipidRecord updates the lipid record in the center of mass structure
     * @param comstructure specifies the center of mass structure
     * @param comgroupindex specifies the index of lipid in the center of mass structure
     * @param moleculetype specifies the type of molecule
     * @param firstatom specifies the first atom index
     * @param comgroupatomsnumber specifies the number of particles per group
     */
    static void updateCOMStructureLipidRecord(COMStructureRecord *comstructure, unsigned int comgroupindex, unsigned short moleculetype, unsigned int firstatom, unsigned int comgroupatomsnumber);

    /**
     * @brief updateProteinResidueNameidentifierTable updates the protein residue namming identifier
     * @param currentmoleculetype specifies the type of the current molecule
     * @param residueid specifies the id of the residue
     * @param residuename specifies the name of the residue
     */
    static void updateProteinResidueNameidentifierTable(unsigned short currentmoleculetype, unsigned short residueid, QString residuename);

    /**
     * @brief updateLipidPOPEResidueNameidentifierTable updates the lipid POPE type namiing identifier
     * @param residuename specifies the name of the residue
     * @param residueid specifies the id of the residue
     * @param particlename specifies the name of the particle
     */
    static void updateLipidPOPEResidueNameidentifierTable(QString residuename, unsigned short residueid, QString particlename);

    /**
     * @brief updateLipidPOPGResidueNameidentifierTable updates the lipid POPG type namiing identifier
     * @param residuename specifies the name of the residue
     * @param residueid specifies the id of the residue
     * @param particlename specifies the name of the particle
     */
    static void updateLipidPOPGResidueNameidentifierTable(QString residuename, unsigned short residueid, QString particlename);

    /**
     * @brief removeGROHeader removes the header of the gro file
     */
    static void removeGROHeader();

    /**
     * @brief removeGROFooter removes the footer of the gro file
     */
    static void removeGROFooter();
};

#endif // GROMANAGER_H
