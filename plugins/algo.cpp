/*
 * This file is part of {{ ultimate_console_v.3.0 }}.
 * This code is made by DingoMC
 * Ultimate Console version 3 - Algo Plugin class method
 */
# include <iostream>
# include <string>
# include <time.h>
# include <fstream>
# include <windows.h>
# include <cmath>
# include <vector>
# include <iomanip>
# include <limits>
# include "algo.h"
# define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.000)
# define PI 3.14159265358979
using namespace std;
/**
 * @brief Algo Constructor
 */
Algo::Algo () {
    prefix = '!';
    err_count = 0;
    exit = false;
    debug = false;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    username = "None";
}
/**
 * @brief Call Commands Setup for an instance
 * 
 * @return vector <Command> Commands List
 */
vector <Command> Algo::SetupCommands() {
    vector <Command> commands_list;
    commands_list.push_back(Command("about", "ab", "Show Info about this plugin", &about));
    commands_list.push_back(Command("clear", "cl", "Clears Algo console display", &clear));
    commands_list.push_back(Command("convert", "conv", "Converts value between different systems", &conv));
    commands_list.push_back(Command("determinant", "det", "Calculates determinant of the matrix (Gauss Redux)", &det));
    commands_list.push_back(Command("exit", "ex", "Exit from Algo console", &exitCmd));
    commands_list.push_back(Command("help", "?", "Show this list", &help));
    commands_list.push_back(Command("interpolationl", "intl", "Creates Lagrange Polynomial based on given nodes", &interpolationl));
    commands_list.push_back(Command("pderivative", "pdrv", "Calculates all derivatives of a polynomial in given point", &pderivative));
    commands_list.push_back(Command("quadratic", "qua", "Calculates roots of ax^2 + bx + c = 0", &quadratic));
    return commands_list;
}
/**
 * @brief Algo Plugin main function
 * 
 * @param debugInit Debug active - Passed from basic
 * @param usernameInit Current user - Passed from basic
 * @param TimeInit Current time - Passed from basic
 */
void Algo::main(bool debugInit, string usernameInit, clock_t TimeInit) {
    C = SetupCommands();
    cmd_count = C.size();
    startTime = TimeInit;
    debug = debugInit;
    username = usernameInit;
    exit = false;
    cc("&aWelcome to &3Algo Plugin&a. Type !help for help.\n");
    while (exit == false) {
        fflush(stdin);
        SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin");
        cc("&aConsole/&3Algo&a> ");
        SetConsoleTextAttribute(hCon, 0x0e);
        getline(cin,cmd);
        if (!cmd.empty()) {
            if (cmd.at(0)!=prefix) echo(cmd);
            else {
                cmd = cmd.erase(0,1);
                err_count = 0;
                for (int i=0; i<cmd_count; i++) if (cmd!=C[i].name) err_count++;
                for (int i=0; i<cmd_count; i++) if (cmd!=C[i].alias) err_count++;
                if (err_count == 2*(cmd_count)) ErrorCommandUnknown(cmd);
                for (int i = 0; i < cmd_count; i++) {
                    if (cmd == C[i].name || cmd == C[i].alias) {
                        if (debug) debugInfo(C[i].name);
                        C[i].exec();
                        if (cmd == "ex" || cmd == "exit") exit = true;
                        break;
                    }
                }
            }
        }
        cin.clear();
        cmd.clear();
    }
    cc("&8Closing &3Algo Plugin&8. Returned to basic console.\n");
}
/// ALGO METHODS ///
/**
 * @brief Algo about
 */
void Algo::about() {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > About");
    cc("&a=====================[ &3Algo Console Plugin. About ... &a]========================\n");
    cc("&a@ &3Copyright ALL_67 Entertainment &f[&6cpp_makers_aka_2.9.5&f], &3All rights reserved!\n");
    cc("&a@ &3Files&f: &6algo.h&f, &6algo.cpp\n");
    cc("&a@ &3Plugin type&f: &6external cpp\n");
    cc("&a@ &3Plugin Version&f: &65\n");
    cc("&a@ &3Plugin Core Version&f: &61.0-Algo\n");
    cc("&a@ &3Algo plugin processes complex mathematical alogrithms\n");
    cc("&a@ &3Remember to add a reference to this plugin in your console !\n");
    cc("&a@ &3Plugin Author: DingoMC\n");
    if (debug) cc("&2@ &9Debug Version: 0.3.8\n");
    cc("&a===============================================================================\n");
}
/**
 * @brief Algo clear
 */
