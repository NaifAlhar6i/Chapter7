#ifndef CLCOMMAND_H
#define CLCOMMAND_H

#include "clcontext.h"
/**
 * @brief The CLCommand class interfaces the OpenCL cl_command_queue object.
 * CLCommand reqires a valid pointer to a CLContext.
 * The class provides three main functions Setup, GetCommand and GetSharedCommand.
 *
 */
class CLCommand : public virtual Debugger
{
public:
    /**
     * @brief CLCommand class constructor
     * @param clcontext a pointer to CLContext object
     */
    CLCommand(CLContext *clcontext);
    ~CLCommand();

    /**
     * @brief Setup creates two OpenCL commands: 1) a default command (non-shareable), and 2) shared command.
     * @return true if booth commands are created sucessully otherways it returns false
     */
    bool Setup();
    /**
     * @brief GetCommand is a global accessor to the default command
     * @return cl_command_queue object
     */
    inline cl_command_queue GetCommand() { return this->getCommand(); }
    /**
     * @brief GetSharedCommand is a global accessor to the shared command
     * @return cl_command_queue object
     */
    inline cl_command_queue GetSharedCommand() { return this->getSharedCommand(); }
protected:

private:
    /**
     * @brief m_CLContext: a pointer to CLContext class
     */
    CLContext *m_CLContext= NULL;

    /**
     * @brief m_Command: OpenCL command object to hold the default OpenCL command
     */
    cl_command_queue m_Command = NULL;

    /**
     * @brief m_SharedCommand: OpenCL command object to hold the shared OpenCL command
     */
    cl_command_queue m_SharedCommand = NULL;

    /**
     * @brief getCLContext: private accessor for CLContext
     * @return a pointer to CLContext
     */
    inline CLContext *getCLContext() { return m_CLContext; }

    /**
     * @brief getContext: private accessor to the OpenCL context
     * @return default cl_context object
     */
    inline cl_context getContext() { return getCLContext()->GetContext(); }

    /**
     * @brief getSharedContext: private accessor to OpenCL context
     * @return shared cl_context object
     */
    inline cl_context getSharedContext() { return getCLContext()->GetSharedContext(); }

    /**
     * @brief getDeviceID: private accessor to openCL device
     * @return cl_device_id
     */
    inline cl_device_id getDeviceID() { return getCLContext()->GetDeviceID(); }

    /**
     * @brief getCommand : private accessor to default command
     * @return default cl_command_queue object
     */
    inline cl_command_queue getCommand() { return m_Command; }

    /**
     * @brief getSharedCommand: private accessor for shared command
     * @return shared cl_command_queue object
     */
    inline cl_command_queue getSharedCommand() { return m_SharedCommand; }

    /**
     * @brief setCommand: private setter for defualt command
     * @param command: defualt cl_command_queue object
     */
    inline void setCommand(cl_command_queue command) { m_Command = command; }

    /**
     * @brief setSharedCommand: private setter for defualt command
     * @param command: shared cl_command_queue object
     */
    inline void setSharedCommand(cl_command_queue command) { m_SharedCommand = command; }

    /**
     * @brief setupCommand creates an OpenCL command from default cl context
     * @return  true if the command is succeffuly created
     */
    bool setupCommand();

    /**
     * @brief setupSharedCommand creates a shared OpenCL command from shared cl context
     * @return true if the command is succeffuly created
     */
    bool setupSharedCommand();

    /**
     * @brief freeResources releases the assiocated object and clear the memory
     */
    void freeResources();

};

#endif // CLCOMMAND_H
