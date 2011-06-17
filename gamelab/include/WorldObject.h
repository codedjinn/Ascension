#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "Drawable.h"

#include <vector>
#include <iterator>

class WorldObject : public Drawable
{
public:
    WorldObject() {}
    virtual ~WorldObject() {}
    std::vector<WorldObject*>* getChildren()
    {
        return &children;
    }

    void add(WorldObject* object)
    {
        children.push_back(object);
    }
    virtual void draw(float interpolation) {};
    virtual void update() = 0;

private:
    std::vector<WorldObject*> children;


};

#endif // WORLDOBJECT_H
