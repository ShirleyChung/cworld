#ifndef _person_define_2024_
#define _person_define_2024_

#include <map>
#include "object.h"

/* 定義一個人物的資料 */
class Person: public JSONObj {

public:
    Person(const std::string& str = "") {
        if (str.empty()) {
            std::stringstream ss;
            ss << "{\"name\":\"person"<< rand() << "\"}";
            LoadFromStr(ss.str());
        } else
            LoadFromStr(str.c_str());
    }
    Person& operator=(const Person& rhs) {
        characters_.SetObject();
        characters_.CopyFrom(rhs.characters_, characters_.GetAllocator());
        return *this;
    }
    // 名字
    std::string GetName() {
        return GetCharacter("name");
    }
    // 增加年紀
    void IncreaseAge(int timepass) {
        int age = atoi(GetCharacter("age").c_str());
        SetCharacter("age", ++age);
    }
    // 取得簡述
    std::string GetBrief() {
        std::stringstream ss;
        ss << "[名字]:" << GetCharacter("name") <<", " << "[年紀]：" << GetCharacter("age") << ", " << GetCharacter("brief");
        return ss.str();
    }
};

#endif