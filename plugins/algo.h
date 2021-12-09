/*
 * This file is part of {{ ultimate_console_v.3.0 }}.
 * This code is made by DingoMC
 * Ultimate Console version 3 - Algo Plugin class definition
 */
# ifndef ALGO_H
# define ALGO_H
# include <string>
# include <time.h>
# include <windows.h>
# include <cmath>
# include <vector>
using namespace std;
/**
 * @brief Matrix - 2-dimensional array of doubles
 */
typedef vector <vector<double>> Matrix;
/**
 * @brief MatrixDet class contains methods for determinant function.
 */
class MatrixDet {
    public:
        Matrix swap_rows (Matrix, int, int);
        double sarrus (Matrix);
        Matrix gauss_redux (Matrix, int, bool&);
};
/**
 * SysVal structure is used for converter function
 * base --> Numeral system base <unsigned int> 
 * value --> Number value as a char string <string>
 */
struct SysVal {
    unsigned int base;
    string value;
};
/**
 * @brief SysConverter class contains methods for converter function.
 */
class SysConverter {
    public:
        bool ValueCorrect (SysVal);
        unsigned long long ConvertToDec (SysVal);
        string ConvertToSys (unsigned long long, unsigned int);
};
/**
 * @brief Horner class contains methods for quadratic function.
 */
class Horner {
    public:
        double factorial (int);
        double HAlgo (double*&, int, int, double);
};
/**
 * @brief Interpolation class contains methods for interpolationl function.
 */
class Interpolation {
    public:
        vector <double> CountFLP (int, double*, int);
        vector <double> MulPolynomialBinomial (vector <double>, int, double, double);
        double NewtonMult (double, double*&, int);
        void DiffDiv (double*&, double*&, double*&, double);
};
// Class Command Pre-declared here
class Command;
class Algo {
    public:
        virtual void about();
        virtual void clear();
        virtual void conv();
        virtual void det();
        virtual void exitCmd();
        virtual void help();
        virtual void interpolationl();
        virtual void interpolationn();
        virtual void pderivative();
        virtual void quadratic();
        Algo();
        void main(bool,string,clock_t);
    private:
        bool debug, exit;
        int cmd_count, err_count;
        char prefix;
        string cmd, username;
        HANDLE hCon;
        vector <Command> C;
        vector <Command> SetupCommands();
        clock_t startTime;
        string getTime();
        MatrixDet MD;
        SysConverter SC;
        Horner HR;
        Interpolation IP;
        void debugInfo(string);
        void cc(string);
        void echo(string);
        void ErrorCommandUnknown(string);
        void ErrorInvalidInput();
};
/**
 * @brief This class is used to store commands data
 */
class Command : public Algo {
    public:
        /**
         * @brief Command Constructor
         * 
         * @param n Command Name
         * @param a Command Alias (If none, set same as Name)
         * @param d Command Description
         * @param init_functor Void function reference executing the command
         */
        Command(string n, string a, string d, void (Algo::*init_functor)()) {
            name = n;
            alias = a;
            desc = d;
            init_f = init_functor;
        }
        string name;                // <Class Field : string> Command Name
        string alias;               // <Class Field : string> Command Alias
        string desc;                // <Class Field : string> Command Description
        void (Algo::*init_f)();     // <Class Field : void(Algo::*)()> Command Initializing Functor (pointer)
        /**
         * @brief void method (Executor) - Executes function as this object. Function passed as pointer
         */
        void exec () {
            (this->*init_f)();
        }
};
#endif // ALGO_H