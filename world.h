#ifndef _cworld_Define_2024_
#define _cworld_Define_2024_

#include <time.h>
#include <thread>
#include <chrono>
#include "prompt.h"
#include "action.h"

using namespace std;

class World : public CommandFunctionSet<World>
{
    PersonManager personMgr_;
    ActionManager actionMgr_;

    // 列出人物, 若參數為空白則列出所有
    const std::string ShowPersons(const std::string& params) {
        std::string str = params;
        do {
            std::string name = GetContent(str, ' ');
            personMgr_.ListPersons(name);
        } while (!str.empty());
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
    // 刪掉一個人物的特徵
    const std::string DeletePersonCharacter(const std::string& params) {
        std::string str = params;
        std::string name = GetContent(str, ' ');
        do {
            std::string key = GetContent(str, ' ');
            personMgr_.DeletePersonCharacter(name, key);
        } while(!str.empty());
        return "";
    }

    const std::string ListCommand(const std::string& params) {
        cout << "\nList All Commands:" << endl;
        for (CMD_SET::iterator i = cmdSet_.begin(); i != cmdSet_.end(); ++i) {
            cout << i->cmd_ << "," << i->alias_ << "\t:" << i->desc_ << endl;
        }
        cout << "--\nexit, quit to Quit\n" << endl;
        return "";
    }

    void SetupCmdLists() {
        cmdSet_.insert(CMD_INFO{&World::ShowPersons, "showperons", "show persons or person's detail.", "sp"});
        cmdSet_.insert(CMD_INFO{&World::CreatePerson, "createperson", "create a person.", "crp"});
        cmdSet_.insert(CMD_INFO{&World::EditPerson, "editperson", "edit a property of a person.", "edp"});
        cmdSet_.insert(CMD_INFO{&World::DeletePerson, "deleteperson", "delete a person.", "rmp"});
        cmdSet_.insert(CMD_INFO{&World::ListCommand, "listcommand", "list all commands.", "ll"});
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
    , actionMgr_(personMgr_)
    {
        SetupCmdLists();
        std::cout << "-= World Start =-" << endl;
    }
    ~World() {
        running_ = false;
        timer_thread_.join();
    }
};

#define _cworld_Define_2024_
#endif