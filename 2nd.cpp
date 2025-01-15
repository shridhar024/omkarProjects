#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Expense {
public:
    string category;
    double amount;
    string date;

    // Constructor without initializer list and without using `this` keyword
    Expense(const string &cat, double amt, const string &dt) {
        category = cat;
        amount = amt;
        date = dt;
    }
};

class ExpenseTracker {
private:
    vector<Expense> expenses;

    void saveToFile() {
        ofstream file("expenses.txt");
        for (const auto &expense : expenses) {
            file << expense.category << "," << expense.amount << "," << expense.date << "\n";
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("expenses.txt");
        if (!file.is_open())
            return;

        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find_last_of(",");
            if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
                string cat = line.substr(0, pos1);
                double amt = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
                string dt = line.substr(pos2 + 1);
                expenses.emplace_back(cat, amt, dt);
            }
        }
        file.close();
    }

public:
    ExpenseTracker() {
        loadFromFile();
    }

    ~ExpenseTracker() {
        saveToFile();
    }

    void addExpense(const string &cat, double amt, const string &dt) {
        expenses.emplace_back(cat, amt, dt);
        cout << "Expense added successfully!\n";
    }

    void viewExpenses() const {
        if (expenses.empty()) {
            cout << "No expenses recorded.\n";
            return;
        }

        cout << setw(15) << "Category" << setw(10) << "Amount" << setw(15) << "Date" << "\n";
        cout << string(40, '-') << "\n";

        for (const auto &expense : expenses) {
            cout << setw(15) << expense.category
                 << setw(10) << expense.amount
                 << setw(15) << expense.date << "\n";
        }
    }

    void viewByCategory(const string &cat) const {
        double total = 0;
        cout << "Expenses for category: " << cat << "\n";

        for (const auto &expense : expenses) {
            if (expense.category == cat) {
                cout << setw(10) << expense.amount << " on " << expense.date << "\n";
                total += expense.amount;
            }
        }

        cout << "Total: " << total << "\n";
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\nExpense Tracker\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. View Expenses by Category\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string cat, dt;
            double amt;
            cout << "Enter category: ";
            cin >> cat;
            cout << "Enter amount: ";
            cin >> amt;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> dt;
            tracker.addExpense(cat, amt, dt);
            break;
        }
        case 2:
            tracker.viewExpenses();
            break;
        case 3: {
            string cat;
            cout << "Enter category: ";
            cin >> cat;
            tracker.viewByCategory(cat);
            break;
        }
        case 4:
            cout << "Exiting Expense Tracker.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
