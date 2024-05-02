#ifndef _cworld_Define_2024_
#define _cworld_Define_2024_

#include "person.h"
#include "prompt.h"
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

// 管理一群JSON物件，可從JSON檔回復
template<class T>
class JSONObjManager {
protected:
    typedef std::map<std::string, T> OBJECTMAP;
    OBJECTMAP objMap_;
public:
    JSONObjManager () {        
    }
    void LoadFromFile(const std::string& fn) {
        cout << "-= Load from " << fn << "=- " << endl;
        std::ifstream fs(fn.c_str());
        if (fs) {
            std::string line;
            while (getline(fs, line)) {
                T p(line);
                objMap_[p.GetName()] = p;
            }
        }
    }
    void SaveToFile(const std::string& fn) {

    }
};

// 管理所有人物
class PersonManager: public JSONObjManager<Person> {
    public:
    PersonManager() {
        LoadFromFile("data/person.data");
    }
    // 列出所有人物
    void ListPersons() {
        for (OBJECTMAP::iterator i = objMap_.begin(); i != objMap_.end(); ++i) {
            cout << i->second.GetBrief() << endl;
        }
    }
    // 所有人物時間流逝1秒
    void PersonAging() {
        for (OBJECTMAP::iterator i = objMap_.begin(); i != objMap_.end(); ++i) {
            i->second.IncreaseAge(1);
        }
    }
};

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
    PersonManager personMgr_;

    typedef std::map<std::string, Object> OBJMAP;
    OBJMAP mapObjects_;

    typedef const std::string (World::*CMD_CALLBACK)(const std::string& param);

    typedef std::map<std::string, CMD_CALLBACK> CMDCBK_MAP;

    CMDCBK_MAP mapCmdCb_;

    const std::string ShowPersons(const std::string& params) {
        personMgr_.ListPersons();
        return "";
    }

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
       mapCmdCb_["sp"] =  mapCmdCb_["showpersons"] = &World::ShowPersons;
    }

    thread timer_thread_;
    bool running_;

    // 每秒事件
    void OnOneSecondPass() {
        // 每個人物都過1秒
        personMgr_.PersonAging();
    }

    // 時計執行緒
    void OnTimerThread() {
        time_t prevTime = time(NULL);
        while (running_) {
            time_t now = time(NULL);
            if (now - prevTime >= 1) {
                prevTime = now;
                OnOneSecondPass();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
public:
    World()
    : timer_thread_(&World::OnTimerThread, this)
    , running_(true)
    {
        SetupCmdLists();
        location_ = Location(0, 0);
        std::cout << "-= World Start =-" << endl;
    }
    ~World() {
        running_ = false;
        timer_thread_.join();
    }

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