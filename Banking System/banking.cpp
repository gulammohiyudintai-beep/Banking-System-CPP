
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int number, string name, double amount) {
        accountNumber = number;
        accountHolderName = name;
        balance = amount;
    }

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance = balance + amount;
            cout << "Amount Deposited Successfully!\n";
        } else {
            cout << "Invalid Amount!\n";
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance = balance - amount;
            cout << "Amount Withdrawn Successfully!\n";
        } else {
            cout << "Insufficient Balance or Invalid Amount!\n";
        }
    }

    double getBalance() {
        return balance;
    }

    
    void addInterest(double amount) {
        balance = balance + amount;
    }

    virtual void calculateInterest() {
        cout << "Interest calculation not available.\n";
    }

    virtual void displayAccountInfo() {
        cout << "\nAccount Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolderName << endl;
        cout << "Balance        : " << balance << endl;
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int n, string name, double b, double rate)
        : BankAccount(n, name, b) {
        interestRate = rate;
    }

    void calculateInterest() override {
        double interest = getBalance() * interestRate / 100;
        addInterest(interest);
        cout << "Savings Interest: " << interest << endl;
    }

    void displayAccountInfo() override {
        cout << "\n--- Savings Account ---\n";
        BankAccount::displayAccountInfo();
        cout << "Interest Rate  : " << interestRate << "%\n";
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(int n, string name, double b, double limit)
        : BankAccount(n, name, b) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
        if (amount > 0 && amount <= getBalance() + overdraftLimit) {
            double newBalance = getBalance() - amount;

            if (amount <= getBalance()) {
                BankAccount::withdraw(amount);
            } else {
                double extra = amount - getBalance();
                BankAccount::withdraw(getBalance());
                cout << "Overdraft Used: " << extra << endl;
                BankAccount::deposit(0);
                setOverdraftBalance(newBalance);
            }
        } else {
            cout << "Overdraft Limit Exceeded!\n";
        }
    }

    void setOverdraftBalance(double amount) {
        if (getBalance() > amount) {
            BankAccount::withdraw(getBalance() - amount);
        } else if (getBalance() < amount) {
            BankAccount::deposit(amount - getBalance());
        }
    }

    bool checkOverdraft(double amount) {
        return amount > getBalance() &&
               amount <= getBalance() + overdraftLimit;
    }

    void displayAccountInfo() override {
        cout << "\n--- Checking Account ---\n";
        BankAccount::displayAccountInfo();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};


class FixedDepositAccount : public BankAccount {
private:
    int term;

public:
    FixedDepositAccount(int n, string name, double b, int months)
        : BankAccount(n, name, b) {
        term = months;
    }

    void calculateInterest() override {
        double rate = 6.0;
        double interest = getBalance() * rate / 100 * term / 12;
        addInterest(interest);
        cout << "Fixed Deposit Interest: " << interest << endl;
    }

    void displayAccountInfo() override {
        cout << "\n--- Fixed Deposit Account ---\n";
        BankAccount::displayAccountInfo();
        cout << "Term           : " << term << " months\n";
    }
};

int main() {
    SavingsAccount savings(101, "Mohiyudin", 10000, 5);
    CheckingAccount checking(102, "Aarzuu", 5000, 2000);
    FixedDepositAccount fixed(103, "Rumesha", 20000, 12);

    BankAccount* accounts[3] = {&savings, &checking, &fixed};

    int choice, type;
    double amount;

    do {
        cout << "\n===== BANKING SYSTEM =====\n";
        cout << "1. Display All Accounts\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Calculate Interest\n";
        cout << "5. Check Balance\n";
        cout << "6. Exit\n";
       cout << "Enter Choice (1-6): ";
        if (!(cin >> choice)) {
            cout << "Please enter numbers only!" << endl;
            return 0;
        }

if (choice < 1 || choice > 6) {
    cout << "Invalid Choice!" << endl;
    continue;
}

        if (choice >= 1 && choice <= 5) {
            cout << "Select Account:\n";
            cout << "1. Savings Account\n";
            cout << "2. Checking Account\n";
            cout << "3. Fixed Deposit Account\n";
            cout << "Enter Account Type: ";
            cin >> type;

            if (type < 1 || type > 3) {
                cout << "Invalid Account Type!\n";
                continue;
            }

            BankAccount* account = accounts[type - 1];

            switch (choice) {
                case 1:
                    account->displayAccountInfo();
                    break;

                case 2:
                    cout << "Enter Deposit Amount: ";
                    cin >> amount;
                    account->deposit(amount);
                    break;

                case 3:
                    cout << "Enter Withdrawal Amount: ";
                    cin >> amount;
                    account->withdraw(amount);
                    break;

                case 4:
                    account->calculateInterest();
                    break;

                case 5:
                    cout << "Current Balance: "
                         << account->getBalance() << endl;
                    break;
            }
        } else if (choice != 6) {
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    cout << "Thank you for using Banking System!\n";

    return 0;
}
