#ifndef _cworld_Define_2024_
#define _cworld_Define_2024_

#include "person.h"
#include "prompt.h"
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

// 取得Token
const std::string GetContent(std::string& str, const char endChar) {
    const std::string::size_type begin_pos = str.find(endChar);
    if (begin_pos != std::string::npos) {
        const std::string substr = str.substr(0, begin_pos);
        str = str.substr(begin_pos + sizeof(endChar));
        return substr;
    }
    const std::string substr = str;
    str = std::string();
    return substr;
}

class World : public CommandReciever
{
    typedef const std::string (World::*CMD_CALLBACK)(const std::string& param);

    typedef std::map<std::string, CMD_CALLBACK> CMDCBK_MAP;

    CMDCBK_MAP mapCmdCb_;
    CMDCBK_MAP cmdAlias_;

    PersonManager personMgr_;

    // 列出所有人物
    const std::string ShowPersons(const std::string& params) {
        personMgr_.ListPersons();
        return "";
    }
    // 建立一個人物
    const std::string CreatePerson(const std::string& params) {
        if (params.empty()) {
            cout << "Please input 'Person_name prop_key1 prop_val1 prop_key2 prop_val2 ...'" << endl;
            return "";
        }
        std::string str = params;
        std::string name = GetContent(str, ' ');
        do {
            std::string key = GetContent(str, ' ');
            std::string value = GetContent(str, ' ');
            personMgr_.EditPerson(name, key, value);
        } while(!str.empty());
        return "";
    }
    // 編輯一個人物的屬性
    const std::string EditPerson(const std::string& params) {
        std::string str = params;
        std::string name = GetContent(str, ' ');
        std::string key = GetContent(str, ' ');
        std::string value = str;
        personMgr_.EditPerson(name, key, value);
        return "";
    }
    // 刪掉一個人物
    const std::string DeletePerson(const std::string& name) {
        personMgr_.DeletePerson(name);
        return "";
    }

    const std::string ListCommand(const std::string& params) {
        for (CMDCBK_MAP::iterator i = mapCmdCb_.begin(); i != mapCmdCb_.end(); ++i) {
            cout << i->first << endl;
        }
        return "";
    }

    void SetupCmdLists() {
        cmdAlias_["sp"]  =  mapCmdCb_["showpersons"] = &World::ShowPersons;
        cmdAlias_["crp"] =  mapCmdCb_["createperson"] = &World::CreatePerson;
        cmdAlias_["edp"] =  mapCmdCb_["editperson"] = &World::EditPerson;
        cmdAlias_["rmp"] =  mapCmdCb_["deleteperson"] = &World::DeletePerson;
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
        std::string str = line;
        std::string cmd   = GetContent(str, ' ');
        std::string param = str;
        std::string result;
        CMDCBK_MAP::iterator i = mapCmdCb_.find(cmd);
        if (i == mapCmdCb_.end())
            i = cmdAlias_.find(cmd);
        if (i != mapCmdCb_.end() || i != cmdAlias_.end()) {
            result = (this->*i->second)(param);
            return true;
        }
        return false;
    }
};

#define _cworld_Define_2024_
#endif