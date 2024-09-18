//Diff between dates with negative result(Support Backward )
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
bool IsLastMonthInYear(short month)
{
	return(month == 12);
}
bool IsDateOneEqualsDateTwo(sDate date1, sDate date2) {
	return(date1.year == date2.year) ? (date1.month == date2.month ? date1.day == date2.day : false) : false;
}
sDate AddOneDay(sDate date) {
	if (IsLastMonthInYear(date.month))
	{
		if (IsLastDayInMonth(date))
		{
			date.year++;
			date.month = 1;
			date.day = 1;
		}
		else
		{
			date.day++;
		}
	}
	else
	{
		if (IsLastDayInMonth(date))
		{
			date.month++;
			date.day = 1;
		}
		else
		{
			date.day++;
		}
	}
	return date;
}
bool IsDateOneBeforeDateTwo(sDate date1, sDate date2) {
	return(date1.year < date2.year) ? true :
		((date1.year == date2.year) ? (date1.month < date2.month ? true :
			(date1.month == date2.month ? date1.day < date2.day : false)) : false);
}
short DiffBetween2Dates(sDate date1, sDate date2, bool includeLastDay = false) {
	short diff = 0;
	//bool negative = false;
	short SwapFlagValue = 1;
	if (!IsDateOneBeforeDateTwo(date1,date2))
	{
		//negative = true;
		SwapFlagValue = -1;
		sDate tmp = date1;
		date1 = date2;
		date2 = tmp;//swap
	}
	while (!IsDateOneEqualsDateTwo(date1, date2))
	{
		date1 = AddOneDay(date1);
		diff++;
	}
	//return (includeLastDay) ? (negative?-(diff+1):diff+1) : (negative)?-diff:diff;
	return (includeLastDay) ? ++diff * SwapFlagValue : diff * SwapFlagValue;
}
int main()
{
	cout << "Enter The First(Older) Date\n";
	sDate date1 = ReadDate();
	cout << "Enter The Second(Later) Date\n";
	sDate date2 = ReadDate();
	cout << "The Difference between Date 1 and Date 2 is [" << DiffBetween2Dates(date1, date2) << "] Days\n\n";
	cout << "The Difference between Date 1 and Date 2 is [" << DiffBetween2Dates(date1, date2, true) << "] Days after including the last day\n";
	system("pause>0");
}