#ifndef _prompt_cmd_2024_
#define _prompt_cmd_2024_

#include <iostream>
#include <string>
#include <list>
#include <set>

// Command callback interface
struct Commandable {
    virtual bool OnCommand(const std::string& cmd) = 0;
};

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

template<typename T>
struct CommandFunctionSet {

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