#ifndef _cworld_Define_2024_
#define _cworld_Define_2024_

#include "person.h"
#include "prompt.h"
#include <time.h>
#include <thread>
#include <chrono>
#include <set>

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

    struct CMD_INFO {
        CMD_CALLBACK cmdCb_;
        std::string  cmd_;
        std::string  desc_;
        std::string  alias_;

        bool operator<(const CMD_INFO& rhs) const {
            return cmd_ < rhs.cmd_;
        }
        bool operator==(const CMD_INFO& rhs) const {
            return cmd_ == rhs.cmd_ && cmdCb_ == rhs.cmdCb_;
        }
    };

    typedef std::set<CMD_INFO> CMD_SET;
    CMD_SET cmdSet_;

    PersonManager personMgr_;

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

        // 比對指令
        CMD_SET::iterator i = find_if(begin(cmdSet_), end(cmdSet_), [cmd](const CMD_INFO& info) {
            return cmd == info.cmd_ || cmd == info.alias_;
        });
        // 執行指令
        if (i != end(cmdSet_)) {
            result = (this->*i->cmdCb_)(param);
            return true;
        }
        return false;
    }
};

#define _cworld_Define_2024_
#endif