//Date 1 == Date 2 ??
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
bool CheckDay(short year, short month, short day) {
	if (isLeapYear(year))
	{
		if (month == 2)
		{
			if (day > 29)
			{
				cout << "Day is invalid\n";
				return false;
			}
		}
	}
	else if (isLeapYear(year) == false)
	{
		if (month == 2)
		{
			if (day > 28)
			{
				cout << "Day is invalid\n";
				return false;
			}
		}
	}
	else
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day > 31)
			{
				cout << "Day is invalid\n";
				return false;
			}
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30)
			{
				cout << "Day is invalid\n";
				return false;
			}
		}
	}
	return true;
}
bool CheckMonth(short year, short month) {
	if (month > 12 || month < 1)
	{
		cout << "Month is invalid\n";
		return false;
	}
	return true;
}
short NumberOfTheDayInYear(short year, short month, short day)
{
	if (CheckDay(year, month, day) && CheckMonth(year, month))
	{
		short total = 0;
		for (short i = 1; i <= month - 1; i++)
		{
			total += DaysInMonth(year, i);
		}
		total += day;
		return total;
	}
	else
		return -1;
}
struct sDate {
	short day;
	short month;
	short year;
};
sDate ReadDate() {
	sDate date;
	date.day = GetNumber("Enter The Day : ");
	date.month = GetNumber("Enter The Month : ");
	date.year = GetNumber("Enter The Year : ");
	return date;
}
bool IsLastDayInMonth(sDate date)
{
	short daysInMonth = DaysInMonth(date.year, date.month);
	return(daysInMonth == date.day);
}
bool IsLastDayInYear(sDate date)
{
	short daysInMonth = DaysInMonth(date.year, date.month);
	return(date.month == 12 && daysInMonth == date.day);
}
int main()
{
	cout << "Enter The Date \n";
	sDate date1 = ReadDate();
	if (IsLastDayInMonth(date1))
		cout << "Yes It's The Last Day in Month\n";
	else
		cout << "No It's not The Last Day in Month\n";
	if(IsLastDayInYear(date1))
		cout << "Yes It's The Last Day in Year\n";
	else
		cout << "No It's not The Last Day in Year\n";
	system("pause>0");
}