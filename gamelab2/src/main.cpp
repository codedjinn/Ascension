#include <iostream>
#include "Application.h"
#include "Game.h"
#include "gamelib/shapes/Point.h"
#include "gamelib/rendering/Color.h"
#include "gamelib/gamesys/GameControl.h"
#include "ExampleGame/BouncyBallGame.h"

using namespace std;

int main(int atgc, char* argv[])
{
    //Game Controller
    BoundedBox* _appSize = new BoundedBox(new Point(0,0), new Point(640,480));
    GameControl* _gc = new BouncyBallGame(_appSize);
    GameControl::toString(_gc);

    //Application
    Application* _app = new Game(_appSize, 16, false, new Color(0.0f, 0.0f, 0.0f) ,_gc);

    _app->runApp();

    return _app->exit_code;
}
