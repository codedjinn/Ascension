#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>

#define _SDL_

#include "SDL/SDL.h"

class System
{
    public:
        System() {}

        static bool initilizeDisplay(int width, int height, int bpp, int flags) {
            if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                std::cout << "Error initializing video: Abort";
                return false;
            }
            else {
                const SDL_VideoInfo* info = SDL_GetVideoInfo();
    //                height = info->current_h;
    //                width = info->current_w;

                if (!info) {
                    std::cout << "Error retieving video info: Abort";
                    return false;
                }
                else {
                    //bpp = info->vfmt->BitsPerPixel;

                    if (!SDL_SetVideoMode(width, height, bpp, flags)) {
                        std::cout << "Error setting video mode: Abort";
                        return false;

                    } else {
                        return true;
                    }
                }
            }
        }


};

#endif // SYSTEM_H
