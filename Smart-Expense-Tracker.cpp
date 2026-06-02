#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Class representing a single financial transaction
class Transaction {
private:
    string category;
    double amount;
    string type; // "Income" or "Expense"

public:
    Transaction(string cat, double amt, string t) : category(cat), amount(amt), type(t) {}

    void displayTransaction() const {
        cout << left << setw(15) << type 
             << setw(20) << category 
             << "$" << fixed << setprecision(2) << amount << endl;
    }
};

// Class managing the user's wallet and budget
class Wallet {
private:
    double balance;
    double budgetLimit;
    double totalExpenses;
    vector<Transaction> history;
    string password;

public:
    Wallet(string pass) : balance(0.0), budgetLimit(0.0), totalExpenses(0.0), password(pass) {}

    bool verifyPassword(const string& inputPass) const {
        return password == inputPass;
    }

    void setBudgetLimit(double limit) {
        if (limit >= 0) {
            budgetLimit = limit;
            cout << "\n[Success] Budget limit set to $" << budgetLimit << "\n";
        } else {
            cout << "\n[Error] Invalid budget limit.\n";
        }
    }

    void addIncome(double amount, string category) {
        if (amount > 0) {
            balance += amount;
            history.push_back(Transaction(category, amount, "Income"));
            cout << "\n[Success] $" << amount << " added to " << category << ".\n";
        } else {
            cout << "\n[Error] Amount must be positive.\n";
        }
    }

    void addExpense(double amount, string category) {
        if (amount <= 0) {
            cout << "\n[Error] Amount must be positive.\n";
            return;
        }

        if (amount > balance) {
            cout << "\n[Warning] Transaction declined! Insufficient balance.\n";
            return;
        }

        balance -= amount;
        totalExpenses += amount;
        history.push_back(Transaction(category, amount, "Expense"));
        cout << "\n[Success] $" << amount << " spent on " << category << ".\n";

        // Check if total expenses exceeded the budget limit
        if (budgetLimit > 0 && totalExpenses > budgetLimit) {
            cout << "\n⚠️ [ALERT] You have exceeded your budget limit of $" << budgetLimit << "!\n";
        }
    }

    void displaySummary() const {
        cout << "\n================ ACCOUNT SUMMARY ================\n";
        cout << "Current Balance : $" << fixed << setprecision(2) << balance << endl;
        cout << "Total Expenses  : $" << totalExpenses << endl;
        cout << "Budget Limit    : $" << budgetLimit << endl;
        if (budgetLimit > 0) {
            cout << "Remaining Budget: $" << (budgetLimit - totalExpenses) << endl;
        }
        cout << "=================================================\n";
    }

    void displayHistory() const {
        if (history.empty()) {
            cout << "\n[Info] No transactions recorded yet.\n";
            return;
        }

        cout << "\n================ TRANSACTION HISTORY ================\n";
        cout << left << setw(15) << "Type" << setw(20) << "Category" << "Amount\n";
        cout << "-----------------------------------------------------\n";
        for (const auto& tx : history) {
            tx.displayTransaction();
        }
        cout << "=====================================================\n";
    }
};

int main() {
    cout << "--- Welcome to Smart Expense Tracker Setup ---\n";
    cout << "Set a password for your digital wallet: ";
    string pass;
    cin >> pass;

    Wallet myWallet(pass);
    
    cout << "\nWallet initialized successfully!\n";
    
    // Security Check
    cout << "\nEnter password to log in: ";
    string loginPass;
    cin >> loginPass;

    if (!myWallet.verifyPassword(loginPass)) {
        cout << "\n[Access Denied] Incorrect password. Exiting program.\n";
        return 0;
    }

    int choice;
    do {
        cout << "\n--- SMART EXPENSE TRACKER MENU ---\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. Set Monthly Budget Limit\n";
        cout << "4. View Account Summary\n";
        cout << "5. View Transaction History\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double amt;
                string cat;
                cout << "Enter income amount: $";
                cin >> amt;
                cout << "Enter income source/category (e.g., Salary, Freelancing): ";
                cin >> cat;
                myWallet.addIncome(amt, cat);
                break;
            }
            case 2: {
                double amt;
                string cat;
                cout << "Enter expense amount: $";
                cin >> amt;
                cout << "Enter expense category (e.g., Food, Transport, Rent): ";
                cin >> cat;
                myWallet.addExpense(amt, cat);
                break;
            }
            case 3: {
                double limit;
                cout << "Enter your maximum budget limit: $";
                cin >> limit;
                myWallet.setBudgetLimit(limit);
                break;
            }
            case 4:
                myWallet.displaySummary();
                break;
            case 5:
                myWallet.displayHistory();
                break;
            case 6:
                cout << "\nThank you for using Smart Expense Tracker. Financial discipline is freedom!\n";
                break;
            default:
                cout << "\n[Error] Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}