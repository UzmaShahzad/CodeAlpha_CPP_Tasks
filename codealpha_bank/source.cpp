#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
public:
    int id;
    string type;
    double amount;
    double balanceAfter;
    string details;

    Transaction(int i, string t, double a, double b, string d) {
        id = i;
        type = t;
        amount = a;
        balanceAfter = b;
        details = d;
    }

    void display() {
        cout << "  #" << id << " | " << type
             << " | Amount: " << amount
             << " | Balance after: " << balanceAfter
             << " | " << details << endl;
    }
};

class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;
    int nextTransactionId;

public:
    Account(int number, double initialBalance) {
        accountNumber = number;
        balance = initialBalance;
        nextTransactionId = 1;
    }

    int getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }

    bool deposit(double amount, string type, string details) {
        if (amount <= 0) {
            cout << "Error: Amount must be greater than 0.\n";
            return false;
        }
        balance = balance + amount;
        history.push_back(Transaction(nextTransactionId, type, amount, balance, details));
        nextTransactionId++;
        return true;
    }

    bool withdraw(double amount, string type, string details) {
        if (amount <= 0) {
            cout << "Error: Amount must be greater than 0.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Error: Insufficient balance.\n";
            return false;
        }
        balance = balance - amount;
        history.push_back(Transaction(nextTransactionId, type, amount, balance, details));
        nextTransactionId++;
        return true;
    }

    void showRecentTransactions(int count) {
        cout << "\n--- Recent Transactions (Account " << accountNumber << ") ---\n";
        if (history.size() == 0) {
            cout << "  No transactions yet.\n";
            return;
        }
        int start = 0;
        if ((int)history.size() > count) {
            start = history.size() - count;
        }
        for (int i = start; i < (int)history.size(); i++) {
            history[i].display();
        }
    }

    void displayInfo() {
        cout << "  Account Number: " << accountNumber
             << " | Balance: " << balance << endl;
    }
};

class Customer {
private:
    int customerId;
    string name;
    vector<Account> accounts;

public:
    Customer(int id, string n) {
        customerId = id;
        name = n;
    }

    int getId() { return customerId; }
    string getName() { return name; }

    void addAccount(int accountNumber, double initialBalance) {
        accounts.push_back(Account(accountNumber, initialBalance));
    }

    Account* findAccount(int accountNumber) {
        for (int i = 0; i < (int)accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accountNumber) {
                return &accounts[i];
            }
        }
        return NULL;
    }

    void displayInfo() {
        cout << "\nCustomer ID: " << customerId << " | Name: " << name << endl;
        if (accounts.size() == 0) {
            cout << "  (No accounts yet)\n";
        }
        for (int i = 0; i < (int)accounts.size(); i++) {
            accounts[i].displayInfo();
        }
    }
};

class Bank {
private:
    vector<Customer> customers;
    int nextCustomerId;
    int nextAccountNumber;

public:
    Bank() {
        nextCustomerId = 1;
        nextAccountNumber = 1001;
    }

    void createCustomer(string name) {
        customers.push_back(Customer(nextCustomerId, name));
        cout << "Customer created! Customer ID = " << nextCustomerId << endl;
        nextCustomerId++;
    }

    Customer* findCustomer(int id) {
        for (int i = 0; i < (int)customers.size(); i++) {
            if (customers[i].getId() == id) {
                return &customers[i];
            }
        }
        return NULL;
    }

    Account* findAccount(int accountNumber) {
        for (int i = 0; i < (int)customers.size(); i++) {
            Account* acc = customers[i].findAccount(accountNumber);
            if (acc != NULL) {
                return acc;
            }
        }
        return NULL;
    }

    void createAccount(int customerId, double initialDeposit) {
        Customer* c = findCustomer(customerId);
        if (c == NULL) {
            cout << "Error: Customer not found.\n";
            return;
        }
        if (initialDeposit < 0) {
            cout << "Error: Initial deposit cannot be negative.\n";
            return;
        }
        c->addAccount(nextAccountNumber, initialDeposit);
        cout << "Account created! Account Number = " << nextAccountNumber << endl;
        nextAccountNumber++;
    }

