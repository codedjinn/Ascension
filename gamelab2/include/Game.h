#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "SDLGLApplication.h"
#include "gamelib/timing/Chronos.h"
#include "gamelib/gamesys/GameControl.h"

#include <iostream>

class Game : public SDLGLApplication
{

public:
    Game(BoundedBox* boundaries, int bpp=32, bool fullscreen=false, Color* color = NULL, GameControl* controller = NULL)
        : SDLGLApplication(boundaries, bpp, fullscreen, color) {
        this->_interpolate = true;
        this->_gamePaused = false;
        this->_gmController = controller;
        this->initGameTimers();
    }

    virtual ~Game() {}

    //[START] - Base Class Methods
    //Game Loop
    virtual void process() {
        if (!_gamePaused)
        {
            int loops = 0;
            while (Chronos::getTicks() > this->_nextGameTick && loops < this->_maxAllowedFrameSkips)
            {
                //updatables hook goes here
                this->_gmController->update();

                //update global last update time
                Chronos::LAST_GAME_UPDATE = Chronos::getTicks();

                //calc next game tick
                this->_nextGameTick += _gameRestBetweenTicks;

                //increase frame skip controller
                loops++;
            }
        }
        else
        {
            //delay thread processing while pausing
            SDL_Delay(_gameRestBetweenTicks);
            //re-initialise game timing controls
            Chronos::LAST_GAME_UPDATE = this->_nextGameTick = Chronos::getTicks();
        }

        if (this->_interpolate)
        {
            this->_interpolVal = float(Chronos::getTicks() - Chronos::LAST_GAME_UPDATE)/float(this->_gameRestBetweenTicks);

            //call interpolate func on the drawables
            this->_gmController->interpolate(this->_interpolVal);
        } else {
            this->_gmController->interpolate(0.0f);
        }
        //pre game draw
        this->preGameDraw();

        //call draw func on the drawables
        this->_gmController->draw();

        //post game draw
        this->postGameDraw();

        //FPS
        //update frame accumulator
        this ->_framesSinceLastSecond++;
        //check if a second has passed
        if (Chronos::getTicks() - this->_startTime >= Chronos::MILLIS_PER_SECOND) {
            //global second counter
             this ->_secondCount++;
            //add accumulated frames since last second
             this ->_frameCount +=  this ->_framesSinceLastSecond;
            //reset frame accumulator
             this ->_framesSinceLastSecond = 0;
            //reset start time
             this ->_startTime = Chronos::getTicks();
        }//FPS
    }

    //Input Control
    virtual void interact() {
        SDL_Event eventType;
        while (SDL_PollEvent(&eventType))
        {
            switch (eventType.type)
            {
            case SDL_QUIT:
                Application::_running = !Application::_running;
                break;

            case SDL_KEYDOWN:
                switch (eventType.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    Application::_running = !Application::_running;
                    break;
                case SDLK_BACKQUOTE:
                    this->_interpolate = !this->_interpolate;
                    break;
                case SDLK_SPACE:
                    this->_gamePaused = !this->_gamePaused;
                    break;
                default:
                    this->_gmController->processInputEvent(eventType);
                    break;
                }
                break;
            default:
                this->_gmController->processInputEvent(eventType);
                break;
            }
        }
    }

    //Cleanup Once Done
    virtual void cleanup() {
    }

    //Closedown Control
    virtual int terminate() {
        using namespace std;
        cout << "Game End Time : " << Chronos::getTicks() << endl;
        cout << "F/S  (" << this->_frameCount << "/" << this->_secondCount << ") = ";
        cout << "FPS :" << (float)this->_frameCount/(float)this->_secondCount << endl;
        return this->exit_code;
    }

    //Initalise The Game Application
    virtual bool initialize() {
        return SDLGLApplication::initialize();
    }
    //[END] - Base Class Methods

    void preGameDraw() {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void postGameDraw() {
        SDL_GL_SwapBuffers();
    }


    //game speed constants
    static const int GAME_SPEED_30 = 30;
    static const int GAME_SPEED_60 = 60;
    static const int GAME_SPEED_120 = 120;

    //frame skip maxes
    static const int FRAME_SKIP_LOW = 1;
    static const int FRAME_SKIP_MED = 5;
    static const int FRAME_SKIP_HIGH = 10;

protected :


    //Game Timer Initialisation
    void initGameTimers() {
        this->_frameCount = 0;
        this->_framesSinceLastSecond = 0;
        this->_avgFps = 0.0f;
        this->_secondCount = 0;
        this->_startTime = Chronos::getTicks();
        this->_gameTicksPerSecond = (int)(GAME_SPEED_30 * Chronos::GS_HALF_SPEED);
        this->_gameRestBetweenTicks = Chronos::MILLIS_PER_SECOND / this->_gameTicksPerSecond;
        this->_nextGameTick = Chronos::getTicks();
        this->_maxAllowedFrameSkips = FRAME_SKIP_MED;
        Chronos::LAST_GAME_UPDATE = this->_nextGameTick;
    }

    //game controller
    GameControl* _gmController;                     //game logic container

    //rendering controllers
    bool _interpolate;                              //bool to turn on/off interpolation
    float _interpolVal;                             //inteprolation value for this render

    //render timers
    unsigned int _frameCount;                       //global frame count
    unsigned int _framesSinceLastSecond;            //frame counter passing second
    float _avgFps;                                  //FPS reading average
    unsigned int _secondCount;                      //number of seconds
    unsigned int _startTime;                        //this seconds start tick counter

    //game loop controllers
    unsigned int _nextGameTick;                     //predicted next game tick
    unsigned int _gameTicksPerSecond;               //controls # of game updates
    unsigned int _gameRestBetweenTicks;             //the rest period between game ticks
    bool _gamePaused;                               //what you think this does brain?
    int _maxAllowedFrameSkips;                      //forces draw
};

#endif // GAME_H_INCLUDED
