#include "Actor.h"
#include "StudentWorld.h"
#include <list>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Penelope::doSomething()
{
    int ch;
    if (getSWorld() -> getKey(ch))
    {
        //user hit a key during this tick!
        switch(ch)
        {
            case KEY_PRESS_LEFT:
                setDirection(left);
                if(getSWorld() -> hitSomething(getX() - 4, getY(), this))
                    return;
                moveTo(getX() - 4, getY());
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if(getSWorld() -> hitSomething(getX() + 4, getY(), this))
                    return;
                moveTo(getX() + 4, getY());
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                if(getSWorld() -> hitSomething(getX(), getY() + 4, this))
                    return;
                moveTo(getX(), getY() + 4);
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                if(getSWorld() -> hitSomething(getX(), getY() - 4, this))
                    return;
                moveTo(getX(), getY() - 4);
                break;
        }
    }
    
}

void Wall::doSomething()
{
    return;
}


