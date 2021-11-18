#include <bits/stdc++.h>
using namespace std;


void clean(){
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) //Не знал, на какой ОС будет запуск, поэтому сделал проверку
	system("cls");
	#else
	system("clean");
	#endif
}
class Client{
public:
	int bankID;
	string name;
	int cardNumber;
	int PIN;
	int balance;
	int lastTransaction;
	
	Client(){}
	Client(int a, string b, int c, int d, int e, int f){
		bankID = a;
		name = b;
		cardNumber = c;
		PIN = d;
		balance = e;
		lastTransaction = f;
	}
}; 

vector<Client> clients;
Client client(1, "", 1, 1, 1, 1);
Client found();

void read_record()
{
  
    // File pointer
    fstream fin;
  
    // Open an existing file
    fin.open("database.csv", ios::in);
  
    // Get the roll number
    // of which the data is required
    //int rollnum, roll2, count = 0;
    //cout << "Enter the roll number "
    //     << "of the student to display details: ";
    //cin >> rollnum;
  
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
    while (fin >> temp) {
  
        row.clear();
  
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);
  
        // used for breaking words
        stringstream s(line);
  
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
  
            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
  
        // convert string to integer for comparision
        //roll2 = stoi(row[0]);
  
        // Compare the roll number
        //if (roll2 == rollnum) {
  
            // Print the found data
            //count = 1;
            //atoi( str.c_str() )
            //QString::fromStdString(str).toInt(&ok)
            
            	
            client.bankID = stoi(row[0]);
            client.name = stoi(row[1]);
            client.cardNumber =  stoi(row[2]);
            client.PIN = stoi(row[3]);
            client.balance = stoi(row[4]);
            client.lastTransaction =  stoi(row[5]);
            clients.push_back(client);
       
            //break;
        //}
    }
    
}

void withdraw_cash();
void deposit_cash();
void modify_pin_code();
void show_balance();
void transfer_between_accounts();

void start(){
	int N;
	while(true){
		cout << "Card number (6 digits): ";
		cin >> N;
		for (int n : clients) {
        	if(n.cardNumber == N){
        		cout << "PIN code (4 digits): ";
        		cin >> N;
        		if(n.PIN == N){
        			found = n;
        			menu();
        			break;
        		}
        		else{
        			clean();
        			cout << "\tWelcom to the Bank of MixChopLove\n"<<endl;
        			cout << "The card number or PIN code is incorrect. Try again!" << endl;
        			start();
        			break;
        		}
        	}
    	}
    	clean();
    	cout << "\tWelcom to the Bank of MixChopLove\n"<<endl;
    	cout << "The card number or PIN code is incorrect. Try again!" << endl;
    	start();
    	break;
	}
}

void menu(){
	int N;
	cout << "\tThe Bank of MixChopLove\n"<<endl;
	cout << "Select one of the following options:\n"<<endl;
	cout << "1. Withdraw Cash\t";
	cout << "2. Deposit Cash\n";
	cout << "3. Modify PIN Code\t";
	cout << "4. Show Balance\n";
	cout << "5. Transfer Between Accounts\t";
	cout << "6. End Session\n"<<endl;
	cout << "Enter option number: ";
	cin >> N;
	switch(N){
		case 1:
			clean();
			withdraw_cash();
			break;
		case 2:
			clean();
			deposit_cash();
			break;
		case 3:
			clean();
			modify_pin_code();
			break;
		case 4:
			clean();
			show_balance();
			break;
		case 5:
			clean();
			transfer_between_accounts();
			break;
		case 6:
			exit(0);
		default:
			clean();
			menu();
			break;
	}
}

int main(){
	read_record();
	start();
	
	/*int A;
	while(true){
		cout << "Ener PIN: ";
		cin >> A;
		if(A != 1111){
			clean();
			cout << "Wrong PIN!" << endl;
		}
		else{
			break;
		}
	}
	*/
}

void withdraw_cash(){
	int N;	
	cout << "\tThe Bank of MixChopLove\n"<<endl;
	cout << "Current balance: " << found.balance << " KZT";
	char A;
	while(true){
		cout << "Enter amount of withdraw: ";
		cin >> N;
		if(N <= sum){
			sum -= N;
			cout << "Cash withdrawn succesfully!"<<endl;
			cout << "Remaining balance: " << sum;
			cout << "Would you like to return to main menu?(Y/N)";
			cin >> A;
			if(A == 'Y'){
				clean();
				menu();
			}
			else{
				exit(0);
			}
		}
		else{
			clean();
		
		}
	}
}

void deposit_cash(){
	cout << "\tThe Bank of MixChopLove\n"<<endl;
}

void modify_pin_code(){
	cout << "\tThe Bank of MixChopLove\n"<<endl;
}

void show_balance(){
	cout << "\tThe Bank of MixChopLove\n"<<endl;
}

void transfer_between_accounts(){
	cout << "\tThe Bank of MixChopLove\n"<<endl;
}
