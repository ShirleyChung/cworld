#ifndef _object_define_2024_
#define _object_define_2024_

#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "rapidjson/document.h"
#include "prompt.h"

#include "rapidjson/stringbuffer.h"
#include <rapidjson/writer.h>

using namespace std;
using namespace rapidjson;

/* 可從JSON回復的物件 */
class JSONObj {
protected:
    /// @brief 特徵資料
    Document characters_;

public:
    void LoadFromStr(const std::string& str) {
        characters_.Parse(str.c_str());
    }
    // 轉成字串以便後續處理
    const std::string ToString() {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        characters_.Accept(writer);
        
        std::string str = buffer.GetString();
        return str;
    }
    // 取得一個特徵
    const std::string GetCharacter(const std::string& key) {
        if (characters_.HasMember(key.c_str())) {
            const rapidjson::Value& value = characters_[key.c_str()];
            return value.IsString()? value.GetString(): "";
        } else {
            return "";
        } 	    
    }
    // 取得一個特徵, 若沒有則以預設值新增
    const std::string GetCharacter(const std::string& key, const std::string& defVal) {
        if (characters_.HasMember(key.c_str())) {
            const rapidjson::Value& value = characters_[key.c_str()];
            return value.IsString()? value.GetString(): "";
        } else {
            AddCharacter(key, defVal);
            return defVal;
        } 	    
    }
    // 取得一個特徵, 若沒有則以預設值新增
    int GetCharacter(const std::string& key, int defVal) {
        if (characters_.HasMember(key.c_str())) {
            const rapidjson::Value& value = characters_[key.c_str()];
            std::string ret = value.IsString()? value.GetString(): "";
            return atoi(ret.c_str());
        } else {
            std::stringstream ss;
            ss << defVal;
            AddCharacter(key, ss.str());
            return defVal;
        } 	    
    }
    // 取得一個特徵, 若沒有則以預設值新增
    float GetCharacter(const std::string& key, float defVal) {
        if (characters_.HasMember(key.c_str())) {
            const rapidjson::Value& value = characters_[key.c_str()];
            std::string ret = value.IsString()? value.GetString(): "";
            return atof(ret.c_str());
        } else {
            std::stringstream ss;
            ss << defVal;
            AddCharacter(key, ss.str());
            return defVal;
        } 	    
    }
    // 加入一個特徵
    void AddCharacter(const std::string& key, const std::string& value) {
        Document::AllocatorType& allocator = characters_.GetAllocator();
        characters_.AddMember(Value(key.c_str(), allocator).Move(), Value(value.c_str(), allocator).Move(), characters_.GetAllocator());
    }
    // 設定一個特徵的值by string
    void SetCharacter(const std::string& key, const std::string& value) {
        if (characters_.HasMember(key.c_str())) {
            rapidjson::Document::AllocatorType& allocator = characters_.GetAllocator();
            characters_[key.c_str()].SetString(value.c_str(), allocator);
        } else
            AddCharacter(key, value);
    }
    // 設定一個特徵的值by int
    void SetCharacter(const std::string& key, int value) {
        if (characters_.HasMember(key.c_str())) {
            rapidjson::Document::AllocatorType& allocator = characters_.GetAllocator();
            std::stringstream ss;
            ss << value;
            characters_[key.c_str()].SetString(ss.str().c_str(), allocator);
        } else {
            std::stringstream ss;
            ss << value;
            AddCharacter(key, ss.str());
        }
    }
    // 刪掉一個特徵
    void DeleteCharacter(const std::string& key) {
        if (characters_.HasMember(key.c_str())) {
            characters_.RemoveMember(key.c_str());
        } else
            cout << "no member named: " << key << endl;
    }
};

// 管理一群JSON物件，可從JSON檔回復
template<class T>
class JSONObjManager {
protected:
    typedef std::vector<T> OBJECTARRAY;
    OBJECTARRAY objMap_;
public:
    JSONObjManager () {        
    }
    void LoadFromFile(const std::string& fn) {
        cout << "-= Load from " << fn << "=- " << endl;
        std::ifstream fs(fn.c_str());
        if (fs) {
            std::string line;
            while (getline(fs, line)) {
                T p(line);
                objMap_.push_back(p);
            }
        }
    }
    void SaveToFile(const std::string& fn) {
        cout << "-= Person Save To " << fn << "=- " << endl;
        std::ofstream fs(fn.c_str(), std::ofstream::out | std::ofstream::trunc);
        if (fs) {
            for (T& i : objMap_) {
                fs << i.ToString() << endl;
            }
            fs.flush();
            cout << "Save OK." << endl;
        } else
            cout << fn << " open fail" << endl;
    }
    // 搜尋陣列中，有成員key=value的元素
    T* GetIf(const std::string& key, const std::string& value) {
        auto it = FindIf(key, value);
        return (it == end(objMap_))? NULL: &(*it);
    }
    typename OBJECTARRAY::iterator FindIf(const std::string& key, const std::string& value) {
        return find_if(begin(objMap_), end(objMap_), [key, value](T& i) {
            return i.GetCharacter(key) == value;
        });
    }
};

#endif