#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <sstream>
#include <list>

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    p = nullptr;
}

int StudentWorld::init()
{
    Level lev(assetPath());
    ostringstream oss;
    oss << "level0" << getLevel() << ".txt";
    string levelFile = oss.str();
    
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        for (int i = 0; i < LEVEL_WIDTH; i++)
            for (int j = 0; j < LEVEL_HEIGHT; j++)
            {
                Level::MazeEntry ge = lev.getContentsOf(i,j); // level_x=5, level_y=10
                switch (ge) // so x=80 and y=160
                {
                    case Level::empty:
                        break;
                    case Level::smart_zombie:
                        break;
                    case Level::dumb_zombie:
                        break;
                    case Level::player:
                        p = new Penelope(i, j, this);
                        break;
                    case Level::exit:
                        break;
                    case Level::wall:
                        m_actors.push_back(new Wall(i, j, this));
                        break;
                    case Level::pit:
                        break;
                        // etc…
                }
                
            }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{

    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    p -> doSomething();
    for (list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
        (*it) -> doSomething();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete p;
    for (list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        delete (*it);
        it = m_actors.erase(it);
    }
}


bool StudentWorld::hitSomething(double x, double y, Actor* a) const
{
    for(list<Actor*>::const_iterator it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if (a != *it)
        {
            //if boundary is to the bottom left with respect to actor
            if (((*it) -> getX() <= x && (*it) -> getX() + SPRITE_WIDTH -1 >= x) &&
                 ((*it) -> getY() <= y && (*it) -> getY() + SPRITE_HEIGHT -1 >= y))
                return true;
            //if boundary is to the bottom right with respect to actor
            else if (((*it) -> getX() <= x + SPRITE_WIDTH - 1 && (*it) -> getX() + SPRITE_WIDTH - 1 >= x + SPRITE_WIDTH - 1) &&
                     ((*it) -> getY() <= y && (*it) -> getY() + SPRITE_HEIGHT - 1 >= y))
                return true;
            //if boundary is to the top right with respect to actor
            else if (((*it) -> getX() <= x + SPRITE_WIDTH - 1 && (*it) -> getX() + SPRITE_WIDTH - 1 >= x + SPRITE_WIDTH - 1) &&
                 (*it) -> getY() <= y + SPRITE_HEIGHT - 1 && (*it) -> getY() + SPRITE_HEIGHT - 1 >= y + SPRITE_WIDTH - 1)
                return true;
            //if boundary is to the top left with respect to actor
            else if (((*it) -> getX() <= x && (*it) -> getX() + SPRITE_WIDTH - 1 >= x) &&
                ((*it) -> getY() <= y + SPRITE_HEIGHT - 1 && (*it) -> getY() + SPRITE_HEIGHT - 1 >= y + SPRITE_WIDTH - 1))
                return true;
        }
    }
    
    return false;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
