#include <iostream>
#include <locale.h>
using namespace std;

int main() {
	int hours, minutes, flag;
	cin >> hours >> minutes;
	setlocale(LC_ALL, "Rus");

	if ((hours >= 24 && minutes > 0) || minutes > 59 || hours < 0 || minutes < 0) { cout << " � ������� ������������ ������"; exit(0); }
	if (hours == 12 && minutes == 0) { cout << " - �������"; exit(0); } // 12 00
	if ((hours == 0 || hours == 24) && minutes == 0) { cout << " - �������"; exit(0); } // 00 00

	if (hours < 5) { flag=0; } // 0-4 ����
	else if (hours < 12) { flag = 1; } //5-11 ����
	else if (hours < 18) { flag = 2; } //12-17 ����
	else { flag = 3; } //18-23 �����

	if (hours > 12) { hours = hours - 12; }

	if (hours == 1) { cout << " - 1 ���"; } // 1 00
	else if (hours < 5) { cout << " - " << hours << " ����"; } // 2 00 - 4 00
	else { cout << " - " << hours << " �����"; } // 00 00 and 5 00 - 12 00

	if (minutes >= 5 && minutes < 20) { cout << " " << minutes << " �����"; } // 6-20
	else if (minutes % 10 == 1) { cout << " " << minutes << " ������"; } //1
	else if (minutes % 10 >= 2 && minutes % 10 <= 4) { cout << " " << minutes << " ������"; }//2-5
	else if (minutes != 0) { cout << " " << minutes << " �����"; }//6-10

	if (flag == 0) { cout << " ����"; } // 0-4
	else if (flag == 1) { cout << " ����"; } //5-11
	else if (flag == 2) { cout << " ���"; } //12-17
	else { cout << " ������"; } //18-23

	if (minutes == 0) { cout << " �����"; } //00
	return 0;
}