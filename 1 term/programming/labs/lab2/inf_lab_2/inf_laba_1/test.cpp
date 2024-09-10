#include <iostream>
#include <locale.h>
using namespace std;

int main2() {
	int hours, minutes, flag, i1, i2;
	setlocale(LC_ALL, "Rus");

	for (i1 = -1; i1 <= 24; i1++) {
		for (i2 = -1; i2 <= 61; i2++) {
			hours = i1;
			minutes = i2;
			cout << hours << " " << minutes;
		
			if ((hours >= 24 && minutes > 0) || minutes > 59 || hours < 0 || minutes < 0) { cout << " – введены недопустимые данные" << endl; continue;}
			if (hours == 12 && minutes == 0) { cout << " - полдень" << endl; continue;} // 12 00
			if ((hours == 0 || hours ==24) && minutes == 0) { cout << " - полночь" << endl; continue;} // 00 00

			if (hours < 5) { flag = 0; } // 0-4 ночь
			else if (hours < 12) { flag = 1; } //5-11 утро
			else if (hours < 18) { flag = 2; } //12-17 день
			else { flag = 3; } //18-23 вечер

			if (hours > 12) { hours = hours - 12; }

			if (hours == 1) { cout << " - 1 час"; } // 1 00
			else if (hours < 5) { cout << " - " << hours << " часа"; } // 2 00 - 4 00
			else { cout << " - " << hours << " часов"; } // 00 00 and 5 00 - 12 00

			if (minutes >= 5 && minutes < 20) { cout << " " << minutes << " минут"; } // 6-20
			else if (minutes % 10 == 1) { cout << " " << minutes << " минута"; } //1
			else if (minutes % 10 >= 2 && minutes % 10 <= 4) { cout << " " << minutes << " минуты"; }//2-5
			else if (minutes != 0) { cout << " " << minutes << " минут"; }//6-10

			if (flag == 0) { cout << " ночи"; } // 0-4
			else if (flag == 1) { cout << " утра"; } //5-11
			else if (flag == 2) { cout << " дня"; } //12-17
			else { cout << " вечера"; } //18-23

			if (minutes == 0) { cout << " ровно"; } //00
			cout << endl;
		}
	}
	return 0;
}