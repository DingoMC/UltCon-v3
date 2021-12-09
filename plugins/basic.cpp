//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Basic Plugin class methods
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <windows.h>
#include "basic.h"
# define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.000)
using namespace std;
Basic::Basic () {
    // Commands List
    commands[0] = "about";
    commands[1] = "clear";
    commands[2] = "crash";
    commands[3] = "debug";
    commands[4] = "disable";
    commands[5] = "enable";
    commands[6] = "exit";
    commands[7] = "help";
    commands[8] = "logout";
    commands[9] = "plugins";
    commands[10] = "reload";
    commands[11] = "system";
    // Aliases to each command
    aliases[0] = "a";
    aliases[1] = "c";
    aliases[2] = "cr";
    aliases[3] = "deb";
    aliases[4] = "dis";
    aliases[5] = "en";
    aliases[6] = "ex";
    aliases[7] = "h";
    aliases[8] = "lo";
    aliases[9] = "pl";
    aliases[10] = "re";
    aliases[11] = "sys";
    // Command permissions
    permissionLevel[0] = 0;
    permissionLevel[1] = 1;
    permissionLevel[2] = 2;
    permissionLevel[3] = 2;
    permissionLevel[4] = 2;
    permissionLevel[5] = 2;
    permissionLevel[6] = 0;
    permissionLevel[7] = 0;
    permissionLevel[8] = 0;
    permissionLevel[9] = 0;
    permissionLevel[10] = 1;
    permissionLevel[11] = 1;
    // Command descriptions
    desc[0] = "About this console";
    desc[1] = "Clear console output";
    desc[2] = "Force console crash";
    desc[3] = "Enable/disable debug messages";
    desc[4] = "Disable selected plugins";
    desc[5] = "Enable selected plugins";
    desc[6] = "Exit this console";
    desc[7] = "Show this list";
    desc[8] = "Log out from this user";
    desc[9] = "Show plugins list";
    desc[10] = "Reload plugins resources";
    desc[11] = "Execute system command";
    // External commands
    external[0] = "math";
    external[1] = "geometry";
    external[2] = "dang$$";
    external[3] = "encryptors";
    external[4] = "algo";
    // External command descriptions
    ext_desc[0] = "Enter math plugin console";
    ext_desc[1] = "Enter geometry plugin console";
    ext_desc[2] = "Enter dang$$ console";
    ext_desc[3] = "Enter encryptors plugin console";
    ext_desc[4] = "Enter algo plugin console";
    // Numeric constants
    cmd_count = sizeof(commands)/sizeof(*commands);
    ext_count = sizeof(external)/sizeof(*external);
    // Command prefix
    prefix = '/';
    // Basic variables init
    err_count = 0;
    exit = false;
    debug = false;
    logged = false;
    username = "None";
    password = "000000";
    UserPermissionLevel = 0;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
}
// COMMAND METHODS
void Basic::about() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    cc("&a=======================[ &bUltimate Console 3.0. About. &a]========================\n");
    cc("&aCreator&f: &6DingoMC\n");
    cc("&aCreator contact&f:\n");
    cc("&9Discord&f: &9DingoMC#2776\n");
    cc("&bFacebook&f: &bhttps://www.facebook.com/martin.dingomc.1\n");
    cc("&aE-mail&f: &amartin701-2001@wp.pl\n");
    cc("&aConsole Version&f: &a3.0-beta_1-pre-release\n");
    cc("&aCore Version&f: &a8.3.17-Umbry\n");
    if (debug) cc("&9Debug Version: 0.3.8\n");
    cc("&a===============================================================================\n");
}
void Basic::clear() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    system("cls");
}
bool Basic::crash() {
    system("color 9f");
    system("cls");
    cout<<"# Uh Oh !\n#\n# ultimate_console_v.3.0.exe has stopped working\n#"<<endl;
	cout<<"# Reason: COMMAND_INIT_MANUAL = "<<__func__<<"\n#\n# Worker: CONSOLE_WORKER\n#"<<endl;
	cout<<"# Timestamp: "<<getTime()<<"\n#\n# Plugins crashed: 1\n#\n# Active User: "<<username<<"\n#\n# "<<endl;
    return true;
}
bool Basic::debugSwitch() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    debug = !debug;
    cc("&9Debug is now turned ");
    if (debug) cc("&aON.\n");
    else cc("&cOFF.\n");
    return debug;
}
void Basic::disable(bool *plugin_cache) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    int n;
    cc("&aType a number from the list to disable specific plugin&f:\n");
    cc("&b0 --> Basic\n");
    for (int i=0; i<ext_count; i++) {
        if (plugin_cache[i+1]) SetConsoleTextAttribute(hCon, 0x0a);
        else SetConsoleTextAttribute(hCon, 0x0c);
        cout<<i+1<<" --> "<<external[i]<<endl;
    }
    cc("&b-1 --> Cancel operation\n&bOption:&e ");
    cin>>n;
    if (n>=0 && n<=ext_count) {
        if (n==0) ErrorBasicPluginDisable();
        else {
            if (!plugin_cache[n]) ErrorPluginDisabled();
            else {
                plugin_cache[n] = 0;
                SetConsoleTextAttribute(hCon, 0x09);
                if (debug) cout<<getTime()<<"[Debug] ";
                cc("&aSuccessfully disabled "+external[n-1]+" plugin.\n");
                saveCacheToFile(*&plugin_cache);
            }
        }
    }
    else {
        if (n==-1) {
            SetConsoleTextAttribute(hCon, 0x09);
            if (debug) cout<<getTime()<<"[Debug] ";
            SetConsoleTextAttribute(hCon, 0x0c);
            cout<<"Operation "<<__func__<<" has been cancelled."<<endl;
        }
        else ErrorInvalidInput();
    }
    cin.clear();
}
void Basic::enable(bool *plugin_cache) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    int n;
    cc("&aType a number from the list to enable specific plugin&f:\n");
    cc("&b0 --> Basic\n");
    for (int i=0; i<ext_count; i++) {
        if (plugin_cache[i+1]) SetConsoleTextAttribute(hCon, 0x0a);
        else SetConsoleTextAttribute(hCon, 0x0c);
        cout<<i+1<<" --> "<<external[i]<<endl;
    }
    cc("&b-1 --> Cancel operation\n&bOption:&e ");
    cin>>n;
    if (n>=0 && n<=ext_count) {
        if (n==0) ErrorBasicPluginEnable();
        else {
            if (plugin_cache[n]) ErrorPluginEnabled();
            else {
                plugin_cache[n] = 1;
                SetConsoleTextAttribute(hCon, 0x09);
                if (debug) cout<<getTime()<<"[Debug] ";
                cc("&aSuccessfully enabled "+external[n-1]+" plugin.\n");
                saveCacheToFile(*&plugin_cache);
            }
        }
    }
    else {
        if (n==-1) {
            SetConsoleTextAttribute(hCon, 0x09);
            if (debug) cout<<getTime()<<"[Debug] ";
            SetConsoleTextAttribute(hCon, 0x0c);
            cout<<"Operation "<<__func__<<" has been cancelled."<<endl;
        }
        else ErrorInvalidInput();
    }
    cin.clear();
}
bool Basic::exitCmd() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x08);
    cout<<"Logged out from console. Press any key to exit ..."<<endl;
    return true;
}
void Basic::help(bool *plugin_cache) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    cc("&a===================[ &bUltimate Console 3.0. Commands help. &a]====================\n");
    for (int i=0; i<cmd_count; i++) if (UserPermissionLevel>=permissionLevel[i]) cc("&a"+commands[i]+" &f:&b "+desc[i]+" &f(&2Alias&f:&a "+aliases[i]+"&f)\n");
    for (int i=0; i<ext_count; i++) if (plugin_cache[i+1]) cc("&2External&f:&a "+external[i]+" &f:&6 "+ext_desc[i]+"\n");
    cc("&a===============================================================================\n");
}
bool Basic::logout() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    if (debug) cout<<getTime()<<" ";
    cc("&8Logging out ...\n");
    Sleep(1500);
    system("cls");
    return false;
}
void Basic::plugins(bool *plugin_cache) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    cc("&aPlugins List&f:\n&b0 --> Basic\n");
    for (int i=0; i<ext_count; i++) {
        if (plugin_cache[i+1]) SetConsoleTextAttribute(hCon, 0x0a);
        else SetConsoleTextAttribute(hCon, 0x0c);
        cout<<i+1<<" --> "<<external[i]<<endl;
    }
}
void Basic::systemCmd() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command /"<<__func__<<endl;
    string sys_cmd;
    cin.clear();
    fflush(stdin);
    cc("&aType in a system command&f:&7 ");
    getline(cin,sys_cmd);
    const char *f = sys_cmd.c_str();
    system(f);
    cin.clear();
}
// OTHERS
void Basic::echo(string message) {
    // Issued when user type a command without prefix (treated as standard text)
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime();
    cc("&a[&b"+username+"&a]&f "+message+"\n");
}
void Basic::getCacheFromFile(bool *plugin_cache) {
    fstream cache;
    cache.open("plugin_cache.txt",ios::in);
    for (int i=0; i<ext_count+1; i++) cache>>plugin_cache[i];
    cache.close();
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" Successfully loaded plugin cache."<<endl;
}
void Basic::saveCacheToFile(bool *plugin_cache) {
    fstream cache;
    cache.open("plugin_cache.txt",ios::out);
    for (int i=0; i<ext_count+1; i++) cache<<plugin_cache[i]<<endl;
    cache.close();
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" Successfully saved plugin cache to a file."<<endl;
}
string Basic::getTime() {
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
bool Basic::auth() {
    fstream auth;
    const int usercount = 2;
    string login_lo[usercount], pass_en_lo[usercount], pass_de[usercount];
    string en="000000", de="000000";
    int autherr=0;
    auth.open("encrypted/auth_table.txt",ios::in);
	for (int i=0; i<usercount; i++) {
		auth>>login_lo[i];
		auth>>pass_en_lo[i];
	}
	auth.close();
    for (int i=0; i<usercount; i++) {
		en=pass_en_lo[i];
		for (int j=0; j<6; j++) {
			if (en.at(j)=='0') de.at(j)='9';
			if (en.at(j)=='1') de.at(j)='3';
			if (en.at(j)=='2') de.at(j)='5';
			if (en.at(j)=='3') de.at(j)='8';
			if (en.at(j)=='4') de.at(j)='1';
			if (en.at(j)=='5') de.at(j)='0';
			if (en.at(j)=='6') de.at(j)='2';
			if (en.at(j)=='7') de.at(j)='4';
			if (en.at(j)=='8') de.at(j)='7';
			if (en.at(j)=='9') de.at(j)='6';
		}
		pass_de[i]=de;
	}
    for (int i=0; i<usercount; i++) {
        if (username == login_lo[i] && password==pass_de[i]) {
            SetConsoleTextAttribute(hCon, 0x09);
            if (debug) cout<<getTime()<<" ";
            SetConsoleTextAttribute(hCon, 0x0a);
            cout<<"Login successful. Welcome "<<username<<"!"<<endl;
            Sleep(1500);
            system("cls");
            cc("&aWelcome to Ultimate console 3.0. Type /help for help.\n");
            return true;
        }
        else autherr++;
    }
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Login failed! Incorrect username or password!"<<endl;
    Sleep(1500);
    system("cls");
    return false;
}
int Basic::SetPermissionLevel() {
    if (username=="Admin") return 2;
    if (username=="User") return 1;
    return 0;
}
void Basic::cc(string text) {
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
// ERRORS
bool Basic::ErrorPluginPanic() {
    // Issued when Basic plugin is disabled
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": Basic plugin is disabled! Bailing out..."<<endl;
    return true;
}
void Basic::ErrorCommandUnknown(string message) {
    // Issued when command cannot be found
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": \'"<<message<<"\'. Type /help for commands list."<<endl;
}
void Basic::ErrorPermissionDenied() {
    // Issued when User doesn't have required permission level
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": Insufficient permission."<<endl;
}
void Basic::ErrorInvalidInput() {
    // Issued when User types invalid value
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": Invalid value."<<endl;
}
void Basic::ErrorBasicPluginDisable() {
    // Issued when User tries to disable basic plugin
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": Cannot disable Basic plugin."<<endl;
}
void Basic::ErrorPluginDisabled() {
    // Issued when User tries to disable plugin already disabled or when User tries to access disabled plugin
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": This plugin is disabled."<<endl;
}
void Basic::ErrorBasicPluginEnable() {
    // Issued when User tries to enable basic plugin
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": Basic plugin is always enabled."<<endl;
}
void Basic::ErrorPluginEnabled() {
    // Issued when User tries to disable plugin already enabled
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"Error # "<<__func__<<": This plugin is enabled."<<endl;
}