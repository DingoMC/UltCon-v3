//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Encryptors plugin class methods
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
#include "encryptors.h"
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.000)
using namespace std;
Enc::Enc () {
    // Commands List
    commands[0] = "about";
    commands[1] = "clear";
    commands[2] = "column";
    commands[3] = "caesar";
    commands[4] = "etm";
    commands[5] = "exit";
    commands[6] = "help";
    // Command Aliases
    aliases[0] = "ab";
    aliases[1] = "cl";
    aliases[2] = "col";
    aliases[3] = "csr";
    aliases[4] = "etm";
    aliases[5] = "ex";
    aliases[6] = "?";
    // Command descriptions
    desc[0] = "Show Info about this plugin";
    desc[1] = "Clears Encryptors console display";
    desc[2] = "Enters Column Coder";
    desc[3] = "Enters Caesar Coder";
    desc[4] = "Enters ETM Coder/Decoder";
    desc[5] = "Exit from Encryptors plugin console";
    desc[6] = "Show this list";
    cmd_count = sizeof(commands)/sizeof(*commands);
    prefix = '$';
    err_count = 0;
    exit = false;
    debug = false;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    username = "None";
}
// MAIN FUNCTION
void Enc::main(bool debugInit, string usernameInit, clock_t TimeInit) {
    startTime = TimeInit;
    debug = debugInit;
    username = usernameInit;
    exit = false;
    cc("&aWelcome to &6Encryptors plugin&a. Type $help for help.\n");
    while (exit == false) {
        fflush(stdin);
        SetConsoleTitleA("Ultimate Console 3.0 > Encryptors");
        cc("&aConsole/&6Encryptors&a> ");
        SetConsoleTextAttribute(hCon, 0x0d);
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
                if (cmd == commands[1] || cmd == aliases[1]) clear();
                if (cmd == commands[2] || cmd == aliases[2]) col();
                if (cmd == commands[3] || cmd == aliases[3]) csr();
                if (cmd == commands[4] || cmd == aliases[4]) etm();
                if (cmd == commands[5] || cmd == aliases[5]) exit = exitCmd();
                if (cmd == commands[6] || cmd == aliases[6]) help();
            }
        }
        cin.clear();
        cmd.clear();
    }
    cc("&8Closing &4Encryptors plugin&8. Returned to basic console.\n");
}
// COMMANDS
void Enc::about() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&a========================[ &6About Encryptors plugin ... &a]========================\n");
    cc("&a@ &6Copyright ALL_67 Entertainment &f[&6cpp_makers_aka_2.9.5&f], &6All rights reserved!\n");
    cc("&a@ &6Files&f: &6encryptors.h&f, &6encryptors.cpp\n");
    cc("&a@ &6Plugin type&f: &6external cpp&f, &6encryptor\n");
    cc("&a@ &6Plugin Version&f: &63-beta\n");
    cc("&a@ &6Plugin Core Version&f: &61.0.4\n");
    cc("&a@ &6Encryptors plugin is used for encoding data in different types\n");
    cc("&a@ &6Remember to add a reference to this plugin in your console !\n");
    cc("&a@ &6Plugin Author: DingoMC\n");
    if (debug) cc("&2@ &9Debug Version: 0.3.8\n");
    cc("&a===============================================================================\n");
}
void Enc::clear() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    system("cls");
}
void Enc::col() {
    string message, output="";
    int cols, i, j, cnt=0;
    SetConsoleTitleA("Ultimate Console 3.0 > Encryptors > Column Encrypting");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&aConsole/&6Encryptors&a/&dCol&a> &bMessage&f:&d ");
    getline(cin,message);
    fflush(stdin);
    int len = message.length();
    cc("&aConsole/&6Encryptors&a/&dCol&a> &bNumber of columns&f[&61~"+ to_string(len) +"&f]:&d ");
    cin>>cols;
    if (cin.fail() || cols <= 0 || cols > len) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        int rows = (len/cols)+1;
        if (len % cols == 0) rows--;
        char** T = new char*[rows];
        int KEY;
        for (i=0; i<rows; i++) T[i] = new char[cols];
        cc("&aConsole/&6Encryptors&a/&dCol&a> &bKey column&f[&60~"+ to_string(cols-1) +"&f]:&d ");
        cin>>KEY;
        if (cin.fail() || KEY < 0 || KEY >= cols) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            for (i=0; i<rows; i++) {
                for (j=0; j<cols; j++) {
                    if (cnt < len) {
                        T[i][j] = message.at(cnt);
                        cnt++;
                    }
                    else T[i][j] = 0;
                }
            }
            cc("&aConsole/&6Encryptors&a/&dCol&a> &aEncrypted Message&f: &e[");
            SetConsoleTextAttribute(hCon, 0x0d);
            cnt=0;
            for (j=KEY; j<cols; j++) {
                for (i=0; i<rows; i++) {
                    if (cnt < len) {
                        cout<<T[i][j];
                        cnt++;
                    }
                }
            }
            for (j=0; j<KEY; j++) {
                for (i=0; i<rows; i++) {
                    if (cnt < len) {
                        cout<<T[i][j];
                        cnt++;
                    }
                }
            }
            cc("&e]");
            cout<<endl;
        }
        for (i=0; i<rows; i++) delete []T[i];
        delete []T;
    }
}
void Enc::csr() {
    string message;
    SetConsoleTitleA("Ultimate Console 3.0 > Encryptors > Caesar Encrypting");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&aConsole/&6Encryptors&a/&dCsr&a> &bMessage&f:&d ");
    getline(cin,message);
    fflush(stdin);
    int len = message.length();
    int KEY;
    cc("&aConsole/&6Encryptors&a/&dCsr&a> &bEncryption Value&f[&61~25&f]:&d ");
    cin>>KEY;
    if (cin.fail() || KEY < 1 || KEY > 25) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        for (int i=0; i<len; i++) {
            if ((int) message.at(i) >= 65 && (int) message.at(i) <= 90) {
                if ((int) message.at(i) + KEY > 90) message.at(i) = (char) ((int) message.at(i) + KEY - 26);
                else message.at(i) = (char) ((int) message.at(i) + KEY);
            }
            if ((int) message.at(i) >= 97 && (int) message.at(i) <= 122) {
                if ((int) message.at(i) + KEY > 122) message.at(i) = (char) ((int) message.at(i) + KEY - 26);
                else message.at(i) = (char) ((int) message.at(i) + KEY);
            }
        }
        cc("&aConsole/&6Encryptors&a/&dCsr&a> &aEncrypted Message&f: &e[&d " + message + " &e]\n");
    }
}
void Enc::etm() {
    SetConsoleTitleA("Ultimate Console 3.0 > Encryptors > ETM Encryptor");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    string etm_path = "\"" + string(buffer).substr(0, pos) + "\\plugins\\etm.exe\"";
    const char *c_etm_path = etm_path.c_str();
    system(c_etm_path);
}
bool Enc::exitCmd() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    return true;
}
void Enc::help() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&a======================[ &6Encryptors Plugin Command Help &a]=======================\n");
    for (int k=0; k<cmd_count; k++) {
        if (commands[k] != aliases[k]) cc("&a"+commands[k]+" &f:&6 "+desc[k]+" &f(&2Alias&f:&a "+aliases[k]+"&f)\n");
        else cc("&a"+commands[k]+" &f:&6 "+desc[k]+"\n");
    }
    cc("&a===============================================================================\n");
}
// OTHERS
// Issued when user type a command without prefix (treated as standard text)
void Enc::echo(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime();
    cc("&a[&6Encryptors&a][&b"+username+"&a]&f "+message+"\n");
}
void Enc::cc(string text) {
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
string Enc::getTime() {
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
void Enc::ErrorCommandUnknown(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Encryptors] Error # "<<__func__<<": \'"<<message<<"\'. Type $help for commands list."<<endl;
}
// Issued when User types invalid value
void Enc::ErrorInvalidInput() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Encryptors] Error # "<<__func__<<": Invalid value."<<endl;
}