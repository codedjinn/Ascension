#ifndef GHOSTOBJ_H_INCLUDED
#define GHOSTOBJ_H_INCLUDED

#include "gamelib/gamesys/Updateable.h"

class GhostObject : public Updateable
{

public:

    GhostObject(){}

    virtual ~GhostObject(){}

protected:
    virtual void update() = 0;
};
#endif // GHOSTOBJ_H_INCLUDED
