//This code is originally made by: Elektroteleinformatyko master v.4
# include <iostream>
# include <conio.h>
# include <windows.h>
# include <string.h>
# include <time.h>
# include <math.h>
# include <cstdlib>
# include <cstdio>
# include <limits>
using namespace std;
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.000)
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
class initial {
	public:
		string txt;
		double len;
		double spd;
		string pass0;
		bool code;
		char act;
};
class CLK {
	public:
		clock_t start;
		clock_t timeElapsed3;
		clock_t timeElapsed2;
		clock_t timeElapsed;
		unsigned msLeft;
		unsigned timeElapsed4;
		unsigned msElapsed;
		int secElapsed;
		int minElapsed;
		int secLeft;
		int minLeft;
		int hrsleft;
		long long average;
		long long avg;
		CLK () {
			msLeft=0;
			timeElapsed4=0;
			msElapsed=0;
			secElapsed=0;
			minElapsed=0;
			secLeft=0;
			minLeft=0;
			hrsleft=0;
			average=0;
			avg=0;
		}
};
class BAR {
	public:
		int cnt;
		double dly;
		int per;
		int pos;
		int Ifill;
		BAR () {
			cnt=0;
			dly=0.000;
			per=0;
			pos=0;
			Ifill=0;
		}
};
// Header
void HEADER () {
	SetConsoleTextAttribute (hConsole, 0x09);
	cout<<"Elektroteleinformatyko master Encryptor \n"<<endl;
}
void ACK () {
	SetConsoleTextAttribute (hConsole, 0x0e);
	cout<<"[";
	SetConsoleTextAttribute (hConsole, 0x0d);
	cout<<"ACK";
	SetConsoleTextAttribute (hConsole, 0x0e);
	cout<<"] ";
}
// Main
main () {
	// Setup Configuration
	SetConsoleTitle("Elektroteleinformatyko master Encryptor");
	bool exit=false;
	char ex;
	// Main Encryptor
	while (exit==false) {
		initial ini;
		CLK clk;
		BAR bar;
		bool err=false;
		int j=0, k=0, i=0;
		string result="", x="";
		system("cls");
		// Select action
		do {
			HEADER();
			SetConsoleTextAttribute (hConsole, 0x0b);
			cout<<"Choose type of an action You wish to perform:\nc --> code\nd --> decode"<<endl;
			SetConsoleTextAttribute (hConsole, 0x0e);
			cin>>ini.act;
			switch (ini.act) {
				case 'c': {
					SetConsoleTextAttribute (hConsole, 0x0a);
					cout<<"Selected action: code"<<endl;
					ini.code=true;
					err=false;
					break;
				}
				case 'd': {
					SetConsoleTextAttribute (hConsole, 0x0a);
					cout<<"Selected action: decode"<<endl;
					ini.code=false;
					err=false;
					break;
				}
				default: {
					cin.clear();
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');
					SetConsoleTextAttribute (hConsole, 0x0c);
					cout<<"Unknown action !"<<endl;
					err=true;
					break;
				}
			}
			Sleep(1500);
			system("cls");
		} while (err==true);
		// Write text
		HEADER();
		SetConsoleTextAttribute (hConsole, 0x0b);
		if (ini.code==true) cout<<"Write a text you want to code \n"<<endl;
		else cout<<"Write a coded string you want to decode \n"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0e);
		cin.clear();
		cin.ignore();
		getline(cin,ini.txt);
		ini.len=ini.txt.length();
		system("cls");
		// Bit time division number
		HEADER();
		SetConsoleTextAttribute (hConsole, 0x0a);
		cout<<"Found ";
		SetConsoleTextAttribute (hConsole, 0x0e);
		cout<<ini.len;
		SetConsoleTextAttribute (hConsole, 0x0a);
		cout<<" chars"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0b);
		cout<<"Type a bit time division number ";
		SetConsoleTextAttribute (hConsole, 0x0a);
		cout<<"[ Recommended ";
		SetConsoleTextAttribute (hConsole, 0x0e);
		if (ini.len<64) cout<<"1";
		if (ini.len>=64 && ini.len<128) cout<<"2";
		if (ini.len>=128 && ini.len<256) cout<<"4";
		if (ini.len>=256 && ini.len<512) cout<<"8";
		if (ini.len>=512 && ini.len<768) cout<<"16";
		if (ini.len>=768) cout<<"32";
		SetConsoleTextAttribute (hConsole, 0x0a);
		cout<<" ]"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0c);
		cout<<"below 1 - very very slow --> Not recommended. Only for experimental purposes"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0c);
		cout<<"1 - very slow --> 51 ms/char [-0.078 ms/char to 64]"<<endl;
		SetConsoleTextAttribute (hConsole, 0x06);
		cout<<"2 - slow --> approx. 43 ms/char [-0.011 ms/char to 256]"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0e);
		cout<<"4 - normal --> approx. 37 ms/char [-0.020 ms/char to 512]"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0a);
		cout<<"8 - fast --> approx. 35 ms/char [-0.010 ms/char to 768]"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0b);
		cout<<"16 - faster --> approx. 32 ms/char [-0.003 ms/char to 1024]"<<endl;
		SetConsoleTextAttribute (hConsole, 0x09);
		cout<<"32 - very fast --> approx. 28 ms/char"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0c);
		cout<<"Values over 32 are not recommended. They could have no effect on speed"<<endl;
		SetConsoleTextAttribute (hConsole, 0x06);
		cout<<"0 - premium only --> only iterator delay approx. 23 ms/char"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0a);
		cin>>ini.spd;																						// User types bit time division number
		if (ini.spd<0 || cin.fail()) {
			cin.clear();
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
			SetConsoleTextAttribute (hConsole, 0x0c);
			cout<<"Invalid number typed. Set automatically to 1."<<endl;
			ini.spd=1;
			Sleep(1500);
		}
		if (ini.spd==0) {
			SetConsoleTextAttribute (hConsole, 0x0c);
			cout<<"Premium authentication. Enter the password: ";
			SetConsoleTextAttribute (hConsole, 0x00);
			cin>>ini.pass0;
			if (ini.pass0=="iwanttogetAdm") ini.spd=0;
			else {
				SetConsoleTextAttribute (hConsole, 0x0c);
				cout<<"Invalid password. Setting to 1."<<endl;
				ini.spd=1;
				Sleep(1500);
			}
		}
		// Start action
		system("cls");
		clk.start = clock();
		if (ini.code==true) {
			for (j=0; j<ini.len; j++) {
				if (ini.txt[j]=='a' || ini.txt[j]=='A') x="4";
				if (ini.txt[j]=='b' || ini.txt[j]=='B') x="8";
				if (ini.txt[j]=='c' || ini.txt[j]=='C') x="(";
				if (ini.txt[j]=='d' || ini.txt[j]=='D') x="|)";
				if (ini.txt[j]=='e' || ini.txt[j]=='E') x="3";
				if (ini.txt[j]=='f' || ini.txt[j]=='F') x="|=";
				if (ini.txt[j]=='g' || ini.txt[j]=='G') x="6";
				if (ini.txt[j]=='h' || ini.txt[j]=='H') x="|-|";
				if (ini.txt[j]=='i' || ini.txt[j]=='I') x="1";
				if (ini.txt[j]=='j' || ini.txt[j]=='J') x="7^.";
				if (ini.txt[j]=='k' || ini.txt[j]=='K') x="/\\|";
				if (ini.txt[j]=='l' || ini.txt[j]=='L') x="7";
				if (ini.txt[j]=='m' || ini.txt[j]=='M') x="W";
				if (ini.txt[j]=='n' || ini.txt[j]=='N') x="Z";
				if (ini.txt[j]=='o' || ini.txt[j]=='O') x="0";
				if (ini.txt[j]=='p' || ini.txt[j]=='P') x="R";
				if (ini.txt[j]=='q' || ini.txt[j]=='Q') x="0,";
				if (ini.txt[j]=='r' || ini.txt[j]=='R') x="P";
				if (ini.txt[j]=='s' || ini.txt[j]=='S') x="5";
				if (ini.txt[j]=='t' || ini.txt[j]=='T') x="}";
				if (ini.txt[j]=='u' || ini.txt[j]=='U') x="V";
				if (ini.txt[j]=='v' || ini.txt[j]=='V') x=">";
				if (ini.txt[j]=='w' || ini.txt[j]=='W') x="M";
				if (ini.txt[j]=='x' || ini.txt[j]=='X') x="/\\";
				if (ini.txt[j]=='y' || ini.txt[j]=='Y') x=">~";
				if (ini.txt[j]=='z' || ini.txt[j]=='Z') x="N";
				if (ini.txt[j]=='0') x="[0";
				if (ini.txt[j]=='1') x="[1";
				if (ini.txt[j]=='2') x="[2";
				if (ini.txt[j]=='3') x="[3";
				if (ini.txt[j]=='4') x="[4";
				if (ini.txt[j]=='5') x="[5";
				if (ini.txt[j]=='6') x="[6";
				if (ini.txt[j]=='7') x="[7";
				if (ini.txt[j]=='8') x="[8";
				if (ini.txt[j]=='9') x="[9";
				if (ini.txt[j]==' ') x=" ";
				result=result+x;
			}
		}
		else {
			for (j=0; j<ini.len; j++) {
					k=0;
					if (ini.txt[j]=='|') {
						if (ini.txt[j+1]==')') {
							x="D";
							k++;
						}
						if (ini.txt[j+1]=='=') {
							x="F";
							k++;
						}
						if (ini.txt[j+1]=='-' && ini.txt[j+2]=='|') {
							x="H";
							k+=2;
						}
					}
					if (ini.txt[j]=='/') {
						if (ini.txt[j+1]=='\\' && ini.txt[j+2]=='|' && ini.txt[j+3]!=')') {
							x="K";
							k+=2;
						}
						else {
							x="X";
							k++;
						}
					}
					if (ini.txt[j]=='7') {
						if (ini.txt[j+1]=='^' && ini.txt[j+2]=='.') {
							x="J";
							k+=2;
						}
						else x="L";
					}
					if (ini.txt[j]=='>') {
						if (ini.txt[j+1]=='~') {
							x="Y";
							k++;
						}
						else x="V";
					}
					if (ini.txt[j]=='[') {
						if (ini.txt[j+1]=='0') x="0";
						if (ini.txt[j+1]=='1') x="1";
						if (ini.txt[j+1]=='2') x="2";
						if (ini.txt[j+1]=='3') x="3";
						if (ini.txt[j+1]=='4') x="4";
						if (ini.txt[j+1]=='5') x="5";
						if (ini.txt[j+1]=='6') x="6";
						if (ini.txt[j+1]=='7') x="7";
						if (ini.txt[j+1]=='8') x="8";
						if (ini.txt[j+1]=='9') x="9";
						k++;
					}
					if (ini.txt[j]=='4') x="A";
					if (ini.txt[j]=='8') x="B";
					if (ini.txt[j]=='(') x="C";
					if (ini.txt[j]=='3') x="E";
					if (ini.txt[j]=='6') x="G";
					if (ini.txt[j]=='1') x="I";
					if (ini.txt[j]=='w' || ini.txt[j]=='W') x="M";
					if (ini.txt[j]=='z' || ini.txt[j]=='Z') x="N";
					if (ini.txt[j]=='0') x="O";
					if (ini.txt[j]=='r' || ini.txt[j]=='R') x="P";
					if (ini.txt[j]=='p' || ini.txt[j]=='P') x="R";
					if (ini.txt[j]=='5') x="S";
					if (ini.txt[j]=='}') x="T";
					if (ini.txt[j]=='v' || ini.txt[j]=='V') x="U";
					if (ini.txt[j]=='m' || ini.txt[j]=='M') x="W";
					if (ini.txt[j]=='n' || ini.txt[j]=='N') x="Z";
					if (ini.txt[j]==' ') x=" ";
					result=result+x;
					if (k==1) j++;
					if (k==2) j+=2;
				}
		}
		j=0;
		// Display Bar
		for (bar.cnt=1; bar.cnt<=ini.len; bar.cnt++) {
			clk.timeElapsed2 = clock() - clk.start;
			if (ini.spd!=0) Sleep(bar.dly);
			system("cls");
			HEADER();
			ACK();
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<"{ ";
			SetConsoleTextAttribute (hConsole, 0x0a);
			cout<<"Get: ";
			SetConsoleTextAttribute (hConsole, 0x0f);
			cout<<ini.txt[j+i];
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<", ";
			SetConsoleTextAttribute (hConsole, 0x0a);
			cout<<"Pos: ";
			SetConsoleTextAttribute (hConsole, 0x0f);
			cout<<bar.cnt;
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<" / ";
			SetConsoleTextAttribute (hConsole, 0x0f);
			cout<<ini.len;
			bar.per=(bar.cnt/ini.len)*100;
			bar.pos=bar.per/1.33;
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<", ";
			SetConsoleTextAttribute (hConsole, 0x0a);
			cout<<"Dly: ";
			SetConsoleTextAttribute (hConsole, 0x0f);
			cout<<bar.dly;
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<", ";
			SetConsoleTextAttribute (hConsole, 0x0a);
			cout<<"Fill: ";
			SetConsoleTextAttribute (hConsole, 0x0f);
			cout<<bar.Ifill;
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<", ";
			SetConsoleTextAttribute (hConsole, 0x0a);
			cout<<"BPos: ";
			SetConsoleTextAttribute (hConsole, 0x0f);
			cout<<bar.pos;
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<" }"<<endl;
			if (bar.per<=50) {
				for (bar.Ifill=1; bar.Ifill<=bar.pos; bar.Ifill++) {
					SetConsoleTextAttribute (hConsole, 0xaa);
					cout<<"*";
				}
				for (bar.Ifill>bar.pos; bar.Ifill<40; bar.Ifill++) {
					SetConsoleTextAttribute (hConsole, 0x00);
					cout<<" ";
				}
				SetConsoleTextAttribute (hConsole, 0x0a);
				cout<<bar.per<<" %"<<endl;
			}
			else {
				for (bar.Ifill=1; bar.Ifill<=39; bar.Ifill++) {
					SetConsoleTextAttribute (hConsole, 0xaa);
					cout<<"*";
				}
				SetConsoleTextAttribute (hConsole, 0xa1);
				cout<<bar.per<<" %";
				for (bar.Ifill>39; bar.Ifill<=bar.pos; bar.Ifill++) {
					SetConsoleTextAttribute (hConsole, 0xaa);
					cout<<"*";
				}
				cout<<endl;
			}
			SetConsoleTextAttribute (hConsole, 0x00);
			bar.dly=(16.000/ini.spd);
			clk.timeElapsed3 = clock() - clk.start;
			clk.timeElapsed4 = (clk.timeElapsed3-clk.timeElapsed2)/CLOCKS_PER_MS;
			SetConsoleTextAttribute (hConsole, 0x0e);
			cout<<"Speed: ";
			if (bar.cnt==1) {
				SetConsoleTextAttribute (hConsole, 0x0c);
				cout<<"Counting ..."<<endl;
			}
			else {
				SetConsoleTextAttribute (hConsole, 0x0a);
				cout<<clk.timeElapsed4<<" ms/char"<<endl;
			}
			clk.msLeft=clk.timeElapsed4*(ini.len-bar.cnt);
			SetConsoleTextAttribute (hConsole, 0x0f);
			cout<<"Time left: ";
			if (bar.cnt==1) {
				SetConsoleTextAttribute (hConsole, 0x0c);
				cout<<"Counting ..."<<endl;
			}
			/*
			This thing decides how the time should be displayed
			For example it corrects the mistakes like this: 012:037.0984 --> It will be changed to: 12:37.984
			Or 9:2.6 --> It will be changed to: 09:02.006
			*/
			else {
				for (clk.msLeft; clk.msLeft>=1000; clk.msLeft-=1000) clk.secLeft++;
				for (clk.secLeft; clk.secLeft>=60; clk.secLeft-=60) clk.minLeft++;
				for (clk.minLeft; clk.minLeft>=60; clk.minLeft-=60) clk.hrsleft++;
				cout<<clk.hrsleft<<":";
				if (clk.minLeft<10) cout<<"0";
				cout<<clk.minLeft<<":";
				if (clk.secLeft<10) cout<<"0";
				cout<<clk.secLeft<<".";
				if (clk.msLeft<10) cout<<"00";
				if (clk.msLeft>=10 && clk.msLeft<100) cout<<"0";
				cout<<clk.msLeft<<endl;
				clk.msLeft=0;
				clk.secLeft=0;
				clk.minLeft=0;
				clk.hrsleft=0;
				// end of display mistake corrector
			}
			i++;
			clk.average+=clk.timeElapsed4;
		}
		system("cls");
		HEADER();
		SetConsoleTextAttribute (hConsole, 0x0d);
		clk.timeElapsed = clock() - clk.start;
		clk.msElapsed = clk.timeElapsed / CLOCKS_PER_MS;						
		for (clk.msElapsed; clk.msElapsed>=1000; clk.msElapsed-=1000) clk.secElapsed++;
		for (clk.secElapsed; clk.secElapsed>=60; clk.secElapsed-=60) clk.minElapsed++;
		cout<<"Done in: ";
		if (clk.minElapsed<10) cout<<"0";
		cout<<clk.minElapsed<<":";
		if (clk.secElapsed<10) cout<<"0";
		cout<<clk.secElapsed<<".";
		if (clk.msElapsed<10) cout<<"00";
		if (clk.msElapsed>=10 && clk.msElapsed<100) cout<<"0";
		cout<<clk.msElapsed<<endl;
		clk.avg=(clk.average/(ini.len-1));																		// Average speed ms/char as sum / total_chars
		SetConsoleTextAttribute (hConsole, 0x0b);
		cout<<"Average speed: "<<clk.avg<<" ms/char"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0a);
		cout<<"Source string: ";
		SetConsoleTextAttribute (hConsole, 0x0e);
		cout<<ini.txt<<endl;
		SetConsoleTextAttribute (hConsole, 0x0a);
		if (ini.code==true) cout<<"Coded string: ";
		else cout<<"Decoded string: ";
		SetConsoleTextAttribute (hConsole, 0x0e);
		cout<<result<<endl;
		SetConsoleTextAttribute (hConsole, 0x0c);
		cout<<"\n\nDo You want to exit [y/n] ?"<<endl;
		SetConsoleTextAttribute (hConsole, 0x0e);
		cin>>ex;
		switch (ex) {
			case 'y': {
				exit=true;
				break;
			}
			default: {
				exit=false;
				break;
			}
		}
	}
	// END //
	cin.ignore();
	cin.get();
	return 0; 
}
