#include <iostream>
using namespace std;

struct stDate
{
	short Year;
	short Month;
	short Day;

};
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
bool IsLastDayInMonth(stDate date)
{
	short daysInMonth = DaysInMonth(date.Year, date.Month);
	return(daysInMonth == date.Day);
}
bool IsLastMonthInYear(short month)
{
	return(month == 12);
}


stDate AddOneDay(stDate& date) {
	if (IsLastMonthInYear(date.Month))
	{
		if (IsLastDayInMonth(date))
		{
			date.Year++;
			date.Month = 1;
			date.Day = 1;
		}
		else
		{
			date.Day++;
		}
	}
	else
	{
		if (IsLastDayInMonth(date))
		{
			date.Month++;
			date.Day = 1;
		}
		else
		{
			date.Day++;
		}
	}
	return date;
}

short DayOfWeekOrder(short Day, short Month, short Year)
{
	short a, y, m;
	a = (14 - Month) / 12;
	y = Year - a;
	m = Month + (12 * a) - 2;
	// Gregorian:
	//0:sun, 1:Mon, 2:Tue...etc
	return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short DayOfWeekOrder(stDate Date)
{
	return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);

}

string DayShortName(short DayOfWeekOrder)
{
	string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

	return arrDayNames[DayOfWeekOrder];

}


short ReadDay()
{
	short Day;
	cout << "\nPlease enter a Day? ";
	cin >> Day;
	return Day;
}

short ReadMonth()
{
	short Month;
	cout << "Please enter a Month? ";
	cin >> Month;
	return Month;
}

short ReadYear()
{
	short Year;
	cout << "Please enter a Year? ";
	cin >> Year;
	return Year;
}

stDate ReadFullDate()
{
	stDate Date;

	Date.Day = ReadDay();
	Date.Month = ReadMonth();
	Date.Year = ReadYear();

	return Date;
}
short DaysBetween2Dates(stDate Date1, stDate Date2) {
	short Days = 0;
	while (Date1.Day != Date2.Day || Date1.Month != Date2.Month || Date1.Year != Date2.Year)
	{
		Date1 = AddOneDay(Date1);
		Days++;
	}
	return Days;
}

int main()
{
	cout << "Enter Period 1:\n";
	stDate Date1 = ReadFullDate();
	cout << "\nEnter End of Period :\n";
	stDate Date2 = ReadFullDate();
	short Days = DaysBetween2Dates(Date1, Date2);
	cout << "\nThere are " << Days << " days between the dates" << endl;
	cout << "The days are (Including end day) : "<< Days + 1 << endl;
	system("pause>0");
	return 0;
}