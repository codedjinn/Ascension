#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{

public:
    Drawable() {};
    virtual ~Drawable() {};

    virtual void draw() = 0;
    virtual void interpolate(float interpolValue) = 0;
};

#endif // DRAWABLE_H
