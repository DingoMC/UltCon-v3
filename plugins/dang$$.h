//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - dang$$ class definition
#ifndef DANG$$_H
#define DANG$$_H
#include <string>
#include <time.h>
#include <windows.h>
#define STDANG_CTYPES 4
#define STDANG_MTYPES 1
using namespace std;
class Dang {
    public:
        Dang();
        void main(bool,string,clock_t);
    private:
        const string CodesList[STDANG_CTYPES] = {"1A","2B","3C","0R"};
        const int Positioners[STDANG_CTYPES] = {26,43,60,0};
        const string MessagesList[STDANG_MTYPES] = {"RS"};
        bool debug, exit;
        int cmd_count, err_count;
        char prefix;
        string cmd, username;
        HANDLE hCon;
        string commands[8], aliases[8], desc[8];
        clock_t startTime;
        string getTime();
        void about();
        void clear();
        void code();
        void decode();
        bool exitCmd();
        void help();
        void message();
        void minecraft();
        string coder(string,string);
        string decoder(string,string);
        string CreateMessage(string,string);
        void cc(string);
        void echo(string);
        void ErrorCommandUnknown(string);
        void ErrorInvalidInput();
};
#endif // DANG$$_H