#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <stdio.h>

using namespace std;

void clean() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) //Íå çíàë, íà êàêîé ÎÑ áóäåò çàïóñê, ïîýòîìó ñäåëàë ïðîâåðêó
	system("cls");
#else
	printf("\033c");
#endif
}
class Client {
public:
	int bankID;
	string name;
	int cardNumber;
	string PIN;
	long long balance;
	int lastTransaction;
	bool active;

	Client() {}
	Client(int a, string b, int c, string d, long long e, int f, bool g) {
		bankID = a;
		name = b;
		cardNumber = c;
		PIN = d;
		balance = e;
		lastTransaction = f;
		active = g;
	}
};

vector<Client> clients;
Client client(1, "", 1, "1", 1, 1, true);
Client found(1, "", 1, "1", 1, 1, true);

void read_record()
{

	// File pointer
	fstream fin;

	// Open an existing file
	fin.open("database.csv", ios::in);
	vector<string> row;
	string line, word, temp;
	word = "";
	bool flag = false;


	for (string line; getline(fin, line); ) {
		row.clear();
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != ',') {
				word += line[i];
				if (i == line.length() - 1) {
					row.push_back(word);
					word = "";
				}
			}
			else {
				row.push_back(word);
				word = "";
			}
		}

		if (flag == true) {
			client.bankID = stoi(row[0]);
			client.name = row[1];
			client.cardNumber = stoi(row[2]);
			client.PIN = row[3];
			client.balance = stoll(row[4]);
			client.lastTransaction = stoi(row[5]);
			for (char i : client.PIN) {
				if (isdigit(i) != 0) {
					client.active = true;
				}
				else {
					client.active = false;
					break;
				}
			}
			clients.push_back(client);
		}
		flag = true;
	}
	fin.close();
}

void withdraw_cash();
void deposit_cash();
void modify_pin_code();
void show_balance();
void transfer_between_accounts();
void menu();

void start() {
	cout << "\tThe Bank of MixChopLove\n" << endl;
	int N;
	while (true) {
		cout << "Card number (6 digits): ";
		cin >> N;
		for (Client n : clients) {
			if (n.cardNumber == N) {
				cout << "PIN code (4 digits): ";
				string S;
				cin >> S;
				if (n.PIN == S) {
					found.bankID = n.bankID;
					found.name = n.name;
					found.cardNumber = n.cardNumber;
					found.PIN = n.PIN;
					found.balance = n.balance;
					found.lastTransaction = n.lastTransaction;
					found.active = n.active;
					clean();
					menu();
					break;
				}
				else {
					clean();
					cout << "\tWelcom to the Bank of MixChopLove\n" << endl;
					cout << "The card number or PIN code is incorrect. Try again!" << endl;
					continue;
				}
			}
		}
		clean();
		cout << "\tWelcom to the Bank of MixChopLove\n" << endl;
		cout << "The card number or PIN code is incorrect. Try again!" << endl;
		continue;
	}
}

void menu() {
	int N;
	cout << "\tThe Bank of MixChopLove\n" << endl;
	cout << "Select one of the following options:\n" << endl;
	cout << "1. Withdraw Cash\t";
	cout << "2. Deposit Cash\n";
	cout << "3. Modify PIN Code\t";
	cout << "4. Show Balance\n";
	cout << "5. Transfer Between Accounts\t";
	cout << "6. End Session\n" << endl;
	cout << "Enter option number: ";
	cin >> N;
	switch (N) {
	case 1:
		if (found.active) {
			clean();
			withdraw_cash();
			break;
		}
		else {
			clean();
			menu();
			break;
		}
	case 2:
		if (found.active) {
			clean();
			deposit_cash();
			break;
		}
		else {
			clean();
			menu();
			break;
		}
	case 3:
		clean();
		modify_pin_code();
		break;
	case 4:
		clean();
		show_balance();
		break;
	case 5:
		if (found.active) {
			clean();
			transfer_between_accounts();
			break;
		}
		else {
			clean();
			menu();
			break;
		}
	case 6:
		start();
		break;
	default:
		clean();
		menu();
		break;
	}
}

int main() {
	read_record();
	start();
}

void withdraw_cash() {
	int N;
	cout << "\tThe Bank of MixChopLove\n" << endl;
	cout << "Current balance: " << found.balance << " KZT" << endl;
	char A;
	while (true) {
		cout << "Enter amount of withdraw: ";
		cin >> N;
		if (N <= found.balance) {
			found.balance -= N;
			clean();
			cout << "\tThe Bank of MixChopLove\n" << endl;
			cout << "Cash withdrawn succesfully!" << endl;
			found.lastTransaction = -N;
			cout << "Remaining balance: " << found.balance << " KZT\n" << endl;
			cout << "Would you like to return to main menu?(Y/N)";
			cin >> A;
			if (A == 'Y') {
				clean();
				menu();
				break;
			}
			else {
				clean();
				withdraw_cash();
				break;
			}
		}
		else {
			clean();
			cout << "\tThe Bank of MixChopLove\n" << endl;
			cout << "Current balance: " << found.balance << " KZT" << endl;
			cout << "Not enought money on your balance!" << endl;
		}
	}
}

