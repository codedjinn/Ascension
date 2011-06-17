#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "gamelib/shapes/Point.h"
#include <iostream>


class Rectangle {
public:
    Rectangle(Point* rctBtmLeft = NULL, Point* rctTopRight = NULL)
    {
        this->inferBordersAndPoints(rctBtmLeft, rctTopRight);
    }

    virtual ~Rectangle() {}

    float getLftBound() {
        return this->_lftBorder;
    }

    float getRhtBound() {
        return this->_rhtBorder;
    }

    float getBtmBound() {
        return this->_btmBorder;
    }

    float getTopBound() {
        return this->_topBorder;
    }

protected:
    Point* _btmLeft;
    Point* _topRight;
    Point* _topLeft;
    Point* _btmRight;

    float _lftBorder;
    float _rhtBorder;
    float _topBorder;
    float _btmBorder;

    void inferBordersAndPoints(Point* rctBtmLeft, Point* rctTopRight) {
        if (rctBtmLeft != NULL && rctTopRight != NULL) {
            this->_topLeft = new Point(rctBtmLeft->getXCoOrd(), rctTopRight->getYCoOrd());
            this->_btmRight = new Point(rctTopRight->getXCoOrd(), rctBtmLeft->getYCoOrd());
            this->_btmLeft = rctBtmLeft;
            this->_topRight = rctTopRight;
        } else {
            this->_topLeft = new Point(0.0f, 1.0f);
            this->_btmRight = new Point(1.0f, 0.0f);
            this->_topRight = new Point(1.0f, 1.0f);
            this->_btmLeft = new Point (0.0f, 0.0f);
        }

        this->_lftBorder = rctBtmLeft->getXCoOrd();
        this->_btmBorder = rctBtmLeft->getYCoOrd();
        this->_rhtBorder = rctTopRight->getXCoOrd();
        this->_topBorder = rctTopRight->getYCoOrd();
    }
};

#endif // RECTANGLE_H_INCLUDED
