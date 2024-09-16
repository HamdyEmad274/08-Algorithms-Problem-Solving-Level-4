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
short GetYear() {
	cout << "Enter year: ";
	short year;
	cin >> year;
	return year;
}
short DaysInYear(short year) {
	return isLeapYear(year) ? 366 : 365;
}
short HoursInYear(short year) {
	return DaysInYear(year) * 24;
}
int MinutesInYear(short year) {
	return HoursInYear(year) * 60;
}
int SecondsInYear(short year) {
	return MinutesInYear(year) * 60;
}
int main()
{
	short year = GetYear();
	cout << "Year: " << year << endl;
	cout << "Number of Days in Year: {" << year << "} = " << DaysInYear(year) << endl;
	cout << "Hours: " << HoursInYear(year) << endl;
	cout << "Minutes: " << MinutesInYear(year) << endl;
	cout << "Seconds: " << SecondsInYear(year) << endl;
}
