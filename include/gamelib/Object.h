#ifndef OBJECT_H
#define OBJECT_H

/*
 * TODO Common ancestor to all objects.....? What is the point ?
 */

#include <string>

class Object
{
public:
    Object() {}

    virtual ~Object() {}

    virtual std::string toString();
};

#endif // OBJECT_H
