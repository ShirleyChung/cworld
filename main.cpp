#include <iostream>
#include "rapidjson/document.h"
#include "world.h"

using namespace std;

int main(int argc, char* argv[])
{
    // 解析 JSON 字符串
    const char* json = "{\"hello\": \"world\",\"code\":100}";
    rapidjson::Document document;
    document.Parse(json);

    // 讀取 JSON 屬性
    if (document.HasMember("hello")) {
        const rapidjson::Value& value = document["hello"];
        if (value.IsString()) {
            std::cout << "hello: " << value.GetString() << std::endl;
        cout << "member: code = " << document["code"].GetInt() << endl;
 	}
	}
    World w;
	cout << "hello~~~~" << endl;
    cout << "world: " << w.ToString();
	return 0;
}
