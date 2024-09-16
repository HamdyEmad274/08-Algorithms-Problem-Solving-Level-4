#include <iostream>
using namespace std;
int DayInYear(int day, int month, int year) {
	int a = (14 - month) / 12;
	int m = month + 12 * a - 2;
	int y = year - a;
	int d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
	return d;
}
int ReadInt(string message) {
	int number;
	cout << message;
	cin >> number;
	return number;
}
string DayName(int day) {
	string dayName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	return dayName[day];
}
int main()
{
	int day = ReadInt("Enter day: ");
	int month = ReadInt("Enter month: ");
	int year = ReadInt("Enter year: ");
	int dayInYear = DayInYear(day, month, year);
	cout << "Date       :"<< day << "/" << month << "/" << year << endl;
	cout << "Day Order  :"<< dayInYear << endl;
	cout << "Day Name   :"<< DayName(dayInYear) << endl;
}
