#ifndef CLPROGRAM_H
#define CLPROGRAM_H

#include "clcommand.h"

/**
 * @brief The CLProgram class interfaces the OpenCL program
 */
class CLProgram : public virtual Debugger
{
public:
    /**
     * @brief CLProgram class constructor
     * @param clcontext a valid pointer to CLContext object
     */
    CLProgram(CLContext *clcontext);
    ~CLProgram();

    /**
     * @brief Create creates an Open cl program
     * @param filename: the name of program file to be created
     * @return
     */
    bool Create(QString filename);

    /**
     * @brief GetProgram: getter for an OpenCL default program
     * @return default opencl program
     */
    inline cl_program GetProgram() { return m_Program;}

    /**
     * @brief GetSharedProgram getter for an OpenCL shared program
     * @return opencl shared program
     */
    inline cl_program GetSharedProgram() { return m_SharedProgram;}

protected:

private:
    /**
     * @brief m_CLContext CLContext object
     */
    CLContext *m_CLContext= NULL;

    /**
     * @brief m_Program open cl default program
     */
    cl_program m_Program = NULL;

    /**
     * @brief m_SharedProgram open cl shared program
     */
    cl_program m_SharedProgram = NULL;

    /**
     * @brief getCLContext accessor for CLContext object
     * @return a pointer to CLContext object
     */
    inline CLContext *getCLContext() { return m_CLContext; }

    /**
     * @brief getContext accessor for openCL context
     * @return defualt opencl context
     */
    inline cl_context getContext() { return getCLContext()->GetContext(); }

    /**
     * @brief getSharedContext accessor for opencl shared context
     * @return open cl shared context
     */
    inline cl_context getSharedContext() { return getCLContext()->GetSharedContext(); }

    /**
     * @brief getDeviceID accessor for opencl device
     * @return open cle device id
     */
    inline cl_device_id getDeviceID() { return getCLContext()->GetDeviceID(); }

    /**
     * @brief getProgram accessor for open cl default program
     * @return open cl default program
     */
    inline  cl_program getProgram() { return m_Program;}

    /**
     * @brief getSharedProgram accessor for open cl shared program
     * @return open cl shred program
     */
    inline  cl_program getSharedProgram() { return m_SharedProgram;}

    /**
     * @brief setProgram setter for open cl default program
     * @param program default open cl program
     */
    inline void setProgram(cl_program program) { m_Program = program; }

    /**
     * @brief setSharedProgram setter for open cl shared program
     * @param program shared open cl program
     */
    inline void setSharedProgram(cl_program program) { m_SharedProgram = program; }

    /**
     * @brief createProgram creates a default open cl program
     * @param filename file name of prgram to be created
     * @return true if program is created sucessully otherways return false
     */
    bool createProgram(QString filename);

    /**
     * @brief buildPrograme builds a default open cl program
     * @return true if program is built sucessully otherways return false
     */
    bool buildPrograme();

    /**
     * @brief createSharedProgram creates a shared open cl program
     * @param filename file name of prgram to be created
     * @return true if shared program is created sucessully otherways return false
     */
    bool createSharedProgram(QString filename);

    /**
     * @brief buildSharedPrograme  builds a shared open cl program
     * @return if shared program is built sucessully otherways return false
     */
    bool buildSharedPrograme();

    /**
     * @brief fetchSource fetches a program source code from file
     * @param filename file name to be read
     * @return true if file data is obtained otherways return false
     */
    QString fetchSource(QString filename);

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // CLPROGRAM_H
