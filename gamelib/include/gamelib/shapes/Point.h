#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point {

public:
    Point() {
        this->_xCord = 0.0f;
        this->_yCord = 0.0f;
        this->_zCord = 0.0f;
    }

    Point(float xCord, float yCord, float zCord = 0.0f) {
        this->_xCord = xCord;
        this->_yCord = yCord;
        this->_zCord = zCord;
    }

    Point(int xCord, int yCord, int zCord = 0) {
        this->_xCord = xCord;
        this->_yCord = yCord;
        this->_zCord = zCord;
    }

    virtual ~Point() {
    }

    float getXCoOrd() {
        return this->_xCord;
    }

    float getYCoOrd() {
        return this->_yCord;
    }

    float getZCoOrd() {
        return this->_zCord;
    }

    void setXCoOrd(float newX) {
        this->_xCord = newX;
    }

    void setYCoOrd(float newY) {
        this->_yCord = newY;
    }

    void setZCoOrd(float newZ) {
        this->_zCord = newZ;
    }

protected:
    float _xCord;
    float _yCord;
    float _zCord;

};

#endif // POINT_H_INCLUDED
