#ifndef CONTAINER_H
#define CONTAINER_H

#include "WorldObject.h"

class Container : public WorldObject
{
    public:
        Container(float lBound, float rBound, float bBound, float tBound) : lftBnd(lBound), rgtBnd(rBound), btmBnd(bBound), topBnd(tBound) {}
        Container(int lBound, int rBound, int bBound, int tBound) : lftBnd(lBound), rgtBnd(rBound), btmBnd(bBound), topBnd(tBound) {}

        virtual ~Container() {}

        virtual void draw() {}
        virtual void update() {}

        virtual float inBoundsX(float x, float sx = 0) {
            if ((x - sx) < lftBnd) {
                return abs(lftBnd) + (x - sx);
            } else if ((x + sx) > rgtBnd) {
                return abs(rgtBnd) - (x + sx);
            } else {
                return rgtBnd - sx;
            }
        }

        virtual float inBoundsY(float y, float sy = 0) {
            if ((y - sy) < btmBnd) {
                return abs(btmBnd) + (y - sy);
            } else if ((y + sy) > topBnd) {
                return abs(topBnd) - (y + sy);
            } else {
                return topBnd - sy;
            }
        }

    protected:
        float lftBnd;
        float rgtBnd;
        float btmBnd;
        float topBnd;
};

#endif // CONTAINER_H
