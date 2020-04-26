#ifndef CONSTDATA_H
#define CONSTDATA_H

#include "Helper/debugger.h"
#include "include/glheaders.h"
#include "include/clheaders.h"
#include "IO/xdrfile.h"
#include "structure.h"

//Global
const unsigned short USHORT_ZERO = 0;
const unsigned short USHORT_ONE = 1;
const unsigned short USHORT_TWO = 2;
const unsigned int UINT_ZERO = 0;
const unsigned int UINT_ONE = 1;
const unsigned int UINT_TWO = 2;
const unsigned int UINT_THREE = 3;
const unsigned int UINT_TEN = 100;
const unsigned int X = 0;
const unsigned int Y = 1;
const unsigned int Z = 2;
const unsigned int W = 3;
const int HANDRED = 100;
const float THOUSAND = 1000.0f;
const size_t ZERO_OFFSET = 0;
const QString EMPTY_STRING = "";
const QString SINGLE_SPACE = " ";
const QString NEW_LINE = "\n";

//System
const unsigned int FRAMES_NUMBER = 1981;
const unsigned short PROTEIN_MOLECULE_0 = 0;
const unsigned short LIPID_MOLECULE_POPE = 1;
const unsigned short LIPID_MOLECULE_POPG = 2;
const unsigned short MOLECULE_UNDEFINED = 500;
const unsigned int PROTEINS_NUMBER = 256;
const unsigned int LIPIDS_NUMBER = 19092;
const unsigned int COM_GROUPS_NUMBER = PROTEINS_NUMBER + LIPIDS_NUMBER;
const unsigned int ATOMS_NUMBER = 336260;
const unsigned int PROTEIN_PARTICLES_NUMBER = 344;
const unsigned int PROTEIN_PARTICLES_UPPER_BOUNDARY = 343;
const unsigned int PROTEIN_RESIDUES_NUMBER = 171;
const unsigned int LIPID_PARTICLES_NUMBER = 13;
const unsigned int LIPID_PARTICLES_UPPER_BOUNDARY = 12;
const unsigned int PROTEIN_SPACE_ORIGIN_INDEX = 0;
const unsigned int PROTEIN_INDEX_LOWER_BOUNDARY = 0;
const unsigned int PROTEIN_INDEX_UPPER_BOUNDARY = 255;
const unsigned int PROTEIN_BROWSER_MAX_NUMBER = 8;
const unsigned int PROTEIN_BROWSER_THRESHOLD = PROTEINS_NUMBER - PROTEIN_BROWSER_MAX_NUMBER;
const unsigned int RVEC_SIZE = sizeof(rvec);
const long PATH_SIZE = RVEC_SIZE * FRAMES_NUMBER;
const long FRAME_SIZE = RVEC_SIZE * ATOMS_NUMBER;
const long COM_PATH_SIZE = PATH_SIZE;
const long COM_FRAME_SIZE = RVEC_SIZE * COM_GROUPS_NUMBER;
const long ONE_TENTH_OF_ATOMS = ATOMS_NUMBER / UINT_TEN;
const long ONE_TENTH_OF_FRAMES = FRAMES_NUMBER / UINT_TEN;
const long SYSTEME_ALIGNMENT = 4096;      // 195156 * 4096 = size of ~33k paths (Original 799357272 bytes)
const long ONE_TENTH_PATH_SIZE = ONE_TENTH_OF_ATOMS * PATH_SIZE;      // (799357272 bytes)
const long ONE_TENTH_FRAME_SIZE = ONE_TENTH_OF_FRAMES * FRAME_SIZE;      //
const long PATH_MAP_PAGE_SIZE = (( ONE_TENTH_PATH_SIZE / SYSTEME_ALIGNMENT) * SYSTEME_ALIGNMENT) + ( UINT_TWO * SYSTEME_ALIGNMENT);      //size of ~33k paths (Original 799357272 bytes)
const long FRAME_MAP_PAGE_SIZE = (( ONE_TENTH_FRAME_SIZE / SYSTEME_ALIGNMENT) * SYSTEME_ALIGNMENT) + ( UINT_TWO * SYSTEME_ALIGNMENT);      //size of ~33k paths (Original 799357272 bytes)
const float HALF = 0.50f;
const float MINUS_HALF = -0.50f;
const float FLOAT_COMPRESSION_RATIO = 1.5f;
const float FLOAT_MAX_DISTANCE = 0.6f;
const float FLOAT_NEGLIGIBLE_LENGHT = 0.003f;
const float PI = 3.14f;
const float TWO = 2.0f;
const float RESOLUTION = 0.2f;
const float SYSTEM_PBC_DETTECTION_VALUE = 0.05f;
const QString POPE_NAME = "POPE";
const QString POPG_NAME = "POPG";
const QString PROTEIN_NAME = "PROTEIN";

//OpenCL
const cl_device_type GPU_DEVICE = 1;
const cl_uint WORK1DIM = 1;
const cl_uint WORK2DIM = 2;
const cl_uint WORK3DIM = 3;
const cl_uint ONE_ENTRIE = 1;
const cl_int PROPERTIES_LIST_TERMINATOR = 0;
const cl_int UNSPECIFIED_QUEUE_LIST = 0;
const cl_uint UNSPECIFIED_EVENTS_LIST = 0;
const QString KERNELS_FILE = ":/Kernels/MDIKernels.cl";
const QString CENTRALIZE_FRAME_KERNEL = "centralizeFrame";
const QString PROTEIN_COM_KERNEL = "proteinCOM";
const QString LIPID_COM_KERNEL = "lipidCOM";
const QString INTERACTION_KERNEL = "ProteinLipidInteracion";
const QString INTERACTION_ON_THE_FLY_KERNEL = "ProteinLipidInteracionOnTheFly";
const QString INTERACTION_COM_KERNEL = "PLCOMInteracion";
const QString INTERACTION_COM_ON_THE_FLY_KERNEL = "PLCOMOnTheFlyInteracion";


//OpenGL
const float FIELD_ANGLE = 45.0f;
const float NEAR_PLANE = 0.00001f;
const float FAR_PLANE = 5.0f;
const float ZOOM_QUANTIFIER = 5000.0f;
const GLuint DYNAMIC_PSUB_BINDING_INDEX = 0;
const GLuint FIXED_PSUB_BINDING_INDEX = 1;
const size_t QVECTOR3D_SIZE = sizeof( QVector3D );
const size_t QVECTOR4D_SIZE = sizeof( QVector4D );
const QString SHADER_DIRECTORY = ":/Shaders";
//Particles
const QString SPHERE_VERTEX_SHADER_FILE = "/sphere.vert";
const QString SPHERE_GEOMETRY_SHADER_FILE = "/sphere.geom";
const QString SPHERE_FRAGMENT_SHADER_FILE = "/sphere.frag";

//Folders and Files
const QString DATA_DIRECTORY = "/Users/Naif/Dropbox/PhD/MDSProject/Data";
const QString IND_DIRECTORY = "/IND";
const QString COM_DIRECTORY = "/COM";
const QString GRO_FILE = "/prot_l0.gro";
const QString XTC_FILE = "/20filter_prot_l0.xtc";
const QString IND_PATH_FILE = "/INDPath.data";
const QString IND_PARTICLE_FILE = "/INDParticle.data";
const QString COM_PATH_FILE = "/COMPath.data";
const QString COM_PARTICLE_FILE = "/COMParticle.data";
const QString IND_FILE = "/ind.data";
const QString COM_FILE = "/com.data";
const QString PROTEIN_SPACE_FILE = "/ProteinSpace.data";


#endif // CONSTDATA_H
