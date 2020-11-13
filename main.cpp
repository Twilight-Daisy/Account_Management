#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;
/*
*
* 프로그램 화면 구성 메소드 함수
*
*/
void firstscreen();
void signin();
void signup();
void viewaccounts();
void addaccount();
void changeaccount();
void recommendpwd();



// 처음 실행 시 나타나는 화면
void firstscreen() {
	int check;

	cout << "1. Sign in" << endl << endl;
	cout << "2. Sign up" << endl;
	cin >> check;
	switch (check)
	{
	case 1:
		system("cls");
		signin();
		break;
	case 2:
		system("cls");
		signup();
		break;
	default:
		break;
	}
}

void signin() {
	string id;
	string pwd;
	string text;
	string stringBuffer;


	ifstream file("./MasterAccounts.dat");
	
	if (!file) {
		cout << "계정이 존재하지 않습니다." << endl;
	}
	else {

		cout << "ID: ";
		cin >> id;
		cout << "PASSWORD: ";
		cin >> pwd;

		while (getline(file, text)) {

			istringstream ss(text);

			getline(ss, stringBuffer, ' ');	// stringBuffer에 id 저장
			if (stringBuffer == id) {
				getline(ss, stringBuffer, ' ');
				if (stringBuffer == pwd) {
					// main화면으로 넘어감.
				}
				else {
					cout << "Password error!" << endl;
					system("cls");
					signin();
				}
			}
		}
		if (file.eof()) {
			cout << "do not exist ID" << endl;
			system("cls");
			signin();
		}
	}

}

void signup() {
	string id;
	string pwd;
	string filepath = "./MasterAccounts.dat";

	cout << "input ID: " << endl;
	cin >> id;
	cout << "input Password" << endl;
	cin >> pwd;

	ofstream file(filepath, std::ios::app);

	file << id << " " << pwd << endl;


}



int main(void) {
	firstscreen();
	return 0;
}

