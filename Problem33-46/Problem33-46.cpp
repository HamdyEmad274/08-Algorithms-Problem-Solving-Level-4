//Decrease Date methods
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
bool IsFirstDayInMonth(sDate date)
{
	return(date.day == 1);
}
bool IsFirstMonthInYear(short month)
{
	return(month == 1);
}
sDate DecreaseOneDay(sDate& date) {
	if (IsFirstMonthInYear(date.month))
	{
		if (IsFirstDayInMonth(date))
		{
			date.year--;
			date.month = 12;
			date.day = 31;
		}
		else
		{
			date.day--;
		}
	}
	else
	{
		if (IsFirstDayInMonth(date))
		{
			date.month--;
			date.day = DaysInMonth(date.year,date.month);
		}
		else
		{
			date.day--;
		}
	}
	return date;
}
sDate DecreaseDateByXDays(sDate& date, short days) {
	for (short i = 0; i < days; i++)
	{
		DecreaseOneDay(date);
	}
	return date;
}
sDate DecreaseDateByOneWeek(sDate& date) {
	DecreaseDateByXDays(date, 7);
	return date;
}
sDate DecreaseDateByXWeek(sDate& date, short weeks) {
	for (short i = 0; i < weeks; i++)
	{
		DecreaseDateByOneWeek(date);
	}
	return date;
}
sDate DecreaseDateByOneMonth(sDate& date) {
	if (date.month == 1)
	{
		date.month = 12;
		date.year--;
	}
	else
	{
		date.month--;
	}
	short DaysOfMonth = DaysInMonth(date.year, date.month);
	if (date.day > DaysOfMonth)
	{
		date.day = DaysOfMonth;
	}
	return date;
}
sDate DecreaseDateByXMonths(sDate& date, short months) {
	for (short i = 0; i < months; i++)
	{
		DecreaseDateByOneMonth(date);
	}
	return date;
}
sDate DecreaseDateByOneYear(sDate& date) {
	date.year--;
	return date;
}
sDate DecreaseDateByXYears(sDate& date, short years) {
	for (short i = 0; i < years; i++)
	{
		DecreaseDateByOneYear(date);
	}
	return date;
}
sDate DecreaseDateByXYearsFaster(sDate& date, short years) {
	date.year -= years;
	return date;
}
sDate DecreaseDateByOneDecade(sDate& date) {
	date.year -= 10;
	return date;
}
sDate DecreaseDateByXDecades(sDate& date, short decades) {
	for (short i = 0; i < decades; i++)
	{
		DecreaseDateByOneDecade(date);
	}
	return date;
}
sDate DecreaseDateByXDecadesFaster(sDate& date, short decades) {
	date.year -= decades * 10;
	return date;
}
sDate DecreaseDateByOneCentury(sDate& date) {
	date.year -= 100;
	return date;
}
sDate DecreaseDateByOneMillenium(sDate& date) {
	date.year -= 1000;
	return date;
}
void PrintDate(sDate date) {
	cout << date.day << "/" << date.month << "/" << date.year << endl;
}
int main()
{
	sDate date = ReadDate();
	cout << "\nDate After:\n\n";
	DecreaseOneDay(date);
	cout << "01-Subtracting One Day is: ";
	PrintDate(date);
	DecreaseDateByXDays(date, 10);
	cout << "02-Subtracting 10 Day is: ";
	PrintDate(date);
	DecreaseDateByOneWeek(date);
	cout << "03-Subtracting One Week is: ";
	PrintDate(date);
	DecreaseDateByXWeek(date, 10);
	cout << "04-Subtracting 10 Week is: ";
	PrintDate(date);
	DecreaseDateByOneMonth(date);
	cout << "05-Subtracting One Month is: ";
	PrintDate(date);
	DecreaseDateByXMonths(date, 5);
	cout << "06-Subtracting 5 Months is: ";
	PrintDate(date);
	DecreaseDateByOneYear(date);
	cout << "07-Subtracting One Year is: ";
	PrintDate(date);
	DecreaseDateByXYears(date, 10);
	cout << "08-Subtracting 10 Years is: ";
	PrintDate(date);
	DecreaseDateByXYearsFaster(date, 10);
	cout << "09-Subtracting 10 Years Faster is: ";
	PrintDate(date);
	DecreaseDateByOneDecade(date);
	cout << "10-Subtracting One Decade is: ";
	PrintDate(date);
	DecreaseDateByXDecades(date, 10);
	cout << "11-Subtracting 10 Decades is: ";
	PrintDate(date);
	DecreaseDateByXDecadesFaster(date, 10);
	cout << "12-Subtracting 10 Decades Faster is: ";
	PrintDate(date);
	DecreaseDateByOneCentury(date);
	cout << "13-Subtracting One Century is: ";
	PrintDate(date);
	DecreaseDateByOneMillenium(date);
	cout << "14-Subtracting One Millenium is: ";
	PrintDate(date);
	system("pause>0");
}