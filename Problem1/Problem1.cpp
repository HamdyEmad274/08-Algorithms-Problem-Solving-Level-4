#include <iostream>
#include <vector>
#include <string>
using namespace std;

int GetNumber() {
    int num;
    cout << "Enter a number: ";
    cin >> num;
    return num;
}

string GetNumberText(int num) {
    if (num == 0) return "Zero";

    vector<string> belowTen = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
    vector<string> belowTwenty = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
    vector<string> belowHundred = { "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

    string result;

    if (num >= 1000000000) {
        result += GetNumberText(num / 1000000000) + " Billion ";
        num %= 1000000000;
    }
    if (num >= 1000000) {
        result += GetNumberText(num / 1000000) + " Million ";
        num %= 1000000;
    }
    if (num >= 1000) {
        result += GetNumberText(num / 1000) + " Thousand ";
        num %= 1000;
    }
    if (num >= 100) {
        result += GetNumberText(num / 100) + " Hundred ";
        num %= 100;
    }
    if (num >= 20) {
        result += belowHundred[num / 10 - 2] + " ";
        num %= 10;
    }
    if (num >= 10) {
        result += belowTwenty[num - 10] + "";
        num = 0;
    }
    if (num > 0) {
        result += belowTen[num - 1] + "";
    }

    return result;
}

int main() {
    cout << GetNumberText(GetNumber()) << endl;
    system("pause>0");
}
