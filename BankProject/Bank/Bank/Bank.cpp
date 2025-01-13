#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "users.txt";
void ShowMainScreen();
void ShowTransactionsMenu();
void GoBackToMainMenu();
void Login();
void ManageUsersScreen();

void GoBackToTransactionsMenu();

struct stUser {
	string Name;
	string Password;
	int Permissions = 0;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;
};
struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0.0;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;
};
enum Permissions {
	ShowClientList = 1 << 0,
	AddNewClients = 1 << 1,
	DeleteClients = 1 << 2,
	UpdateClients = 1 << 3,
	FindClients = 1 << 4,
	Transaction = 1 << 5,
	ManageUsers = 1 << 6
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

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
	sClient Client;
	vector<string> vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]); // cast string to double

	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}
string ConvertRecordToLine(stUser User, string Separator = "#//#") {
	string stClientRecord = "";

	stClientRecord += User.Name + Separator;
	stClientRecord += User.Password + Separator;
	stClientRecord += to_string(User.Permissions);

	return stClientRecord;
}
vector<sClient> LoadClientsDataFromFile(string fileName) {
	vector<sClient> Clients;
	fstream MyFile;
	MyFile.open(fileName, ios::in);
	if (MyFile.is_open())
	{
		string line;
		while (getline(MyFile, line))
		{
			sClient Client = ConvertLinetoRecord(line);
			Clients.push_back(Client);
		}
		MyFile.close();
	}
	return Clients;
}
string ReadString(string Message) {
	string String = "";
	cout << "\n" << Message;
	getline(cin >> ws, String);
	return String;
}
void PrintUserRecord(stUser User) {
	cout << "| " << setw(15) << left << User.Name;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permissions;
}
void PrintClientRecord(sClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintShortClientRecord(sClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintSingleClientRecord(sClient Client) {

	if (Client.Name != "")
	{
		cout << "The Following Is The Client Record:" << endl;
		cout << "_______________________________________________________";
		cout << "\nAccount Number: " << Client.AccountNumber;
		cout << "\nPin Code      : " << Client.PinCode;
		cout << "\nClient Name   : " << Client.Name;
		cout << "\nPhone         : " << Client.Phone;
		cout << "\nBalance       : " << Client.AccountBalance;
		cout << "\n_______________________________________________________\n\n";
	}
	else
	{
		cout << "Client Not Found" << endl;
	}
}
void PrintAllClientsData(vector<sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	// Loop through each client and print their record
	for (sClient& Client : vClients) {
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	GoBackToMainMenu();
}
void PrintAllClientsBalanceData(vector<sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalance = 0;
	// Loop through each client and print their record
	for (sClient& Client : vClients) {
		TotalBalance += Client.AccountBalance;
		PrintShortClientRecord(Client);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t\tTotal Balance: " << TotalBalance << endl;
	GoBackToMainMenu();
}

bool AddingClientToFile(string fileName) {
	bool bResult = false;
	fstream MyFile;
	vector<sClient> vClients = LoadClientsDataFromFile(fileName);
	MyFile.open(fileName, ios::app);
	if (MyFile.is_open())
	{
		sClient NewClient;
		NewClient.AccountNumber = ReadString("Enter Account Number: ");
		for (sClient& Client : vClients) {
			do
			{
				if (Client.AccountNumber == NewClient.AccountNumber) {
					cout << "This Account Number Is Already Exist. Please Enter Another One." << endl;
					NewClient.AccountNumber = ReadString("Enter Account Number: ");
				}
				else
				{
					break;
				}
			} while (true);
		}
		NewClient.PinCode = ReadString("Enter Pin Code: ");
		NewClient.Name = ReadString("Enter Name: ");
		NewClient.Phone = ReadString("Enter Phone: ");
		NewClient.AccountBalance = stod(ReadString("Enter Account Balance: "));
		MyFile << ConvertRecordToLine(NewClient) << endl;
		MyFile.close();
		cout << "Client Added Successfully." << endl;
		bResult = true;
	}
	else
	{
		bResult = false;
		cout << "Could Not Add Client." << endl;
	}

	GoBackToMainMenu();
	return bResult;
}
bool SaveClientsDataToFile(string fileName, vector<sClient> vClients) {
	fstream MyFile;
	MyFile.open(fileName, ios::out);
	if (MyFile.is_open())
	{
		for (sClient& Client : vClients) {
			if (!Client.MarkForDelete)
			{
				MyFile << ConvertRecordToLine(Client) << endl;
			}
		}
		MyFile.close();
		return true;
	}
	else
	{
		return false;
	}
}
bool SaveUsersDataToFile(string fileName, vector<stUser> vUsers) {
	fstream MyFile;
	MyFile.open(fileName, ios::out);
	if (MyFile.is_open())
	{
		for (stUser& User : vUsers) {
			if (!User.MarkForDelete)
			{
				MyFile << ConvertRecordToLine(User) << endl;
			}
		}
		MyFile.close();
		return true;
	}
	else
	{
		return false;
	}
}
sClient FindClientByAccountNumber(string AccountNumber) {
	sClient Client;
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return Client;
		}
	}
	return sClient();
}

bool MarkClientForDelete(sClient& Client) {
	char choice;
	cout << "Are You Sure To Delete This Client? [Y/N]";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		Client.MarkForDelete = true;
		return true;
	}
	else
	{
		return false;
	}
}
bool MarkUserForDelete(stUser& User) {
	char choice;
	cout << "\nAre You Sure To Delete This Client? [Y/N]";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		User.MarkForDelete = true;
		return true;
	}
	else
	{
		return false;
	}
}
bool MarkClientForUpdate(sClient& Client) {
	char choice;
	cout << "Are You Sure To Update This Client? [Y/N]";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		Client.MarkForUpdate = true;
		return true;
	}
	else
	{
		return false;
	}
}
sClient UpdateClient() {
	sClient UpdatedClient;
	UpdatedClient.PinCode = ReadString("Enter Pin Code: ");
	UpdatedClient.Name = ReadString("Enter Name: ");
	UpdatedClient.Phone = ReadString("Enter Phone: ");
	UpdatedClient.AccountBalance = stod(ReadString("Enter Account Balance: "));
	return UpdatedClient;
}
bool UpdateClientFromFile(string AccountNumber) {
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (sClient& Client : vClients) {
		if (Client.AccountNumber == AccountNumber) {
			PrintSingleClientRecord(Client);
			if (MarkClientForUpdate(Client))
			{
				sClient UpdatedClient = UpdateClient();
				UpdatedClient.AccountNumber = AccountNumber;
				Client = UpdatedClient;
				if (SaveClientsDataToFile(ClientsFileName, vClients))
				{
					cout << "Client Updated Successfully." << endl;
					GoBackToMainMenu();
					return true;
				}
			}
			else
			{
				cout << "Client Not Updated." << endl;
				GoBackToMainMenu();
				return false;
			}
		}
	}
	cout << "Client Not Found." << endl;
	GoBackToMainMenu();
	return false;
}
bool DeleteClientFromFile(string AccountNumber) {
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (sClient& Client : vClients) {
		if (Client.AccountNumber == AccountNumber) {
			PrintSingleClientRecord(Client);
			if (MarkClientForDelete(Client))
			{
				if (SaveClientsDataToFile(ClientsFileName, vClients))
				{
					cout << "Client Deleted Successfully." << endl;
					GoBackToMainMenu();
					return true;
				}

			}
			else
			{
				cout << "Client Not Deleted." << endl;
				GoBackToMainMenu();
				return false;
			}
		}
	}
	cout << "Client Not Found." << endl;
	GoBackToMainMenu();
	return false;

}
char ChooseFromMenu(string message) {
	cout << message;
	char choice;
	cin >> choice;
	return choice;
}
bool ConfirmProcess(string message) {
	cout << message;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		return true;
	}
	else
	{
		return false;
	}
}
bool Deposit() {
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadString("Enter Account Number: ");
	while (FindClientByAccountNumber(AccountNumber).Name == "")
	{
		cout << "Client Not Found. Please Try Again." << endl;
		AccountNumber = ReadString("Enter Account Number: ");
	}
	for (sClient& client : vClients)
	{
		if (client.AccountNumber == AccountNumber)
		{
			PrintSingleClientRecord(client);
			double Amount = stod(ReadString("Enter Amount: "));
			cout << "The New Balance Will Be: " << client.AccountBalance + Amount << endl;
			if (ConfirmProcess("Are You Sure To Save Changes? [Y/N] "))
				client.AccountBalance += Amount;
			SaveClientsDataToFile(ClientsFileName, vClients);
			cout << "Client Balance Updated Successfully." << endl;
			GoBackToTransactionsMenu();
			return true;
		}
	}
	cout << "Client Balance Was Not Updated." << endl;
	GoBackToTransactionsMenu();
	return false;
}
bool Withdraw() {
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadString("Enter Account Number: ");
	while (FindClientByAccountNumber(AccountNumber).Name == "")
	{
		cout << "Client Not Found. Please Try Again." << endl;
		AccountNumber = ReadString("Enter Account Number: ");
	}
	for (sClient& client : vClients)
	{
		if (client.AccountNumber == AccountNumber)
		{
			PrintSingleClientRecord(client);
			double Amount = stod(ReadString("Enter Amount: "));
			while (client.AccountBalance - Amount < 0)
			{
				cout << "Insufficient Balance. Please Try Again." << endl;
				Amount = stod(ReadString("Enter Amount: "));
			}
			cout << "The New Balance Will Be: " << client.AccountBalance - Amount << endl;
			if (ConfirmProcess("Are You Sure To Save Changes? [Y/N] "))
				client.AccountBalance -= Amount;
			SaveClientsDataToFile(ClientsFileName, vClients);
			cout << "Client Balance Updated Successfully." << endl;
			GoBackToTransactionsMenu();
			return true;
		}
	}
	cout << "Client Balance Was Not Updated." << endl;
	GoBackToTransactionsMenu();
	return false;
}
void ShowTotalBalances() {
	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	PrintAllClientsBalanceData(vClients);
}
void ShowTransactionsMenu() {
	cout << "===================================================";
	cout << "\n\t\Transactions Menu Screen\n";
	cout << "===================================================";
	cout << "\n\t[1] Deposit.";
	cout << "\n\t[2] Withdraw.";
	cout << "\n\t[3] Total Balances.";
	cout << "\n\t[4] Main Menu.\n";
	cout << "===================================================\n";

	switch (ChooseFromMenu("Enter Your Choice [1-4]: "))
	{
	case '1':
		system("cls");
		Deposit();
		break;
	case '2':
		system("cls");
		Withdraw();
		break;
	case '3':
		system("cls");
		ShowTotalBalances();
		break;
	case '4':
		system("cls");
		ShowMainScreen();
		break;
	default:
		cout << "Invalid Option";
		break;
	}
}
void GoBackToMainMenu() {
	cout << "Press Any Key To Return To Main Menu...";
	cin.ignore();
	cin.get();
	system("cls");
	ShowMainScreen();
}
void GoBackToUserMenu() {
	cout << "Press Any Key To Return To Users Manager Menu...";
	cin.ignore();
	cin.get();
	system("cls");
	ManageUsersScreen();
}
void GoBackToTransactionsMenu() {
	cout << "Press Any Key To Return To Transactions Menu...";
	cin.ignore();
	cin.get();
	system("cls");
	ShowTransactionsMenu();
}
void ShowMainScreen() {
	cout << "===================================================";
	cout << "\n\t\tMain Menu Screen\n";
	cout << "===================================================";
	cout << "\n\t[1] Show Client(s) List.";
	cout << "\n\t[2] Add New Client.";
	cout << "\n\t[3] Delete Client.";
	cout << "\n\t[4] Update Client's Info.";
	cout << "\n\t[5] Find Client.";
	cout << "\n\t[6] Transactions.";
	cout << "\n\t[7] Manage Users.";
	cout << "\n\t[8] Logout.\n";
	cout << "===================================================\n";

	switch (ChooseFromMenu("Enter Your Choice [1-8]: "))
	{
	case '1':
		system("cls");
		PrintAllClientsData(LoadClientsDataFromFile(ClientsFileName));
		break;
	case '2':
		system("cls");
		cout << "Adding Clients....";
		AddingClientToFile(ClientsFileName);
		break;
	case '3':
		system("cls");
		cout << "Delete Clients....";
		DeleteClientFromFile(ReadString("Enter Account Number: "));
		break;
	case '4':
		system("cls");
		cout << "Update Clients....";
		UpdateClientFromFile(ReadString("Enter Account Number: "));
		break;
	case '5':
		system("cls");
		cout << "Finding Clients....";
		PrintSingleClientRecord(FindClientByAccountNumber(ReadString("Enter Account Number: ")));
		GoBackToMainMenu();
		break;
	case '6':
		system("cls");
		ShowTransactionsMenu();
		break;

	case '7':
		system("cls");
		ManageUsersScreen();
		break;
	case '8':
		system("cls");
		Login();
		break;

	default:
		cout << "Invalid Option";
		break;
	}
}
stUser ConvertLineToUserRecord(string line, string delimiter) {
	stUser user;
	vector<string> userData = SplitString(line, delimiter);
	if (userData.size() == 3) {
		user.Name = userData[0];
		user.Password = userData[1];
		user.Permissions = stoi(userData[2]);
	}
	return user;
}
vector<stUser> LoadUsersDataFromFile(string fileName) {
	vector<stUser> vUsers;
	fstream MyFile;
	MyFile.open(fileName, ios::in);
	if (MyFile.is_open())
	{
		string line;
		while (getline(MyFile, line))
		{
			stUser user = ConvertLineToUserRecord(line, "#//#");
			vUsers.push_back(user);
		}
		MyFile.close();
	}
	return vUsers;
}
bool IsValidUser(stUser user) {
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	for (stUser& u : vUsers) {
		if (u.Name == user.Name && u.Password == user.Password) {
			return true;
		}
	}
	return false;
}

