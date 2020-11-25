#include "interface.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <list>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <direct.h>
#include <vector>


using namespace std;
/*
*
* 프로그램 화면 구성 메소드 함수
*
*/



void mainmenu(string user);		// 마스터 계정 로그인 후, 메인 메뉴
string signin();			// 마스터 계정 로그인 
void signup();			// 마스터 계정 회원가입
void viewaccounts(string user);	// 등록한 계정,비밀번호 보기
void addaccount(string user);		// 계정,비밀번호 추가
void changeaccount(string user);	// 계정,비밀번호 변경
void recommendpwd();	// 비밀번호 추천 기능 구현

CONSOLE_SCREEN_BUFFER_INFO info_color, info_xy;



string signin() {
	string id;
	string pwd;
	string text;
	string stringBuffer;

	ifstream file("./MasterAccounts.dat");
	int width = 41;

	getinitcolor(info_color);
	getxy(info_xy);
	setcolor(7, 0);
	print_hyphen(width, "T");
	for (int i = 0; i < 7; i++) {
		cout << "|"; print_blank(width - 2); cout << "|";
		cout << endl;
	}
	print_hyphen(width, "T");
	
	if (!file) {
		gotoxy(1, 1); cout << "계정이 존재하지 않습니다." << endl;
		gotoxy(1, 4); cout << "enter를 누르면 mainmenu로 돌아갑니다.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
	}
	else {

		gotoxy(1, 1); cout << "ID: ";	cin >> id;
		cin.ignore(256, '\n');
		gotoxy(1, 2); cout << "PASSWORD: "; cin >> pwd;
		cin.ignore(256, '\n');

		while (getline(file, text)) {

			istringstream ss(text);

			getline(ss, stringBuffer, ' ');	// stringBuffer에 id 저장
			if (stringBuffer == id) {
				getline(ss, stringBuffer, ' ');
				if (stringBuffer == pwd) {
					resetcolor(info_color);
					system("cls");
					return id;
				}
				else {
					resetcolor(info_color);
					resetxy(info_xy);
					system("cls");
					gotoxy(0, 9); cout << "Password error!" << endl;
					resetxy(info_xy);
					return signin();
					
				}
			}
		}
		if (file.eof()) {
			resetcolor(info_color);
			system("cls");
			gotoxy(0, 9); cout << "do not exist ID" << endl;
			resetxy(info_xy);
			return signin();
			
		}
	}

}

