#include <iostream>
#include <string>
using namespace std;
bool isLeapYear(int year) {
	if (year % 400 == 0)
	{
		return true;
	}
	else if (year % 100 == 0)
	{
		return false;
	}
	else if (year % 4 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int GetYear() {
	cout << "Enter year: ";
	int year;
	cin >> year;
	return year;
}
int main()
{
	while (true)
	{
		int year = GetYear();
		if (isLeapYear(year))
		{
			cout << "Leap Year" << endl;
		}
		else
		{
			cout << "Not Leap Year" << endl;
		}
		if (year == 0)
		{
			break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
