#include <iostream>
#include <vector>
#include <limits>
#ifdef _WIN32
#include <cstdlib>
#else
#include <unistd.h>
#endif

using namespace std;

class Account {
private:
    string accountHolder;
    double balance;
    int accountNumber;

public:
    Account(string holder, int accNumber)
        : accountHolder(holder), accountNumber(accNumber), balance(0.0) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    string getHolderName() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "\nDeposit successful. New balance: $" << balance << endl;
        } else {
            cout << "\nInvalid amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "\nInvalid amount!" << endl;
        } else if (amount > balance) {
            cout << "\nInsufficient funds!" << endl;
        } else {
            balance -= amount;
            cout << "\nWithdrawal successful. New balance: $" << balance << endl;
        }
    }

    void display() const {
        cout << "\n-----------------------------\n";
        cout << "Holder Name   : " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance       : $" << balance << endl;
        cout << "-----------------------------\n";
    }

    void modifyAccount(string newName) {
        accountHolder = newName;
        cout << "\nAccount modified successfully.\n";
    }
};

vector<Account> accounts;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseAndReturn() {
    cout << "\nPress Enter to return to main menu...";
    cin.ignore();
    cin.get();
}

Account* findAccount(int number) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == number) {
            return &acc;
        }
    }
    return nullptr;
}

void createAccount() {
    clearScreen();
    cout << "Create New Account\n";
    string name;
    int number;

    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter account number: ";
    cin >> number;

    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == number) {
            cout << "\nAccount number already exists!\n";
            pauseAndReturn();
            return;
        }
    }

    accounts.emplace_back(name, number);
    cout << "\nAccount created successfully!\n";
    pauseAndReturn();
}

void deposit() {
    clearScreen();
    cout << "Deposit Money\n";
    int number;
    double amount;

    cout << "Enter account number: ";
    cin >> number;
    Account* acc = findAccount(number);

    if (!acc) {
        cout << "\nAccount not found.\n";
    } else {
        cout << "Enter amount to deposit: ";
        cin >> amount;
        acc->deposit(amount);
    }

    pauseAndReturn();
}

void withdraw() {
    clearScreen();
    cout << "Withdraw Money\n";
    int number;
    double amount;

    cout << "Enter account number: ";
    cin >> number;
    Account* acc = findAccount(number);

    if (!acc) {
        cout << "\nAccount not found.\n";
    } else {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        acc->withdraw(amount);
    }

    pauseAndReturn();
}

void displayAccount() {
    clearScreen();
    cout << "Account Information\n";
    int number;

    cout << "Enter account number: ";
    cin >> number;
    Account* acc = findAccount(number);

    if (!acc) {
        cout << "\nAccount not found.\n";
    } else {
        acc->display();
    }

    pauseAndReturn();
}

void showAllAccounts() {
    clearScreen();
    cout << "All Accounts\n";

    if (accounts.empty()) {
        cout << "\nNo accounts found.\n";
    } else {
        for (auto &acc : accounts) {
            acc.display();
        }
    }

    pauseAndReturn();
}

void modifyAccount() {
    clearScreen();
    cout << "Modify Account\n";
    int number;

    cout << "Enter account number to modify: ";
    cin >> number;
    Account* acc = findAccount(number);

    if (!acc) {
        cout << "\nAccount not found.\n";
    } else {
        string newName;
        cout << "Enter new account holder name: ";
        cin.ignore();
        getline(cin, newName);
        acc->modifyAccount(newName);
    }

    pauseAndReturn();
}

void deleteAccount() {
    clearScreen();
    cout << "Delete Account\n";
    int number;

    cout << "Enter account number to delete: ";
    cin >> number;

    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountNumber() == number) {
            accounts.erase(it);
            cout << "\nAccount deleted successfully.\n";
            pauseAndReturn();
            return;
        }
    }

    cout << "\nAccount not found.\n";
    pauseAndReturn();
}

int main() {
    int choice;

    while (true) {
        clearScreen();
        cout << "==============================\n";
        cout << "       BANKING SYSTEM MENU     \n";
        cout << "==============================\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Display Account Info\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Modify Account\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Enter a number.\n";
            pauseAndReturn();
            continue;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: displayAccount(); break;
            case 5: showAllAccounts(); break;
            case 6: modifyAccount(); break;
            case 7: deleteAccount(); break;
            case 8:
                clearScreen();
                cout << "\nThank you for using the banking system. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Try again.\n";
                pauseAndReturn();
        }
    }
}
