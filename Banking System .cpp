#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Transaction Class
class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        details = d;
    }

    void display() const {
        cout << type << " | Amount: ₹" << amount
             << " | " << details << endl;
    }
};

// Account Class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo) {
        accountNumber = accNo;
        balance = 0.0;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount, "Amount credited");
        cout << "✅ Deposit successful.\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "❌ Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdraw", amount, "Amount debited");
        cout << "✅ Withdrawal successful.\n";
        return true;
    }

    bool transfer(Account &toAccount, double amount) {
        if (amount > balance) {
            cout << "❌ Insufficient balance for transfer.\n";
            return false;
        }

        balance -= amount;
        toAccount.balance += amount;

        transactions.emplace_back("Transfer", amount,
                                  "Transferred to Account " + to_string(toAccount.accountNumber));
        toAccount.transactions.emplace_back("Transfer", amount,
                                  "Received from Account " + to_string(accountNumber));

        cout << "✅ Transfer successful.\n";
        return true;
    }

    void showTransactions() const {
        cout << "\n📄 Transaction History:\n";
        if (transactions.empty()) {
            cout << "No transactions available.\n";
            return;
        }
        for (const auto &t : transactions)
            t.display();
    }

    void displayAccountInfo() const {
        cout << "\n🏦 Account Number: " << accountNumber
             << "\n💰 Balance: ₹" << balance << endl;
    }
};

// Customer Class
class Customer {
private:
    int customerID;
    string name;
    Account account;

public:
    Customer(int id, string n, int accNo)
        : customerID(id), name(n), account(accNo) {}

    int getCustomerID() const {
        return customerID;
    }

    Account &getAccount() {
        return account;
    }

    void displayCustomerInfo() const {
        cout << "\n👤 Customer ID: " << customerID
             << "\nName: " << name << endl;
        account.displayAccountInfo();
    }
};

int main() {
    Customer c1(101, "Harsh Tomar", 1001);
    Customer c2(102, "Amit Kumar", 1002);

    int choice;
    double amount;

    do {
        cout << "\n===== Banking System Menu =====\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer Funds\n";
        cout << "4. View Account Info\n";
        cout << "5. View Transactions\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter deposit amount: ";
                cin >> amount;
                c1.getAccount().deposit(amount);
                break;

            case 2:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                c1.getAccount().withdraw(amount);
                break;

            case 3:
                cout << "Enter transfer amount: ";
                cin >> amount;
                c1.getAccount().transfer(c2.getAccount(), amount);
                break;

            case 4:
                c1.displayCustomerInfo();
                break;

            case 5:
                c1.getAccount().showTransactions();
                break;

            case 6:
                cout << "👋 Thank you for using the Banking System.\n";
                break;

            default:
                cout << "❌ Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
