#ifndef APPLICATION_H
#define APPLICATION_H

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "Game.h"
#include "System.h"

#include <vector>

class Application {

public:
    bool quit;
    bool pause;
    unsigned int nextTick;
    bool interpolating;

    Application(unsigned int _width, unsigned int _height, unsigned int _bpp=32, bool _fullscreen=false) : width(_width), height(_height), bpp(_bpp), fullscreen(_fullscreen)
    {
        quit = false;
        pause = false;
        nextTick = 0;
        interpolating = true;
        flags = SDL_OPENGL | SDL_DOUBLEBUF;
        if (fullscreen)
        {
            flags |= SDL_FULLSCREEN;
        }
    }

    virtual ~Application() {
        terminate();
    }

    void terminate() {
        game->end();
        SDL_Quit();
    }

    void interact() { //TODO: Seperate to EventHandler code
        SDL_Event eventType;
        while (SDL_PollEvent(&eventType))
        {

            switch (eventType.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch (eventType.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_SPACE:
                    pause = !pause;
                    break;
                case SDLK_F10:
                    //TODO: Menu;
                    break;
                case SDLK_BACKQUOTE:
                    interpolating = !interpolating;
                    break;
                }
                break;
            }
        }
    }

    virtual void update() {
        game->update();

    }

    void draw(float interpolation) {

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        game->draw(interpolation);

        SDL_GL_SwapBuffers();
    }

    void initialize() {
        if (System::initilizeDisplay(width, height, bpp, flags)) {
            initOpengl();
            game = new Game();
            game->start();

        } else  {
            terminate();
        }
    }

    //game speed constants
    static const int GAME_SPEED_30 = 30;
    static const int GAME_SPEED_60 = 60;
    static const int GAME_SPEED_120 = 120;

    //frame skip maxes
    static const int FRAME_SKIP_LOW = 1;
    static const int FRAME_SKIP_MED = 5;
    static const int FRAME_SKIP_HIGH = 10;

private:

    unsigned int width;
    unsigned int height;
    unsigned int bpp;

    bool fullscreen;
    int flags;
    Game* game;

    void initOpengl()
    {
        glClearColor(0, 0, 0, 1);

        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //we are rendering on the xy plane, thus no z-depth
        glOrtho(0, width, 0, height, -1, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    }

};

#endif // APPLICATION_H
