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

	while (1) {
		ifstream file("./MasterAccounts.dat");
		int width = 41;

		getinitcolor(info_color);
		getxy(info_xy);
		setcolor(15, 9);
		print_hyphen(width, "T");
		for (int i = 0; i < 7; i++) {
			cout << "|"; print_blank(width - 2); cout << "|";
			cout << endl;
		}
		print_hyphen(width, "T");

		if (!file) {
			gotoxy(1, 1); cout << "저장된 계정이 없습니다.";
			gotoxy(1, 2); cout << "sign up을 먼저 진행하세요.";
			gotoxy(1, 4); cout << "enter를 누르면 프로그램을 종료합니다.";
			resetcolor(info_color); gotoxy(0, 9);
			check_enter();
			exit(1);
		}
		else {

			gotoxy(1, 1); cout << "ID: "; cin >> id;
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
						system("cls");
						gotoxy(0, 9); cout << "Password error!";
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

}

void signup() {
	string id;
	string pwd;
	string filepath = "./MasterAccounts.dat";
	int width = 41;

	getinitcolor(info_color);
	setcolor(15, 9);
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
		gotoxy(1, 3); cout << "디렉토리 생성에 실패하였습니다.";
		gotoxy(1, 4); cout << "mainmenu로 돌아가려면 enter를 누르세요.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}

	ofstream file(filepath, std::ios::app);

	file << id << " " << pwd << endl;

	gotoxy(1, 3); cout << "디렉토리 생성에 성공하였습니다.";
	gotoxy(1, 4); cout << "mainmenu로 돌아가려면 enter를 누르세요.";
	resetcolor(info_color); resetxy(info_xy);
	check_enter();
	return;
}

void mainmenu(string user) {
	int check, width = 49;
	getinitcolor(info_color);
	while (1)
	{
		system("cls");
		setcolor(15, 9);
		print_hyphen(width, "T");
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|             1. 계정/비밀번호 보기             |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|             2. 계정/비밀번호 추가             |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|             3. 계정/비밀번호 변경             |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|             4. 비밀번호 추천                  |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|             5. 로그 아웃                      |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		print_hyphen(width, "T");
		resetcolor(info_color);
		check = _getch();
		switch (check)
		{
		case '1':
			system("cls");
			viewaccounts(user);
			break;
		case '2':
			system("cls");
			addaccount(user);
			break;
		case '3':
			system("cls");
			changeaccount(user);
			break;
		case '4':
			system("cls");
			recommendpwd();
			break;
		case '5':
			return;
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
	int max_length = 41, count = 0;

	getinitcolor(info_color);
	setcolor(15, 9);

	if (!file) {
		print_hyphen(max_length, "T");
		for (int i = 0; i < 4; i++) {
			cout << "|"; print_blank(max_length - 2); cout << "|";
			cout << endl;
		}
		print_hyphen(max_length, "T");
		getxy(info_xy);
		gotoxy(1, 1); cout << "파일이 없습니다.";
		gotoxy(1, 2); cout << "먼저 계정/비밀번호를 추가해주세요.";
		gotoxy(1, 4); cout << "mainmenu로 돌아가려면 enter를 누르세요.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}

	while (getline(file, text)) {
		vec.push_back(text);
		if (max_length < text.length())
			max_length = (int)text.length();

		for (size_t j = 0; j < vec.size() - 1; j++) {
			for (size_t i = (vec.size() - 1); i > j; i--) {
				if (vec[i] < vec[i - 1]) {
					string temp = vec[i];
					vec[i] = vec[i - 1];
					vec[i - 1] = temp;
				}
			}
		}
		count++;
	}

	int width = max_length + 2;
	print_hyphen(width, "T");
	for (int i = 0; i < count + 1; i++) {
		cout << "|"; print_blank(width - 2); cout << "|";
		cout << endl;
	}
	print_hyphen(width, "T");
	getxy(info_xy);
	int num = 1;
	for (iter = vec.begin(); iter != vec.end(); iter++) {
		gotoxy(1, num);
		cout << (*iter) << endl;
		num++;
	}

	gotoxy(1, num); cout << "mainmenu로 돌아가려면 enter를 누르세요.";
	resetcolor(info_color); resetxy(info_xy);
	check_enter();
}

void addaccount(string user) {

	string info;
	string filepath = "./" + user + "/Accounts.txt";
	int width = 70;
	getinitcolor(info_color);
	setcolor(15, 9);
	print_hyphen(width, "T");
	for (int i = 0; i < 4; i++) {
		cout << "|"; print_blank(width - 2); cout << "|";
		cout << endl;
	}
	print_hyphen(width, "T");
	getxy(info_xy);
	gotoxy(1, 1); cout << "계정 정보를 입력하세요.";
	gotoxy(1, 2);
	cout << "(사이트명) (계정명) (비밀번호) (입력 날짜) (메모)";

	gotoxy(1, 4);
	getline(cin, info);

	ofstream file(filepath, std::ios::app);

	file << info << endl;
	resetcolor(info_color);
}

void changeaccount(string user) {
	string filepath = "./" + user + "/Accounts.txt";
	ifstream file(filepath);
	string text;


	vector<string> vec;
	vector<string>::iterator iter;
	int max_length = 41, count = 0;

	getinitcolor(info_color);
	setcolor(15, 9);

	if (!file) {
		print_hyphen(max_length, "T");
		for (int i = 0; i < 4; i++) {
			cout << "|"; print_blank(max_length - 2); cout << "|";
			cout << endl;
		}
		print_hyphen(max_length, "T");
		getxy(info_xy);
		gotoxy(1, 1); cout << "파일이 없습니다.";
		gotoxy(1, 2); cout << "먼저 계정/비밀번호를 추가해주세요.";
		gotoxy(1, 4); cout << "mainmenu로 돌아가려면 enter를 누르세요.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}

	while (getline(file, text)) {
		vec.push_back(text);
		if (max_length < text.length())
			max_length = (int)text.length();

		for (size_t j = 0; j < vec.size() - 1; j++) {
			for (size_t i = (vec.size() - 1); i > j; i--) {
				if (vec[i] < vec[i - 1]) {
					string temp = vec[i];
					vec[i] = vec[i - 1];
					vec[i - 1] = temp;
				}
			}
		}
		count++;
	}

	int width = max_length + 14 + 2;
	print_hyphen(width, "T");
	for (int i = 0; i < count + 12; i++) {
		cout << "|"; print_blank(width - 2); cout << "|";
		cout << endl;
	}
	print_hyphen(width, "T");
	getxy(info_xy);
	gotoxy(1, 1); cout << "변경할 계정을 선택해주세요";
	int i = 1;
	string temp;
	for (iter = vec.begin(); iter != vec.end(); iter++) {
		gotoxy(1, i + 1);
		cout << i << ": " << (*iter) << endl;
		i++;
	}
	gotoxy(1, i + 1); cout << "선택: ";
	size_t choice;
	cin >> choice;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		gotoxy(1, i + 3); cout << "잘못된 입력입니다.";
		gotoxy(1, i + 4);
		cout << "mainmenu로 돌아가려면 enter를 누르세요.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}
	else if (choice < 1 || choice > count) {
		cin.ignore(256, '\n');
		gotoxy(1, i + 3); cout << "입력된 숫자에 해당하는 계정이 없습니다.";
		gotoxy(1, i + 4);
		cout << "mainmenu로 돌아가려면 enter를 누르세요.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}
	cin.ignore(256, '\n');

	gotoxy(1, i + 3); cout << "변경 내용을 입력해주세요";
	gotoxy(1, i + 4);
	cout << "(사이트명) (계정명) (비밀번호) (입력 날짜) (메모)";

	string info;

	gotoxy(1, i + 5); getline(cin, info);

	gotoxy(1, i + 7); cout << "변경할 내용 : " << vec[choice - 1];
	gotoxy(1, i + 8); cout << "변경된 내용 : " << info;

	vec.erase(vec.begin() + choice - 1);
	vec.push_back(info);

	string filepath1 = "./" + user + "/newdata.txt";
	ofstream newdata(filepath1);
	for (size_t i = 0; i < vec.size(); i++) {
		newdata << vec[i] << endl;
	}
	newdata.close();
	file.close();

	const char* c = filepath.c_str();
	const char* c1 = filepath1.c_str();


	if (remove(c) == -1) {
		gotoxy(1, i + 9); cout << "remove error";
	}
	int result = rename(c1, c);
	if (result == -1) {
		gotoxy(1, i + 10); cout << "rename error";
	}

	gotoxy(1, i + 11);
	cout << "mainmenu로 돌아가려면 enter를 누르세요.";
	resetcolor(info_color); resetxy(info_xy);
	check_enter();
}

//character set
static const char alphnum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;

char RandomGen()
{
	return alphnum[rand() % strLen];
}

void recommendpwd() {
	int plength, c = 0, s = 0, width = 54;
	srand((unsigned int)time(0));
	getinitcolor(info_color);
	setcolor(15, 9);
	print_hyphen(width, "T");
	for (int i = 0; i < 8; i++) {
		cout << "|"; print_blank(width - 2); cout << "|";
		cout << endl;
	}
	print_hyphen(width, "T");
	getxy(info_xy);
	gotoxy(2, 2); cout << "enter password length(1~30) = ";
	cin >> plength;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		gotoxy(2, 3); cout << "잘못된 입력입니다.";
		gotoxy(2, 5);
		cout << "mainmenu로 돌아가려면 enter를 누르세요.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}
	else if (plength < 1 || plength > 30) {
		cin.ignore(256, '\n');
		gotoxy(2, 3); cout << "잘못된 범위입니다.";
		gotoxy(2, 4); cout << "1~30 사이의 정수를 입력하세요.";
		gotoxy(2, 6);
		cout << "mainmenu로 돌아가려면 enter를 누르세요.";
		resetcolor(info_color); resetxy(info_xy);
		check_enter();
		return;
	}
	cin.ignore(256, '\n');
	gotoxy(2, 3);
	cout << "generating a random password with " << plength << " characters";
	gotoxy(2, 5); cout << "generated password: ";

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

	cout << passw;

	gotoxy(2, 7);
	cout << "mainmenu로 돌아가려면 enter를 누르세요.";
	resetcolor(info_color); resetxy(info_xy);
	check_enter();
}




int main(void) {

	string user;
	int check, width = 41;

	getinitcolor(info_color);
	while (1) {
		system("cls");
		setcolor(15, 9);
		print_hyphen(width, "T");
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|              1. sign in               |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|              2. sign up               |" << endl;
		cout << "|"; print_blank(width - 2); cout << "|" << endl;
		cout << "|              3. exit                  |" << endl;
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