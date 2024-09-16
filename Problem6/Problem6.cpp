#include <iostream>
#include <string>
using namespace std;
bool isLeapYear(short year) {
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return true;
	}
	return false;
}
short GetNumber(string message) {
	cout << message;
	short Number;
	cin >> Number;
	return Number;
}
short DaysInMonth(short year, short month) {
	if (month < 1 || month > 12)
	{
		return 0;
	}
	short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return NumberOfDays[month - 1] + (isLeapYear(year) && month == 2 ? 1 : 0);
}
short HoursInMonth(short year, short month) {
	return DaysInMonth(year, month) * 24;
}
int MinutesInMonth(short year, short month) {
	return HoursInMonth(year, month) * 60;
}
int SecondsInMonth(short year, short month) {
	return MinutesInMonth(year, month) * 60;
}
int main()
{
	short year = GetNumber("Enter year: ");
	short month = GetNumber("Enter month: ");
	cout << "There are " << DaysInMonth(year, month) << " days in this month." << endl;
	cout << "There are " << HoursInMonth(year, month) << " hours in this month." << endl;
	cout << "There are " << MinutesInMonth(year, month) << " minutes in this month." << endl;
	cout << "There are " << SecondsInMonth(year, month) << " seconds in this month." << endl;
}
