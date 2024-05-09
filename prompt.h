#ifndef _prompt_cmd_2024_
#define _prompt_cmd_2024_

#include <iostream>
#include <list>
#include <set>
#include "utility.h"

// 可讓Promprt指令列註冊呼叫的介面
struct Commandable {
    virtual bool OnCommand(const std::string& cmd) = 0;
};

// 指令對應函式的類別. 子類別可以實作指令函式，讓指令介面呼叫
template<typename T>
struct CommandFunctionSet: Commandable {

    typedef const std::string (T::*CMD_CALLBACK)(const std::string& param);

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

       // 輸入字串，從字串中拆解出command及parameter, 並從mapCmdCb中找出對應的函式來呼叫
    virtual bool OnCommand(const std::string &line)
    {
        std::string str = line;
        std::string cmd   = GetContent(str, ' ');
        std::string param = str;
        std::string result;

        // 比對指令
        typename CMD_SET::iterator i = find_if(begin(cmdSet_), end(cmdSet_), [cmd](const CMD_INFO& info) {
            return cmd == info.cmd_ || cmd == info.alias_;
        });
        // 執行指令
        if (i != end(cmdSet_)) {
            result = (((T*)this)->*i->cmdCb_)(param);
            return true;
        }
        return false;
    }
};

// Prompt and Input Command to execute
template<typename T>
class Prompt 
{
    std::string prompt_;
    std::string cmd_;
    typedef std::list<Commandable*> CMDRCV_LIST;
    CMDRCV_LIST cmdrcvList_;
    bool loopWork_;
public:
    Prompt()
    : prompt_("enter command")
    , loopWork_(true)
    {}

    // 註冊命令呼叫Callback
    void RegisterCmdCallback(Commandable* pCmdRcv) {
        cmdrcvList_.push_back(pCmdRcv);
    }

    // 取消註冊Callback
    void UnRegisterCmdCallback(Commandable* pObj) {
        for (typename CMDRCV_LIST::iterator i = cmdrcvList_.begin(); i != cmdrcvList_.end(); ++i) {
            if (*i == pObj) {
                cmdrcvList_.erase(i);
                i = cmdrcvList_.begin();
            }
        }
    }

    // 呼叫所註冊的Callback
    void ExecuteCommand(const std::string& cmd) {
        bool ok = false;
        for (typename CMDRCV_LIST::iterator i = cmdrcvList_.begin(); i != cmdrcvList_.end(); ++i) {
            ok |= (*i)->OnCommand(cmd);
        }
        if (!ok)
            std::cout << "Unknown command: " << cmd << std::endl;
    }

    // 檢查是否Quit
    bool QuitCommand(const std::string& cmd) {
        if (cmd == "quit" || cmd == "exit" || cmd == "q") {
            std::cout << "Finish process. Bye." << std::endl;
            return true;
        }
        return false;
    }

    //  執行命令
    void run() {
        while(loopWork_) {
            std::cout << prompt_ << " > ";
            std::getline(std::cin, cmd_);
            if (QuitCommand(cmd_))
                break;
            ExecuteCommand(cmd_);
        }
    }
};

#endif