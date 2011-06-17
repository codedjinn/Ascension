#ifndef BALL_H
#define BALL_H

#include "Application.h"
#include "WorldObject.h"
#include "Vector.h"
#include "Color.h"

#include <cmath>
#include <iostream>

#define PI (3.141592653589793)

using namespace std;

class Ball : public WorldObject
{
    public:


        Ball(float _x, float _y, float _radius, Container* _container, Color* _color):  WorldObject(), x(_x), y(_y), radius(_radius), container(_container) {
            init();
            this->v = new Vector();
            this->c = _color;
        }

        Ball(float _x, float _y, float _radius, float vx, float vy, Container* _container, Color* _color):  WorldObject(), x(_x), y(_y), radius(_radius), container(_container) {
            init();
            this->v = new Vector(vy, vy);
            this->c = _color;
        }

        Ball(float _x, float _y, float _radius, Container* _container):  WorldObject(), x(_x), y(_y), radius(_radius), container(_container) {
            init();
            this->v = new Vector();
            this->c = new Color(1.0f, 1.0f, 1.0f);
        }

        Ball(float _x, float _y, float _radius, float vx, float vy, Container* _container):  WorldObject(), x(_x), y(_y), radius(_radius), container(_container) {
            init();
            this->v = new Vector(vy, vy);
            this->c = new Color(1.0f, 1.0f, 1.0f);
        }

        virtual ~Ball() {}

        virtual void update() {
            updatex();
            updatey();
        }

        void updatex() {
            float newx = x + (v->x);
            float resultx = container->inBoundsX(newx, radius);
            if (resultx < 0) {
                if (v->x < 0) {
                    x -= resultx;
                }
                if (v->x < 0) {
                    x += resultx;
                }
                v->x *= -1;
            } else {
                x = x + (v->x);

            }
        }

        void updatey() {
            float newy = y + (v->y);
            float resulty = container->inBoundsY(newy, radius);
            if (resulty < 0) {
                if (v->y < 0) {
                    y -= resulty;
                }
                if (v->y < 0) {
                    y += resulty;
                }
                v->y *= -1;
            } else {
                y = y + (v->y);

            }
        }

        virtual void draw(float interpolation) {
            glBegin(GL_TRIANGLE_FAN);
                float realX = 0.0f;
                float realY = 0.0f;

                if (interpolation != 0.0) {
                    realX = x + (v->x * interpolation);
                    realY = y + (v->y * interpolation);
                } else {
                    realX = x;
                    realY = y;
                }

                glColor3f(c->gRed(),c->gGreen(),c->gBlue());
                //glVertex3f(x, y , 0);

                for (float angle = 0.0f; angle <= 360.0f; angle += 1.0f) {
                    glVertex2f(realX + (radius * _cos[(int)angle]), realY + (radius * _sin[(int)angle]));
                }
            glEnd();
        }

    protected:
        float x;
        float y;
        int radius;

		float _cos[360];
		float _sin[360];

        Vector* v;
        Color* c;

        Container* container;

        private:
            void init() {
                for (int a=0; a<360; a++) {
                    _cos[a] = cos(a * PI/180);
                    _sin[a] = sin(a * PI/180);
                }
            }
};

class GravityBall : public Ball
{

    public:
        GravityBall(float _x, float _y, float _radius, Container* _container, Color* _color):  Ball(_x, _y, _radius, _container, _color) {
            this->v = new Vector(0, 0);

        }
        GravityBall(float _x, float _y, float _radius, float vx, float vy, Container* _container, Color* _color):  Ball(_x, _y, _radius, _container, _color) {
            this->v = new Vector(vx, vy);
        }

        void update()
        {
            float newx = x + (v->x);
            float resultx = container->inBoundsX(newx, radius);
            if (resultx < 0)
            {
                if (v->x < 0) {
                    x -= resultx;
                }
                if (v->x < 0) {
                    x += resultx;
                }
                v->x *= -0.9;
            }
            else
            {
                x = x + (v->x);

            }

            v->y -= 0.011;

            float newy = y + (v->y);
            float resulty = container->inBoundsY(newy, radius);
            if ((((int) resulty) == 0) && (abs(v->y) < 0.11f)) {
                v->x *=0.993f; //Friction
            }
            if (resulty < 0)
            {
                if (v->y < 0) {
                    y -= resulty;
                }
                if (v->y < 0) {
                    y += resulty;
                }
                v->y *= -0.6;
            }
            else if (resulty > 0)
            {
                y = y + (v->y);

            }
        }
    };


#endif // BALL_H

