#include <iostream>
using namespace std;

struct stDate
{
	short Year;
	short Month;
	short Day;

};

bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
{
	return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}

bool IsDate1EqualsDate2(stDate Date1, stDate Date2)
{
	return  ((Date1.Year == Date2.Year) && (Date1.Month) == Date2.Month && (Date1.Day == Date2.Day));
}
bool IsDate1AfterDate2(stDate Date1, stDate Date2)
{
	return  (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualsDate2(Date1, Date2));
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
short CompareDates(stDate Date1, stDate Date2) {
	if (IsDate1EqualsDate2(Date1, Date2))
		return 0;
	if (IsDate1BeforeDate2(Date1, Date2))
		return -1;
	return 1;
}

bool IsOverlap(stDate Date1Start, stDate Date1End, stDate Date2Start, stDate Date2End) {

	if (IsDate1BeforeDate2(Date1End, Date2Start) || IsDate1BeforeDate2(Date2End, Date1Start))
		return false;

	return true;
}
int main()
{
	cout << "\nFirst Date Start : ";
	stDate FirstDateStart = ReadFullDate();
	cout << "\nFirst Date End : ";
	stDate FirstDateEnd = ReadFullDate();
	cout << "\nSecond Date Start : ";
	stDate SecondDateStart = ReadFullDate();
	cout << "\nSecond Date End : ";
	stDate SecondDateEnd = ReadFullDate();
	IsOverlap(FirstDateStart, FirstDateEnd, SecondDateStart, SecondDateEnd) ? cout << "\nYes They Overlap" : cout << "\nNope They do not Overlap";
	

	system("pause>0");
	return 0;
}