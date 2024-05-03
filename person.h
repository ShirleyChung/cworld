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
        SetCharacter("age", age + timepass);
    }
    // 取得簡述
    std::string GetBrief() {
        std::stringstream ss;
        ss << "[名字]:" << GetCharacter("name") <<", " << "[年紀]：" << GetCharacter("age") << ", " << GetCharacter("brief");
        return ss.str();
    }
};

// 管理所有人物
class PersonManager: public JSONObjManager<Person> {
    public:
    PersonManager() {
        LoadFromFile("data/person.data");
    }
    // 列出所有人物
    void ListPersons() {
        for (OBJECTMAP::iterator i = objMap_.begin(); i != objMap_.end(); ++i) {
            cout << i->second.GetBrief() << endl;
        }
    }
    // 所有人物時間流逝1秒
    void PersonAging() {
        for (OBJECTMAP::iterator i = objMap_.begin(); i != objMap_.end(); ++i) {
            i->second.IncreaseAge(1);
        }
    }
    // 列出所有人物
    const std::string ShowPersons(const std::string& params) {
        ListPersons();
        return "";
    }
};

#endif