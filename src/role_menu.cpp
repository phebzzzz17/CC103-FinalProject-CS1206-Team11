#include <iostream>
using namespace std;

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
            case 2: adminMenu(); break;
        }

    } while (role != 0);

    return 0;
}
