#ifndef CLMEMORY_H
#define CLMEMORY_H

#include "clcontext.h"

/**
 * @brief The CLMemory class interfaces the OpenCL memory object
 *CLMemory requires a valid pointer to CLContext object.
 * The class provides four main functions: 1) Create, 2)CreateShared, 3) GetMemoryObject, and 4) GetSharedMemoryObject
 */
class CLMemory: public virtual Debugger
{
public:
    /**
     * @brief CLMemory class constructor
     * @param clcontext a pointer to CLContext
     */
    CLMemory(CLContext *clcontext);
    ~CLMemory();

    /**
     * @brief GetMemoryObject: accessor for default OpenCL memory object
     * @return cl_mem
     */
    inline cl_mem GetMemoryObject() { return m_MemoryObject; }

    /**
     * @brief GetSharedMemoryObject: accessor for shared OpenCL memory object
     * @return cl_mem
     */
    inline cl_mem GetSharedMemoryObject() { return m_SharedMemoryObject; }

    /**
     * @brief Create creates a default OpenCL memory object
     * @param buffersize specifies the required size
     * @param usesharedcontext specifies whether the OpenCL memory
     * @return true if the default memory object is created sucessully otherways it returns false
     */
    bool Create(size_t buffersize, bool usesharedcontext = false);

    /**
     * @brief CreateShared creates a shared OpenCL memory object
     * @param glbufferid specifies the OpenGL buufer id
     * @return true if the shared memory object is created sucessully otherways it returns false
     * NOTE: This function creates an OpenCL memory object from an OpenGL buffer
     */
    bool CreateShared(GLuint glbufferid);

private:
    /**
     * @brief m_CLContext
     */
    CLContext *m_CLContext = NULL;

    /**
     * @brief m_MemoryObject an OpenCL memory object
     */
    cl_mem m_MemoryObject = NULL;

    /**
     * @brief m_SharedMemoryObject an OpenCL memory object
     */
    cl_mem m_SharedMemoryObject = NULL;

    /**
     * @brief m_BufferSize a buffer size
     */
    size_t m_BufferSize = UINT_ZERO;

    /**
     * @brief m_SharingState a bool variable to hold the sharing state.
     * This variable is used to specify the sharing state of the selected memory object
     */
    bool m_SharingState = false;

    /**
     * @brief getCLContext: getter for CLContext object
     * @return a pointer to CLContext object
     */
    inline CLContext *getCLContext() { return m_CLContext; }

    /**
     * @brief getMemoryObject: getter for a default OpenCL memory object
     * @return default memory object
     */
    inline cl_mem getMemoryObject() { return m_MemoryObject; }

    /**
     * @brief getSharedMemoryObject getter for a shared OpenCL memory object
     * @return shared memory object
     */
    inline cl_mem getSharedMemoryObject() { return m_SharedMemoryObject; }

    /**
     * @brief getContext: getter for default OpenCL context
     * @return default open cl context
     */
    inline cl_context getContext() { return getCLContext()->GetContext(); }

    /**
     * @brief getSharedContext: getter for shared OpenCL context
     * @return shared cl context
     */
    inline cl_context getSharedContext() { return getCLContext()->GetSharedContext(); }

    /**
     * @brief getBufferSize: getter for memory object buffer size
     * @return size of buffer
     */
    inline size_t getBufferSize() { return m_BufferSize; }

    /**
     * @brief getSharingState: getter for sharing state variable
     * @return bool
     */
    inline bool getSharingState() { return m_SharingState; }

    /**
     * @brief setBufferSize: setter for buffer size
     * @param size size of the buffer in bytes
     */
    inline void setBufferSize(size_t size ) {m_BufferSize = size;}

    /**
     * @brief setMemoryObject: setter for default memory object
     * @param memoryobject memory object
     */
    inline void setMemoryObject(cl_mem memoryobject ) { m_MemoryObject = memoryobject; }

    /**
     * @brief setSharedMemoryObject: setter for shared memory object
     * @param memoryobject shared memory object
     */
    inline void setSharedMemoryObject(cl_mem memoryobject ) { m_SharedMemoryObject = memoryobject; }

    /**
     * @brief setSharingState: setter for the sharing state
     * @param state current memory object sharing state
     */
    inline void setSharingState(bool state) { m_SharingState = state; }

    /**
     * @brief createMemoryFromCLContext creates a default OpenCL memory object
     * @param buffersize the memory object buffer size in byte
     * @return true if the default memory object is created sucessully otherways it returns false
     */
    bool createMemoryFromCLContext(size_t buffersize);

    /**
     * @brief createMemoryFromSharedContext creates shared OpenCL memory object
     * @param buffersize buffer size
     * @return true if the default memory object is created sucessully otherways it returns false
     * NOTE: This function does not utilize OpenGL buffer! It just creates an OpenCL memory object using open cl shared context
     */
    bool createMemoryFromSharedContext(size_t buffersize);

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // CLMEMORY_H
