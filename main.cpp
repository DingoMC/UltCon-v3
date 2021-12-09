//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Main Code
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include "plugins/basic.cpp"
#include "plugins/math_ex.cpp"
#include "plugins/geometry.cpp"
#include "plugins/dang$$.cpp"
#include "plugins/encryptors.cpp"
#include "plugins/algo.cpp"
using namespace std;
int main () {
    SetConsoleTitleA("Ultimate Console 3.0 - Getting ready...");
    Basic basic;
    basic.startTime = clock();
    MathEx mathex;
    Geometry geometry;
    Dang dang;
    Enc enc;
    Algo algo;
    bool *plugin_cache = new bool[basic.ext_count+1];
    int cmdlen;
    string cmd;
    basic.getCacheFromFile(*&plugin_cache);
    if (!plugin_cache[0]) {
        SetConsoleTitleA("Ultimate Console 3.0 > Fatal Error!");
        basic.exit = basic.crash();
        basic.exit = basic.ErrorPluginPanic();
    }
    while (basic.exit == false) {
        while (basic.logged == false) {
            SetConsoleTitleA("Ultimate Console 3.0 > User Authentication");
            basic.cc("&cUltimate Console - User Authentication (Login as \'Guest\' to skip)\n");
            basic.cc("&bUsername:&e ");
            cin>>basic.username;
            if (basic.username == "Guest") {
                if (basic.debug) basic.cc("&f"+basic.getTime()+" ");
                basic.cc("&aAutologin with Guest account.\n");
                basic.logged = true;
                Sleep(1500);
                system("cls");
                basic.cc("&aWelcome to Ultimate console 3.0. Type /help for help.\n");
            }
            else {
                basic.cc("&bPassword:&0 ");
                cin>>basic.password;
                basic.logged = basic.auth();
            }
            if (basic.logged) basic.UserPermissionLevel = basic.SetPermissionLevel();
            else basic.UserPermissionLevel = 0;
        }
        SetConsoleTitleA("Ultimate Console 3.0");
        fflush(stdin);
        basic.cc("&aConsole> ");
        SetConsoleTextAttribute(basic.hCon, 0x0e);
        getline(cin,basic.cmd);
        if (!basic.cmd.empty()) {
            if (basic.cmd.at(0)!=basic.prefix) basic.echo(basic.cmd);
            else {
                cmd = basic.cmd.erase(0,1);
                basic.err_count = 0;
                for (int i=0; i<basic.cmd_count; i++) if (cmd!=basic.commands[i]) basic.err_count++;
                for (int i=0; i<basic.cmd_count; i++) if (cmd!=basic.aliases[i]) basic.err_count++;
                for (int i=0; i<basic.ext_count; i++) if (cmd!=basic.external[i]) basic.err_count++;
                if (basic.err_count == basic.ext_count+2*(basic.cmd_count)) basic.ErrorCommandUnknown(cmd);
                if (cmd == basic.commands[0] || cmd == basic.aliases[0]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[0]) basic.about();
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[1] || cmd == basic.aliases[1]) {
                    if (plugin_cache[0]) { 
                        if (basic.UserPermissionLevel>=basic.permissionLevel[1]) basic.clear();
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[2] || cmd == basic.aliases[2]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[2]) basic.exit = basic.crash();
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[3] || cmd == basic.aliases[3]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[3]) basic.debug = basic.debugSwitch();
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[4] || cmd == basic.aliases[4]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[4]) basic.disable(*&plugin_cache);
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[5] || cmd == basic.aliases[5]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[5]) basic.enable(*&plugin_cache);
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[6] || cmd == basic.aliases[6]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[6]) basic.exit = basic.exitCmd();
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[7] || cmd == basic.aliases[7]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[7]) basic.help(*&plugin_cache);
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[8] || cmd == basic.aliases[8]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[8]) basic.logged = basic.logout();
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[9] || cmd == basic.aliases[9]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[9]) basic.plugins(*&plugin_cache);
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[10] || cmd == basic.aliases[10]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[10]) basic.getCacheFromFile(*&plugin_cache);
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.commands[11] || cmd == basic.aliases[11]) {
                    if (plugin_cache[0]) {
                        if (basic.UserPermissionLevel>=basic.permissionLevel[11]) basic.systemCmd();
                        else basic.ErrorPermissionDenied();
                    }
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.external[0]) {
                    if (plugin_cache[1]) mathex.main(basic.debug, basic.username, basic.startTime);
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.external[1]) {
                    if (plugin_cache[2]) geometry.main(basic.debug, basic.username, basic.startTime);
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.external[2]) {
                    if (plugin_cache[3]) dang.main(basic.debug, basic.username, basic.startTime);
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.external[3]) {
                    if (plugin_cache[4]) enc.main(basic.debug, basic.username, basic.startTime);
                    else basic.ErrorPluginDisabled();
                }
                if (cmd == basic.external[4]) {
                    if (plugin_cache[5]) algo.main(basic.debug, basic.username, basic.startTime);
                    else basic.ErrorPluginDisabled();
                }
            }
        }
        cin.clear();
        basic.cmd.clear();
    }
    // END //
    delete []plugin_cache;
    cin.ignore();
    cin.get();
    return 0;
}