void Algo::clear() {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > Clear");
    system("cls");
}
/**
 * @brief Algo converter
 */
void Algo::conv() {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > Convert");
    cc("&aConsole/&3Algo&a/&6Conv&a> &3Primary Value System &f[&62~36&f]:&e ");
    SysVal a;
    cin>>a.base;
    if (cin.fail() || a.base < 2 || a.base > 36) {
        cin.clear();
        ErrorInvalidInput();
        return;
    }
    cc("&aConsole/&3Algo&a/&6Conv&a> &3Value &3[" + to_string(a.base) + "]&f:&e ");
    cin>>a.value;
    if (!SC.ValueCorrect(a)) {
        cin.clear();
        ErrorInvalidInput();
        return;
    }
    cc("&aConsole/&3Algo&a/&6Conv&a> &3Target Value System &f[&62~36&f]:&e ");
    SysVal b;
    cin>>b.base;
    if (cin.fail() || b.base < 2 || b.base > 36) {
        cin.clear();
        ErrorInvalidInput();
        return;
    }
    unsigned long long decimal = SC.ConvertToDec(a);
    b.value = SC.ConvertToSys(decimal, b.base);
    cc("&aConsole/&3Algo&a/&6Conv&a> &3Final Value &3[" + to_string(b.base) + "]&f:&a ");
    cout<<b.value<<endl;
}
/**
 * @brief Algo determinant
 */
void Algo::det() {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > Determinant");
    Matrix A;
    bool negative = false;
    int len;
    cc("&aConsole/&3Algo&a/&6Det&a> &3Matrix Size &f[&61+&f]:&e ");
    cin>>len;
    if (cin.fail() || len < 1) {
        cin.clear();
        ErrorInvalidInput();
        return;
    }
    A.resize(len);
    for (int i=0; i<len; i++) A[i].resize(len);
    for (int i=0; i<len; i++) {
        cc("&aConsole/&3Algo&a/&6Det&a> &3Row[" + to_string(i+1) + "&3] = ");
        for (int j=0; j<len; j++) {
            SetConsoleTextAttribute(hCon, 0x0e);
            cin>>A[i][j];
            if (cin.fail()) {
                cin.clear();
                ErrorInvalidInput();
                return;
            }
        }
    }
    double det;
    if (len > 3) {
        det = 1;
        for (int i=0; i<len-1; i++) A = MD.gauss_redux(A,i,negative);
        SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > Determinant");
        cc("&aConsole/&3Algo&a/&6Det&a> &3Matrix after Gauss Redux\n");
        for (int i=0; i<len; i++) {
            cc("&aConsole/&3Algo&a/&6Det&a> &3Row[" + to_string(i+1) + "&3] = ");
            for (int j=0; j<len; j++) {
                SetConsoleTextAttribute(hCon, 0x0d);
                cout<<A[i][j]<<" ";
            }
            cout<<endl;
        }
        if (negative) det = -1;
        for (int i=0; i<len; i++) det *= A[i][i];
    }
    if (len == 3) det = MD.sarrus(A);
    if (len == 2) det = A[0][0]*A[1][1] - (A[0][1]*A[1][0]);
    if (len == 1) det = A[0][0];
    cc("&aConsole/&3Algo&a/&6Det&a> &3Matrix Determinant&f: ");
    SetConsoleTextAttribute(hCon, 0x0a);
    cout<<det<<endl;
}
/**
 * @brief Algo exit (null)
 */
void Algo::exitCmd() {
    return;
}
/**
 * @brief Algo help
 */
void Algo::help() {
    C = SetupCommands();
    cc("&a===================[ &3Algo Console Plugin. Command Help &a]=======================\n");
    for (int k=0; k<C.size(); k++) {
        if (C[k].name != C[k].alias) cc("&a"+C[k].name+" &f:&3 "+C[k].desc+" &f(&2Alias&f:&a "+C[k].alias+"&f)\n");
        else cc("&a"+C[k].name+" &f:&3 "+C[k].desc+"\n");
    }
    cc("&a===============================================================================\n");
}
/**
 * @brief Algo interpolationl
 */
