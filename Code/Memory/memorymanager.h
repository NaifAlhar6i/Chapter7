#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "datastructure.h"

/**
 * @brief The MemoryManager class manages the memory objects
 */
class MemoryManager : public DataStructure
{
public:
    /**
     * @brief MemoryManager class constructure
     */
    MemoryManager();
    ~MemoryManager();


protected:


private:

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    static void freeResources();

};

#endif // MEMORYMANAGER_H
