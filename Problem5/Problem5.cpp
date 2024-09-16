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
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		return 31;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return 30;
	}
	else if (month == 2)
	{
		return isLeapYear(year) ? 29 : 28;
	}
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
