#ifndef _object_define_2024_
#define _object_define_2024_

#include <string>
#include <sstream>
#include <map>
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
    // 加入一個特徵
    void AddCharacter(const std::string& key, const std::string& value) {
        Document::AllocatorType& allocator = characters_.GetAllocator();
        characters_.AddMember(Value(key.c_str(), allocator).Move(), Value(value.c_str(), allocator).Move(), characters_.GetAllocator());
    }
};

#endif