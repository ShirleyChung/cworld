#ifndef _action_of_persons_2024_
#define _action_of_persons_2024_

#include "person.h"
#include "prompt.h"

using namespace std;

struct Action {

};

class ActionManager: public CommandFunctionSet<ActionManager> {

    const std::string Attack(const std::string& params) {
        std::string str;
        std::string person1 = GetContent(str, ' ');
        std::string person2 = GetContent(str, ' ');
        if (Person* p1 = personMgr_.GetIf("name", person1)) {
            if (Person* p2 = personMgr_.GetIf("name", person2)) {
                cout << person1 << " attacking " << person2 << endl;
            } else
                cout << person2 << " not found" << endl;
        } else
            cout << person1 << " not found" << endl;
        return "";
    }

    void SetupCmdLists() {
        cmdSet_.insert(CMD_INFO{&ActionManager::Attack, "attack", "one person attack to other", "atk"});
    }

    PersonManager& personMgr_;
public:
    ActionManager(PersonManager& mgr)
    : personMgr_(mgr)
    {
        SetupCmdLists();
    }
};

#endif
