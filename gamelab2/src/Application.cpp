#include "Chronos.h"
#include "Application.h"
#include <iostream>

using namespace std;

int main(int atgc, char* argv[])
{
    float interpolation;
    unsigned int frameCount = 0;
    unsigned int framesSinceLastSecond = 0;
    float avgFps = 0.0f;
    unsigned int secondCount = 0;
    unsigned int startTime = Chronos::getTicks();

    cout << "Game Start : " << startTime << endl;

    Application* application =  new Application(640, 480);

    application->initialize();

    //TODO move game/loop related constants/calcs to game or application set game speed
    int gmUpdateInterval = (int)(Application::GAME_SPEED_30 * Chronos::GS_HALF_SPEED);
    int gmUpdateRestPeriod = Chronos::MILLIS_PER_SECOND / gmUpdateInterval;

    //next game tick and last update time
    Chronos::LAST_GAME_UPDATE = application->nextTick = Chronos::getTicks();

    while (!application->quit)
    {
        application->interact();
        if (!application->pause)
        {
            int loops = 0;
            while (Chronos::getTicks() > application->nextTick && loops < Application::FRAME_SKIP_MED)
            {
                //update game state
                application->update();

                //update last update time
                Chronos::LAST_GAME_UPDATE = Chronos::getTicks();

                //update the next tick target
                application->nextTick += gmUpdateRestPeriod;
                loops++;
            }
        } else {
            //delay thread processing while pausing
            SDL_Delay(gmUpdateInterval);
            //re-initialise game timing controls
            Chronos::LAST_GAME_UPDATE = application->nextTick = Chronos::getTicks();
        }

        //TODO move interoplation to more granular level
        interpolation = float(Chronos::getTicks() - Chronos::LAST_GAME_UPDATE)/float(gmUpdateRestPeriod);

        if (application->interpolating) {
            application->draw(interpolation);
        } else {
            application->draw(0.0f);
        }

        //FPS
        //update frame accumulator
        framesSinceLastSecond++;
        //check if a second has passed
        if (Chronos::getTicks() - startTime >= Chronos::MILLIS_PER_SECOND) {
            //global second counter
            secondCount++;
            //add accumulated frames since last second
            frameCount += framesSinceLastSecond;
            //reset frame accumulator
            framesSinceLastSecond = 0;
            //reset start time
            startTime = Chronos::getTicks();
        }//FPS
    }
    //TODO create propper logging system.
    cout << "Game End Time : " << Chronos::getTicks() << endl;
    cout << "F/S  (" << frameCount << "/" << secondCount << ") = ";
    cout << "FPS :" << (float)frameCount/(float)secondCount << endl;
    application->terminate();
    return 0;
}