void Algo::interpolationl() {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > InterpolationL");
    cc("&aConsole/&3Algo&a/&6IntL&a> &3Node Count &f[&62+&f]:&e ");
    unsigned int node_count;
    cin>>node_count;
    if (cin.fail() || node_count < 2) {
        cin.clear();
        ErrorInvalidInput();
        return;
    }
    double *node_xval = new double[node_count];
    for (int i = 0; i < node_count; i++) {
        cc("&aConsole/&3Algo&a/&6IntL&a> &3X Value of Node " + to_string(i+1) + "&f:&e ");
        cin>>node_xval[i];
        if (cin.fail() || (i > 0 && node_xval[i-1] >= node_xval[i])) {
            cin.clear();
            ErrorInvalidInput();
            delete node_xval;
            return;
        }
    }
    double *node_val = new double[node_count];
    for (int i = 0; i < node_count; i++) {
        cc("&aConsole/&3Algo&a/&6IntL&a> &3Y Value of Node " + to_string(i+1) + "&f:&e ");
        cin>>node_val[i];
        if (cin.fail()) {
            cin.clear();
            ErrorInvalidInput();
            delete node_val;
            return;
        }
    }
    vector <double> polynomial;
    polynomial.resize(node_count);
    for (int i = 0; i < node_count; i++) polynomial[i] = 0.0;
    Matrix lagrange_p;
    lagrange_p.resize(node_count);
    for (int i = 0; i < node_count; i++) {
        lagrange_p[i].resize(node_count);
        lagrange_p[i] = IP.CountFLP(i, *&node_xval, node_count);
        for (int j = 0; j < node_count; j++) {
            lagrange_p[i][j] *= node_val[i];
            polynomial[j] += lagrange_p[i][j];
        }
    }
    cc("&aConsole/&3Algo&a/&6IntL&a> &3Lagrange Polynomial&f:&a ");
    bool first_coeff = true;
    for (int i = node_count - 1; i >= 0; i--) {
        if (polynomial[i] != 0) {
            if (polynomial[i] > 0) {
                if (!first_coeff) cout<<" + ";
                else first_coeff = false;
                if (polynomial[i] != 1) cout<<polynomial[i];
                else if (i == 0) cout<<polynomial[i];
            }
            else {
                if (!first_coeff) {
                    cout<<" - ";
                    if (polynomial[i] != -1) cout<<(-polynomial[i]);
                    else if (i == 0) cout<<(-polynomial[i]);
                }
                else {
                    if (polynomial[i] != -1) cout<<polynomial[i];
                    else cout<<"-";
                    first_coeff = false;
                }
            }
            if (i > 1) cout<<"x^"<<i;
            if (i == 1) cout<<"x";
        }
    }
    cout<<endl;
    delete node_val;
    delete node_xval;
}
/**
 * @brief Algo interpolationn
 */
void Algo::interpolationn() {
    
}
/**
 * @brief Algo pderivative
 */
void Algo::pderivative() {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > Quadratic");
    cc("&aConsole/&3Algo&a/&6Pdrv&a> &3Polynomial Step &f[&6>0&f]:&e ");
    unsigned int st;
    cin>>st;
    if (cin.fail() || st < 1) {
        cin.clear();
        ErrorInvalidInput();
        return;
    }
    double *coeff = new double[st+1];
    for (int i = 0; i < st + 1; i++) {
        if (st - i == 0) cc("&aConsole/&3Algo&a/&6Pdrv&a> &3Free coefficient&f:&e ");
        if (st - i == 1) cc("&aConsole/&3Algo&a/&6Pdrv&a> &3Coefficient of x&f:&e ");
        if (st - i > 1) cc("&aConsole/&3Algo&a/&6Pdrv&a> &3Coefficient of x^" + to_string(st-i) + "&f:&e ");
        cin>>coeff[i];
        if (cin.fail()) {
            cin.clear();
            delete coeff;
            ErrorInvalidInput();
            return;
        }
    }
    double point;
    cc("&aConsole/&3Algo&a/&6Pdrv&a> &3Derivative point X value&f:&e ");
    cin>>point;
    if (cin.fail()) {
        cin.clear();
        delete coeff;
        ErrorInvalidInput();
        return;
    }
    double *drv = new double[st+1];
    for (int i = 0; i <= st; i++) {
        drv[i] = HR.HAlgo(*&coeff, st, i, point);
        cc("&aConsole/&3Algo&a/&6Pdrv&a> &3Derivative (" + to_string(i) + ") in x = " + to_string(point) + "&f:&a ");
        cout<<drv[i]<<endl;
    }
    delete drv;
    delete coeff;
}
/**
 * @brief Algo quadratic
 */
