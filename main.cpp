#include "rapidjson/document.h"
#include "world.h"

using namespace std;

int main(int argc, char* argv[])
{
    Person person1;
    person1.LoadFromStr("{\"name\": \"dummy\",\"inteligent\":1}");
    cout << "person 1's name: " << person1.GetCharacter("name") << endl;
    cout << "person 1's intl: " << person1.GetCharacter("inteligent") << endl;

    World w;
    Prompt pmt;
    pmt.RegisterCmdCallback(&w);
    pmt.run();
	return 0;
}
