//Increase Date methods
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
bool IsLastDayInMonth(sDate date)
{
	short daysInMonth = DaysInMonth(date.year, date.month);
	return(daysInMonth == date.day);
}
bool IsLastMonthInYear(short month)
{
	return(month == 12);
}
sDate AddOneDay(sDate& date) {
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
sDate IncreaseDateByXDays(sDate& date , short days) {
	for (short i = 0; i < days; i++)
	{
		AddOneDay(date);
	}
	return date;
}
sDate IncreaseDateByOneWeek(sDate& date) {
	IncreaseDateByXDays(date, 7);
	return date;
}
sDate IncreaseDateByXWeek(sDate& date, short weeks) {
	for (short i = 0; i < weeks; i++)
	{
		IncreaseDateByOneWeek(date);
	}
	return date;
}
sDate IncreaseDateByOneMonth(sDate& date) {
	if (date.month==12)
	{
		date.month = 1;
		date.year++;
	}
	else
	{
		date.month++;
	}
	short DaysOfMonth = DaysInMonth(date.year, date.month);
	if (date.day > DaysOfMonth)
	{
		date.day = DaysOfMonth;
	}
	return date;
}
sDate IncreaseDateByXMonths(sDate& date, short months) {
	for (short i = 0; i < months; i++)
	{
		IncreaseDateByOneMonth(date);
	}
	return date;
}
sDate IncreaseDateByOneYear(sDate& date) {
	date.year++;
	return date;
}
sDate IncreaseDateByXYears(sDate& date, short years) {
	for (short i = 0; i < years; i++)
	{
		IncreaseDateByOneYear(date);
	}
	return date;
}
sDate IncreaseDateByXYearsFaster(sDate& date, short years) {
	date.year += years;
	return date;
}
sDate IncreaseDateByOneDecade(sDate& date) {
	date.year += 10;
	return date;
}
sDate IncreaseDateByXDecades(sDate& date, short decades) {
	for (short i = 0; i < decades; i++)
	{
		IncreaseDateByOneDecade(date);
	}
	return date;
}
sDate IncreaseDateByXDecadesFaster(sDate& date, short decades) {
	date.year += decades * 10;
	return date;
}
sDate IncreaseDateByOneCentury(sDate& date) {
	date.year += 100;
	return date;
}
sDate IncreaseDateByOneMillenium(sDate& date) {
	date.year += 1000;
	return date;
}
void PrintDate(sDate date) {
	cout << date.day << "/" << date.month << "/" << date.year << endl;
}
int main()
{
	sDate date = ReadDate();
	cout << "\nDate After:\n\n";
	AddOneDay(date);
	cout << "01-Adding One Day is: ";
	PrintDate(date);
	IncreaseDateByXDays(date, 10);
	cout << "02-Adding 10 Day is: ";
	PrintDate(date);
	IncreaseDateByOneWeek(date);
	cout << "03-Adding One Week is: ";
	PrintDate(date);
	IncreaseDateByXWeek(date, 10);
	cout << "04-Adding 10 Week is: ";
	PrintDate(date);
	IncreaseDateByOneMonth(date);
	cout << "05-Adding One Month is: ";
	PrintDate(date);
	IncreaseDateByXMonths(date, 5);
	cout << "06-Adding 5 Months is: ";
	PrintDate(date);
	IncreaseDateByOneYear(date);
	cout << "07-Adding One Year is: ";
	PrintDate(date);
	IncreaseDateByXYears(date, 10);
	cout << "08-Adding 10 Years is: ";
	PrintDate(date);
	IncreaseDateByXYearsFaster(date, 10);
	cout << "09-Adding 10 Years Faster is: ";
	PrintDate(date);
	IncreaseDateByOneDecade(date);
	cout << "10-Adding One Decade is: ";
	PrintDate(date);
	IncreaseDateByXDecades(date, 10);
	cout << "11-Adding 10 Decades is: ";
	PrintDate(date);
	IncreaseDateByXDecadesFaster(date, 10);
	cout << "12-Adding 10 Decades Faster is: ";
	PrintDate(date);
	IncreaseDateByOneCentury(date);
	cout << "13-Adding One Century is: ";
	PrintDate(date);
	IncreaseDateByOneMillenium(date);
	cout << "14-Adding One Millenium is: ";
	PrintDate(date);
	system("pause>0");
}