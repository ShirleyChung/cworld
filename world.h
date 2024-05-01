#ifndef _cworld_Define_2024_
#define _cworld_Define_2024_

#include "person.h"
#include "prompt.h"

using namespace std;

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


class World : public Object, public CommandReciever
{
    typedef std::map<std::string, Object> OBJMAP;
    OBJMAP mapObjects_;

    typedef const std::string (World::*CMD_CALLBACK)(const std::string& param);

    typedef std::map<std::string, CMD_CALLBACK> CMDCBK_MAP;

    CMDCBK_MAP mapCmdCb_;

    const std::string ListItems(const std::string& params) {
        std::cout << "listing item..." << std::endl;
        if (!mapObjects_.size())
            std::cout << "Empty" << std::endl;
        else
            for (OBJMAP::iterator i = mapObjects_.begin(); i != mapObjects_.end(); ++i) {
                std::cout << i->first << ":" << i->second.ToString() << std::endl;
            }
        return "complete.";
    }

    void SetupCmdLists() {
        mapCmdCb_["listitem"] = &World::ListItems;
    }
public:
    World()
    {
        SetupCmdLists();
        location_ = Location(0, 0);
        std::cout << "-= World Start =-" << endl;
    }
    ~World() {}

    // 輸入字串，從字串中拆解出command及parameter, 並從mapCmdCb中找出對應的函式來呼叫
    virtual bool OnCommand(const std::string &line)
    {
        std::string cmd, param, result;
        size_t pos = line.find(' ');
        if (pos == std::string::npos)
            cmd = line;
        else {
            cmd = line.substr(0, pos++);
            param = line.substr(pos);
        }
        CMDCBK_MAP::iterator i = mapCmdCb_.find(cmd);
        if (i != mapCmdCb_.end()) {
            result = (this->*i->second)(param);
            return true;
        }
        return false;
    }
};

#define _cworld_Define_2024_
#endif