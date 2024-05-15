#ifndef _lib_cworld_declaration_2024_
#define _lib_cworld_declaration_2024_

extern "C" {
    typedef const char* (*CALLBACK)(const char*, const char*);

    void InputCommand(const char* cmd);
    void SetOutputCallback(CALLBACK cb);
}

#endif