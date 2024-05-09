#ifndef _utility_for_programming_2024_
#define _utility_for_programming_2024_

#include <string>

// 取得Token
const std::string GetContent(std::string& str, const char endChar) {
    const std::string::size_type begin_pos = str.find(endChar);
    if (begin_pos != std::string::npos) {
        const std::string substr = str.substr(0, begin_pos);
        str = str.substr(begin_pos + sizeof(endChar));
        return substr;
    }
    const std::string substr = str;
    str = std::string();
    return substr;
}

#endif
