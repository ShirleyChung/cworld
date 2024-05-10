#ifndef _action_of_persons_2024_
#define _action_of_persons_2024_

#include "person.h"
#include "prompt.h"
#include <time.h>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

// 一個動作
struct Action {
    std::thread action_thread_;
    virtual void OnActing() {}
    Action()
    : action_thread_(&Action::OnActing, this)
    {}
    // 隨機暫停atLeast~atMost
    void SleepRandom(unsigned int atLeast, unsigned int atMost) {
        int rest_time = atLeast + int((float(atMost - atLeast)*(float)rand() / (float)RAND_MAX));
        std::this_thread::sleep_for(std::chrono::milliseconds(rest_time));
    }
};

// 人物之間攻擊
struct Fighting: Action {
    Person &person1_, &person2_;
    Fighting(Person& p1, Person& p2) 
    : person1_(p1)
    , person2_(p2)
    {}
    
    // 計算統合輸出
    int CalculateForce(Person& p) {
        float strengh = p.GetCharacter("strength", 50.0f) * 0.5f;
        float skill   = p.GetCharacter("skill", 50.0f) * 0.3f; 
        float speed   = p.GetCharacter("speed", 50.0f) * 0.2f; 
        float locky = (80.0f + 20.0f * ((float)rand() / (float)RAND_MAX)) / 100.0f;
        int force = int((strengh + skill + speed) * locky);
        return force;
    }

    // 攻擊對手
    void Beat(Person& offender, Person& defender) {
        // 雙方的統合輸出的差值, 給予方不能小於接受方
        int damage = max(0, CalculateForce(offender) - CalculateForce(defender));
        defender.stamina_ -= damage;
        cout << offender.GetName() << " 攻擊了 " << defender.GetName() << " 造成 " << damage << " 點傷害." << endl;
    }
    virtual void OnActing() {
        person1_.stamina_ = 100;
        person2_.stamina_ = 100;
        cout << person1_.GetName() << " stamina:" << person1_.stamina_ << endl;
        cout << person2_.GetName() << " stamina:" << person2_.stamina_ << endl;
        int count = 10;
        while (person1_.stamina_ > 0 && person2_.stamina_ > 0 && count-- > 0) {
            srand((unsigned)time(NULL));
            Beat(person1_, person2_);
            SleepRandom(1000, 3000);
            Beat(person2_, person1_);
            SleepRandom(1000, 3000);
        }
        if (person1_.stamina_ != person2_.stamina_) {
            std::string name = person1_.stamina_ > person2_.stamina_? person1_.GetName(): person2_.GetName();
            cout << name << " win!" << endl;
        }
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
