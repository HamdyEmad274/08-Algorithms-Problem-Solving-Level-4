#include <iostream>
#include <iomanip>
using namespace std;
int DayInYear(int day, int month, int year) {
	int a = (14 - month) / 12;
	int m = month + 12 * a - 2;
	int y = year - a;
	int d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
	return d;
}
bool isLeapYear(short year) {
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return true;
	}
	return false;
}
short DaysInMonth(short year, short month) {
	if (month < 1 || month > 12)
	{
		return 0;
	}
	short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return NumberOfDays[month - 1] + (isLeapYear(year) && month == 2 ? 1 : 0);
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
string MonthName(int month) {
	string monthName[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return monthName[month - 1];
}
void PrintMonthCalendar(int month, int year) {
	cout << "\n    ______________" << MonthName(month) << "______________\n";
	cout << "    Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";
	int day = DayInYear(1, month, year);
	for (int i = 0; i < day; i++) {
		cout << "     ";
	}
	for (short i = 1; i <= DaysInMonth(year, month); i++)
	{
		if (day == 7) {
			day = 0;
			cout << "\n    ";
		}
		if (i == 1)
		{
			cout << "    ";
		}
		cout << setw(2) << i << "   ";
		day++;
	}


}
void PrintYearCalendar(int year) {
	for (int i = 1; i <= 12; i++)
	{
		PrintMonthCalendar(i, year);
		cout << "\n     ________________________________\n";
	}
}
int main()
{
	int year = ReadInt("Enter a year: ");
	cout << "Calendar for " << year << ":\n\n";
	PrintYearCalendar(year);
	system("pause>bool");
	return 0;
}
