//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - dang$$ class methods
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
#include "dang$$.h"
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.000)
using namespace std;
Dang::Dang () {
    // Commands List
    commands[0] = "about";
    commands[1] = "clear";
    commands[2] = "code";
    commands[3] = "decode";
    commands[4] = "exit";
    commands[5] = "help";
    commands[6] = "message";
    commands[7] = "minecraft";
    // Command Aliases
    aliases[0] = "ab";
    aliases[1] = "cl";
    aliases[2] = "co";
    aliases[3] = "de";
    aliases[4] = "ex";
    aliases[5] = "?";
    aliases[6] = "msg";
    aliases[7] = "mc";
    // Command descriptions
    desc[0] = "Show Info about this plugin";
    desc[1] = "Clears dang$$ console display";
    desc[2] = "Enters dang$$ coding console";
    desc[3] = "Enters dang$$ decoding console";
    desc[4] = "Exit from dang$$ console";
    desc[5] = "Show this list";
    desc[6] = "Enters dang$$ message creator";
    desc[7] = "Runs Minecraft launcher (if available)";
    cmd_count = sizeof(commands)/sizeof(*commands);
    prefix = '$';
    err_count = 0;
    exit = false;
    debug = false;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    username = "None";
}
// MAIN FUNCTION
void Dang::main(bool debugInit, string usernameInit, clock_t TimeInit) {
    startTime = TimeInit;
    debug = debugInit;
    username = usernameInit;
    exit = false;
    cc("&aWelcome to &cdang$$&a. Type $help for help.\n");
    while (exit == false) {
        fflush(stdin);
        SetConsoleTitleA("Ultimate Console 3.0 > dang$$");
        cc("&aConsole/&cdang$$&a> ");
        SetConsoleTextAttribute(hCon, 0x0c);
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
                if (cmd == commands[2] || cmd == aliases[2]) code();
                if (cmd == commands[3] || cmd == aliases[3]) decode();
                if (cmd == commands[4] || cmd == aliases[4]) exit = exitCmd();
                if (cmd == commands[5] || cmd == aliases[5]) help();
                if (cmd == commands[6] || cmd == aliases[6]) message();
                if (cmd == commands[7] || cmd == aliases[7]) minecraft();
            }
        }
        cin.clear();
        cmd.clear();
    }
    cc("&8Closing &4dang$$&8. Returned to basic console.\n");
}
// COMMANDS
void Dang::about() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&a==============================[ &cAbout dang$$... &a]==============================\n");
    cc("&a@ &cCopyright ALL_67 Entertainment &f[&6cpp_makers_aka_2.9.5&f], &cAll rights reserved!\n");
    cc("&a@ &cFiles&f: &6dang$$.h&f, &6dang$$.cpp\n");
    cc("&a@ &cPlugin type&f: &6external cpp&f, &6translator [lan_server]\n");
    cc("&a@ &cPlugin Version&f: &62-beta\n");
    cc("&a@ &cPlugin Core Init&f: &60.1778-15-Umbry\n");
    cc("&a@ &cPlugin Core Shell&f: &6akka-2.9.8\n");
    cc("&a@ &cdang$$ plugin is used for encoding data to hex form\n");
    cc("&a@ &cRemember to add a reference to this plugin in your console !\n");
    cc("&a@ &cPlugin Author: DingoMC\n");
    if (debug) cc("&2@ &9Debug Version: 0.3.8\n");
    cc("&a===============================================================================\n");
}
void Dang::clear() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    system("cls");
}
void Dang::code() {
    string message, codetype, result;
    SetConsoleTitleA("Ultimate Console 3.0 > dang$$ > Code");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&aConsole/&cdang$$&a/&4Enc&a> &bMessage&f:&c ");
    getline(cin,message);
    fflush(stdin);
    cc("&aConsole/&cdang$$&a/&4Enc&a> &bCodeType &f(&30R&f, &31A&f, &32B&f, &33C&f)&f:&c ");
    getline(cin,codetype);
    fflush(stdin);
    result = coder(message,codetype);
    cc("&aConsole/&cdang$$&a/&4Enc&a> &bCoded Message&f[&3" + codetype + "&f]:&a " + result + "\n");
}
void Dang::decode() {
    string message, codetype, result;
    SetConsoleTitleA("Ultimate Console 3.0 > dang$$ > Decode");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&aConsole/&cdang$$&a/&4Dec&a> &bMessage&f:&c ");
    getline(cin,message);
    fflush(stdin);
    cc("&aConsole/&cdang$$&a/&4Dec&a> &bCodeType &f(&30R&f, &31A&f, &32B&f, &33C&f)&f:&c ");
    getline(cin,codetype);
    fflush(stdin);
    result = decoder(message,codetype);
    cc("&aConsole/&cdang$$&a/&4Dec&a> &bDecoded Message&f[&3" + codetype + "&f]:&a " + result + "\n");
}
bool Dang::exitCmd() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    return true;
}
void Dang::help() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&a========================[ &cdang$$ Console Command Help &a]========================\n");
    for (int k=0; k<cmd_count; k++) {
        if (commands[k] != aliases[k]) cc("&a"+commands[k]+" &f:&c "+desc[k]+" &f(&2Alias&f:&a "+aliases[k]+"&f)\n");
        else cc("&a"+commands[k]+" &f:&c "+desc[k]+"\n");
    }
    cc("&a===============================================================================\n");
}
void Dang::message() {
    string message, msgtype, result;
    SetConsoleTitleA("Ultimate Console 3.0 > dang$$ > Message");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&aConsole/&cdang$$&a/&4Msg&a> &bMessage&f:&c ");
    getline(cin,message);
    fflush(stdin);
    cc("&aConsole/&cdang$$&a/&4Msg&a> &bMessageType &f(&3RS&f)&f:&c ");
    getline(cin,msgtype);
    fflush(stdin);
    result = CreateMessage(message,msgtype);
    cc("&aConsole/&cdang$$&a/&4Msg&a> &bFinal Message&f[&3" + msgtype + "&f]:&a " + result + "\n");
}
void Dang::minecraft() {
    SetConsoleTitleA("Ultimate Console 3.0 > dang$$ > Minecraft");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&aConsole/&cdang$$&a/&4MC&a> &bAttempting to run...\n");
    SetConsoleTextAttribute(hCon, 0x08);
    // This path must be changed if necessary
    system("\"C:/Program Files (x86)/Minecraft Launcher/MinecraftLauncher.exe\"");
    cc("&aConsole/&cdang$$&a/&4MC&a> &aExecution has finished.\n");
}
// OTHERS
// dang$$ Coder
string Dang::coder(string Text, string Coding) {
    string Result = "";
    int Pos = 0, Errors = 0;
    vector <string> hexnum;
    vector <int> num;
    hexnum.resize(Text.length());
    num.resize(Text.length());
    SetConsoleTitleA("Ultimate Console 3.0 > dang$$ > Code > Coding...");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&b[SYN] Checking entered code type...\n");
    for (int i=0; i < STDANG_CTYPES; i++) {
        if (Coding != CodesList[i]) Errors++;
        else {
            cc("&a[ACK] Code found: " + CodesList[i] + "\n");
            Pos = Positioners[i];
            cc("&b[STA] Starting coding...\n");
            break;
        }
    }
    if (Errors == STDANG_CTYPES) {
        cc("&c[ERR] Unknown coding type!\n");
        return "&c[dang$$#Error] Unknown coding type!";
    }
    for (int i=0; i<Text.length(); i++) {
        num[i] = (int) Text[i];
        if (num[i] == 32) num[i] = 0;
        else {
            cc("&f[OPR]&9 " + to_string(num[i]) + " &e--> ");
            num[i] += Pos;
            cc("&b" + to_string(num[i]) + "\n");
        }
        if (num[i] == 0) hexnum[i] = " ";
        else {
            hexnum[i].resize(2);
            if (num[i]%16 >= 0 && num[i]%16 <= 9) hexnum[i].at(1) = (char) 48+(num[i]%16);
            if (num[i]%16 >= 10 && num[i]%16 <= 15) hexnum[i].at(1) = (char) 87+(num[i]%16);
            num[i] /= 16;
            if (num[i]%16 >= 0 && num[i]%16 <= 9) hexnum[i].at(0) = (char) 48+(num[i]%16);
            if (num[i]%16 >= 10 && num[i]%16 <= 15) hexnum[i].at(0) = (char) 87+(num[i]%16);
        }
        Result += hexnum[i];
        cc("&f[ACK] {&dPos&f:&b" + to_string(i) + "&f, &dInt&f:&b" + to_string(num[i]*16) + " &e--> &dString&c[&5" + hexnum[i] + "&c]&f}\n");
    }
    return Result;
}
// dang$$ Decoder
string Dang::decoder(string Text, string Coding) {
    string Result = "";
    int Pos = 0, Errors = 0, RawCnt = 0;
    vector <int> Num;
    vector <int> RawNum;
    vector <char> Raw;
    Num.resize(Text.length());
    RawNum.resize(Text.length());
    Raw.resize(Text.length());
    SetConsoleTitleA("Ultimate Console 3.0 > dang$$ > Decode > Decoding...");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command $"<<__func__<<endl;
    cc("&b[SYN] Checking entered code type...\n");
    for (int i=0; i < STDANG_CTYPES; i++) {
        if (Coding != CodesList[i]) Errors++;
        else {
            cc("&a[ACK] Code found: " + CodesList[i] + "\n");
            Pos = Positioners[i];
            cc("&b[STA] Starting coding...\n");
            break;
        }
    }
    if (Errors == STDANG_CTYPES) {
        cc("&c[ERR] Unknown coding type!\n");
        return "&c[dang$$#Error] Unknown coding type!";
    }
    for (int i=0; i<Text.length(); i++) {
        Num[i] = (int) Text.at(i);
        if (Num[i] == 32) Raw[RawCnt]=' ';
        else {
            cc("&f[OPR]&9 " + to_string(Num[i]) + " &e--> ");
            if (Num[i] >= 48 && Num[i] <= 57) Num[i] -= 48;
            if (Num[i] >= 97 && Num[i] <= 102) Num[i] -= 87;
            Num[i] *= 16;
            cc("&b" + to_string(Num[i]) + " &a+ ");
            i++;
            Num[i]= (int) Text.at(i);
            cc(to_string(Num[i]) + " &e--> ");
            if (Num[i] >= 48 && Num[i] <= 57) Num[i] -= 48;
            if (Num[i] >= 97 && Num[i] <= 102) Num[i] -= 87;
            RawNum[RawCnt] = Num[i] + Num[i-1];
            cc("&b" + to_string(Num[i]) + " &d=&b " + to_string(RawNum[RawCnt]) + " &e-->&9 ");
            RawNum[RawCnt] -= Pos;
            cc(to_string(RawNum[RawCnt]) + "\n");
            Raw[RawCnt] = (char) RawNum[RawCnt];
        }
        cc("&f[ACK] {&dPos&f:&b" + to_string(RawCnt) + "&f, &dInt&f:&b" + to_string(RawNum[RawCnt]) + " &e--> &dChar&c[&5" + Raw[RawCnt] + "&c]&f}\n");
        RawCnt++;
    }
    for (int i=0; i<RawCnt; i++) Result += Raw[i];
    return Result;
}
// dang$$ Message generator
string Dang::CreateMessage(string Message, string Type) {
    string Result = "";
    int Errors = 0;
    cc("&b[SYN] Checking entered message type...\n");
    for (int i=0; i < STDANG_MTYPES; i++) {
        if (Type != MessagesList[i]) Errors++;
        else {
            cc("&a[ACK] Type found: " + MessagesList[i] + "\n");
            cc("&b[STA] Generating message...\n");
            break;
        }
    }
    if (Errors == STDANG_MTYPES) {
        cc("&c[ERR] Unknown message type!\n");
        return "&c[dang$$#Error] Unknown message type!";
    }
    if (Type == "RS") Result="$$ --msg(\""+Message+"\")[Type:RS,Attrib:{Len:"+ to_string(Message.length()) +",__cdecl}]";
    return Result;
}
// Issued when user type a command without prefix (treated as standard text)
void Dang::echo(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime();
    cc("&a[&cdang$$&a][&b"+username+"&a]&f "+message+"\n");
}
void Dang::cc(string text) {
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
string Dang::getTime() {
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
void Dang::ErrorCommandUnknown(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[dang$$] Error # "<<__func__<<": \'"<<message<<"\'. Type $help for commands list."<<endl;
}
// Issued when User types invalid value
void Dang::ErrorInvalidInput() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[dang$$] Error # "<<__func__<<": Invalid value."<<endl;
}