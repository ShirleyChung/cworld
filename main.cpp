#include "rapidjson/document.h"
#include "world.h"

using namespace std;

extern "C" {
World w;

int main(int, char* [])
{

    w.run();
	return 0;
}
}