    void deposit(int accountNumber, double amount) {
        Account* acc = findAccount(accountNumber);
        if (acc == NULL) {
            cout << "Error: Account not found.\n";
            return;
        }
        if (acc->deposit(amount, "Deposit", "Cash deposit")) {
            cout << "Deposit successful. New balance: " << acc->getBalance() << endl;
        }
    }

    void withdraw(int accountNumber, double amount) {
        Account* acc = findAccount(accountNumber);
        if (acc == NULL) {
            cout << "Error: Account not found.\n";
            return;
        }
        if (acc->withdraw(amount, "Withdrawal", "Cash withdrawal")) {
            cout << "Withdrawal successful. New balance: " << acc->getBalance() << endl;
        }
    }

    void transfer(int fromNumber, int toNumber, double amount) {
        if (fromNumber == toNumber) {
            cout << "Error: Cannot transfer to the same account.\n";
            return;
        }
        Account* from = findAccount(fromNumber);
        Account* to = findAccount(toNumber);
        if (from == NULL || to == NULL) {
            cout << "Error: One of the accounts was not found.\n";
            return;
        }
        string outDetails = "To account " + to_string(toNumber);
        if (from->withdraw(amount, "Transfer Out", outDetails)) {
            string inDetails = "From account " + to_string(fromNumber);
            to->deposit(amount, "Transfer In", inDetails);
            cout << "Transfer successful.\n";
            cout << "  Your new balance: " << from->getBalance() << endl;
        }
    }

    void showTransactions(int accountNumber) {
        Account* acc = findAccount(accountNumber);
        if (acc == NULL) {
            cout << "Error: Account not found.\n";
            return;
        }
        acc->showRecentTransactions(5);
    }

    void showCustomerInfo(int customerId) {
        Customer* c = findCustomer(customerId);
        if (c == NULL) {
            cout << "Error: Customer not found.\n";
            return;
        }
        c->displayInfo();
    }
};

int readInt(string message) {
    int value;
    cout << message;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. " << message;
    }
    return value;
}

double readDouble(string message) {
    double value;
    cout << message;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. " << message;
    }
    return value;
}

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n========== BANKING SYSTEM ==========\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer Funds\n";
        cout << "6. View Recent Transactions\n";
        cout << "7. View Customer / Account Info\n";
        cout << "0. Exit\n";
        choice = readInt("Enter your choice: ");

        if (choice == 1) {
            string name;
            cout << "Enter customer name: ";
            cin.ignore(1000, '\n');
            getline(cin, name);
            bank.createCustomer(name);
        }
        else if (choice == 2) {
            int id = readInt("Enter customer ID: ");
            double amount = readDouble("Enter initial deposit: ");
            bank.createAccount(id, amount);
        }
        else if (choice == 3) {
            int acc = readInt("Enter account number: ");
            double amount = readDouble("Enter amount to deposit: ");
            bank.deposit(acc, amount);
        }
        else if (choice == 4) {
            int acc = readInt("Enter account number: ");
            double amount = readDouble("Enter amount to withdraw: ");
            bank.withdraw(acc, amount);
        }
        else if (choice == 5) {
            int from = readInt("Enter YOUR account number: ");
            int to = readInt("Enter RECEIVER account number: ");
            double amount = readDouble("Enter amount to transfer: ");
            bank.transfer(from, to, amount);
        }
        else if (choice == 6) {
            int acc = readInt("Enter account number: ");
            bank.showTransactions(acc);
        }
        else if (choice == 7) {
            int id = readInt("Enter customer ID: ");
            bank.showCustomerInfo(id);
        }
        else if (choice == 0) {
            cout << "Thank you for using the Banking System. Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
