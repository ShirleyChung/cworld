#ifndef _action_of_persons_2024_
#define _action_of_persons_2024_

#include "person.h"
#include <set>

using namespace std;

struct Action {

};

class ActionManager {
    typedef const std::string (ActionManager::*CMD_CALLBACK)(const std::string& param);

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

    PersonManager& personMgr_;
public:
    ActionManager(PersonManager& mgr)
    : personMgr_(mgr)
    {}
};

#endif