void Algo::quadratic() {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo Plugin > Quadratic");
    cc("&aConsole/&3Algo&a/&6Qua&a> &3Coefficient a &f[&6!0&f]:&e ");
    double a, b, c;
    cin>>a;
    if (cin.fail() || a == 0) {
        cin.clear();
        ErrorInvalidInput();
        return;
    }
    cc("&aConsole/&3Algo&a/&6Qua&a> &3Coefficient b&f:&e ");
    cin>>b;
    cc("&aConsole/&3Algo&a/&6Qua&a> &3Coefficient c&f:&e ");
    cin>>c;
    double delta = pow(b, 2.0) - 4.0 * a * c;
    if (delta < 0) {
        cc("&aConsole/&3Algo&a/&6Qua&a> &cNo real solutions found.\n");
        return;
    }
    double x1 = (-b - sqrt(delta)) / (2.0 * a), x2 = (-b + sqrt(delta)) / (2.0 * a);
    if (delta == 0) {
        cc("&aConsole/&3Algo&a/&6Qua&a> &aFound 1 real solution&f:&a ");
        cout<<x1<<endl;
        return;
    }
    cc("&aConsole/&3Algo&a/&6Qua&a> &aFound 2 real solutions&f:&a ");
    cout<<x1<<", "<<x2<<endl;
}
/**
 * @brief Multiplies Polynomial by Binomial
 * 
 * @param P_Coeff Polynomial coefficients : vector <double>
 * @param P_Step Polynomial step : int
 * @param Bi_A Binomial x coefficient : double
 * @param Bi_B Binomial free coefficient : double
 * @return vector <double> Multiplied polynomial coefficients
 */
