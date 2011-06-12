#ifndef UPDATEABLE_H_INCLUDED
#define UPDATEABLE_H_INCLUDED

class Updateable
{

public:
    Updateable() {};
    virtual ~Updateable() {};

    virtual void update() = 0;
};

#endif // UPDATEABLE_H_INCLUDED
