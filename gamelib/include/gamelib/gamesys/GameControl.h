#ifndef GAMECONTROL_H_INCLUDED
#define GAMECONTROL_H_INCLUDED

#include <vector>
#include <iostream>

#include "SDL/SDL.h"

#include "gamelib/gamesys/Updateable.h"
#include "gamelib/gamesys/VisibleObject.h"
#include "gamelib/rendering/Drawable.h"
#include "gamelib/containers/BoundedBox.h"

using namespace std;

class GameControl {

public:
    GameControl()
    {
        init();
        this->setRenderBoundaries(new BoundedBox(0.0f, 100.0f, 0.0, 100.0f));
        GameControl::count++;
    }

    GameControl(BoundedBox* maxRenderBoundaries)
    {
        init();
        this->setRenderBoundaries(maxRenderBoundaries);
        GameControl::count++;
    }

    virtual ~GameControl(){};

    void addVisibleGO(VisibleObject* obj) {
        this->gameObjects.push_back(obj);
        this->_hasGameObjects = true;
    }

    void addUpdatableOnlyGO(Updateable* obj) {
        this->updatableComponents.push_back(obj);
        this->_hasOnlyUpdateables = true;
    }

    void addDrawableOnlyGO(Drawable* obj) {
        this->drawableComponents.push_back(obj);
        this->_hasOnlyDrawables = true;
    }

    std::vector<VisibleObject*>* getVisibleGO() {
        return &this->gameObjects;
    }

    std::vector<Updateable*>* getUpdatableOnlyGO() {
        return &this->updatableComponents;
    }

    std::vector<Drawable*>* getDrawableOnlyGO() {
        return &this->drawableComponents;
    }

    void update() {
        if (this->_hasOnlyUpdateables) {
            vector<Updateable*>* updChildObj = this->getUpdatableOnlyGO();
            for (vector<Updateable*>::iterator  i = updChildObj->begin(); i != updChildObj->end(); i++)
            {
                (*i)->update();
            }
        }

        if (this->_hasGameObjects) {
            vector<VisibleObject*>*  visChildObj = this->getVisibleGO();
            for (vector<VisibleObject*>::iterator  i = visChildObj->begin(); i != visChildObj->end(); i++)
            {
                (*i)->update();
            }
        }
    }

    void draw() {
        if (this->_hasOnlyDrawables) {
            vector<Drawable*>* drwChildObj = this->getDrawableOnlyGO();
            for (vector<Drawable*>::iterator  i = drwChildObj->begin(); i != drwChildObj->end(); i++)
            {
                (*i)->draw();
            }
        }

        if (this->_hasGameObjects) {
            vector<VisibleObject*>* visChildObj = this->getVisibleGO();
            for (vector<VisibleObject*>::iterator  i = visChildObj->begin(); i != visChildObj->end(); i++)
            {
                (*i)->draw();
            }
        }
    }

    void interpolate(float interpolVal) {
        if (_hasOnlyDrawables) {
            vector<Drawable*>* drwChildObj = this->getDrawableOnlyGO();
            for (vector<Drawable*>::iterator  i = drwChildObj->begin(); i != drwChildObj->end(); i++)
            {
                (*i)->interpolate(interpolVal);
            }
        }

        if (_hasGameObjects) {
            vector<VisibleObject*>* visChildObj = this->getVisibleGO();
            for (vector<VisibleObject*>::iterator  i = visChildObj->begin(); i != visChildObj->end(); i++)
            {
                (*i)->interpolate(interpolVal);
            }
        }
    }

    void setRenderBoundaries(BoundedBox* _boundaries) {
        if (_boundaries != NULL) {
            this->_maxRenderBoundaries = _boundaries;
        }
    }

    static void toString(GameControl* _controler) {
        using namespace std;
        cout << "GameController Instance Count " << GameControl::count << endl;
    }

    virtual void processInputEvent(const SDL_Event evnt) = 0;
protected:

    virtual bool initGameControler() = 0;
    virtual bool loadGame() = 0;

    std::vector<VisibleObject*> gameObjects;
    std::vector<Updateable*> updatableComponents;
    std::vector<Drawable*> drawableComponents;
    bool _hasOnlyDrawables;
    bool _hasOnlyUpdateables;
    bool _hasGameObjects;
    BoundedBox* _maxRenderBoundaries;

private:
    void init()
    {
        this->_hasOnlyDrawables = false;
        this->_hasOnlyUpdateables = false;
        this->_hasGameObjects = false;
    }

    static int count;
};

int GameControl::count = 0;

#endif // GAMECONTROL_H_INCLUDED
