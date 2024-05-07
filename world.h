#ifndef _cworld_Define_2024_
#define _cworld_Define_2024_

#include "person.h"
#include "prompt.h"
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

class World : public CommandReciever
{
    typedef const std::string (World::*CMD_CALLBACK)(const std::string& param);

    typedef std::map<std::string, CMD_CALLBACK> CMDCBK_MAP;

    CMDCBK_MAP mapCmdCb_;

    PersonManager personMgr_;

        // 列出所有人物
    const std::string ShowPersons(const std::string& params) {
        personMgr_.ListPersons();
        return "";
    }
    const std::string CreatePerson(const std::string& name) {
        personMgr_.CreatePerson(name);
        return "";
    }


    void SetupCmdLists() {
        mapCmdCb_["sp"] =  mapCmdCb_["showpersons"] = &World::ShowPersons;
        mapCmdCb_["crp"] =  mapCmdCb_["createperson"] = &World::CreatePerson;
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