void signup() {
	string id;
	string pwd;
	string filepath = "./MasterAccounts.dat";
	int width = 41;

	getinitcolor(info_color);
	setcolor(7, 0);
	print_hyphen(width, "T");
	for (int i = 0; i < 7; i++) {
		cout << "|"; print_blank(width - 2); cout << "|";
		cout << endl;
	}
	print_hyphen(width, "T");

	getxy(info_xy);
	gotoxy(1, 1); cout << "input ID: ";	cin >> id;
	cin.ignore(256, '\n');
	gotoxy(1, 2); cout << "input Password: "; cin >> pwd;
	cin.ignore(256, '\n');

	string dir = "./" + id;

	if (_mkdir(dir.c_str()) == -1) {
		gotoxy(1, 3); cout << "디렉토리 생성에 실패하였습니다." << endl;
		gotoxy(1, 4); cout << "enter를 누르면 mainmenu로 돌아갑니다.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}

	ofstream file(filepath, std::ios::app);

	file << id << " " << pwd << endl;

	gotoxy(1, 3); cout << "디렉토리 생성에 성공하였습니다." << endl;
	gotoxy(1, 4); cout << "enter를 누르면 mainmenu로 돌아갑니다.";
	resetcolor(info_color); resetxy(info_xy);
	check_enter();
	return;
}

void mainmenu(string user) {
	while (1)
	{
		system("cls");

		int check;

		cout << "-------------------------------------------------" << endl << endl;
		cout << "|		1. 계정/비밀번호 보기		|" << endl << endl;
		cout << "|		2. 계정/비밀번호 추가		|" << endl << endl;
		cout << "|		3. 계정/비밀번호 변경		|" << endl << endl;
		cout << "|		4. 비밀번호 추천		|" << endl << endl;
		cout << "-------------------------------------------------" << endl;
		cin >> check;
		switch (check)
		{
		case 1:
			system("cls");
			viewaccounts(user);
			break;
		case 2:
			system("cls");
			addaccount(user);
			break;
		case 3:
			system("cls");
			changeaccount(user);
			break;
		case 4:
			system("cls");
			recommendpwd();
			break;
		default:
			break;
		}
	}
}

void viewaccounts(string user) {

	string filepath = "./" + user + "/Accounts.txt";
	ifstream file(filepath);
	string text;
	vector<string> vec;
	vector<string>::iterator iter;

	while (getline(file, text)) {
		vec.push_back(text);

		for (int j = 0; j < vec.size()-1; j++) {
			for (int i = (vec.size() - 1); i > j; i--) {
				if (vec[i] < vec[i - 1]) {
					string temp = vec[i];
					vec[i] = vec[i - 1];
					vec[i - 1] = temp;
				}
			}
		}
	}

	for (iter = vec.begin(); iter != vec.end(); iter++) {
		cout << (*iter) << endl;
	}

	char ch;
	cout << "mainmenu로 돌아가려면 문자를 입력하고 enter를 누르세요." << endl;
	cin >> ch;
}

void addaccount(string user) {

	string info;
	string filepath = "./" + user + "/Accounts.txt";

	cout << "계정 정보를 입력하세요." << endl;
	cout << "(사이트명) (계정명) (비밀번호) (입력 날짜) (메모)" << endl;

	getline(cin, info);
	getline(cin, info);

	ofstream file(filepath, std::ios::app);

	file << info << endl;

}

void changeaccount(string user) {
	string filepath = "./" + user + "/Accounts.txt";
	ifstream file(filepath);
	string text;


	vector<string> vec;
	vector<string>::iterator iter;

	while (getline(file, text)) {
		vec.push_back(text);

		for (int j = 0; j < vec.size() - 1; j++) {
			for (int i = (vec.size() - 1); i > j; i--) {
				if (vec[i] < vec[i - 1]) {
					string temp = vec[i];
					vec[i] = vec[i - 1];
					vec[i - 1] = temp;
				}
			}
		}
	}
	cout << "변경할 계정을 선택해주세요" << endl;
	int i = 1;
	string temp;
	for (iter = vec.begin(); iter != vec.end(); iter++) {
		cout << i << ": " << (*iter) << endl;
		i++;
	}
	cout << "선택:";
	int choice;
	cin >> choice;

	cout << "변경 내용을 입력해주세요" << endl;
	cout << "(사이트명) (계정명) (비밀번호) (입력 날짜) (메모)" << endl;

	string info;

	getline(cin, info);
	getline(cin, info);
	cout << endl;

	cout << "변경할 계정 : " << vec[choice - 1] << " --> ";
	cout << "변경된 내용 : " << info << endl;

	vec.erase(vec.begin() + choice - 1);
	vec.push_back(info);

	string filepath1 = "./" + user + "/newdata.txt";
	ofstream newdata(filepath1);
	for (int i = 0; i < vec.size(); i++) {
		newdata << vec[i] << endl;
	}
	newdata.close();
	file.close();
	/*char* c = new char[filepath.size() + 1];
	copy(filepath.begin(), filepath.end(), c);
	c[filepath.size()] = '\0';
	char* c1 = new char[filepath1.size() + 1];
	copy(filepath1.begin(), filepath1.end(), c1);
	c1[filepath1.size()] = '\0';*/

	/*vector<char> vc(filepath.begin(), filepath.end());
	vc.push_back('\0');
	char* c = &*vc.begin();
	vector<char> vc1(filepath1.begin(), filepath1.end());
	vc.push_back('\0');
	char* c1 = &*vc1.begin();*/

	const char* c = filepath.c_str();
	const char* c1 = filepath1.c_str();


	if (remove(c) == -1) {
		cout << "remove error" << endl;
	}
	int result = rename(c1, c);
	if (result == -1)
		cout << "rename error" << endl;


	char ch;
	cout << "mainmenu로 돌아가려면 문자를 입력하고 enter를 누르세요." << endl;
	cin >> ch;
}

//character set
static const char alphnum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;

char RandomGen()
{
	return alphnum[rand() % strLen];
}

void recommendpwd() {
	
		int plength, c = 0, s = 0;
		srand((unsigned int)time(0));
		cout << "enter password length = ";
		cin >> plength;
		cout << "generating a random password with " << plength << " characters" << endl;
		cout << "generated password: ";

	loopGen:
		char C;
		string passw;
		for (int z = 0; z < plength; z++)
		{
			C = RandomGen();
			passw += C;
			if (isdigit(C))
			{
				c++;
			}
			//special character
			if (C == '!' || C == '@' || C == '$' || C == '%' || C == '^' || C == '&' || C == '*' || C == '#')
			{
				s++;
			}
		}
		if (plength > 2 && (s == 0 || c == 0))
		{
			goto loopGen;
		}

		cout << passw<<endl;
	

	char ch;
	cout << "mainmenu로 돌아가려면 문자를 입력하고 enter를 누르세요." << endl;
	cin >> ch;

	system("cls");
}




int main(void) {

	string user;
	int check, width = 41;

	getinitcolor(info_color);
	while (1) {
		system("cls");
		setcolor(7, 0);
		print_hyphen(width, "T");
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|               1. sign in              |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|               2. Sign up              |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|               3. exit                 |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		print_hyphen(width, "T");
		resetcolor(info_color);
		check = _getch();
		switch (check)
		{
		case '1':
			system("cls");
			user = signin();
			mainmenu(user);
			break;
		case '2':
			system("cls");
			signup();
			break;
		case '3':
			exit(1);
		default:
			continue;
		}
	}
	return 0;
	
}