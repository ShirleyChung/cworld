#ifndef _person_define_2024_
#define _person_define_2024_

#include <map>
#include "object.h"

/* 定義一個人物的資料 */
class Person: public JSONObj {
    int age;
    std::string name;
public:
    // 以JSON建立一個Person
    Person(const std::string& str = "")
    : age(-1)
    {
        if (str.empty()) {
            std::stringstream ss;
            ss << "{\"name\":\"person"<< rand() << "\"}";
            LoadFromStr(ss.str());
        } else
            LoadFromStr(str.c_str());
    }
    // 建立一個Person, 並指定某個特徵
    Person(const std::string& key, const std::string& value) 
    : age(-1)
    {
        characters_.SetObject();
        AddCharacter(key, value);
    }
    // Copy constructor. C++11已明確定義=delete, 因有自定義的Constructor, 因此需要明確實作以便後續的複製操作.
    Person(const Person& rhs) {
        (*this) = rhs;
    }
    Person& operator=(const Person& rhs) {
        this->age = rhs.age;
        this->name = rhs.name;
        characters_.SetObject();
        characters_.CopyFrom(rhs.characters_, characters_.GetAllocator());
        return *this;
    }
    // 名字
    std::string GetName() {
        if (name.empty())
            name = GetCharacter("name");
        return name;
    }
    // 增加年紀
    void IncreaseAge(int timepass) {
        if (age < 0)
            age = atoi(GetCharacter("age").c_str());
        age += timepass;
        SetCharacter("age", age);
    }
    // 取得簡述
    std::string GetBrief() {
        std::stringstream ss;
        ss << "[名字]:" << GetCharacter("name") <<", " << "[年紀]：" << GetCharacter("age") << ", " << GetCharacter("brief");
        return ss.str();
    }
};

// 管理所有人物
#define PERSON_DATA_FILE "data/person.data"
class PersonManager: public JSONObjManager<Person> {
    public:
    PersonManager() {
        LoadFromFile(PERSON_DATA_FILE);
    }
    virtual ~PersonManager() {
        SaveToFile(PERSON_DATA_FILE);
    }
    // 列出所有人物
    void ListPersons() {
        for (Person& p : objMap_) {
            cout << p.GetBrief() << endl;
        }
    }
    // 所有人物時間流逝1秒
    void PersonAging() {
        for (Person& p : objMap_) {
            p.IncreaseAge(1);
        }
    }
    // 建立一個Person
    Person& CreatePerson(const std::string name) {
        cout << "Creating " << name << "..." << endl;
        objMap_.push_back(Person("name", name));
        return objMap_.back();
    }
};

#endif