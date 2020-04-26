#ifndef CLMANAGER_H
#define CLMANAGER_H

#include "cltask.h"
#include "clgltask.h"
/**
 * @brief The CLManager class
 * Purpose: Interfaces the CLGLTask and CLTask class.
 */
class CLManager : public virtual CLGLTask
{
public:
    /**
     * @brief CLManager class constructure
     */
    CLManager();
    ~CLManager();

};

#endif // CLMANAGER_H
