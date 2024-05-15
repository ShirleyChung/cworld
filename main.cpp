#include "rapidjson/document.h"
#include "world.h"
#include "libcworld.h"

using namespace std;

extern "C" {
    World w;

    int main(int, char* [])
    {

        w.run();
        return 0;
    }

    void InputCommand(const char* cmd) {
        cout << "test " << cmd << endl;
    }
    
    void SetOutputCallback(CALLBACK cb) {
        cout << "test callback:" << cb << " set" << endl;
        cout << cb("test", "123");
    }
}