void Login() {
	bool loginFailed = false;

	while (true) {
		system("cls");

		cout << "===================================================";
		cout << "\n\t\tLogin Screen\n";
		cout << "===================================================";

		if (loginFailed) {
			cout << "\nInvalid Username or Password.\n";
		}

		stUser user;
		user.Name = ReadString("Enter Username: ");
		user.Password = ReadString("Enter Password: ");

		if (IsValidUser(user)) {
			system("cls");
			ShowMainScreen();
			break;
		}
		else {
			loginFailed = true;
		}
	}
}
vector<stUser> GetAllUsers(string fileName)
{
	vector<stUser> vUsers;
	fstream MyFile;
	MyFile.open(fileName, ios::in);
	if (MyFile.is_open())
	{
		string line;
		while (getline(MyFile, line)) {
			stUser user = ConvertLineToUserRecord(line, "#//#");
			vUsers.push_back(user);
		}
		MyFile.close();
	}
	return vUsers;
}
void PrintAllUsersData(vector<stUser> vUsers) {
	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "UserName";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	// Loop through each client and print their record
	for (stUser& User : vUsers) {
		PrintUserRecord(User);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	GoBackToMainMenu();
}
int AddingPermissionsToUser() {
	int Permissions = 0;
	string choice = ReadString("Do You Want To Give Full Permissions To This User? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions = -1;
		return Permissions;
	}
	choice = ReadString("Do You Want To Give Access To : \n\nShow Client List ? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions |= Permissions::ShowClientList;
	}
	choice = ReadString("\n\nAdd Client ? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions |= Permissions::AddNewClients;
	}
	choice = ReadString("\n\nDelete Client ? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions |= Permissions::DeleteClients;
	}
	choice = ReadString("\n\nUpdate Client ? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions |= Permissions::UpdateClients;
	}
	choice = ReadString("\n\nFind Client ? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions |= Permissions::FindClients;
	}
	choice = ReadString("\n\nTransactions ? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions |= Permissions::Transaction;
	}
	choice = ReadString("\n\nManage Users ? (y/n)");
	if (choice == "y" || choice == "Y") {
		Permissions |= Permissions::ManageUsers;
	}
	return Permissions;
}
bool AddingUserToFile(string fileName) {
	bool bResult = false;
	fstream MyFile;
	vector<stUser> vUsers = LoadUsersDataFromFile(fileName);
	MyFile.open(fileName, ios::app);
	if (MyFile.is_open())
	{
		stUser NewUser;
		NewUser.Name = ReadString("Enter User Name: ");
		for (stUser& User : vUsers) {
			do
			{
				if (User.Name == NewUser.Name) {
					cout << "This User Name Is Already Exist. Please Enter Another One." << endl;
					NewUser.Name = ReadString("Enter User Name: ");
				}
				else
				{
					break;
				}
			} while (true);
		}
		NewUser.Password = ReadString("Enter Password: ");
		NewUser.Permissions = AddingPermissionsToUser();
		MyFile << ConvertRecordToLine(NewUser) << endl;
		MyFile.close();
		cout << "User Added Successfully." << endl;
		bResult = true;
	}
	else
	{
		bResult = false;
		cout << "Could Not Add User." << endl;
	}

	GoBackToUserMenu();
	return bResult;
}
bool DeleteUserFromFile(string UserName) {
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	for (stUser& User : vUsers) {
		if (User.Name == UserName) {
			PrintUserRecord(User);
			if (MarkUserForDelete(User))
			{
				if (SaveUsersDataToFile(UsersFileName, vUsers))
				{
					cout << "User Deleted Successfully." << endl;
					GoBackToUserMenu();
					return true;
				}

			}
			else
			{
				cout << "User Not Deleted." << endl;
				GoBackToUserMenu();
				return false;
			}
		}
	}
	cout << "User Not Found." << endl;
	GoBackToUserMenu();
	return false;

}
void ManageUsersScreen() {
	cout << "===================================================";
	cout << "\n\t\tManage Users Menu Screen\n";
	cout << "===================================================";
	cout << "\n\t[1] List Users.";
	cout << "\n\t[2] Add New User.";
	cout << "\n\t[3] Delete User.";
	cout << "\n\t[4] Update User.";
	cout << "\n\t[5] Find User.";
	cout << "\n\t[6] Main Menu.\n";
	cout << "===================================================\n";

	switch (ChooseFromMenu("Enter Your Choice [1-6]: "))
	{
	case '1':
		system("cls");
		PrintAllUsersData(GetAllUsers(UsersFileName));
		break;

	case '2':
		system("cls");
		AddingUserToFile(UsersFileName);
		break;

	case '3':
		system("cls");
		DeleteUserFromFile(ReadString("Enter User Name: "));
		break;

	case '4':
		system("cls");
		break;

	case '5':
		system("cls");
		break;

	case '6':
		system("cls");
		ShowMainScreen();
		break;

	default:
		cout << "Invalid Option";
		break;
	}
}
int main()
{
	Login();
	return 0;
}