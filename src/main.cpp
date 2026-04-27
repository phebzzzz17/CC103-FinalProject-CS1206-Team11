#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void roleMenu();

// ANSI color codes
#define BLUE "\033[34m"
#define RESET "\033[0m"

// ===================== LOADING BAR =====================
void loadingBar() {
    cout << "\nLoading system:\n\n[";

    for (int i = 0; i < 20; i++) {
        cout << BLUE << "█" << RESET;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "] 100%\n";
}

// ===================== MAIN =====================
int main() {

    cout << "\n========================================\n";
    cout << "        🚢 SAILCHECK SYSTEM 🌊\n";
    cout << "        Port Booking Platform\n";
    cout << "========================================\n";

    // Boat animation
    cout << "\nInitializing system... ";
    for (int i = 0; i < 3; i++) {
        cout << "🛥️ ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(400));
    }
    cout << "\n";

    // Blue loading bar
    loadingBar();

    cout << "\n✅ System ready!\n";
    cout << "👉 Please log in to continue.\n";

    roleMenu();

    return 0;
}
