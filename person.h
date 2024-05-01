#ifndef _person_define_2024_
#define _person_define_2024_

#include <map>
#include <string>
#include <sstream>
#include <map>
#include "rapidjson/document.h"
#include "prompt.h"

#include "rapidjson/stringbuffer.h"
#include <rapidjson/writer.h>

using namespace std;
using namespace rapidjson;

/* 定義一個人物的資料 */
class Person {
    /// @brief 人物特徵資料
    Document characters_;

public:
    Person() {

    }
    void LoadFromStr(const char* str) {
        characters_.Parse(str);
    }
    // 轉成字串以便整合儲成檔案
    const std::string ToString() {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        characters_.Accept(writer);
        
        std::string str = buffer.GetString();
        return str;
    }
    // 取得人物的一個特徵
    const std::string GetCharacter(const std::string& key) {
        const rapidjson::Value& value = characters_[key.c_str()];
        return value.IsString()? value.GetString(): "";
 	    
    }
};

#endif