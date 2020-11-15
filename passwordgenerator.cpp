#include<iostream>
#include<cstdlib> 
#include<ctime> 
#include <string>
#include <Windows.h>


using namespace std;
//character set
static const char alphnum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int strLen = sizeof(alphnum) - 1;

void toClipboard(HWND hwnd, const string& s);

char RandomGen()
{
	return alphnum[rand() % strLen];
}

int main()
{
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

	cout << passw;
	
	return 0;
}

