// ATM System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string CardsFile = "Cards.txt";
struct stCard {
	string pinCode;
	double balance;
	string password;
};
stCard globalCard;
enum Commands {
	QuickWithdraw = 1,
	NormalWithdraw,
	Deposit,
	CheckBalance
};
vector<string> SplitString(string S1, string Delim) {
	vector<string> vString;
	size_t pos = 0;
	string sWord;

	while ((pos = S1.find(Delim)) != std::string::npos) {
		sWord = S1.substr(0, pos);
		if (!sWord.empty()) {
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}

	if (!S1.empty()) {
		vString.push_back(S1);
	}

	return vString;
}
stCard ConvertLinetoRecord(string Line, string Seperator = "#//#") {
	stCard Card;
	vector<string> vCardsData = SplitString(Line, Seperator);

	Card.pinCode = vCardsData[0];
	Card.password = vCardsData[1];
	Card.balance = stod(vCardsData[2]);
	return Card;
}
string ConvertRecordtoLine(stCard Card, string Seperator = "#//#") {
	string Line;
	Line = Card.pinCode + Seperator + Card.password + Seperator + to_string(Card.balance);
	return Line;
}
vector <stCard> LoadCards(string CardsFile) {
	vector<stCard> Cards;
	ifstream File(CardsFile);
	string Line;
	while (getline(File, Line)) {
		Cards.push_back(ConvertLinetoRecord(Line));
	}
	return Cards;
}
string ReadString(string Message) {
	string String = "";
	cout << "\n" << Message;
	getline(cin >> ws, String);
	return String;
}
bool isValidCard(stCard& Card) {
	vector<stCard> Cards = LoadCards(CardsFile);
	for (int i = 0; i < Cards.size(); i++) {
		if (Cards[i].pinCode == Card.pinCode && Cards[i].password == Card.password) {
			Card.balance = Cards[i].balance;
			return true;
		}
	}
	return false;
}
void ScreenOpener(Commands Command) {
	switch (Command)
	{
	case QuickWithdraw:
		break;
	case NormalWithdraw:
		break;
	case Deposit:
		break;
	case CheckBalance:
		break;
	default:
		ShowMenu();
		break;
	}
}
void ShowMenu() {
	system("cls");

	cout << "===================================================";
	cout << "\n\t\Welcome to ATM System Screen\n";
	cout << "===================================================";

	cout << "\n1. Quick Withdraw\n";
	cout << "2. Normal Withdraw\n";
	cout << "3. Deposit\n";
	cout << "4. Check Balance\n";
	cout << "5. Exit\n";
	cout << "===================================================\n";
	cout << "Enter Your Choice: [1-5]";


}
void Login() {
	bool loggedIn = false;
	while (!loggedIn) {
		system("cls");

		cout << "===================================================";
		cout << "\n\t\tLogin Screen\n";
		cout << "===================================================";

		if (loggedIn) {
			cout << "\nInvalid PinCode or Password.\n";
		}
		stCard Card;
		Card.pinCode = ReadString("Enter your Pin Code: ");
		Card.password = ReadString("Enter your Password: ");

		if (isValidCard(Card))
		{
			system("cls");
			globalCard = Card;
			ShowMenu();
		}
	}
}

int main()
{
	cout << "Hello World!\n";
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
