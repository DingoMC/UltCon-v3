//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Encryptors plugin class definition
#ifndef ENCRYPTORS_H
#define ENCRYPTORS_H
#include <string>
#include <time.h>
#include <windows.h>
#define ENC_CMDS 7
using namespace std;
class Enc {
    public:
        Enc();
        void main(bool,string,clock_t);
    private:
        bool debug, exit;
        int cmd_count, err_count;
        char prefix;
        string cmd, username;
        HANDLE hCon;
        string commands[ENC_CMDS], aliases[ENC_CMDS], desc[ENC_CMDS];
        clock_t startTime;
        string getTime();
        void about();
        void clear();
        void col();
        void csr();
        void etm();
        bool exitCmd();
        void help();
        void cc(string);
        void echo(string);
        void ErrorCommandUnknown(string);
        void ErrorInvalidInput();
};
#endif // ENCRYPTORS_H