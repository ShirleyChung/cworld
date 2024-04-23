#include <iostream>
#include <string>
#include <list>

// Command callback interface
struct CommandReciever {
    virtual bool OnCommand(const std::string& cmd) = 0;
};

// Prompt and Input Command to execute
class Prompt 
{
    std::string prompt_;
    std::string cmd_;
    typedef std::list<CommandReciever*> CMDRCV_LIST;
    CMDRCV_LIST cmdrcvList_;
public:
    Prompt()
    : prompt_("enter command")
    {}

    // 註冊命令呼叫Callback
    void RegisterCmdCallback(CommandReciever* pCmdRcv) {
        cmdrcvList_.push_back(pCmdRcv);
    }

    // 取消註冊Callback
    void UnRegisterCmdCallback(CommandReciever* pObj) {
        for (CMDRCV_LIST::iterator i = cmdrcvList_.begin(); i != cmdrcvList_.end(); ++i) {
            if (*i == pObj) {
                cmdrcvList_.erase(i);
                i = cmdrcvList_.begin();
            }
        }
    }

    // 呼叫所註冊的Callback
    void ExecuteCommand(const std::string& cmd) {
        for (CMDRCV_LIST::iterator i = cmdrcvList_.begin(); i != cmdrcvList_.end(); ++i) {
            (*i)->OnCommand(cmd);
        }
    }

    // 檢查是否Quit
    bool QuitCommand(const std::string& cmd) {
        if (cmd == "quit" || cmd == "exit" || cmd == "q") {
            std::cout << cmd << std::endl;
            return true;
        }
        return false;
    }

    //  執行命令
    void run() {
        do {
            std::cout << prompt_ << " > ";
            std::cin >> cmd_;
            ExecuteCommand(cmd_);
        } while (!QuitCommand(cmd_));
    }
};