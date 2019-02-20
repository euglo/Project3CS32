#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor: public GraphObject
{
public:
    //getX();
    //getY();
    //moveTo(double x, double y);
    //getDirection();
    //setDirection(Direction d);
    
    Actor(int imageID, double x, double y, int direction, int depth, StudentWorld* ptr)
    : GraphObject(imageID, SPRITE_WIDTH * x, SPRITE_WIDTH * y, direction, depth)
    {
        m_player = ptr;
    }
    
    
    virtual void doSomething() = 0;
    StudentWorld* getSWorld() const
    {
        return m_player;
    }

    virtual ~Actor()
    {}
    
private:
     StudentWorld* m_player;
};

class Penelope: public Actor
{
public:
    Penelope(double x, double y, StudentWorld* ptr)
    : Actor(IID_PLAYER, x, y, 0, 0, ptr)
    {
    }
    
    virtual void doSomething();
    
    virtual ~Penelope()
    {}
    
private:
   
};

class Wall: public Actor
{
public:
    Wall(double x, double y, StudentWorld* ptr)
    : Actor(IID_WALL, x, y, 0, 0, ptr)
    {}
    
    virtual void doSomething();
    
    virtual ~Wall()
    {}

private:
    
};
#endif // ACTOR_H_
