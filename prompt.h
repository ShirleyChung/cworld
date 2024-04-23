#include <iostream>
#include <string>
#include <list>

typedef bool(*CMD_CALLBACK)(const std::string& cmd, void* pObj);

struct CBData {
    CMD_CALLBACK cb_;
    void* pObj_;
};

class Prompt 
{
    std::string prompt_;
    std::string cmd_;
    typedef std::list<CBData> CBDAT_LIST; 
    CBDAT_LIST cbList_;
public:
    Prompt()
    : prompt_("enter command")
    {}

    // 註冊命令呼叫Callback
    void RegisterCmdCallback(CMD_CALLBACK cb, void* pObj) {
        CBData cbDat;
        cbDat.cb_ = cb;
        cbDat.pObj_ = pObj;
        cbList_.push_back(cbDat);
    }

    // 取消註冊Callback
    void UnRegisterCmdCallback(void* pObj) {
        for (CBDAT_LIST::iterator i = cbList_.begin(); i != cbList_.end(); ++i) {
            if (i->pObj_ == pObj) {
                cbList_.erase(i);
                i = cbList_.begin();
            }
        }
    }

    // 呼叫所註冊的Callback
    void ExecuteCommand(const std::string& cmd) {
        for (CBDAT_LIST::iterator i = cbList_.begin(); i != cbList_.end(); ++i) {
            i->cb_(cmd, i->pObj_);
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