#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Transaction
{
public:
string type;
double amount;
string dateTime;
string sourceAccount;
string destinationAccount;

Transaction(string t, double a, string src = "", string dest = "")
{
type = t;
amount = a;
sourceAccount = src;
destinationAccount = dest;
time_t now = time(0);
dateTime = ctime(&now);
dateTime.pop_back();
}
void displayTransaction()
{
cout << "[" << dateTime << "]" << type << ": " << amount;
if(!sourceAccount.empty())
cout << " From: " << sourceAccount;
if(!destinationAccount.empty())
cout << " To: "  <<destinationAccount;
cout << endl;
}
};



class Account
{
private:
string accountNumber;
string accountType;
double balance;
vector<Transaction> transactions;

public:
Account(string accNum, string accType, double initialBalance = 0.0)
{
accountNumber = accNum;
accountType = accType;
balance = initialBalance;
}
string getAccountNumber()
{
return accountNumber;
}

double getBalance()
{
return balance;
}

void deposit(double amount)
{
if(amount <= 0) 
{
cout << "Amount must be positive!" << endl;
return;
}
balance += amount;
transactions.push_back(Transaction("Deposit", amount));
cout << "Deposited " << amount << ". New Balance: " << balance << endl;
}

void withdraw(double amount)
{
if(amount <= 0) 
{
cout << "Amount must be positive!" << endl;
return;
}
if(amount > balance)
{
cout << "Insufficient balance! " << endl;
return;
}
balance -= amount;
transactions.push_back(Transaction("Withdrawal", amount));
cout << "Withdrawal " << amount << ". New Balance: " << balance << endl;
}

void transferFunds(Account &toAccount, double amount)
{
if(amount <= 0)
{
cout << "Amount must be positive! " << endl;
return;
}
balance -= amount;
toAccount.balance += amount;
transactions.push_back(Transaction("Transfer", amount, accountNumber, toAccount.getAccountNumber()));
toAccount.transactions.push_back(Transaction("Received", amount, accountNumber, toAccount.getAccountNumber()));
cout << "Transferred " << amount << " to Account " << toAccount.getAccountNumber() << endl;
cout << "Your new balance: " << balance << endl;
}

void viewTransactions() 
{
if (transactions.empty()) 
{
cout << "No transactions yet." << endl;
return;
}
cout << "Transaction History for Account " << accountNumber << ":" << endl;
for (auto &t : transactions)
t.displayTransaction();
}

void displayAccountInfo() 
{
cout << "Account Number: " << accountNumber << endl;
cout << "Account Type: " << accountType << endl;
cout << "Balance: " << balance << endl;
viewTransactions();
}
};



class Customer
{
private:
string customerID;
string name;
string email;
vector<Account> accounts;

public:
Customer(string id, string n, string e)
{
customerID = id;
name = n;
email = e;
}
 void createAccount(string accNum, string accType, double initialBalance =0.0)
{
accounts.push_back(Account(accNum, accType, initialBalance));
cout << "Account created successfully.." << endl;
}

Account *getAccount(string accNum)
{
for(auto &acc : accounts)
{
if(acc.getAccountNumber() == accNum)
return &acc;
}
return nullptr;
}

void viewAccounts() 
{
cout << "Accounts of " << name << ":" << endl;
for (auto &acc : accounts)
acc.displayAccountInfo();
}
};



int main() 
{
cout << "=== Welcome to Simple Banking System ===" << endl;

string customerID, name, email;
cout << "Enter Customer ID: ";
cin >> customerID;
cout << "Enter Customer Name: ";
cin.ignore();
getline(cin, name);
cout << "Enter Email: ";
cin >> email;

Customer customer(customerID, name, email);
cout << "Customer created successfully!" << endl;

int choice;
do
{
cout << "\n----- MENU -----" << endl;
cout << "1. Create Account" << endl;
cout << "2. Deposit" << endl;
cout << "3. Withdraw" << endl;
cout << "4. Transfer Funds" << endl;
cout << "5. View Transactions" << endl;
cout << "6. View Account Info" << endl;
cout << "7. Exit" << endl;
cout << "Enter your choice: ";
cin >> choice;

if (choice == 1) 
{
string accNum, accType;
double balance;
cout << "Enter Account Number: ";
cin >> accNum;
cout << "Enter Account Type (Savings/Checking): ";
cin >> accType;
cout << "Enter Initial Balance: ";
cin >> balance;
customer.createAccount(accNum, accType, balance);
}

else if (choice == 2) 
{
string accNum;
double amount;
cout << "Enter Account Number: ";
cin >> accNum;
Account* acc = customer.getAccount(accNum);
if (acc) 
{
cout << "Enter amount to deposit: ";
cin >> amount;
acc->deposit(amount);
} 
else 
{
cout << "Account not found!" << endl;
}
}

else if (choice == 3) 
{
string accNum;
double amount;
cout << "Enter Account Number: ";
cin >> accNum;
Account* acc = customer.getAccount(accNum);
if (acc) 
{
cout << "Enter amount to withdraw: ";
cin >> amount;
acc->withdraw(amount);
} 
else 
{
cout << "Account not found!" << endl;
}
}

else if (choice == 4) 
{
string fromAccNum, toAccNum;
double amount;
cout << "Enter Source Account Number: ";
cin >> fromAccNum;
cout << "Enter Destination Account Number: ";
cin >> toAccNum;
cout << "Enter amount to transfer: ";
cin >> amount;

Account* fromAcc = customer.getAccount(fromAccNum);
Account* toAcc = customer.getAccount(toAccNum);

if (fromAcc && toAcc) 
{
fromAcc->transferFunds(*toAcc, amount);
} 
else 
{
cout << "Invalid account number(s)!" << endl;
}
}

else if (choice == 5) 
{
string accNum;
cout << "Enter Account Number: ";
cin >> accNum;
Account* acc = customer.getAccount(accNum);
if (acc) 
{
acc->viewTransactions();
}
else 
{
cout << "Account not found!" << endl;
}
}

else if (choice == 6) 
{
customer.viewAccounts();
}

else if (choice == 7) 
{
cout << "Exiting... Thank you for using the system!" << endl;
}

else 
{
cout << "Invalid choice! Try again." << endl;
}
} 
while (choice != 7);
return 0;
}
