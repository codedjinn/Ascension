#ifndef BALL_H
#define BALL_H

//SDL Includes
#include "SDL/SDL_opengl.h"

//Game Lib Includes
#include "gamelib/physics/Vector.h"
#include "gamelib/shapes/Point.h"
#include "gamelib/rendering/Color.h"
#include "gamelib/gamesys/VisibleObject.h"
#include "gamelib/containers/BoundedBox.h"

//Std Includes
#ifndef _USE_MATH_DEFINES

#define _USE_MATH_DEFINES
#include <math.h>

#endif

#include <iostream>

using namespace std;

class Ball : public VisibleObject
{
    public:
        Ball(float _x, float _y, float _radius, BoundedBox* _boundry, Color* _color):  VisibleObject(),  radius(_radius), constraints(_boundry) {
            this->v = new Vector();
            this->c = _color;
            this->initialise(_x, _y);
        }

        Ball(float _x, float _y, float _radius, float vx, float vy, BoundedBox* _boundry, Color* _color):  VisibleObject(), radius(_radius), constraints(_boundry) {
            this->v = new Vector(vy, vy);
            this->c = _color;
            this->initialise(_x, _y);
        }

        Ball(float _x, float _y, float _radius, BoundedBox* _boundry):  VisibleObject(), radius(_radius), constraints(_boundry) {
             this->v = new Vector();
             this->c = new Color(1.0f, 1.0f, 1.0f);
             this->initialise(_x, _y);
        }

        Ball(float _x, float _y, float _radius, float vx, float vy, BoundedBox* _boundry):  VisibleObject(), radius(_radius), constraints(_boundry) {
            this->v = new Vector(vy, vy);
            this->c = new Color(1.0f, 1.0f, 1.0f);
            this->initialise(_x, _y);
        }

        virtual ~Ball() {}

        //calculate the location of the new x,y of the centrepoint
        virtual void update() {
            updatex();
            updatey();
        }

        void updatex() {
            //check if our next location is in bounds
            if (!constraints->inBoundsX(this->cntrPoint->getXCoOrd() + (v->x), radius))
            {
                //set on boundry before rebound
                if (v->x > 0) {
                    this->cntrPoint->setXCoOrd(this->constraints->getRhtBound() - radius);
                } else {
                    this->cntrPoint->setXCoOrd(this->constraints->getLftBound() + radius);
                }
                //rebound if not
                v->x *= -1.0f;
            } else {
                this->cntrPoint->setXCoOrd(this->cntrPoint->getXCoOrd() + (v->x));
            }

        }

        void updatey() {
            //check if our next location is in bounds
            if (!constraints->inBoundsY(this->cntrPoint->getYCoOrd() + (v->y), radius))
            {
                //set on boundry before rebound
                if (v->y > 0) {
                    this->cntrPoint->setYCoOrd(this->constraints->getTopBound() - radius);
                } else {
                    this->cntrPoint->setYCoOrd(this->constraints->getBtmBound() + radius);
                }
                //rebound if not
                v->y *= -1.0f;
            } else {
                this->cntrPoint->setYCoOrd(this->cntrPoint->getYCoOrd() + (v->y));
            }

        }

        //calculates the position of the object between game ticks
        virtual void interpolate(float interpVal)
        {
            delete this->lastLocation;
            this->lastLocation = new Point(this->intrpPoint->getXCoOrd(), this->intrpPoint->getYCoOrd());

            if (interpVal != 0.0) {
                this->intrpPoint->setXCoOrd(this->cntrPoint->getXCoOrd() + (v->x * interpVal));
                this->intrpPoint->setYCoOrd(this->cntrPoint->getYCoOrd() + (v->y * interpVal));
            } else {
                this->intrpPoint->setXCoOrd(this->cntrPoint->getXCoOrd());
                this->intrpPoint->setYCoOrd(this->cntrPoint->getYCoOrd());

            }

            float nettX = calculateNett(this->lastLocation->getXCoOrd(), this->intrpPoint->getXCoOrd());
            float nettY = calculateNett(this->lastLocation->getYCoOrd(), this->intrpPoint->getYCoOrd());

            if (nettX != 0.0f || nettY != 0.0f) {
                inferNewRelativesXYs(nettX, nettY);
            }
        }

