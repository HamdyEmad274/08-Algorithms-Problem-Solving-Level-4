#include <iostream>
using namespace std;

struct sDate {
	int day;
	int month;
	int year;
};
sDate GetDate(string message) {
	sDate date;
	cout << message;
	cin >> date.day >> date.month >> date.year;
	return date;
}
bool IsLeapYear(int year) {
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return true;
	return false;
}
bool IsValidDate(sDate vacStart, sDate vacEnd) {
	if (vacEnd.year < vacStart.year)
		return false;
	if (vacEnd.year == vacStart.year && vacEnd.month < vacStart.month)
		return false;
	if (vacEnd.year == vacStart.year && vacEnd.month == vacStart.month && vacEnd.day < vacStart.day)
		return false;
	return true;
}
short DayOfTheWeek(sDate date) {
	int q = date.day;
	int m = date.month;
	int y = date.year;

	if (m < 3) {
		m += 12;
		y--;
	}

	int k = (q + 13 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
	return k;
}
short DaysBetweenDates(sDate vacStart, sDate vacEnd) {
	short daysInMonths[13] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	short totalDays = 0;

	while (vacStart.year != vacEnd.year || vacStart.month != vacEnd.month || vacStart.day != vacEnd.day) {
		if (IsLeapYear(vacStart.year))
			daysInMonths[2] = 29;
		else
			daysInMonths[2] = 28;

		vacStart.day++;
		if (DayOfTheWeek(vacStart) != 6 && DayOfTheWeek(vacStart) != 5)
		{
			totalDays++;
		}
		if (vacStart.day > daysInMonths[vacStart.month]) {
			vacStart.day = 1;
			vacStart.month++;
			if (vacStart.month > 12) {
				vacStart.month = 1;
				vacStart.year++;
			}
		}
	}
	return totalDays;
}
int main()
{
	cout << "Hello and Welcome To The Vacation Days Calculator" << endl;
	sDate vacStart = GetDate("Enter The Vacation Start Date (DD MM YYYY) : ");
	sDate vacEnd = GetDate("Enter The Vacation End Date (DD MM YYYY) : ");
	if (IsValidDate(vacStart, vacEnd)) {
		cout << "Vacation From " << vacStart.day << "/" << vacStart.month << "/" << vacStart.year << endl;
		cout << "Vacation To " << vacEnd.day << "/" << vacEnd.month << "/" << vacEnd.year << endl << endl;
		cout << "The Vacation Days Are : " << DaysBetweenDates(vacStart, vacEnd) << endl;
	}
}