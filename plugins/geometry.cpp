//  @ This code is made by DingoMC
//  @ Ultimate Console version 3 - Geometry Plugin class methods
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
#include "geometry.h"
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.000)
#define PI 3.14159265358979
using namespace std;
Geometry::Geometry() {
    // Commands List
    commands[0] = "about";
    commands[1] = "circle";
    commands[2] = "clear";
    commands[3] = "cube";
    commands[4] = "exit";
    commands[5] = "help";
    commands[6] = "hexagon";
    commands[7] = "octogon";
    commands[8] = "precision";
    commands[9] = "rectangle";
    commands[10] = "rhomboid";
    commands[11] = "rhombus";
    commands[12] = "rtriangle";
    commands[13] = "square";
    commands[14] = "triangle";
    // Command Aliases
    aliases[0] = "ab";
    aliases[1] = "ci";
    aliases[2] = "cl";
    aliases[3] = "cu";
    aliases[4] = "ex";
    aliases[5] = "?";
    aliases[6] = "hex";
    aliases[7] = "oct";
    aliases[8] = "prec";
    aliases[9] = "rect";
    aliases[10] = "rhomboid";
    aliases[11] = "rhombus";
    aliases[12] = "rt";
    aliases[13] = "sq";
    aliases[14] = "tri";
    // Command descriptions
    desc[0] = "Show Info about this plugin";
    desc[1] = "Calculates circle parameters based on its radius";
    desc[2] = "Clears Geometry console display";
    desc[3] = "Calculates cube parameters based on its side";
    desc[4] = "Exit from Geometry console";
    desc[5] = "Show this list";
    desc[6] = "Calculates regular hexagon parameters based on its side";
    desc[7] = "Calculates regular octogon parameters based on its side";
    desc[8] = "Set precision for numbers";
    desc[9] = "Calculates rectangle parameters based on its two sides";
    desc[10] = "Calculates rhomboid parameters based on its two sides and height";
    desc[11] = "Calculates rhombus parameters based on its two diagonals";
    desc[12] = "Calculates right triangle parameters based on its two catheti";
    desc[13] = "Calculates square parameters based on its side";
    desc[14] = "Calculates equilateral triangle parameters based on its side";
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
void Geometry::main(bool debugInit, string usernameInit, clock_t startTime) {
    debug = debugInit;
    username = usernameInit;
    exit = false;
    startInit = startTime;
    cc("&aWelcome to &eGeometry Plugin&a. Type !help for help.\n");
    while (exit == false) {
        fflush(stdin);
        SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin");
        cc("&aConsole/&eGeometry&a> ");
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
                if (cmd == commands[1] || cmd == aliases[1]) circle();
                if (cmd == commands[2] || cmd == aliases[2]) clear();
                if (cmd == commands[3] || cmd == aliases[3]) cube();
                if (cmd == commands[4] || cmd == aliases[4]) exit = exitCmd();
                if (cmd == commands[5] || cmd == aliases[5]) help();
                if (cmd == commands[6] || cmd == aliases[6]) hexagon();
                if (cmd == commands[7] || cmd == aliases[7]) octogon();
                if (cmd == commands[8] || cmd == aliases[8]) prc();
                if (cmd == commands[9] || cmd == aliases[9]) rectangle();
                if (cmd == commands[10] || cmd == aliases[10]) rhomboid();
                if (cmd == commands[11] || cmd == aliases[11]) rhombus();
                if (cmd == commands[12] || cmd == aliases[12]) rtriangle();
                if (cmd == commands[13] || cmd == aliases[13]) square();
                if (cmd == commands[14] || cmd == aliases[14]) triangle();
            }
        }
        cin.clear();
        cmd.clear();
    }
    cc("&8Closing &6Geometry Plugin&8. Returned to basic console.\n");
}
// COMMANDS
void Geometry::about() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    cc("&a===================[ &eGeometry Console Plugin. About ... &a]======================\n");
    cc("&a@ &eCopyright ALL_67 Entertainment &f[&6cpp_makers_aka_2.9.5&f], &eAll rights reserved!\n");
    cc("&a@ &eFiles&f: &6geometry.h&f, &6geometry.cpp\n");
    cc("&a@ &ePlugin type&f: &6external cpp\n");
    cc("&a@ &ePlugin Version&f: &610\n");
    cc("&a@ &ePlugin Core Version&f: &61.0.4-Geo\n");
    cc("&a@ &eGeometry plugin is useful for calculating parameters of right figures and geometrical solids\n");
    cc("&a@ &eRemember to add a reference to this plugin in your console !\n");
    cc("&a@ &ePlugin Author: DingoMC\n");
    if (debug) cc("&2@ &6Debug Version: 0.3.8\n");
    cc("&a===============================================================================\n");
}
void Geometry::circle() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Circle");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double radius;
    cc("&aConsole/&eGeometry&a/&6Cir&a> &eType radius of a circle &f[&6>0&f]:&6 ");
    cin>>radius;
    if (cin.fail() || radius <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Cir&a> &2Area &f=&a ");
        cout<<fixed<<setprecision(prec)<<pow(radius,2.0)*PI<<endl;
        cc("&aConsole/&eGeometry&a/&6Cir&a> &2Circumference &f=&a ");
        cout<<fixed<<setprecision(prec)<<radius*2.0*PI<<endl;
    }
}
void Geometry::clear() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    system("cls");
}
void Geometry::cube() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Cube");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double side;
    cc("&aConsole/&eGeometry&a/&6C3D&a> &eType side of a cube &f[&6>0&f]:&6 ");
    cin>>side;
    if (cin.fail() || side <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6C3D&a> &2Total area &f=&a ");
        cout<<fixed<<setprecision(prec)<<pow(side,2.0)*6.0<<endl;
        cc("&aConsole/&eGeometry&a/&6C3D&a> &2Volume &f=&a ");
        cout<<fixed<<setprecision(prec)<<pow(side,3.0)<<endl;
        cc("&aConsole/&eGeometry&a/&6C3D&a> &2Wall diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(2.0)<<endl;
        cc("&aConsole/&eGeometry&a/&6C3D&a> &2Cube diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(3.0)<<endl;
        cc("&aConsole/&eGeometry&a/&6C3D&a> &2Sum of all edges &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*12<<endl;
        cc("&aConsole/&eGeometry&a/&6C3D&a> &2Inscribed sphere radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<side/2.0<<endl;
        cc("&aConsole/&eGeometry&a/&6C3D&a> &2Circumscribed sphere radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(3.0)/2.0<<endl;
    }
}
bool Geometry::exitCmd() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    return true;
}
void Geometry::help() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    cc("&a=================[ &eGeometry Console Plugin. Command Help &a]=================\n");
    for (int k=0; k<cmd_count; k++) {
        if (commands[k] != aliases[k]) cc("&a"+commands[k]+" &f:&e "+desc[k]+" &f(&2Alias&f:&a "+aliases[k]+"&f)\n");
        else cc("&a"+commands[k]+" &f:&e "+desc[k]+"\n");
    }
    cc("&a===============================================================================\n");
}
void Geometry::hexagon() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Hexagon");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double side;
    cc("&aConsole/&eGeometry&a/&6Hex&a> &eType side of a regular hexagon &f[&6>0&f]:&6 ");
    cin>>side;
    if (cin.fail() || side <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Hex&a> &2Area &f=&a ");
        cout<<fixed<<setprecision(prec)<<pow(side,2.0)*sqrt(3)*1.5<<endl;
        cc("&aConsole/&eGeometry&a/&6Hex&a> &2Shorter diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(3.0)<<endl;
        cc("&aConsole/&eGeometry&a/&6Hex&a> &2Longer diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*2.0<<endl;
        cc("&aConsole/&eGeometry&a/&6Hex&a> &2Perimeter &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*6<<endl;
        cc("&aConsole/&eGeometry&a/&6Hex&a> &2Inscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(3)*0.5<<endl;
        cc("&aConsole/&eGeometry&a/&6Hex&a> &2Circumscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<side<<endl;
    }
}
void Geometry::octogon() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Octogon");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double side;
    cc("&aConsole/&eGeometry&a/&6Oct&a> &eType side of a regular octogon &f[&6>0&f]:&6 ");
    cin>>side;
    if (cin.fail() || side <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Oct&a> &2Area &f=&a ");
        cout<<fixed<<setprecision(prec)<<pow(side,2.0)*2.0*(1+sqrt(2))<<endl;
        cc("&aConsole/&eGeometry&a/&6Oct&a> &2Shorter diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(2.0+sqrt(2))<<endl;
        cc("&aConsole/&eGeometry&a/&6Oct&a> &2Longer diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*(1.0+sqrt(2))<<endl;
        cc("&aConsole/&eGeometry&a/&6Oct&a> &2Longest diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(4.0+2.0*sqrt(2))<<endl;
        cc("&aConsole/&eGeometry&a/&6Oct&a> &2Perimeter &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*8<<endl;
        cc("&aConsole/&eGeometry&a/&6Oct&a> &2Inscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<0.5*side*(1.0+sqrt(2))<<endl;
        cc("&aConsole/&eGeometry&a/&6Oct&a> &2Circumscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<0.5*side*sqrt(4.0+2.0*sqrt(2))<<endl;
    }
}
void Geometry::prc() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Prc");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    int p = 3;
    cc("&aConsole/&eGeometry&a/&6Prc&a> &bSet precision &f[&60~15&f]:&e ");
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
void Geometry::rectangle() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Rectangle");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double side, side2;
    cc("&aConsole/&eGeometry&a/&6Rct&a> &eType first side of a rectangle &f[&6>0&f]:&6 ");
    cin>>side;
    if (cin.fail() || side <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Rct&a> &eType second side of a rectangle &f[&6>0&f]:&6 ");
        cin>>side2;
        if (cin.fail() || side2 <= 0) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            cc("&aConsole/&eGeometry&a/&6Rct&a> &2Area &f=&a ");
            cout<<fixed<<setprecision(prec)<<side*side2<<endl;
            cc("&aConsole/&eGeometry&a/&6Rct&a> &2Diagonal &f=&a ");
            cout<<fixed<<setprecision(prec)<<sqrt(pow(side,2.0)+pow(side2,2.0))<<endl;
            cc("&aConsole/&eGeometry&a/&6Rct&a> &2Perimeter &f=&a ");
            cout<<fixed<<setprecision(prec)<<2.0*(side+side2)<<endl;
            cc("&aConsole/&eGeometry&a/&6Rct&a> &2Circumscribed circle radius &f=&a ");
            cout<<fixed<<setprecision(prec)<<0.5*sqrt(pow(side,2.0)+pow(side2,2.0))<<endl;
            if (side==side2) cc("&6* This rectangle is a square. Type !square for more params.\n");
        }
    }
}
void Geometry::rhomboid() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Rhomboid");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double b, s, h;
    cc("&aConsole/&eGeometry&a/&6Rbd&a> &eType base of a rhomboid &f[&6>0&f]:&6 ");
    cin>>b;
    if (cin.fail() || b <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Rbd&a> &eType side of a rhomboid &f[&6>0&f]:&6 ");
        cin>>s;
        if (cin.fail() || s <= 0) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            cc("&aConsole/&eGeometry&a/&6Rbd&a> &eType height of a rhomboid &f[&6>0&f]:&6 ");
            cin>>h;
            if (cin.fail() || h <= 0) {
                cin.clear();
                ErrorInvalidInput();
            }
            else {
                cc("&aConsole/&eGeometry&a/&6Rbd&a> &2Area &f=&a ");
                cout<<fixed<<setprecision(prec)<<b*h<<endl;
                cc("&aConsole/&eGeometry&a/&6Rbd&a> &2Shorter diagonal &f=&a ");
                cout<<fixed<<setprecision(prec)<<sqrt(pow(b,2.0)+pow(s,2.0)-2.0*b*sqrt(pow(s,2.0)-pow(h,2.0)))<<endl;
                cc("&aConsole/&eGeometry&a/&6Rbd&a> &2Longer diagonal &f=&a ");
                cout<<fixed<<setprecision(prec)<<sqrt(pow(b,2.0)+pow(s,2.0)+2.0*b*sqrt(pow(s,2.0)-pow(h,2.0)))<<endl;
                cc("&aConsole/&eGeometry&a/&6Rbd&a> &2Perimeter &f=&a ");
                cout<<fixed<<setprecision(prec)<<2.0*(b+s)<<endl;
                if (s==h) {
                    if (b==s) cc("&6* This rhomboid is a square. Type !square for more params.\n");
                    else cc("&6* This rhomboid is a rectangle. Type !rectangle for more params.\n");
                }
                else if (b==s) cc("&6* This rhomboid is a rhombus. Type !rhombus for more params.\n");
            }
        }
    }
}
void Geometry::rhombus() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Rhombus");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double d1, d2;
    cc("&aConsole/&eGeometry&a/&6Rbs&a> &eType first diagonal of a rhombus &f[&6>0&f]:&6 ");
    cin>>d1;
    if (cin.fail() || d1 <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Rbs&a> &eType second diagonal of a rhombus &f[&6>0&f]:&6 ");
        cin>>d2;
        if (cin.fail() || d2 <= 0) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            cc("&aConsole/&eGeometry&a/&6Rbs&a> &2Area &f=&a ");
            cout<<fixed<<setprecision(prec)<<0.5*d1*d2<<endl;
            cc("&aConsole/&eGeometry&a/&6Rbs&a> &2Side &f=&a ");
            cout<<fixed<<setprecision(prec)<<sqrt(pow(d1*0.5,2.0)+pow(d2*0.5,2.0))<<endl;
            cc("&aConsole/&eGeometry&a/&6Rbs&a> &2Perimeter &f=&a ");
            cout<<fixed<<setprecision(prec)<<4.0*sqrt(pow(d1*0.5,2.0)+pow(d2*0.5,2.0))<<endl;
            cc("&aConsole/&eGeometry&a/&6Rbs&a> &2Inscribed circle radius &f=&a ");
            cout<<fixed<<setprecision(prec)<<(d1*d2)/(4.0*sqrt(pow(d1*0.5,2.0)+pow(d2*0.5,2.0)))<<endl;
            if (d1==d2) cc("&6* This rhombus is a square. Type !square for more params.\n");
        }
    }
}
void Geometry::rtriangle() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > RTriangle");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double cat1, cat2;
    cc("&aConsole/&eGeometry&a/&6Rtr&a> &eType first cathetus of a right triangle &f[&6>0&f]:&6 ");
    cin>>cat1;
    if (cin.fail() || cat1 <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Rtr&a> &eType second cathetus of a right triangle &f[&6>0&f]:&6 ");
        cin>>cat2;
        if (cin.fail() || cat2 <= 0) {
            cin.clear();
            ErrorInvalidInput();
        }
        else {
            cc("&aConsole/&eGeometry&a/&6Rtr&a> &2Area &f=&a ");
            cout<<fixed<<setprecision(prec)<<0.5*cat1*cat2<<endl;
            cc("&aConsole/&eGeometry&a/&6Rtr&a> &2Hypotenuse &f=&a ");
            cout<<fixed<<setprecision(prec)<<sqrt(pow(cat1,2.0)+pow(cat2,2.0))<<endl;
            cc("&aConsole/&eGeometry&a/&6Rtr&a> &2Perimeter &f=&a ");
            cout<<fixed<<setprecision(prec)<<cat1+cat2+sqrt(pow(cat1,2.0)+pow(cat2,2.0))<<endl;
            cc("&aConsole/&eGeometry&a/&6Rtr&a> &2Inscribed circle radius &f=&a ");
            cout<<fixed<<setprecision(prec)<<0.5*(cat1+cat2-sqrt(pow(cat1,2.0)+pow(cat2,2.0)))<<endl;
            cc("&aConsole/&eGeometry&a/&6Rtr&a> &2Circumscribed circle radius &f=&a ");
            cout<<fixed<<setprecision(prec)<<0.5*sqrt(pow(cat1,2.0)+pow(cat2,2.0))<<endl;
        }
    }
}
void Geometry::square() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Square");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double side;
    cc("&aConsole/&eGeometry&a/&6Sqr&a> &eType side of a square &f[&6>0&f]:&6 ");
    cin>>side;
    if (cin.fail() || side <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Sqr&a> &2Area &f=&a ");
        cout<<fixed<<setprecision(prec)<<pow(side,2.0)<<endl;
        cc("&aConsole/&eGeometry&a/&6Sqr&a> &2Diagonal &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(2)<<endl;
        cc("&aConsole/&eGeometry&a/&6Sqr&a> &2Perimeter &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*4.0<<endl;
        cc("&aConsole/&eGeometry&a/&6Sqr&a> &2Inscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*0.5<<endl;
        cc("&aConsole/&eGeometry&a/&6Sqr&a> &2Circumscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*0.5*sqrt(2)<<endl;
    }
}
void Geometry::triangle() {
    SetConsoleTitleA("Ultimate Console 3.0 > Geometry Plugin > Triangle");
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<"[Debug] "<<username<<" issued command !"<<__func__<<endl;
    double side;
    cc("&aConsole/&eGeometry&a/&6Tri&a> &eType side of an equilateral triangle &f[&6>0&f]:&6 ");
    cin>>side;
    if (cin.fail() || side <= 0) {
        cin.clear();
        ErrorInvalidInput();
    }
    else {
        cc("&aConsole/&eGeometry&a/&6Tri&a> &2Area &f=&a ");
        cout<<fixed<<setprecision(prec)<<pow(side,2.0)*sqrt(3)*0.25<<endl;
        cc("&aConsole/&eGeometry&a/&6Tri&a> &2Height &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*sqrt(3.0)*0.5<<endl;
        cc("&aConsole/&eGeometry&a/&6Tri&a> &2Perimeter &f=&a ");
        cout<<fixed<<setprecision(prec)<<side*3<<endl;
        cc("&aConsole/&eGeometry&a/&6Tri&a> &2Inscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<(side*sqrt(3.0)*0.5)/3.0<<endl;
        cc("&aConsole/&eGeometry&a/&6Tri&a> &2Circumscribed circle radius &f=&a ");
        cout<<fixed<<setprecision(prec)<<((side*sqrt(3.0)*0.5)/3.0)*2.0<<endl;
    }
}
// OTHERS
// Issued when user type a command without prefix (treated as standard text)
void Geometry::echo(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime();
    cc("&a[&eGeometry&a][&b"+username+"&a]&f "+message+"\n");
}
void Geometry::cc(string text) {
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
string Geometry::getTime() {
    // Get current active time and return it as a string
    string clock_str="[";
    clock_t end = clock() - startInit;
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
void Geometry::ErrorCommandUnknown(string message) {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Geometry] Error # "<<__func__<<": \'"<<message<<"\'. Type !help for commands list."<<endl;
}
// Issued when User types invalid value
void Geometry::ErrorInvalidInput() {
    SetConsoleTextAttribute(hCon, 0x09);
    if (debug) cout<<getTime()<<" ";
    SetConsoleTextAttribute(hCon, 0x0c);
    cout<<"[Geometry] Error # "<<__func__<<": Invalid value."<<endl;
}