#ifndef CRONOS_H_INCLUDED
#define CRONOS_H_INCLUDED

#define _SDL_

#include "SDL/SDL.h"

class Cronos {

    public:
        Cronos() {}

        virtual ~Cronos() {}

        //constants
        static const float GS_NORMAL_SPEED = 1.0f;
        static const float GS_HALF_SPEED = 0.5f;
        static const float GS_DOUBLE_SPEED = 2.0f;

        //static
        static const int MILLIS_PER_SECOND = 1000;

        static unsigned int getTicks()
        {
            #ifdef _SDL_
            return SDL_GetTicks();
            #endif

            #ifdef _SFML_
            return SFML_GetTicks();
            #endif
        }
};

#endif // CRONOS_H_INCLUDED
