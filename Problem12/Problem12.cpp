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
short DaysInMonth(short year, short month) {
	if (month < 1 || month > 12)
	{
		return 0;
	}
	short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return NumberOfDays[month - 1] + (isLeapYear(year) && month == 2 ? 1 : 0);
}
#pragma region Help Of Codeium
//short DayNumberInYear(short year, short month, short day) {
	//	if (CheckDay(year, month, day) && CheckMonth(year, month))
	//	{
	//		short sum = 0;
	//		for (short i = 1; i < month; i++)
	//		{
	//			if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
	//			{
	//				sum += 31;
	//			}
	//			else if (i == 4 || i == 6 || i == 9 || i == 11)
	//			{
	//				sum += 30;
	//			}
	//			else if (i == 2)
	//			{
	//				if (isLeapYear(year))
	//				{
	//					sum += 29;
	//				}
	//				else
	//				{
	//					sum += 28;
	//				}
	//			}
	//		}
	//		sum += day;
	//		return sum;
	//	}
	//	else
	//	{
	//		return -1;
	//	}
	//
	//}  
#pragma endregion
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
string DateOfDayInYear(short dayOrder, short year) {
	if ((isLeapYear(year) && dayOrder <= 366) || (!isLeapYear(year) && dayOrder <= 365))
	{
		short day = 0, month = 0, counter = 0;
		for (short i = 1; i <= 12; i++)
		{
			for (short j = 1; j <= DaysInMonth(year, i); j++)
			{
				if (counter == dayOrder)
				{
					month = i;
					day = j - 1;
					return "Date For [" + to_string(dayOrder) + "] is : " + to_string(day) + "/" + to_string(month) + "/" + to_string(year);
				}
				counter++;
			}
		}
	}
	return "Invalid DayOrder";
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
sDate AddDaysToDate(short days, sDate date) {
	short RemainingDays = days + NumberOfTheDayInYear(date.year, date.month, date.day);
	short MonthDays = 0;
	date.month = 1;
	while (true)
	{
		MonthDays = DaysInMonth(date.year, date.month);
		if (RemainingDays > MonthDays)
		{
			RemainingDays -= MonthDays;
			date.month++;
			if (date.month > 12)
			{
				date.year++;
				date.month = 1;
			}
		}
		else
		{
			date.day = RemainingDays;
			break;
		}
	}
	return date;
}
int main()
{
	sDate date = ReadDate();
	short daysToAdd = GetNumber("Enter The Days To Add : ");
	date = AddDaysToDate(daysToAdd, date);
	cout << "The New Date after adding ["<< daysToAdd << "] is " << date.day << " / " << date.month << " / " << date.year << endl;
	system("pause>0");
}
