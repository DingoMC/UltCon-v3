//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Math Plugin class definition
#ifndef MATH_EX_H
#define MATH_EX_H
#include <string>
#include <time.h>
#include <windows.h>
#include <cmath>
using namespace std;
class MathEx {
    public:
        MathEx();
        void main(bool,string,clock_t);
    private:
        bool debug, exit;
        int cmd_count, err_count, prec;
        char prefix;
        string cmd, username;
        HANDLE hCon;
        string commands[19], aliases[19], desc[19];
        clock_t startTime;
        string getTime();
        void about();
        void add();
        void clear();
        void cosine();
        void divide();
        bool exitCmd();
        void factorial();
        void factorize();
        void gcd();
        void help();
        void logn();
        void logb();
        void multiply();
        void power();
        void prc();
        void sine();
        void root2();
        void subtract();
        void tangent();
        void cc(string);
        void echo(string);
        void ErrorCommandUnknown(string);
        void ErrorInvalidInput();
};
#endif // MATH_EX_H