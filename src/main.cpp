#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// ANSI color codes
#define BLUE "\033[34m"
#define RESET "\033[0m"

// Function declaration
void roleMenu();

// ===================== LOADING BAR =====================
void loadingBar() {
    cout << "\nLoading system:\n\n[";

    for (int i = 0; i < 20; i++) {
        cout << BLUE << "█" << RESET;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100)); // faster (100ms)
    }

    cout << "] 100%\n";
}

// ===================== ROLE MENU (temporary) =====================
void roleMenu() {
    cout << "\nRole Menu loaded...\n";
}

// ===================== MAIN =====================
int main() {

    cout << "\n========================================\n";
    cout << "        🚢 SAILCHECK SYSTEM 🌊\n";
    cout << "        Port Booking Platform\n";
    cout << "========================================\n";

    cout << "\nInitializing system... ";

    for (int i = 0; i < 3; i++) {
        cout << "🛥️ ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300)); // faster here too
    }

    cout << "\n";

    loadingBar();

    cout << "\n✅ System ready!\n";
    cout << "👉 Please log in to continue.\n";

    roleMenu();

    return 0;
}