        //calculate the new x,y values of the perimiter points
        virtual void inferNewRelativesXYs(float changeX, float changeY) {
            for (int i = 0 ; i < this->circleSegments; i++) {
                relativeBoundaryPoints[i]->setXCoOrd(relativeBoundaryPoints[i]->getXCoOrd() + changeX);
                relativeBoundaryPoints[i]->setYCoOrd(relativeBoundaryPoints[i]->getYCoOrd() + changeY);
            }
        }

        //draw method (renders the object)
        virtual void draw() {
            glBegin(GL_TRIANGLE_FAN);
                glColor3f(c->gRed(),c->gGreen(),c->gBlue());

                for (int i = 0; i < this->circleSegments; i++) {
                    glVertex2f(relativeBoundaryPoints[i]->getXCoOrd(), relativeBoundaryPoints[i]->getYCoOrd());
                }
            glEnd();
        }

        //string representation of the current ball
        static void toString(Ball* ballPtr) {
            using namespace std;

            cout<< "Ball (X,Y,RAD) (" << ballPtr->cntrPoint->getXCoOrd() << ", " << ballPtr->cntrPoint->getYCoOrd() << "," << ballPtr->radius << ")" << endl;
            cout<< "Ball Count " << Ball::count << endl;
        }

        static unsigned int count;
    protected:
        //centre of the circle
        Point* cntrPoint;
        //interpolated centre of the circle
        Point* intrpPoint;
        //last location of the centre point
        Point* lastLocation;
        //segments of the circle
        int circleSegments;

        //examine how to dynamically size according to segments (improve memory usage)
        Point* relativeBoundaryPoints[360];
        //degrees of each segment
        float angleStep;
        //radius of the circle
        float radius;

        //force applied to circle
        Vector* v;
        //color of the circle
        Color* c;

        //the dimensions the circle moves in
        BoundedBox* constraints;

    private:
        void initialise(float _x, float _y) {
            Ball::count++;

            //centre point of cicle
            this->cntrPoint = new Point(_x, _y);
            //centre point if interpolated circle between gameticks
            this->intrpPoint = new Point(_x, _y);
            //last location of the point interpolated or gametick
            this->lastLocation = new Point(_x, _y);

            //segments to divide the divide the circle in
            if (this->radius <= 5) {
                this->circleSegments=6;
            } else if (this->radius > 5 && this->radius <= 10) {
                this->circleSegments=15;
            } else if (this->radius > 10 && this->radius <= 20) {
                this->circleSegments=25;
            } else if (this->radius > 20 && this->radius <= 30) {
                this->circleSegments=35;
            } else if (this->radius > 30 && this->radius <= 40) {
                this->circleSegments=45;
            } else if (this->radius > 40 && this->radius <= 50) {
                this->circleSegments=55;
            } else if (this->radius > 50 && this->radius <= 60) {
                this->circleSegments=65;
            } else if (this->radius > 60 && this->radius <= 70) {
                this->circleSegments=75;
            } else if (this->radius > 70 && this->radius <= 80) {
                this->circleSegments=85;
            } else if (this->radius > 80 && this->radius <= 90) {
                this->circleSegments=95;
            } else if (this->radius > 90 && this->radius <= 100) {
                this->circleSegments=105;
            } else if (this->radius > 100 && this->radius <= 110) {
                this->circleSegments=115;
            } else if (this->radius > 110 && this->radius <= 120) {
                this->circleSegments=125;
            } else if (this->radius > 120 && this->radius <= 130) {
                this->circleSegments=135;
            } else if (this->radius > 130 && this->radius <= 140) {
                this->circleSegments=145;
            } else if (this->radius > 140 && this->radius <= 150) {
                this->circleSegments=155;
            } else if (this->radius > 150 && this->radius <= 160) {
                this->circleSegments=165;
            } else if (this->radius > 160 && this->radius <= 170) {
                this->circleSegments=175;
            } else if (this->radius > 170 && this->radius <= 180) {
                this->circleSegments=180;
            } else {
                this->circleSegments=360;
            }

            //determine angle increments based on number of segments
            this->angleStep = 360.0f/float(this->circleSegments);

            //local to store the radian value of the angle 1radian = 180deg
            float angleRadians = 0.0f;
            //local to keep track of current angle
            float angle = 0.0f;
            //
            float cosVal = 0.0f;
            float sinVal = 0.0f;

            //pie = 360deg ratio, cos sin functions work on radian, thus PI/180deg
            float pieRadianRatio =  M_PI/180;

            for (int i = 0; i < this->circleSegments; i++) {
                //radian value of the angle
                angleRadians = angle * pieRadianRatio;

                //determine the x co-ord
                cosVal = cos(angleRadians);
                //determine the y co-ord
                sinVal = sin(angleRadians);

                //points on perimiter relative to the centre point
                relativeBoundaryPoints[i] = new Point(this->cntrPoint->getXCoOrd() + (this->radius * cosVal),
                                                      this->cntrPoint->getYCoOrd() + (this->radius * sinVal));

                //increase current angle by segmentStep
                angle+=this->angleStep;
            }
        }

