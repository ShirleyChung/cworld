#ifndef _cworld_Define_2024_
#define _cworld_Define_2024_

#include "action.h"

using namespace std;

class World : public Prompt<World>
{
    PersonManager personMgr_;
    ActionManager actionMgr_;

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
    : actionMgr_(personMgr_)
    , timer_thread_(&World::OnTimerThread, this)
    , running_(true)
    {
        RegisterCmdCallback(&personMgr_);
        RegisterCmdCallback(&actionMgr_);
        std::cout << "-= World Start =-" << endl;
    }
    ~World() {
        running_ = false;
        timer_thread_.join();
    }
};

#define _cworld_Define_2024_
#endif