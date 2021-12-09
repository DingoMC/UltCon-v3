//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Basic Plugin class definition
#ifndef BASIC_H
#define BASIC_H
#include <string>
#include <time.h>
#include <windows.h>
using namespace std;
class Basic {
    public:
        Basic();
        // Basic Variables
        bool debug, exit, logged;
        int cmd_count, ext_count, err_count, UserPermissionLevel;
        int permissionLevel[12];
        char prefix;
        string cmd, username, password;
        HANDLE hCon;
        clock_t startTime;
        // Constant lists set up in basic.cpp
        string commands[12], aliases[12], external[5], desc[12], ext_desc[5];
        void about();
        void clear();
        bool crash();
        bool debugSwitch();
        void disable(bool*);
        void enable(bool*);
        bool exitCmd();
        void help(bool*);
        bool logout();
        void plugins(bool*);
        void systemCmd();
        void echo(string);
        void getCacheFromFile(bool*);
        void saveCacheToFile(bool*);
        bool auth();
        int SetPermissionLevel();
        string getTime();
        void cc(string);
        void ErrorCommandUnknown(string);
        void ErrorPermissionDenied();
        bool ErrorPluginPanic();
        void ErrorInvalidInput();
        void ErrorBasicPluginDisable();
        void ErrorPluginDisabled();
        void ErrorBasicPluginEnable();
        void ErrorPluginEnabled();
};
#endif // BASIC_H