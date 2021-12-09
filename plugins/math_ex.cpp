//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Math Plugin class methods
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
#include "math_ex.h"
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.000)
#define PI 3.14159265358979
using namespace std;
MathEx::MathEx () {
    // Commands List
    commands[0] = "about";
    commands[1] = "add";
    commands[2] = "clear";
    commands[3] = "cos";
    commands[4] = "divide";
    commands[5] = "exit";
    commands[6] = "factorial";
    commands[7] = "factorize";
    commands[8] = "gcd";
    commands[9] = "help";
    commands[10] = "ln";
    commands[11] = "log";
    commands[12] = "multiply";
    commands[13] = "power";
    commands[14] = "precision";
    commands[15] = "sin";
    commands[16] = "sqrt";
    commands[17] = "subtract";
    commands[18] = "tan";
    // Command Aliases
    aliases[0] = "ab";
    aliases[1] = "+";
    aliases[2] = "cl";
    aliases[3] = "cos";
    aliases[4] = "/";
    aliases[5] = "ex";
    aliases[6] = "!";
    aliases[7] = "fc";
    aliases[8] = "gcd";
    aliases[9] = "?";
    aliases[10] = "ln";
    aliases[11] = "log";
    aliases[12] = "*";
    aliases[13] = "^";
    aliases[14] = "prec";
    aliases[15] = "sin";
    aliases[16] = "sqrt";
    aliases[17] = "-";
    aliases[18] = "tan";
    // Command descriptions
    desc[0] = "Show Info about this plugin";
    desc[1] = "Adds numbers";
    desc[2] = "Clears Math console display";
    desc[3] = "Calculates cosine from an angle";
    desc[4] = "Divides the number";
    desc[5] = "Exit from Math console";
    desc[6] = "Calculates factorial from a number";
    desc[7] = "Gives factors of a number";
    desc[8] = "Gives greatest common divisor";
    desc[9] = "Show this list";
    desc[10] = "Calculates natural log from a number";
    desc[11] = "Calculates a log from a number with custom base";
    desc[12] = "Multiplies numbers";
    desc[13] = "Powers the number";
    desc[14] = "Set precision for numbers";
    desc[15] = "Calculates sine from an angle";
    desc[16] = "Calculates square root from a number";
    desc[17] = "Subtracts from the number";
    desc[18] = "Calculates tangent from an angle";
    cmd_count = sizeof(commands)/sizeof(*commands);
    prefix = '!';
    err_count = 0;
    prec = 3;
    exit = false;
    debug = false;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    username = "None";
}
// MAIN FUNCTION
void MathEx::main(bool debugInit, string usernameInit, clock_t TimeInit) {
    startTime = TimeInit;
    debug = debugInit;
    username = usernameInit;
    exit = false;
    cc("&aWelcome to &bMath Plugin&a. Type !help for help.\n");
    while (exit == false) {
        fflush(stdin);
        SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin");
        cc("&aConsole/&bMath&a> ");
        SetConsoleTextAttribute(hCon, 0x0e);
        getline(cin,cmd);
        if (!cmd.empty()) {
            if (cmd.at(0)!=prefix) echo(cmd);
            else {
                cmd = cmd.erase(0,1);
                err_count = 0;
                for (int i=0; i<cmd_count; i++) if (cmd!=commands[i]) err_count++;
                for (int i=0; i<cmd_count; i++) if (cmd!=aliases[i]) err_count++;
                if (err_count == 2*(cmd_count)) ErrorCommandUnknown(cmd);
                if (cmd == commands[0] || cmd == aliases[0]) about();
                if (cmd == commands[1] || cmd == aliases[1]) add();
                if (cmd == commands[2] || cmd == aliases[2]) clear();
                if (cmd == commands[3] || cmd == aliases[3]) cosine();
                if (cmd == commands[4] || cmd == aliases[4]) divide();
                if (cmd == commands[5] || cmd == aliases[5]) exit = exitCmd();
                if (cmd == commands[6] || cmd == aliases[6]) factorial();
                if (cmd == commands[7] || cmd == aliases[7]) factorize();
                if (cmd == commands[8] || cmd == aliases[8]) gcd();
                if (cmd == commands[9] || cmd == aliases[9]) help();
                if (cmd == commands[10] || cmd == aliases[10]) logn();
                if (cmd == commands[11] || cmd == aliases[11]) logb();
                if (cmd == commands[12] || cmd == aliases[12]) multiply();
                if (cmd == commands[13] || cmd == aliases[13]) power();
                if (cmd == commands[14] || cmd == aliases[14]) prc();
                if (cmd == commands[15] || cmd == aliases[15]) sine();
                if (cmd == commands[16] || cmd == aliases[16]) root2();
                if (cmd == commands[17] || cmd == aliases[17]) subtract();
                if (cmd == commands[18] || cmd == aliases[18]) tangent();
            }
        }
        cin.clear();
        cmd.clear();
    }
    cc("&8Closing &3Math Plugin&8. Returned to basic console.\n");
}
// COMMANDS
void MathEx::about() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    cc("&a=====================[ &bMath Console Plugin. About ... &a]========================\n");
    cc("&a@ &bCopyright ALL_67 Entertainment &f[&6cpp_makers_aka_2.9.5&f], &bAll rights reserved!\n");
    cc("&a@ &bFiles&f: &6math_ex.h&f, &6math_ex.cpp\n");
    cc("&a@ &bPlugin type&f: &6external cpp\n");
    cc("&a@ &bPlugin Version&f: &612\n");
    cc("&a@ &bPlugin Core Version&f: &61.1-MathEx\n");
    cc("&a@ &bMath plugin calculates basic and advanced mathematical operations\n");
    cc("&a@ &bRemember to add a reference to this plugin in your console !\n");
    cc("&a@ &bPlugin Author: DingoMC\n");
    if (debug) cc("&2@ &9Debug Version: 0.3.8\n");
    cc("&a===============================================================================\n");
}
void MathEx::add() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Add");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    vector <double>adders;
    double eq = 0;
    int n;
    cc("&aConsole/&bMath&a/&6Add&a> &bNumber of elements &f[&61+&f]:&e ");
    cin>>n;
    if (cin.fail() || n<1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        adders.resize(n);
        for (int k=0; k<n; k++) {
            cc("&aConsole/&bMath&a/&6Add&a>&b "+to_string(k+1)+"&f. &bElement&f:&e ");
    		cin>>adders[k];
    		if(cin.fail()) {
	        	cin.clear();
                ErrorInvalidInput();
	       		break;
       		}
       		else eq+=adders[k];
    	}
    	for (int k=0; k<n; k++) {
            SetConsoleTextAttribute (hCon, 0x02);
       		cout<<fixed<<setprecision(prec)<<adders[k];
	    	if (adders[k+1]>=0) {
                SetConsoleTextAttribute (hCon, 0x0f);
	    		if (k==n-1) {
                    SetConsoleTextAttribute (hCon, 0x0a);
                    cout<<fixed<<setprecision(prec)<<" = "<<eq<<endl;
                }
	    		else cout<<"+";
	    	}
	    	else {
                SetConsoleTextAttribute (hCon, 0x0f);
	    		if (k==n-1) {
                    SetConsoleTextAttribute (hCon, 0x0a);
                    cout<<fixed<<setprecision(prec)<<" = "<<eq<<endl;
                }
	    		else cout<<"";
	    	}
    	}
    }
}
void MathEx::clear() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    system("cls");
}
void MathEx::cosine() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Cos");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double n, eq;
    int opt;
    cc("&aConsole/&bMath&a/&6Cos&a> &bChoose angle unit&f:\n");
    cc("&aConsole/&bMath&a/&6Cos&a> &a1 &f--> &aDegrees\n");
    cc("&aConsole/&bMath&a/&6Cos&a> &a2 &f--> &aRadians\n");
    cc("&aConsole/&bMath&a/&6Cos&a> &a3 &f--> &aGrads\n");
    cc("&aConsole/&bMath&a/&6Cos&a> &bOption&f:&e ");
    cin>>opt;
    if (cin.fail() || opt > 3 || opt < 1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        if (opt == 1) cc("&aConsole/&bMath&a/&6Cos&a> &bType angle value &f[&6DEG&f]:&e ");
        if (opt == 2) cc("&aConsole/&bMath&a/&6Cos&a> &bType angle value &f[&6RAD&f]:&e ");
        if (opt == 3) cc("&aConsole/&bMath&a/&6Cos&a> &bType angle value &f[&6GRA&f]:&e ");
        cin>>n;
        if (opt == 1) eq = cos(n * (PI/180.0));
        if (opt == 2) eq = cos(n);
        if (opt == 3) eq = cos(n * (PI/200.0));
        SetConsoleTextAttribute(hCon, 0x02);
        if (opt == 1) cout<<fixed<<setprecision(prec)<<"cos("<<n<<" deg)";
        if (opt == 2) cout<<fixed<<setprecision(prec)<<"cos("<<n<<" rad)";
        if (opt == 3) cout<<fixed<<setprecision(prec)<<"cos("<<n<<" gra)";
        SetConsoleTextAttribute(hCon, 0x0a);
        cout<<" = "<<eq<<endl;
    }
}
void MathEx::divide() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Div");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    vector <double>divisors;
    double eq = 0, num = 0, div = 1;
    int n;
    cc("&aConsole/&bMath&a/&6Div&a> &bNumber of divisors &f[&61+&f]:&e ");
    cin>>n;
    if (cin.fail() || n<1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        divisors.resize(n);
        cc("&aConsole/&bMath&a/&6Div&a> &bNumber to be divided&f:&e ");
        cin>>num;
        if (cin.fail()) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            eq = num;
            for (int k=0; k<n; k++) {
                cc("&aConsole/&bMath&a/&6Div&a>&b "+to_string(k+1)+"&f. &bDivisor&f:&e ");
                cin>>divisors[k];
                if(cin.fail()) {
                    cin.clear();
                    ErrorInvalidInput();
                    break;
                }
                else {
                    eq /= divisors[k];
                    div *= divisors[k];
                }
    	    }
            SetConsoleTextAttribute(hCon, 0x02);
            cout<<fixed<<setprecision(prec)<<"("<<num<<")/("<<div<<")";
            SetConsoleTextAttribute(hCon, 0x0a);
            cout<<" = "<<eq<<endl;
        }
    }
}
bool MathEx::exitCmd() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    return true;
}
void MathEx::factorial() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Factorial");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double eq = 1;
    int n;
    cc("&aConsole/&bMath&a/&6Fc!&a> &bType an integer&f[&60+&f]:&e ");
    cin>>n;
    if (cin.fail() || n < 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        if (n > 1) for (int k=2; k<=n; k++) eq *= k;
        SetConsoleTextAttribute(hCon, 0x02);
        cout<<fixed<<setprecision(0)<<n<<"!";
        SetConsoleTextAttribute(hCon, 0x0a);
        cout<<fixed<<setprecision(0)<<" = "<<eq<<endl;
    }
}
void MathEx::factorize() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Factorize");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    unsigned long long int n;
    cc("&aConsole/&bMath&a/&6Fc%&a> &bType an integer&f[&61+&f]:&e ");
    cin>>n;
    if (cin.fail() || n <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        vector <unsigned long long int> eq;
        unsigned long long int cnt = 0;
        if (n == 1) {
            cnt++;
            eq.resize(1);
            eq[0] = 1;
        }
        else {
            for (unsigned long long int k=1; k<=n/2; k++) {
                if (n % k == 0) {
                    cnt++;
                    eq.resize(cnt);
                    eq[cnt-1] = k;
                }
            }
            cnt++;
            eq.resize(cnt);
            eq[cnt-1] = n;
        }
        SetConsoleTextAttribute(hCon, 0x02);
        cout<<"Found "<<cnt<<" factors of "<<n;
        SetConsoleTextAttribute(hCon, 0x0f);
        cout<<": ";
        for (int k=0; k<cnt; k++) {
            SetConsoleTextAttribute(hCon, 0x0a);
            cout<<eq[k];
            SetConsoleTextAttribute(hCon, 0x0f);
            if (k == cnt-1) cout<<"."<<endl;
            else cout<<", ";
        }
        SetConsoleTextAttribute(hCon, 0x03);
        if (cnt == 2) cout<<"* "<<n<<" is a prime number."<<endl;
    }
}
void MathEx::gcd() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Gcd");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    unsigned long long int m, n, a, b, c;
    cc("&aConsole/&bMath&a/&6Fc%&a> &bType first integer&f[&61+&f]:&e ");
    cin>>m;
    if (cin.fail() || m <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&bMath&a/&6Fc%&a> &bType second integer&f[&61+&f]:&e ");
        cin>>n;
        if (cin.fail() || n <= 0) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            if (m > n) {
                a = m;
                b = n;
            }
            else {
                a = n;
                b = m;
            }
            while (b > 0) {
                c = a % b;
                a = b;
                b = c;
            }
            SetConsoleTextAttribute(hCon, 0x02);
            cout<<"GCD("<<m<<","<<n<<")";
            SetConsoleTextAttribute(hCon, 0x0a);
            cout<<" = "<<a<<endl;
        }
    }
}
void MathEx::help() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    cc("&a===================[ &bMath Console Plugin. Command Help &a]=======================\n");
    for (int k=0; k<cmd_count; k++) {
        if (commands[k] != aliases[k]) cc("&a"+commands[k]+" &f:&b "+desc[k]+" &f(&2Alias&f:&a "+aliases[k]+"&f)\n");
        else cc("&a"+commands[k]+" &f:&b "+desc[k]+"\n");
    }
    cc("&a===============================================================================\n");
}
void MathEx::logn() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Ln");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double n, eq;
    cc("&aConsole/&bMath&a/&6Ln&a> &bType a value &f[&6>0&f]:&e ");
    cin>>n;
    if (cin.fail() || n <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        eq = log(n);
        SetConsoleTextAttribute(hCon, 0x02);
        cout<<fixed<<setprecision(prec)<<"ln("<<n<<")";
        SetConsoleTextAttribute(hCon, 0x0a);
        cout<<" = "<<eq<<endl;
    } 
}
void MathEx::logb() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Log");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double n, eq, base;
    cc("&aConsole/&bMath&a/&6Log&a> &bType a base &f[&6>0&f,&6!=1&f]:&e ");
    cin>>base;
    if (cin.fail() || base <= 0 || base == 1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&bMath&a/&6Log&a> &bType a value &f[&6>0&f]:&e ");
        cin>>n;
        if (cin.fail() || n <= 0) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            eq = log10(n)/log10(base);
            SetConsoleTextAttribute(hCon, 0x02);
            cout<<fixed<<setprecision(prec)<<"log["<<base<<"]("<<n<<")";
            SetConsoleTextAttribute(hCon, 0x0a);
            cout<<" = "<<eq<<endl;
        }
    } 
}
void MathEx::multiply() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Mul");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    vector <double>multipliers;
    double eq = 1;
    int n;
    cc("&aConsole/&bMath&a/&6Mul&a> &bNumber of elements &f[&61+&f]:&e ");
    cin>>n;
    if (cin.fail() || n<1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        multipliers.resize(n);
        for (int k=0; k<n; k++) {
            cc("&aConsole/&bMath&a/&6Mul&a>&b "+to_string(k+1)+"&f. &bMultiplier&f:&e ");
    		cin>>multipliers[k];
    		if(cin.fail()) {
	        	cin.clear();
                ErrorInvalidInput();
	       		break;
       		}
       		else eq*=multipliers[k];
    	}
    	for (int k=0; k<n; k++) {
            SetConsoleTextAttribute (hCon, 0x02);
       		if (multipliers[k]<0) cout<<fixed<<setprecision(prec)<<"("<<multipliers[k]<<")";
       		else cout<<fixed<<setprecision(prec)<<multipliers[k];
	    	if (k==n-1) {
                SetConsoleTextAttribute (hCon, 0x0a);
                cout<<fixed<<setprecision(prec)<<" = "<<eq<<endl;
            }
	    	else cout<<"*";
    	}
    }
}
void MathEx::power() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Pow");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    vector <double>powers;
    double eq = 0, num = 0, p = 1;
    int n;
    cc("&aConsole/&bMath&a/&6Pow&a> &bNumber of exponents &f[&61+&f]:&e ");
    cin>>n;
    if (cin.fail() || n<1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        powers.resize(n);
        cc("&aConsole/&bMath&a/&6Pow&a> &bBase&f:&e ");
        cin>>num;
        if (cin.fail()) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            eq = num;
            for (int k=0; k<n; k++) {
                cc("&aConsole/&bMath&a/&6Pow&a>&b "+to_string(k+1)+"&f. &bExponent&f:&e ");
                cin>>powers[k];
                if(cin.fail()) {
                    cin.clear();
                    ErrorInvalidInput();
                    break;
                }
                else {
                    eq = pow(eq,powers[k]);
                    p *= powers[k];
                }
    	    }
            SetConsoleTextAttribute(hCon, 0x02);
            cout<<fixed<<setprecision(prec)<<"("<<num<<")^("<<p<<")";
            SetConsoleTextAttribute(hCon, 0x0a);
            cout<<" = "<<eq<<endl;
        }
    }
}
void MathEx::prc() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Prc");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    int p = 3;
    cc("&aConsole/&bMath&a/&6Prc&a> &bSet precision &f[&60~15&f]:&e ");
    cin>>p;
    if (cin.fail() || p < 0 || p > 15) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        prec = p;
        SetConsoleTextAttribute(hCon, 0x02);
        cout<<"Precision set to ";
        SetConsoleTextAttribute(hCon, 0x0a);
        cout<<prec<<endl;
    }
}
void MathEx::sine() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Sin");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double n, eq;
    int opt;
    cc("&aConsole/&bMath&a/&6Sin&a> &bChoose angle unit&f:\n");
    cc("&aConsole/&bMath&a/&6Sin&a> &a1 &f--> &aDegrees\n");
    cc("&aConsole/&bMath&a/&6Sin&a> &a2 &f--> &aRadians\n");
    cc("&aConsole/&bMath&a/&6Sin&a> &a3 &f--> &aGrads\n");
    cc("&aConsole/&bMath&a/&6Sin&a> &bOption&f:&e ");
    cin>>opt;
    if (cin.fail() || opt > 3 || opt < 1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        if (opt == 1) cc("&aConsole/&bMath&a/&6Sin&a> &bType angle value &f[&6DEG&f]:&e ");
        if (opt == 2) cc("&aConsole/&bMath&a/&6Sin&a> &bType angle value &f[&6RAD&f]:&e ");
        if (opt == 3) cc("&aConsole/&bMath&a/&6Sin&a> &bType angle value &f[&6GRA&f]:&e ");
        cin>>n;
        if (opt == 1) eq = sin(n * (PI/180.0));
        if (opt == 2) eq = sin(n);
        if (opt == 3) eq = sin(n * (PI/200.0));
        SetConsoleTextAttribute(hCon, 0x02);
        if (opt == 1) cout<<fixed<<setprecision(prec)<<"sin("<<n<<" deg)";
        if (opt == 2) cout<<fixed<<setprecision(prec)<<"sin("<<n<<" rad)";
        if (opt == 3) cout<<fixed<<setprecision(prec)<<"sin("<<n<<" gra)";
        SetConsoleTextAttribute(hCon, 0x0a);
        cout<<" = "<<eq<<endl;
    }
}
void MathEx::root2() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Sqrt");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double n, eq;
    cc("&aConsole/&bMath&a/&6Sqt&a> &bType a value &f[&6>=0&f]:&e ");
    cin>>n;
    if (cin.fail() || n < 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        eq = sqrt(n);
        SetConsoleTextAttribute(hCon, 0x02);
        cout<<fixed<<setprecision(prec)<<"sqrt("<<n<<")";
        SetConsoleTextAttribute(hCon, 0x0a);
        cout<<" = "<<eq<<endl;
    } 
}
void MathEx::subtract() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Sub");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    vector <double>subs;
    double eq = 0, num = 0, div = 1;
    int n;
    cc("&aConsole/&bMath&a/&6Sub&a> &bNumber of subtrahends &f[&61+&f]:&e ");
    cin>>n;
    if (cin.fail() || n<1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        subs.resize(n);
        cc("&aConsole/&bMath&a/&6Sub&a> &bNumber to subtract from&f:&e ");
        cin>>num;
        if (cin.fail()) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            eq = num;
            for (int k=0; k<n; k++) {
                cc("&aConsole/&bMath&a/&6Sub&a>&b "+to_string(k+1)+"&f. &bSubtrahend&f:&e ");
                cin>>subs[k];
                if(cin.fail()) {
                    cin.clear();
                    ErrorInvalidInput();
                    break;
                }
                else {
                    eq -= subs[k];
                }
    	    }
            SetConsoleTextAttribute (hCon, 0x02);
            cout<<fixed<<setprecision(prec)<<num;
            for (int k=0; k<n; k++) {
                if (subs[k]>=0) {
                    SetConsoleTextAttribute (hCon, 0x0f);
                    cout<<"-";
                    SetConsoleTextAttribute (hCon, 0x02);
                    cout<<fixed<<setprecision(prec)<<subs[k];
                }
                else {
                    SetConsoleTextAttribute (hCon, 0x0f);
                    cout<<"+";
                    SetConsoleTextAttribute (hCon, 0x02);
                    cout<<fixed<<setprecision(prec)<<(-subs[k]);
                }
            }
            cout<<fixed<<setprecision(prec)<<" = "<<eq<<endl;
        }
    }
}
void MathEx::tangent() {
    SetConsoleTitleA("Ultimate Console 3.0 > Math Plugin > Tan");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double n, eq;
    int opt;
    cc("&aConsole/&bMath&a/&6Tan&a> &bChoose angle unit&f:\n");
    cc("&aConsole/&bMath&a/&6Tan&a> &a1 &f--> &aDegrees\n");
    cc("&aConsole/&bMath&a/&6Tan&a> &a2 &f--> &aRadians\n");
    cc("&aConsole/&bMath&a/&6Tan&a> &a3 &f--> &aGrads\n");
    cc("&aConsole/&bMath&a/&6Tan&a> &bOption&f:&e ");
    cin>>opt;
    if (cin.fail() || opt > 3 || opt < 1) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        if (opt == 1) cc("&aConsole/&bMath&a/&6Tan&a> &bType angle value &f[&6DEG&f]:&e ");
        if (opt == 2) cc("&aConsole/&bMath&a/&6Tan&a> &bType angle value &f[&6RAD&f]:&e ");
        if (opt == 3) cc("&aConsole/&bMath&a/&6Tan&a> &bType angle value &f[&6GRA&f]:&e ");
        cin>>n;
        if (opt == 1) eq = tan(n * (PI/180.0));
        if (opt == 2) eq = tan(n);
        if (opt == 3) eq = tan(n * (PI/200.0));
        SetConsoleTextAttribute(hCon, 0x02);
        if (opt == 1) cout<<fixed<<setprecision(prec)<<"tan("<<n<<" deg)";
        if (opt == 2) cout<<fixed<<setprecision(prec)<<"tan("<<n<<" rad)";
        if (opt == 3) cout<<fixed<<setprecision(prec)<<"tan("<<n<<" gra)";
        SetConsoleTextAttribute(hCon, 0x0a);
        cout<<" = "<<eq<<endl;
    }
}
// OTHERS
// Issued when user type a command without prefix (treated as standard text)
void MathEx::echo(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime();
    cc("&a[&bMath&a][&b"+username+"&a]&f "+message+"\n");
}
void MathEx::cc(string text) {
    int i=0, j=0, err=0;
	char chk[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	for (i=0; i<text.length(); i++) {
		err=0;
		while (text.at(i)=='&' && err<16) {
			i++;
			switch (text.at(i)) {
				case '0': {
					SetConsoleTextAttribute(hCon, 0x00);
					break;
				}
				case '1': {
					SetConsoleTextAttribute(hCon, 0x01);
					break;
				}
				case '2': {
					SetConsoleTextAttribute(hCon, 0x02);
					break;
				}
				case '3': {
					SetConsoleTextAttribute(hCon, 0x03);
					break;
				}
				case '4': {
					SetConsoleTextAttribute(hCon, 0x04);
					break;
				}
				case '5': {
					SetConsoleTextAttribute(hCon, 0x05);
					break;
				}
				case '6': {
					SetConsoleTextAttribute(hCon, 0x06);
					break;
				}
				case '7': {
					SetConsoleTextAttribute(hCon, 0x07);
					break;
				}
				case '8': {
					SetConsoleTextAttribute(hCon, 0x08);
					break;
				}
				case '9': {
					SetConsoleTextAttribute(hCon, 0x09);
					break;
				}
				case 'a': {
					SetConsoleTextAttribute(hCon, 0x0a);
					break;
				}
				case 'b': {
					SetConsoleTextAttribute(hCon, 0x0b);
					break;
				}
				case 'c': {
					SetConsoleTextAttribute(hCon, 0x0c);
					break;
				}
				case 'd': {
					SetConsoleTextAttribute(hCon, 0x0d);
					break;
				}
				case 'e': {
					SetConsoleTextAttribute(hCon, 0x0e);
					break;
				}
				case 'f': {
					SetConsoleTextAttribute(hCon, 0x0f);
					break;
				}
				default: {
					for (j=0; j<16; j++) if (text.at(i)!=chk[j]) err++;
					break;
				}
			}
			if ((text.at(i)>=48 && text.at(i)<=57) || (text.at(i)>=97 && text.at(i)<=102)) i++;
			else i--;
		}
		if (i<text.length()) cout<<text.at(i);
	}
}
string MathEx::getTime() {
    // Get current active time and return it as a string
    string clock_str="[";
    clock_t end = clock() - startTime;
	unsigned long long ms = end / CLOCKS_PER_MS;
	int s=0, m=0;
	for (ms; ms>=1000; ms-=1000) s++;
	for (s; s>=60; s-=60) m++;
	if (m<=9) clock_str += "0";
    clock_str += to_string(m);
    clock_str += ":";
	if (s<=9) clock_str += "0";
	clock_str += to_string(s);
    clock_str += ".";
	if (ms<=9) clock_str += "00";
	if (ms>9 && ms<=99) clock_str += "0";
	clock_str += to_string(ms);
    clock_str += "]";
    return clock_str;
}
// ERRORS
// Issued when command cannot be found
void MathEx::ErrorCommandUnknown(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Math] Error # "<<__func__<<": \'"<<message<<"\'. Type !help for commands list."<<endl;
}
// Issued when User types invalid value
void MathEx::ErrorInvalidInput() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Math] Error # "<<__func__<<": Invalid value."<<endl;
}