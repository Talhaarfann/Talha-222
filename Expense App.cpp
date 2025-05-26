#include <iostream>
using namespace std;

struct Expense {
    int id;
    string name;
    float price;
    string date;
    Expense* next;

    Expense(int i, string n, float p, string d) {
        id = i;
        name = n;
        price = p;
        date = d;
        next = NULL;
    }
};

class ExpenseList {
public:
    Expense* head;

    ExpenseList() {
        head = NULL;
    }

    void addExpense(int id, string name, float price, string date) {
        Expense* newExpense = new Expense(id, name, price, date);
        if (head == NULL) {
            head = newExpense;
        } else {
            Expense* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newExpense;
        }
    }

    void viewExpenses() {
        Expense* temp = head;
        if (temp == NULL) {
            cout << "No expenses in this list.\n";
            return;
        }
        while (temp != NULL) {
            cout << "ID: " << temp->id << ", Name: " << temp->name
                 << ", Price: " << temp->price << ", Date: " << temp->date << endl;
            temp = temp->next;
        }
    }

    void reportMonthly(string month) {
        Expense* temp = head;
        bool found = false;
        while (temp != NULL) {
            if (temp->date.substr(0, 7) == month) {
                cout << "ID: " << temp->id << ", Name: " << temp->name
                     << ", Price: " << temp->price << ", Date: " << temp->date << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No expenses found for this month.\n";
        }
    }

    void reportWeekly(string startDate, string endDate) {
        Expense* temp = head;
        bool found = false;
        while (temp != NULL) {
            if (temp->date >= startDate && temp->date <= endDate) {
                cout << "ID: " << temp->id << ", Name: " << temp->name
                     << ", Price: " << temp->price << ", Date: " << temp->date << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No expenses found in this week.\n";
        }
    }
};

struct MasterNode {
    ExpenseList* list;
    MasterNode* next;

    MasterNode(ExpenseList* l) {
        list = l;
        next = NULL;
    }
};

class MasterList {
public:
    MasterNode* head;

    MasterList() {
        head = NULL;
    }

    void addExpenseList(ExpenseList* list) {
        MasterNode* newNode = new MasterNode(list);
        if (head == NULL) {
            head = newNode;
        } else {
            MasterNode* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void viewAllExpenseLists() {
        MasterNode* temp = head;
        int count = 1;
        if (!temp) {
            cout << "No expense lists found.\n";
            return;
        }
        while (temp != NULL) {
            cout << "\n--- Expense List #" << count << " ---\n";
            temp->list->viewExpenses();
            temp = temp->next;
            count++;
        }
    }

    ExpenseList* getListByIndex(int index) {
        MasterNode* temp = head;
        int count = 1;
        while (temp != NULL) {
            if (count == index) return temp->list;
            temp = temp->next;
            count++;
        }
        return NULL;
    }

    int countLists() {
        int count = 0;
        MasterNode* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    MasterList master;
    int choice;

    while (true) {
        cout << "\n=== Expense Tracker Menu ===\n";
        cout << "1. Create New Expense List\n";
        cout << "2. Add Expense to a List\n";
        cout << "3. View All Expense Lists\n";
        cout << "4. Generate Monthly Report\n";
        cout << "5. Generate Weekly Report\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            ExpenseList* newList = new ExpenseList();
            master.addExpenseList(newList);
            cout << "New expense list created (List #" << master.countLists() << ").\n";
        }

        else if (choice == 2) {
            int total = master.countLists();
            if (total == 0) {
                cout << "No expense list found. Create one first.\n";
                continue;
            }

            int listNum;
            cout << "Enter list number (1 to " << total << "): ";
            cin >> listNum;
            ExpenseList* targetList = master.getListByIndex(listNum);
            if (!targetList) {
                cout << "Invalid list number.\n";
                continue;
            }

            int id;
            string name, date;
            float price;

            cout << "Enter Expense ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;

            targetList->addExpense(id, name, price, date);
            cout << "Expense added to List #" << listNum << ".\n";
        }

        else if (choice == 3) {
            master.viewAllExpenseLists();
        }

        else if (choice == 4) {
            string month;
            cout << "Enter month (YYYY-MM): ";
            cin >> month;

            MasterNode* temp = master.head;
            int count = 1;
            while (temp != NULL) {
                cout << "\n--- Monthly Report for List #" << count << " ---\n";
                temp->list->reportMonthly(month);
                temp = temp->next;
                count++;
            }
        }

        else if (choice == 5) {
            string startDate, endDate;
            cout << "Enter start date (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Enter end date (YYYY-MM-DD): ";
            cin >> endDate;

            MasterNode* temp = master.head;
            int count = 1;
            while (temp != NULL) {
                cout << "\n--- Weekly Report for List #" << count << " ---\n";
                temp->list->reportWeekly(startDate, endDate);
                temp = temp->next;
                count++;
            }
        }

        else if (choice == 6) {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
