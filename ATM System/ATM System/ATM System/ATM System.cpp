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
	CheckBalance,
	Exit
};
void ShowMenu();
void Login();
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
stCard ConvertLineToRecord(string Line, string Seperator = "#//#") {
	stCard Card;
	vector<string> vCardsData = SplitString(Line, Seperator);

	Card.pinCode = vCardsData[0];
	Card.password = vCardsData[1];
	Card.balance = stod(vCardsData[2]);
	return Card;
}
string ConvertRecordToLine(stCard Card, string Seperator = "#//#") {
	string Line;
	Line = Card.pinCode + Seperator + Card.password + Seperator + to_string(Card.balance);
	return Line;
}
vector <stCard> LoadCards(string CardsFile) {
	vector<stCard> Cards;
	ifstream File(CardsFile);
	string Line;
	while (getline(File, Line)) {
		Cards.push_back(ConvertLineToRecord(Line));
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
bool UpdateCard(string CardFile) {
	vector<stCard> Cards = LoadCards(CardsFile);
	for (int i = 0; i < Cards.size(); i++) {
		if (Cards[i].pinCode == globalCard.pinCode && Cards[i].password == globalCard.password) {
			Cards[i].balance = globalCard.balance;
			ofstream File(CardsFile);
			for (int j = 0; j < Cards.size(); j++) {
				File << ConvertRecordToLine(Cards[j]) << endl;
			}
			return true;
		}
	}
	return false;
}
void QuickWithdrawScreen() {
	int QuickWithdrawOptions[] = { 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
	system("cls");
	cout << "===================================================";
	cout << "\n\t\tQuick Withdraw Screen\n";
	cout << "===================================================";
	cout << "\n\t[1] 50 LE \t\t [2] 100 LE\n";
	cout << "\t[3] 200 LE \t\t [4] 500 LE\n";
	cout << "\t[5] 1000 LE \t\t [6] 2000 LE\n";
	cout << "\t[7] 5000 LE \t\t [8] 10000 LE\n";
	cout << "\t[9] Exit\n";
	cout << "===================================================\n";
	cout << "your balance is: " << globalCard.balance << " LE\n";
	string choice = ReadString("Choose what you want to withdraw: [1-8]");
	cout << "Are you sure you want to withdraw " << QuickWithdrawOptions[stoi(choice) - 1] << " LE ? (y/n)\n";
	if (cin.get() == 'y' || cin.get() == 'Y')
	{
		if (globalCard.balance < QuickWithdrawOptions[stoi(choice) - 1])
		{
			cout << "You don't have enough balance\n";
			cout << "Press any key to go back to the menu ...\n";
			cin.get();
			ShowMenu();
		}
		globalCard.balance -= QuickWithdrawOptions[stoi(choice) - 1];
		if (UpdateCard(CardsFile)) {
			cout << "Your balance is now: " << globalCard.balance << " LE\n";
			cout << "Press any key to go back to the menu ...\n";
			cin.ignore();
			cin.get();
			ShowMenu();
		}
		else {
			cout << "Error in updating card data\n";
			cout << "Press any key to go back to the menu ...\n";
			cin.get();
			ShowMenu();
		}
	}
}
void NormalWithdrawScreen() {
	system("cls");
	cout << "===================================================";
	cout << "\n\t\Normal Withdraw Screen\n";
	cout << "===================================================";
	cout << "your balance is: " << globalCard.balance << " LE\n";
	string amount = ReadString("please, enter the amount you want to withdraw");

}
void CheckBalanceScreen() {
	system("cls");
	cout << "===================================================";
	cout << "\n\t\tCheck Balance Screen\n";
	cout << "===================================================";
	cout << "\nYour Balance is: " << globalCard.balance << " LE\n";
	cout << "\nPress any key to go back to the menu ...\n";
	cin.get();
	ShowMenu();
}
void ScreenOpener(Commands Command) {
	switch (Command)
	{
	case QuickWithdraw:
		QuickWithdrawScreen();
		break;
	case NormalWithdraw:
		break;
	case Deposit:
		break;
	case CheckBalance:
		CheckBalanceScreen();
		break;
	case Exit:
		Login();
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
	ScreenOpener(Commands(stoi(ReadString("Enter your choice: [1-5]"))));

}
void Login() {
	bool loggedIn = false;
	bool wrongPin = false;
	while (!loggedIn) {
		system("cls");

		cout << "===================================================";
		cout << "\n\t\tLogin Screen\n";
		cout << "===================================================";

		if (wrongPin) {
			cout << "\nInvalid PinCode or Password.\n";
		}
		stCard Card;
		Card.pinCode = ReadString("Enter your Pin Code: ");
		Card.password = ReadString("Enter your Password: ");

		if (isValidCard(Card))
		{
			system("cls");
			globalCard = Card;
			loggedIn = true;
			ShowMenu();
		}
		else {
			wrongPin = true;
		}
	}
}

int main()
{
	Login();
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
