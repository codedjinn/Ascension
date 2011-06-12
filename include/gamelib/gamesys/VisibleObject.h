#ifndef VISIBLEOBJECT_H_INCLUDED
#define VISIBLEOBJECT_H_INCLUDED

#include "gamelib/gamesys/GhostObject.h"
#include "gamelib/rendering/Drawable.h"

class VisibleObject : public GhostObject, public Drawable
{

public:

    VisibleObject(){}
    virtual ~VisibleObject(){}

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void interpolate(float interpolValue) = 0;
};

#endif // VISIBLEOBJECT_H_INCLUDED
