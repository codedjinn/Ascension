#ifndef GAME_H
#define GAME_H

#include "Container.h"
#include "Ball.h"
#include "Color.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

class Game
{
    public:
        Game() {}
        virtual ~Game() {}

        void start() {

            container = new Container(0, 640, 0, 480);
            Color *col = new Color(0.5f, 0.5f, 0.0f);

            srand(Chronos::getTicks());

            for (int i = 0; i < 10000; i++) {
                container->add(
                    new GravityBall(
                        (float)(rand()%530)+55,
                        (float)(rand()%370)+55,
                        (float)(rand()%50),
                        rand()%10 <= 5 ? (float)(-rand()%10) : (float)(rand()%10),
                        rand()%10 >= 5 ? (float)(-rand()%10) : (float)(rand()%10),
                        container,
                        new Color((float)(rand()%100/100.0f),(float)(rand()%100/100.0f),(float)(rand()%100/100.0f))));
            }
        }

        void end() {
        }

        void update() {
            if (container)
            {
                using namespace std;

                vector<WorldObject*>* children = container->getChildren();
                for (vector<WorldObject*>::iterator  i = children->begin(); i != children->end(); i++)
                {
                    (*i)->update();
                }
            }
        }

        void draw(float interpolation) {
            if (container)
            {
                using namespace std;

                vector<WorldObject*>* children = container->getChildren();
                for (vector<WorldObject*>::iterator  i = children->begin(); i != children->end(); i++)
                {
                    (*i)->draw(interpolation);
                }
            }
        }

    protected:
    private:
        Container* container;

//        GravityBall* bb;
};

#endif // GAME_H
