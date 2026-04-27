#include <iostream>
#include <string>
using namespace std;

// ===== Function Declarations =====
void enqueue();
void dequeue();
void displayQueue();

void printHeader(const string& title);
void showTrips();

bool adminLogin();
void customerMenu();
void adminMenu();
void roleMenu();

// ===================== UI HELPERS =====================
void printHeader(const string& title) {
    cout << "\n=================================\n";
    cout << "   " << title << "\n";
    cout << "=================================\n";
}

void showTrips() {
    cout << "\n🛳 Available Trips:\n";
    cout << "1. Batangas → Mindoro | 08:00 AM\n";
    cout << "2. Batangas → Mindoro | 12:00 PM\n";
    cout << "3. Batangas → Mindoro | 04:00 PM\n";
}

// ===================== ADMIN LOGIN =====================
bool adminLogin() {
    string password;
    const string correctPassword = "admin123";
    int attempts = 3;

    printHeader("🔐 ADMIN LOGIN");

    while (attempts--) {
        cout << "Enter password: ";
        cin >> password;

        if (password == correctPassword) {
            cout << "\n✅ Login successful. Welcome Admin!\n";
            return true;
        } else {
            cout << "❌ Wrong password. Attempts left: " << attempts << "\n";
        }
    }

    cout << "\n🚫 Access denied.\n";
    return false;
}

// ===================== CUSTOMER MENU =====================
void customerMenu() {
    int choice;

    do {
        printHeader("👤 CUSTOMER MENU 🌊");

        cout << "1. 📝 Book Ticket\n";
        cout << "2. 🔍 Search Available Trips\n";
        cout << "3. ❌ Cancel Ticket\n";
        cout << "4. 📊 View Booking Status\n";
        cout << "5. 🎫 Display Booking Ticket\n";
        cout << "0. 🔙 Back\n";
        cout << "---------------------------------\n";
        cout << "👉 Select: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "⚠ Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                enqueue();
                break;

            case 2:
                showTrips();
                break;

            case 3:
                cout << "\n❌ Cancellation feature coming soon...\n";
                break;

            case 4: // fallthrough
            case 5:
                displayQueue();
                break;

            case 0:
                break;

            default:
                cout << "\n⚠ Invalid choice.\n";
        }

    } while (choice != 0);
}

// ===================== ADMIN MENU =====================
void adminMenu() {
    int choice;

    do {
        printHeader("🛠 ADMIN MENU 🌊");

        cout << "1. 🗂 Manage Trips\n";
        cout << "2. 📋 View All Bookings\n";
        cout << "3. 📡 Monitor Queue\n";
        cout << "4. 🚢 Serve Passenger\n";
        cout << "5. 🔍 Search / Sort Records\n";
        cout << "6. ⚙ Handle Cancellations\n";
        cout << "0. 🔙 Back\n";
        cout << "---------------------------------\n";
        cout << "👉 Select: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "⚠ Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 2:
            case 3:
                displayQueue();
                break;

            case 4:
                dequeue();
                break;

            case 5:
                cout << "\n🔍 Search/Sort coming soon...\n";
                break;

            case 6:
                cout << "\n⚙ Cancellation system coming soon...\n";
                break;

            case 0:
                break;

            default:
                cout << "\n⚠ Invalid choice.\n";
        }

    } while (choice != 0);
}

// ===================== ROLE MENU =====================
void roleMenu() {
    int role;

    do {
        printHeader("🚢 SAILCHECK SYSTEM 🌊");

        cout << "1. 👤 Customer\n";
        cout << "2. 🛠 Admin\n";
        cout << "0. ❌ Exit\n";
        cout << "---------------------------------\n";
        cout << "👉 Select Role: ";

        if (!(cin >> role)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "⚠ Invalid input. Try again.\n";
            continue;
        }

        switch (role) {
            case 1:
                customerMenu();
                break;

            case 2:
                if (adminLogin()) {
                    adminMenu();
                }
                break;

            case 0:
                cout << "\n👋 Exiting system...\n";
                break;

            default:
                cout << "\n⚠ Invalid choice.\n";
        }

    } while (role != 0);
}

// ===================== MAIN =====================
int main() {
    roleMenu();
    return 0;
}
