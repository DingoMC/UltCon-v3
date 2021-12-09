//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Geometry Plugin class definition
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <string>
#include <time.h>
#include <windows.h>
#include <cmath>
using namespace std;
class Geometry {
    public:
        Geometry();
        void main(bool,string,clock_t);
    private:
        bool debug, exit;
        int cmd_count, err_count, prec;
        char prefix;
        string cmd, username;
        HANDLE hCon;
        string commands[15], aliases[15], desc[15];
        clock_t startInit;
        void about();
        void circle();
        void clear();
        void cube();
        bool exitCmd();
        void help();
        void hexagon();
        void octogon();
        void prc();
        void rectangle();
        void rhomboid();
        void rhombus();
        void rtriangle();
        void square();
        void triangle();
        string getTime();
        void cc(string);
        void echo(string);
        void ErrorCommandUnknown(string);
        void ErrorInvalidInput();
};
#endif //GEOMETRY_H