        //prints the perimiter points
        void printPoints() {
            for (int i = 0; i < this->circleSegments; i++) {
                cout<<"Circle XY (" << this->relativeBoundaryPoints[i]->getXCoOrd() << ", " << this->relativeBoundaryPoints[i]->getYCoOrd() <<")" <<endl;
            }
        }

        //calculate the net movement (only works in postive x,y cartesian space
        float calculateNett(float start, float end) {
            float returnValue = 0.0f;
            if (start > end) {
                returnValue =  -(start - end);
            } else if (start < end) {
                returnValue =  (end - start);
            } else {
                returnValue = 0.0f;
            }
            return returnValue;
        }
};

class GravityBall : public Ball
{

public:
    GravityBall(float _x, float _y, float _radius, BoundedBox* _bounds, Color* _color):  Ball(_x, _y, _radius, _bounds, _color) {
        this->v = new Vector(0, 0);

    }
    GravityBall(float _x, float _y, float _radius, float vx, float vy, BoundedBox* _bounds, Color* _color):  Ball(_x, _y, _radius, _bounds, _color) {
        this->v = new Vector(vx, vy);
    }

    void update()
    {
        //update the last location before the new move
        delete this->lastLocation;
        this->lastLocation = new Point(this->cntrPoint->getXCoOrd(), this->cntrPoint->getYCoOrd());

        //apply gravity only untill we are at the source
        if ((this->cntrPoint->getYCoOrd() - radius) >= (this->constraints->getBtmBound() + POS_TOLLERANCE_LEVEL)) {
            //decelerate against gravity
            if (v->y >= 0.0f)
            {
                v->y -= GRAVITATIONAL_CONSTANT + 0.1f;      //grav factor + friction factor
            //accelerate with gravity
            }
            else if (v->y < 0.0f)
            {
                v->y -= GRAVITATIONAL_CONSTANT;
                v->y += 0.2f;                               //friction factor decelerates
            }
        } else {
            //check the magnitude of the force to see if we can zero it
            if ((v->y >= NEG_TOLLERANCE_LEVEL && v->y <= POS_TOLLERANCE_LEVEL) && (v->y != 0.0f)) {
                v->y = 0.0f;
                this->cntrPoint->setYCoOrd(this->constraints->getBtmBound() + radius);
            }
        }

        //no movement along the y-axis thus must be on gravity source base
        if(((this->cntrPoint->getYCoOrd() - radius) <= (this->constraints->getBtmBound() + POS_TOLLERANCE_LEVEL)) &&
           ((this->cntrPoint->getYCoOrd() >= this->lastLocation->getYCoOrd() - POS_TOLLERANCE_LEVEL)
            && (this->cntrPoint->getYCoOrd() <= this->lastLocation->getYCoOrd() + POS_TOLLERANCE_LEVEL))) {

           if (v->x > POS_TOLLERANCE_LEVEL) {
               v->x -= 0.025f;
           } else if (v->x < NEG_TOLLERANCE_LEVEL) {
               v->x += 0.025f;
           } else {
               v->x = 0.0f;
           }
        }

        updatex();
        updatey();
    }

protected :
    //gravitational constant (9.8m/s) div game updates per second
    static const float GRAVITATIONAL_CONSTANT = 9.8f/15.0f;
    static const float POS_TOLLERANCE_LEVEL = 1.0f;
    static const float NEG_TOLLERANCE_LEVEL = -1.0f;
};

unsigned int Ball::count = 0;

#endif // BALL_H
