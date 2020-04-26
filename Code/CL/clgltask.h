#ifndef CLGLTASK_H
#define CLGLTASK_H

#include "include/constdata.h"
#include "cltask.h"
#include <QTime>

/**
 * @brief The CLGLTask class is responsible for shared tasks.
 * The shared tasks are the tasks that utilize OpenCL-GL interoperability.
 */
class CLGLTask : public CLTask
{
public:
    /**
     * @brief CLGLTask class constructor
     */
    CLGLTask();
    ~CLGLTask();

    /**
     * @brief ComputeProteinLipidInteraction this function utilize the shared context to perform the protein-lipid interaction test.
     * @param vertexbufferid the id of a valid OpenGL vertext buffer
     * @param colorbufferid the id of a valid OpenGL color buffer
     * @param systemstructure   a void pointer to SystemStructureRecord structure. This structure is used in the GPU.
     * @param proteinspaces a void pointer to ProteinSpace structure. This structure is used in the GPU.
     * @param proteinparticles a void pointer to ProteinParticle structure. This structure is used in the GPU.
     * @param atomsnumber number of atoms involved in the interaction test
     * @param interactiondistance a float point number to specify the maximum distance of the interaction
     * @param workitemssize specifying the number of work items to be excuteed in the GPU. Usually we use the atoms number.
     * @param localsize specify the number of items to be excuted within each group in the GPU.
     */
    void ComputeProteinLipidInteraction(GLuint vertexbufferid, GLuint colorbufferid, void *systemstructure, void *proteinspaces, void *proteinparticles,
                            unsigned int atomsnumber, float interactiondistance,  unsigned int workitemssize = 0, unsigned int localsize = 0);

private:

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};
#endif // CLGLTASK_H
