#ifndef _SDLGLAPPLICATION_H_
#define _SDLGLAPPLICATION_H_

#include "Application.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL.h"
#include "gamelib/rendering/Color.h"
#include "gamelib/containers/BoundedBox.h"
#include <iostream>

class SDLGLApplication : public Application
{
public:

    SDLGLApplication(BoundedBox* renderBorders = NULL, int bpp=32, bool fullscreen=false, Color* col = NULL): Application()
    {
        this->_bpp = bpp;
        this->_fullscreen = fullscreen;
        this->exit_code = SDLGLApplication::SEC_CLEAN_EXIT;
        this->_clearcolor = col;
        if (renderBorders != NULL) {
            this->_renderBorders = renderBorders;
        } else {
            this->_renderBorders = new BoundedBox(0, 100, 0, 100);
        }
    }

    virtual ~SDLGLApplication(){}

protected:
    virtual bool initialize() {
        this->_flags = SDL_OPENGL | SDL_DOUBLEBUF;

        if (this->_fullscreen)
        {
            this->_flags |= SDL_FULLSCREEN;
        }

        if (initilizeDisplay(this->_renderBorders->getRhtBound(), this->_renderBorders->getTopBound(), this->_bpp, this->_flags))
        {
            initGLRenderContext();
        }
        else
        {
            this->exit_code = SDLGLApplication::FEC_FAILED_DISPLAY_INIT;
            return false;
        }
        Application::_running = !Application::_running;
        return true;
    }

   /*
    * This will setup a 2d ortho rendering context
    * with black as the clear color.
    */
    void initGLRenderContext() {
        //gaurd against no clear color existing.
        if (this->_clearcolor == NULL)
        {
            this->_clearcolor = new Color(0.0f, 0.0f, 0.0f);
        }

        glClearColor(this->_clearcolor->gRed(), this->_clearcolor->gGreen(), this->_clearcolor->gBlue(), this->_clearcolor->gAlpha());

        glViewport(this->_renderBorders->getLftBound(), this->_renderBorders->getBtmBound(), this->_renderBorders->getRhtBound(), this->_renderBorders->getTopBound());

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //we are rendering on the xy plane, thus no z-depth
        glOrtho(this->_renderBorders->getLftBound(), this->_renderBorders->getRhtBound(), this->_renderBorders->getBtmBound(), this->_renderBorders->getTopBound(), 0, 1);

        //no depth in 2d space
        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    static bool initilizeDisplay(int width, int height, int bpp, int flags) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Error initializing video: Abort";
            return false;
        }
        else
        {
            const SDL_VideoInfo* info = SDL_GetVideoInfo();

            if (!info) {
                std::cout << "Error retieving video info: Abort";
                return false;
            }
            else
            {
                if (!SDL_SetVideoMode(width, height, bpp, flags)) {
                    std::cout << "Error setting video mode: Abort";
                    return false;
                } else {
                    return true;
                }
            }
        }
    }

    virtual void delay(unsigned int delay) {
        SDL_Delay(delay);
    }

    virtual void preGameDraw() = 0;
    virtual void postGameDraw() = 0;

    //[START] - Base Class Methods
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
                }
                break;
            }
        }
    }
    //Application Processing
    virtual void process() = 0;
    //Application Resource Cleaning
    virtual void cleanup() = 0;
    //Application Exit
    virtual int terminate() {
        return this->exit_code;
    }
    //[END] - Base Class Methods

    static const unsigned int SEC_CLEAN_EXIT=0x0000;
    static const unsigned int FEC_FAILED_INIT=0x0001;
    static const unsigned int FEC_FAILED_DISPLAY_INIT=0x0002;

    int _flags;
    int _width;
    int _height;
    int _bpp;
    bool _fullscreen;
    Color* _clearcolor;
    BoundedBox* _renderBorders;                   //App Render Borders
};
#endif // _SDLGLAPPLICATION_H_