vector <double> Interpolation::MulPolynomialBinomial (vector <double> P_Coeff, int P_Step, double Bi_A, double Bi_B) {
    vector <double> P_New;
    P_New.resize(P_Step + 1);
    P_New[P_Step] = Bi_A * P_Coeff[P_Step-1];
    for (int i = P_Step - 1; i >= 1; i--) P_New[i] = Bi_B * P_Coeff[i] + Bi_A * P_Coeff[i-1];
    P_New[0] = P_Coeff[0] * Bi_B;
    return P_New;
}
// Interpolation: Count Fundamental Lagrange Polynomial l(x)
vector <double> Interpolation::CountFLP (int iter, double* node_xval, int node_count) {
    vector <double> FLP_Coeff;
    FLP_Coeff.resize(node_count);
    unsigned int mul_count = 1;
    FLP_Coeff[0] = 1.0;
    for (int k = 0; k < node_count; k++) {
        if (k != iter) {
            FLP_Coeff = MulPolynomialBinomial(FLP_Coeff, mul_count, 1.0 / (node_xval[iter] - node_xval[k]), (-node_xval[k]) / (node_xval[iter] - node_xval[k]));
            mul_count++;
        }
    }
    return FLP_Coeff;
}
// Horner: Factorial Algorithm
double Horner::factorial (int n) {
    if (n == 0) return 1;
    double w = 1;
    for (int i = 1; i <= n; i++) w *= i;
    return w;
}
// Horner: Horner Algorithm
double Horner::HAlgo (double *&coeff, int step, int iter, double point) {
    for (int i = 1; i <= step - iter; i++) coeff[i] = coeff[i-1] * point + coeff[i];
    return coeff[step-iter] * factorial(iter);
}
// SysConverter: Checking if value is correct in given systsem
bool SysConverter::ValueCorrect (SysVal v) {
    for (int i = 0; i < v.value.length(); i++) {
        if ((int) v.value.at(i) < 48) return false;
        if ((int) v.value.at(i) > 57 && (int) v.value.at(i) < 65) return false;
        if ((int) v.value.at(i) > 90) return false;
        if (v.base <= 10 && (int) v.value.at(i) >= 48 + v.base) return false;
        if (v.base > 10 && (int) v.value.at(i) >= 55 + v.base) return false;
    }
    return true;
}
// SysConverter: Conversion to decimal
unsigned long long SysConverter::ConvertToDec (SysVal v) {
    unsigned long long charValue = 0;
    unsigned long long decimal = 0;
    for (int i = v.value.length() - 1; i >= 0; i--) {
        if ((int) v.value.at(i) >= 48 && (int) v.value.at(i) <= 57) charValue = (int) v.value.at(i) - 48;
        if ((int) v.value.at(i) >= 65 && (int) v.value.at(i) <= 90) charValue = (int) v.value.at(i) - 55;
        charValue *= pow(v.base, v.value.length() - 1 - i);
        decimal += charValue;
    }
    return decimal;
}
// SysConverter: Conversion from decimal to another system
string SysConverter::ConvertToSys (unsigned long long decimal, unsigned int base) {
    if (decimal == 0) return "0";
    string f = "", value = "";
    int charValue = 0;
    while (decimal > 0) {
        charValue = decimal % base;
        if (charValue < 10) f += (char) (48 + charValue);
        else f += (char) (55 + charValue);
        decimal /= base;
    }
    for (int i = f.length() - 1; i >= 0; i--) value += f.at(i);
    return value;
}
// MatrixDet: Swapping Matrix rows
Matrix MatrixDet::swap_rows(Matrix M, int row_1_index, int row_2_index) {
    double pom;
    for (int j=0; j<4; j++) {
        pom = M[row_1_index][j];
        M[row_1_index][j] = M[row_2_index][j];
        M[row_2_index][j] = pom;
    }
    return M;
}
// MatrixDet: Sarrus Method
double MatrixDet::sarrus (Matrix M) {
    double dia[6];
    dia[0] = M[0][0]*M[1][1]*M[2][2];
    dia[1] = M[0][1]*M[1][2]*M[2][0];
    dia[2] = M[0][2]*M[1][0]*M[2][1];
    dia[3] = M[0][2]*M[1][1]*M[2][0];
    dia[4] = M[0][0]*M[1][2]*M[2][1];
    dia[5] = M[0][1]*M[1][0]*M[2][2];
    return dia[0] + dia[1] + dia[2] - dia[3] - dia[4] - dia[5];
}
// MatrixDet: Gauss Redux
Matrix MatrixDet::gauss_redux (Matrix M, int iter, bool& negative) {
    SetConsoleTitleA("Ultimate Console 3.0 > Algo/MatrixDet > Gauss Redux");
    vector <double> coeff;
    int len = M[0].size();
    int row_min = fabs(M[iter][iter]), who_first = iter;
    for (int i=iter; i<len; i++) {
        if (row_min == 0) {
            row_min = fabs(M[i][iter]);
            who_first = i;
        }
        else break;
    }
    if (row_min == 0) return M;
    for (int i=iter; i<len; i++) {
        if (fabs(M[i][iter]) < row_min && M[i][iter] != 0) {
            row_min = fabs(M[i][iter]);
            who_first = i;
        }
    }
    if (who_first != iter) {
        M = swap_rows(M, iter, who_first);
        negative = !negative;
    }
    coeff.resize(len-1);
    for (int i=0; i<len-iter-1; i++) coeff[i] = (M[i+iter+1][iter]/M[iter][iter]);
    for (int i=iter+1; i<len; i++) {
        for (int j=iter; j<len; j++) M[i][j] -= coeff[i-iter-1]*M[iter][j];
    }
    return M;
}
// Issued when user type a command without prefix (treated as standard text)
void Algo::echo(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime();
    cc("&a[&3Algo&a][&b"+username+"&a]&f "+message+"\n");
}
void Algo::debugInfo(string cmd_name) {
    SetConsoleTextAttribute(hCon, 0x09);
    cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<cmd_name<<endl;
}
/**
 * Displays coloured text. (akka:cpp-2.9.4-basic)
 * 
 * @param text Formatted text to be disaplyed in color
 */
void Algo::cc(string text) {
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
string Algo::getTime() {
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
void Algo::ErrorCommandUnknown(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Algo] Error # "<<__func__<<": \'"<<message<<"\'. Type !help for commands list."<<endl;
}
// Issued when User types invalid value
void Algo::ErrorInvalidInput() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Algo] Error # "<<__func__<<": Invalid value."<<endl;
}