void deposit_cash() {
	int N;
	cout << "\tThe Bank of MixChopLove\n" << endl;
	cout << "Current balance: " << found.balance << " KZT" << endl;
	char A;
	cout << "Enter amount of deposit: ";
	cin >> N;
	found.balance += N;
	clean();
	cout << "\tThe Bank of MixChopLove\n" << endl;
	cout << "Den'gi vneseni uspeshno!" << endl;
	found.lastTransaction = N;
	cout << "Remaining balance: " << found.balance << " KZT\n" << endl;
	cout << "Would you like to return to main menu?(Y/N)";
	cin >> A;
	if (A == 'Y') {
		clean();
		menu();
	}
	else {
		clean();
		deposit_cash();
	}
}

void modify_pin_code() {
	cout << "\tThe Bank of MixChopLove\n" << endl;
	if (found.active) {
		int A;
		cout << "Enter new PIN: ";
		cin >> A;
		found.PIN = A;
		cout << "Changed succesfully!\n" << endl;
		cout << "Do you want return to main menu? (Y/N)";
		char B;
		cin >> B;
		if (B == 'Y') {
			clean();
			menu();
		}
		else {
			clean();
			start();
		}
	}
	else {
		int A;
		cout << "Setup your PIN (4 sym): ";
		cin >> A;
		found.PIN = A;
		cout << "Succesfully!\n" << endl;
		cout << "Do you want return to main menu? (Y/N)";
		char B;
		cin >> B;
		if (B == 'Y') {
			clean();
			menu();
		}
		else {
			clean();
			start();
		}
	}
}

void show_balance() {
	char A;
	cout << "\tThe Bank of MixChopLove\n" << endl;
	cout << "Card owner: " << found.name << endl;
	cout << "Card number: " << found.cardNumber << endl;
	cout << "Current balance in KZT: " << found.balance << endl;
	cout << "Current balance in USD: " << (found.balance / 433) << endl;
	cout << "Last transaction: " << found.lastTransaction << "\n" << endl;
	cout << "Would you like to return to main menu?(Y/N)";
	cin >> A;
	if (A == 'Y') {
		clean();
		menu();
	}
	else {
		clean();
		start();
	}
}

void transfer_between_accounts() {
	int N;
	char A;
	cout << "\tThe Bank of MixChopLove\n" << endl;
	cout << "**Comission for fund transfers over 20,000 KZT is 500 KZT\n" << endl;
	cout << "Beneficiary's card number: ";
	cin >> N;
	bool flag = false;

	for (Client n : clients) {
		if (N == n.cardNumber) {
			flag = true;
			cout << "Transfer amount (in KZT): ";
			cin >> N;
			if (N >= n.balance && N < 20000 && n.bankID == found.bankID) {
				cout << endl;
				cout << "Beneficiary's name: " << n.name << endl;
				cout << "Confirm transfer? (Y/N): ";
				cin >> A;
				if (A == 'Y') {
					n.balance += N;
					found.balance -= N;
					found.lastTransaction = -N;
					n.lastTransaction = N;
				}
				else {
					clean();
					transfer_between_accounts();
					break;
				}
			}
			else if (N >= n.balance + 700 && N > 20000 && n.bankID != found.bankID) {
				cout << endl;
				cout << "Beneficiary's name: " << n.name << endl;
				cout << "Confirm transfer? (Y/N): ";
				cin >> A;
				if (A == 'Y') {
					n.balance += N;
					found.balance -= (N + 700);
					found.lastTransaction = -(N + 700);
					n.lastTransaction = N + 700;
				}
				else {
					clean();
					transfer_between_accounts();
					break;
				}
			}
			else if (N >= n.balance + 500 && N > 20000 && n.bankID == found.bankID) {
				cout << endl;
				cout << "Beneficiary's name: " << n.name << endl;
				cout << "Confirm transfer? (Y/N): ";
				cin >> A;
				if (A == 'Y') {
					n.balance += N;
					found.balance -= (N + 500);
					found.lastTransaction = -(N + 500);
					n.lastTransaction = N + 500;
				}
				else {
					clean();
					transfer_between_accounts();
					break;
				}
			}
			else if (N >= n.balance + 200 && N < 20000 && n.bankID != found.bankID) {
				cout << endl;
				cout << "Beneficiary's name: " << n.name << endl;
				cout << "Confirm transfer? (Y/N): ";
				cin >> A;
				if (A == 'Y') {
					n.balance += N;
					found.balance -= (N + 200);
					found.lastTransaction = -(N + 200);
					n.lastTransaction = N + 200;
				}
				else {
					clean();
					transfer_between_accounts();
					break;
				}
			}
			else {
				clean();
				transfer_between_accounts();
				break;
			}
		}
	}
	if (!flag) {
		cout << "There is no such client. Do you want to exit to main menu? (Y/N): ";
		cin >> A;
		if (A == 'Y') {
			clean();
			menu();
		}
		else {
			clean();
			transfer_between_accounts();
		}
	}
}
