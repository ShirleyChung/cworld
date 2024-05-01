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
    std::string GetName() {
        return GetCharacter("name");
    }
};

#endif