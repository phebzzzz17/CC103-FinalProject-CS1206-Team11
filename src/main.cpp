#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


int main() {

    void roleMenu();

    // ===================== WELCOME DESIGN =====================
    cout << "\n=================================\n";
    cout << "   🚢 WELCOME TO SAILCHECK🌊\n";
    cout << "   Port Booking System\n";
    cout << "=================================\n";

    cout << "Loading system...\n";

    // loading animation
    for (int i = 0; i < 3; i++) {
        cout << "🛥️ ";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "\nSystem ready! Please log in to continue.\n";

    // go to role menu
    roleMenu();

    return 0;
}