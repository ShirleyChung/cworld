#ifndef _action_of_persons_2024_
#define _action_of_persons_2024_

#include "person.h"
#include "prompt.h"
#include <time.h>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

struct Action {
    std::thread action_thread_;
    virtual void OnActing() {}
    Action()
    : action_thread_(&Action::OnActing, this)
    {}
};

struct Fighting: Action {
    Person &person1_, &person2_;
    Fighting(Person& p1, Person& p2) 
    : person1_(p1)
    , person2_(p2)
    {}
    virtual void OnActing() {
        person1_.stamina_ = 100;
        person2_.stamina_ = 100;
        cout << person1_.GetName() << " stamina:" << person1_.stamina_ << endl;
        cout << person2_.GetName() << " stamina:" << person2_.stamina_ << endl;
        int count = 10;
        while (person1_.stamina_ > 0 && person2_.stamina_ > 0 && count-- > 0) {
            person1_.Beat(person2_);
            srand((unsigned)time(NULL));
            int rest_time = 1 + int((2.0f*(float)rand() / (float)RAND_MAX));
            std::this_thread::sleep_for(std::chrono::milliseconds(rest_time * 1000));
            person2_.Beat(person1_);
            rest_time = 1 + int((2.0f*(float)rand() / (float)RAND_MAX));
            std::this_thread::sleep_for(std::chrono::milliseconds(rest_time * 1000));
        }
        if (person1_.stamina_ > person2_.stamina_)
            cout << person1_.GetName() << " win!" << endl;
        else if ((person1_.stamina_ < person2_.stamina_))
            cout << person2_.GetName() << " win!" << endl;
        else
            cout << "draw!" << endl;
    }
};

class ActionManager: public CommandFunctionSet<ActionManager> {

    typedef std::list<Action*> ACTION_LIST;
    ACTION_LIST act_list_;

    const std::string Attack(const std::string& params) {
        std::string str = params;
        std::string person1 = GetContent(str, ' ');
        std::string person2 = GetContent(str, ' ');
        if (Person* p1 = personMgr_.GetIf("name", person1)) {
            if (Person* p2 = personMgr_.GetIf("name", person2)) {
                cout << person1 << " attacking " << person2 << endl;
                act_list_.push_back(new Fighting(*p1, *p2));
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
