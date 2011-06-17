#ifndef BB_GAME_H_INCLUDED
#define BB_GAME_H_INCLUDED

#include "gamelib/gamesys/GameControl.h"
#include "gamelib/rendering/Ball.h"
#include "gamelib/containers/BoundedBox.h"


class BouncyBallGame : public GameControl
{

public:
    BouncyBallGame() : GameControl()
    {
        this->_maxRenderBoundaries = new BoundedBox(0.0f, 640.0f, 0.0f, 480.0f);
        this->initGameControler();
    }

    BouncyBallGame(BoundedBox* boundaries) : GameControl(boundaries)
    {
        this->initGameControler();
    }

    bool initGameControler()
    {
        return loadGame();
    }

    bool loadGame()
    {
        addGravityBall();
        return true;
    }

    void processInputEvent(SDL_Event event) {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_g:
                this->addGravityBall();
                break;
            case SDLK_b:
                this->addBall();
                break;
            }
            break;
        }
    }

private:
    void addGravityBall() {
        srand(Chronos::getTicks());
        this->addVisibleGO(
            new GravityBall(
                (float)(rand()%530)+55,
                (float)(rand()%370)+55,
                (float)(rand()%50),
                rand()%20 >= 10 ? (float)(-rand()%20) : (float)(rand()%20),
                rand()%10 >= 5 ? (float)(-rand()%10) : (float)(rand()%10),
                this->_maxRenderBoundaries,
                new Color((float)(rand()%100/100.0f),(float)(rand()%100/100.0f),(float)(rand()%100/100.0f)),
                (float)(rand()%100/100.0f)));
    }

    void addBall() {
        srand(Chronos::getTicks());
        this->addVisibleGO(
            new Ball(
                (float)(rand()%530)+55,
                (float)(rand()%370)+55,
                (float)(rand()%50),
                rand()%20 >= 10 ? (float)(-rand()%20) : (float)(rand()%20),
                rand()%10 >= 5 ? (float)(-rand()%10) : (float)(rand()%10),
                this->_maxRenderBoundaries,
                new Color((float)(rand()%100/100.0f),(float)(rand()%100/100.0f),(float)(rand()%100/100.0f)),
                (float)(rand()%100/100.0f)));
    }
};

#endif // BB_GAME_H_INCLUDED
