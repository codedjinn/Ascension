#ifndef BOUNDEDBOX_H
#define BOUNDEDBOX_H

#include <stdlib.h>
#include "gamelib/shapes/Rectangle.h"
#include "gamelib/shapes/Point.h"

class BoundedBox : public Rectangle
{
public:
     BoundedBox(Point* btmLeft, Point* topRight)
        : Rectangle(btmLeft, topRight)
    {

    }

    BoundedBox(float lBound, float rBound, float bBound, float tBound)
        : Rectangle(new Point(lBound, bBound), new Point(rBound, tBound))
    {

    }

    BoundedBox(int lBound, int rBound, int bBound, int tBound)
        : Rectangle(new Point(lBound, bBound), new Point(rBound, tBound))
    {

    }

    virtual ~BoundedBox() {}

    virtual float inBoundsX(float x, float sx = 0) {
        if ((x - sx) < this->getLftBound()) {
            return abs(this->getLftBound()) + (x - sx);
        } else if ((x + sx) > this->getRhtBound()) {
            return abs(this->getRhtBound()) - (x + sx);
        } else {
            return this->getRhtBound() - sx;
        }
    }

    virtual float inBoundsY(float y, float sy = 0) {
        if ((y - sy) < this->getBtmBound()) {
            return abs(this->getBtmBound()) + (y - sy);
        } else if ((y + sy) > this->getTopBound()) {
            return abs(this->getTopBound()) - (y + sy);
        } else {
            return this->getTopBound() - sy;
        }
    }
};

#endif // BOUNDEDBOX_H
