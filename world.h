#ifndef _cworld_Define_2024_

#include <map>
#include <string>
#include <sstream>
#include "prompt.h"

struct Location
{
    int x_;
    int y_;
    Location(int x = -1, int y = -1)
    : x_(x)
    , y_(y) {}
};

struct Object
{
    std::string desc_;
    Location location_;
    std::string ToString() {
        std::stringstream ss;
        ss << desc_ << " at (" << location_.x_ << ", " << location_.y_ << ")";
        return ss.str();
    }
};

class World : public Object
{
    void ExecuteCommand(std::string &cmd)
    {
        std::cout << "world checking " << cmd << "..." << std::endl;
    }

    std::map<std::string, Object> objects_map_;

public:
    World()
    {
        location_ = Location(0, 0);
    }
    ~World() {}

    static bool OnCommand(std::string &cmd, void *pObj)
    {
        World *pThis = (World *)pObj;
        if (pThis)
        {
            pThis->ExecuteCommand(cmd);
        }
        return true;
    }
};

#define _cworld_Define_2024_
#endif