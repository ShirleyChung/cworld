#ifndef _lib_cworld_declaration_2024_
#define _lib_cworld_declaration_2024_

extern "C" {
    enum MESSAGE_TYPE {
        MSG_HINT,
        MSG_INFO,
        TOTAL_MSG_TYPES
    };
    typedef const char* (*CALLBACK)(MESSAGE_TYPE, const char*);

    /* 從外部輸入指令 */
    void InputCommand(const char* cmd);
    /* 設定輸出時，要導向的回呼函式 */
    void SetOutputCallback(CALLBACK cb);
    /* 輸出時，呼叫此函式 */
    void OnOutput(MESSAGE_TYPE key, const char* message);
}

#endif