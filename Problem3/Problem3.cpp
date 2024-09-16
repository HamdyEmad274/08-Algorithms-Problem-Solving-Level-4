#include <iostream>
#include <string>
using namespace std;
bool isLeapYear(int year) {
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return true;
	}
	return false;
}
int GetYear() {
	cout << "Enter year: ";
	int year;
	cin >> year;
	return year;
}
void Start() {
	while (true)
	{
		int year = GetYear();
		if (year == 0)
		{
			break;
		}
		if (isLeapYear(year))
		{
			cout << "Leap Year" << endl;
		}
		else
		{
			cout << "Not Leap Year" << endl;
		}
	}
}
int main()
{
	Start();
	return 0;
}
