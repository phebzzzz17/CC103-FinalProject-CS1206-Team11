#include <iostream>
#include <string>
using namespace std;

void customerMenu();
void adminMenu();
bool adminLogin();

int main() {
    int role;

    do {
        cout << "\n==== SHIP SYSTEM ====\n";
        cout << "1. Customer\n";
        cout << "2. Admin\n";
        cout << "0. Exit\n";
        cout << "Select Role: ";
        cin >> role;

        switch (role) {
            case 1: customerMenu(); break;

            case 2: 
            if (adminLogin()) {
                adminMenu();
            }else {
                cout << "Access denied.\n";
            }
            break;
        }

    } while (role != 0);

    return 0;
}

// ADMIN LOGIN FUNCTION
bool adminLogin() {
    string password;
    const string correctPassword = "admin123"; 
    cout << "\n--- ADMIN LOGIN ---\n";
    cout << "Enter password: ";
    cin >> password;

    if (password == correctPassword) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Wrong password.\n";
        return false;
    }
}

// SAMPLE MENUS
void customerMenu() {
    cout << "\nCustomer Menu (placeholder)\n";
}

void adminMenu() {
    cout << "\nAdmin Menu (secured)\n";
}