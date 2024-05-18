#include "rapidjson/document.h"
#include "world.h"
#include "libcworld.h"

using namespace std;

extern "C" {
    World w;
    CALLBACK cmdCb_ = NULL;

    int main(int, char* [])
    {

        w.run();
        return 0;
    }

    /* 從外部輸入指令 */
    void InputCommand(const char* cmd) {
        w.ExecuteCommand(cmd);
    }
    
    /* 設定輸出時，要導向的回呼函式 */
    void SetOutputCallback(CALLBACK cb) {
        cmdCb_ = cb;
    }

    /* 輸出時，呼叫此函式 */
    /// key:     訊息種類
    /// message: 訊息內容
    void  OnOutput(MESSAGE_TYPE key, const char* message) {
        if (cmdCb_)
            cmdCb_(key, message);
        else
            cout << message << endl;
    }
}
