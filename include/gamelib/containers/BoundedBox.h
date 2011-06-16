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

    virtual bool inBoundsX(float x, float sx = 0) {
        if ((x - sx) < this->getLftBound()) {
            return false;
        } else if ((x + sx) > this->getRhtBound()) {
            return false;
        } else {
            return true;
        }
    }

    virtual bool inBoundsY(float y, float sy = 0) {
        if ((y - sy) < this->getBtmBound()) {
            return false;
        } else if ((y + sy) > this->getTopBound()) {
             return false;
        } else {
            return true;
        }
    }
};

#endif // BOUNDEDBOX_H
