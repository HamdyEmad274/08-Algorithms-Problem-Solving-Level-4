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
    if (IsDate1EqualsDate2(Date1,Date2))
    {
        return 0;
    }
    else if (IsDate1BeforeDate2(Date1, Date2))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
int main()
{
    cout << "\nFirst Date : ";
    stDate FirstDate = ReadFullDate();
    cout << "\nSecond Date : ";
    stDate SecondDate = ReadFullDate();
    short result = CompareDates(FirstDate, SecondDate);
    if (result == -1)
    {
        cout << "The First Date " << FirstDate.Year << "/" << FirstDate.Month << "/" << FirstDate.Day << " Is Before The Second Date "
            << SecondDate.Year << "/" << SecondDate.Month << "/" << SecondDate.Day;
    }
    else if (result == 0)
    {
        cout << "The First Date " << FirstDate.Year << "/" << FirstDate.Month << "/" << FirstDate.Day << " Is Equal to The Second Date "
            << SecondDate.Year << "/" << SecondDate.Month << "/" << SecondDate.Day;

    }
    else
    {
        cout << "The First Date " << FirstDate.Year << "/" << FirstDate.Month << "/" << FirstDate.Day << " Is After The Second Date "
            << SecondDate.Year << "/" << SecondDate.Month << "/" << SecondDate.Day;

    }
    system("pause>0");
    return 0;
}