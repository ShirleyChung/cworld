#include "rapidjson/document.h"
#include "world.h"

using namespace std;

int main(int argc, char* argv[])
{
    World w;
    Prompt pmt;
    pmt.RegisterCmdCallback(&w);
    pmt.run();
	return 0;
}
