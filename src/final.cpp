#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include <cstdlib>
#include <locale>
using namespace std;

// ===================== PASSENGER STRUCT =====================
struct Passenger {
    int id;
    string name;
    string trip;
    string tripKey;
    bool isPriority;
    int age;
    string category;
    string assignedSeat;
    bool operator<(const Passenger& other) const {
        return name < other.name;
    }
};

// ===================== PRIORITY =====================
struct ComparePriority {
    bool operator()(Passenger a, Passenger b) {
        return a.isPriority < b.isPriority;
    }
};

// ===================== SEAT STRUCT =====================
struct Seat {
    string id;
    bool occupied;
};

// ===================== DATA =====================
queue<Passenger> regularQueue;
priority_queue<Passenger, vector<Passenger>, ComparePriority> priorityQueue;
stack<string> transactionStack;
vector<Passenger> allBookings;
vector<Passenger> confirmedPassengers;
map<string, vector<Passenger>> tripBookings;
map<string, int> tripSeats;
int ticketCounter = 1000;
double baseFare = 500;

// ===================== PER-TRIP SEAT STORAGE =====================
map<string, vector<Seat>> tripNormalOrder;
map<string, vector<Seat>> tripPriorityOrder;

const int ROWS = 5;
const int COLS = 4;

// ===================== ANIMATION HELPERS =====================
void loadingAnimation(string text) {
    cout << text;
    for (int i = 0; i < 5; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    cout << endl;
}

void progressBar() {
    cout << "[";
    for (int i = 0; i < 20; i++) {
        cout << "■";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(40));
    }
    cout << "] Done!\n";
}

// ===================== SPINNER LINE =====================
void spinnerLine(const string& label, int ms = 600) {
    string frames = "|/-\\";
    int cycles = ms / 100;
    for (int i = 0; i < cycles; i++) {
        cout << "\r  " << label << " " << frames[i % 4] << "  ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "\r  " << label << " done       \n";
}

// ===================== CLEAR SCREEN (ANSI) =====================
void clearScreen() {
    cout << "\033[2J\033[H";
    cout.flush();
}

// ===================== PAUSE SCREEN HELPER =====================
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ===================== INIT SEATS PER TRIP =====================
void initTripSeatMap(const string& tripKey) {
    tripNormalOrder[tripKey].clear();
    tripPriorityOrder[tripKey].clear();

    char row = 'A';
    for (int i = 0; i < ROWS; i++) {
        for (int j = 1; j <= COLS; j++) {
            tripNormalOrder[tripKey].push_back({string(1, row) + to_string(j), false});
        }
        row++;
    }

    for (int i = ROWS - 1; i >= 0; i--) {
        char r = 'A' + i;
        for (int j = 1; j <= COLS; j++) {
            tripPriorityOrder[tripKey].push_back({string(1, r) + to_string(j), false});
        }
    }
}

// ===================== PRINT SEAT GRID =====================
void printSeatGrid(const string& tripLabel, vector<bool>& displayState) {
    cout << "\n🪑 SEAT MAP — " << tripLabel << "\n\n";
    cout << " -------------------------------------------------\n";
    cout << "        [1]    [2]    [3]    [4]                 \n";
    cout << " -------------------------------------------------\n";

    int index = 0;
    for (int r = 0; r < ROWS; r++) {
        char rowLabel = 'A' + r;
        cout << " " << rowLabel << "   ";
        for (int c = 0; c < COLS; c++) {
            cout << " } "
                 << (displayState[index] ? "🟥" : "🟩")
                 << " ] ";
            index++;
        }
        cout << "\n";
    }

    cout << " -------------------------------------------------\n";
    cout << "  🚪 EXIT/ENTRANCE             🚪 EXIT/ENTRANCE\n";
}

// ===================== DISPLAY SEAT MAP (ANIMATED) =====================
void displaySeatMap(const string& tripKey, const string& tripLabel) {
    vector<Seat>& seats = tripNormalOrder[tripKey];
    int total = ROWS * COLS;

    vector<bool> displayState(total, false);

    vector<int> occupiedIndices;
    for (int i = 0; i < total; i++) {
        if (seats[i].occupied) occupiedIndices.push_back(i);
    }

    // Step 1: Initial load with spinner
    clearScreen();
    spinnerLine("Loading seat map...", 700);   
    this_thread::sleep_for(chrono::milliseconds(200));

    clearScreen();
    printSeatGrid(tripLabel, displayState);
    cout << "\nLegend:\n";
    cout << "🟩 Available   🟥 Reserved\n";
    cout << "🔄 Revealing reserved seats...\n";
    this_thread::sleep_for(chrono::milliseconds(700));

    // Step 2: Animate each reserved seat
    for (int idx : occupiedIndices) {
        displayState[idx] = true;

        clearScreen();
        printSeatGrid(tripLabel, displayState);
        cout << "\nLegend:\n";
        cout << "🟩 Available   🟥 Reserved\n";
        cout << "🔄 Revealing reserved seats...\n";

        this_thread::sleep_for(chrono::milliseconds(350));
    }

    // Step 3: Final state
    clearScreen();
    printSeatGrid(tripLabel, displayState);

    int available = total - (int)occupiedIndices.size();
    int reserved  = (int)occupiedIndices.size();

    cout << "\nLegend:\n";
    cout << "🟩 Available   🟥 Reserved\n";
    cout << "\n📊 Summary:\n";
    cout << "  ✅ Available : " << available << " seat(s)\n";
    cout << "  🔴 Reserved  : " << reserved  << " seat(s)\n";
    cout << "  📦 Total     : " << total     << " seat(s)\n";

    if (reserved == 0)
        cout << "\n🎉 No reservations yet — all seats free!\n";
    else if (available == 0)
        cout << "\n🚫 This trip is FULLY BOOKED!\n";
    else
        cout << "\n🚢 Seat map fully loaded.\n";

    pauseScreen();
}

// ===================== ASSIGN SEAT PER TRIP =====================
string assignSeat(const string& tripKey, bool isPriority) {
    vector<Seat>& orderRef  = isPriority ? tripPriorityOrder[tripKey] : tripNormalOrder[tripKey];
    vector<Seat>& normalRef = tripNormalOrder[tripKey];

    for (auto& seat : orderRef) {
        if (!seat.occupied) {
            seat.occupied = true;
            for (auto& ns : normalRef) {
                if (ns.id == seat.id) { ns.occupied = true; break; }
            }
            if (!isPriority) {
                for (auto& ps : tripPriorityOrder[tripKey]) {
                    if (ps.id == seat.id) { ps.occupied = true; break; }
                }
            }
            return seat.id;
        }
    }
    return "FULL";
}

// ===================== FREE SEAT PER TRIP =====================
void freeSeat(const string& tripKey, const string& seatId) {
    for (auto& s : tripNormalOrder[tripKey])
        if (s.id == seatId) s.occupied = false;
    for (auto& s : tripPriorityOrder[tripKey])
        if (s.id == seatId) s.occupied = false;
}

// ===================== TRIP LABEL HELPER =====================
string getTripLabel(const string& key) {
    if (key == "1") return "Trip 1 — 08:00 AM";
    if (key == "2") return "Trip 2 — 12:00 PM";
    if (key == "3") return "Trip 3 — 04:00 PM";
    return "Unknown Trip";
}

// ===================== INIT =====================
void initTrips() {
    tripBookings["1"] = {};
    tripBookings["2"] = {};
    tripBookings["3"] = {};
    tripSeats["1"] = ROWS * COLS;
    tripSeats["2"] = ROWS * COLS;
    tripSeats["3"] = ROWS * COLS;

    initTripSeatMap("1");
    initTripSeatMap("2");
    initTripSeatMap("3");
}

// ===================== UI =====================
void printHeader(const string& title) {
    cout << "\n=================================\n";
    cout << "  " << title << "\n";
    cout << "=================================\n";
}

void showTrips() {
    cout << "\n🛳 Available Trips:\n";
    for (auto& pair : tripBookings) {
        int booked    = pair.second.size();
        int total     = tripSeats[pair.first];
        int available = total - booked;
        cout << pair.first << ". " << getTripLabel(pair.first)
             << " | Seats Left: " << available << "/" << total << "\n";
    }
}

// ===================== BOOK =====================
void bookTicket() {
    Passenger p;
    p.id = ticketCounter++;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Enter Age: ";
    cin >> p.age;

    showTrips();
    cout << "Select Trip (1-3): ";
    string choice;
    cin >> choice;

    if (tripBookings.find(choice) == tripBookings.end()) {
        cout << "❌ Invalid trip selected.\n";
        pauseScreen();
        return;
    }
    if ((int)tripBookings[choice].size() >= tripSeats[choice]) {
        cout << "\n❌ TRIP FULLY BOOKED\n";
        cout << "🚫 This schedule is no longer available.\n";
        pauseScreen();
        return;
    }

    // ================= PRIORITY LOGIC =================
    if (p.age >= 60) {
        p.isPriority = true;
        p.category = "Senior";
        cout << "👴 Senior detected -> Auto Priority\n";
    } else {
        int type;
        cout << "\nSelect Passenger Type:\n";
        cout << "1. Regular\n";
        cout << "2. Pregnant\n";
        cout << "3. PWD\n";
        cout << "4. VIP\n👉 ";
        cin >> type;
        if      (type == 1) { p.isPriority = false; p.category = "Regular";  }
        else if (type == 2) { p.isPriority = true;  p.category = "Pregnant"; }
        else if (type == 3) { p.isPriority = true;  p.category = "PWD";      }
        else if (type == 4) { p.isPriority = true;  p.category = "VIP";      }
        else                { p.isPriority = false; p.category = "Regular";  }
    }

    if      (choice == "1") p.trip = "08:00 AM";
    else if (choice == "2") p.trip = "12:00 PM";
    else if (choice == "3") p.trip = "04:00 PM";

    p.tripKey = choice;

    loadingAnimation("Booking your seat");
    progressBar();
    spinnerLine("Assigning seat", 500);  

    string assignedSeat = assignSeat(choice, p.isPriority);
    if (assignedSeat == "FULL") {
        cout << "❌ No seats available on this vessel!\n";
        pauseScreen();
        return;
    }

    p.assignedSeat = assignedSeat;
    tripBookings[choice].push_back(p);
    allBookings.push_back(p);

    if (p.isPriority) priorityQueue.push(p);
    else              regularQueue.push(p);

    transactionStack.push("Booked ID: " + to_string(p.id));

    cout << "\n✅ BOOKING CONFIRMED\n";
    cout << "Booking ID    : " << p.id           << "\n";
    cout << "Name          : " << p.name         << "\n";
    cout << "Trip          : " << getTripLabel(choice) << "\n";
    cout << "Category      : " << p.category     << "\n";
    cout << "Seat Assigned : " << assignedSeat   << "\n";
    pauseScreen();
}

// ===================== FARE =====================
double computeFare(Passenger p) {
    if (p.age < 3)   return 0;
    if (p.age >= 60) return baseFare * 0.8;
    return baseFare;
}

// ===================== ADMIN PROCESS =====================
void servePassenger() {
    // ── Guard: nothing in either queue ──
    if (priorityQueue.empty() && regularQueue.empty()) {
        cout << "\n⚠️  No passengers in queue to process.\n";
        pauseScreen();
        return;
    }

    loadingAnimation("Processing queue");
    progressBar();
    spinnerLine("Fetching next passenger", 500);  

    cout << "\n🔄 PROCESSING...\n";
    Passenger p;
    if (!priorityQueue.empty()) {
        p = priorityQueue.top();
        priorityQueue.pop();
        cout << "🚢 PRIORITY SERVED\n";
    } else {
        p = regularQueue.front();
        regularQueue.pop();
        cout << "🚢 REGULAR SERVED\n";
    }

    confirmedPassengers.push_back(p);
    double fare = computeFare(p);

    cout << "\n🎟 ===== TICKET =====\n";
    cout << "Booking ID : " << p.id           << "\n";
    cout << "Name       : " << p.name         << "\n";
    cout << "Age        : " << p.age          << "\n";
    cout << "Category   : " << p.category     << "\n";
    cout << "Trip       : " << p.trip         << "\n";
    cout << "Seat       : " << p.assignedSeat << "\n";
    cout << "Base Fare  : P" << baseFare      << "\n";
    if      (p.age >= 60) cout << "Discount   : 20% (Senior)\n";
    else if (p.age < 3)   cout << "Discount   : FREE (Infant)\n";
    else                  cout << "Discount   : None\n";
    cout << "TOTAL      : P" << fare          << "\n";
    cout << "====================\n";
    pauseScreen();
}

// ===================== VIEW BOOKINGS =====================
void viewBookings() {
    // ── Guard: no bookings at all ──
    if (allBookings.empty()) {
        cout << "\n📭 No bookings yet.\n";
        pauseScreen();
        return;
    }

    spinnerLine("Loading bookings", 500);   
    cout << "\n📋 ALL BOOKINGS (BY TRIP):\n";
    for (auto& pair : tripBookings) {
        if (pair.second.empty()) continue;
        cout << "\n📍 " << getTripLabel(pair.first) << ":\n";
        for (auto& p : pair.second) {
            cout << "  ID: " << p.id
                 << " | Name: " << p.name
                 << " | Seat: " << p.assignedSeat
                 << " | Category: " << p.category
                 << "\n";
        }
    }
    pauseScreen();
}

// ===================== CANCEL =====================
void cancelTicket() {
    // ── Guard: nothing to cancel ──
    if (allBookings.empty()) {
        cout << "\n📭 No bookings to cancel.\n";
        pauseScreen();
        return;
    }

    int id;
    cout << "Enter Booking ID: ";
    cin >> id;

    loadingAnimation("Processing cancellation");
    spinnerLine("Verifying booking", 400); 

    for (auto it = allBookings.begin(); it != allBookings.end(); ++it) {
        if (it->id == id) {
            freeSeat(it->tripKey, it->assignedSeat);
            for (auto& t : tripBookings) {
                auto& vec = t.second;
                vec.erase(remove_if(vec.begin(), vec.end(),
                    [&](Passenger& p) { return p.id == id; }), vec.end());
            }
            allBookings.erase(it);
            transactionStack.push("Cancelled Ticket ID: " + to_string(id));
            cout << "✅ Cancelled Booking ID " << id << "\n";
            pauseScreen();
            return;
        }
    }
    cout << "❌ Booking ID not found.\n";
    pauseScreen();
}

// ===================== SEARCH =====================
void searchBooking() {
    // ── Guard: nothing to search ──
    if (allBookings.empty()) {
        cout << "\n📭 No bookings to search.\n";
        pauseScreen();
        return;
    }

    int id;
    cout << "Enter Booking ID: ";
    cin >> id;

    spinnerLine("Searching records", 500);  

    for (auto& p : allBookings) {
        if (p.id == id) {
            cout << "\n🔍 FOUND:\n";
            cout << "ID       : " << p.id           << "\n";
            cout << "Name     : " << p.name         << "\n";
            cout << "Trip     : " << p.trip         << "\n";
            cout << "Seat     : " << p.assignedSeat << "\n";
            cout << "Category : " << p.category     << "\n";
            cout << "Priority : " << (p.isPriority ? "YES" : "NO") << "\n";
            pauseScreen();
            return;
        }
    }
    cout << "❌ Not found.\n";
    pauseScreen();
}

// ===================== SORT =====================
void sortBookings() {
    // ── Guard: nothing to sort ──
    if (allBookings.empty()) {
        cout << "\n📭 No bookings to sort.\n";
        pauseScreen();
        return;
    }

    spinnerLine("Sorting bookings", 500);  
    cout << "\n📋 SORTED BY TRIP + PRIORITY:\n";
    for (auto& pair : tripBookings) {
        if (pair.second.empty()) continue;
        cout << "\n📍 " << getTripLabel(pair.first) << ":\n";
        vector<Passenger> temp = pair.second;
        sort(temp.begin(), temp.end(), [](const Passenger& a, const Passenger& b) {
            return a.isPriority > b.isPriority;
        });
        for (auto& p : temp) {
            cout << "  ID: " << p.id
                 << " | Name: " << p.name
                 << " | Seat: " << p.assignedSeat
                 << " | Category: " << p.category
                 << "\n";
        }
    }
    pauseScreen();
}

// ===================== HISTORY =====================
void viewHistory() {
    stack<string> temp = transactionStack;
    cout << "\n📜 TRANSACTION HISTORY (most recent first):\n";
    if (temp.empty()) {
        cout << "  No transactions yet.\n";
        pauseScreen();
        return;
    }
    spinnerLine("Loading history", 400); 
    while (!temp.empty()) {
        cout << "  " << temp.top() << "\n";
        temp.pop();
    }
    pauseScreen();
}

// ===================== ADMIN SEAT MAP VIEWER =====================
void adminViewSeatMap() {
    cout << "\n📍 VIEW SEAT MAP — SELECT TRIP:\n";
    cout << "1. Trip 1 — 08:00 AM\n";
    cout << "2. Trip 2 — 12:00 PM\n";
    cout << "3. Trip 3 — 04:00 PM\n";
    cout << "0. Back\n👉 ";

    string choice;
    cin >> choice;

    if (choice == "0") return;

    if (tripNormalOrder.find(choice) == tripNormalOrder.end()) {
        cout << "❌ Invalid choice.\n";
        pauseScreen();
        return;
    }

    displaySeatMap(choice, getTripLabel(choice));
}

// ===================== LOGIN =====================
bool adminLogin() {
    string password;
    int attempts = 3;
    while (attempts--) {
        cout << "Enter password: ";
        cin >> password;
        if (password == "admin123") {
            loadingAnimation("Logging in");
            spinnerLine("Verifying credentials", 600);  
            cout << "✅ Login success\n";
            return true;
        }
        cout << "❌ Wrong. Attempts left: " << attempts << "\n";
    }
    return false;
}

// ===================== MENUS =====================
void customerMenu() {
    int choice;
    do {
        printHeader("👤 PASSENGER MENU");
        cout << "1. Book Trip\n";
        cout << "2. View Trips\n";
        cout << "3. Cancel Booking\n";
        cout << "4. View My Bookings\n";
        cout << "0. Back\n👉 ";
        cin >> choice;
        switch (choice) {
            case 1: bookTicket();   break;
            case 2: showTrips();    break;
            case 3: cancelTicket(); break;
            case 4: viewBookings(); break;
        }
    } while (choice != 0);
}

void adminMenu() {
    int choice;
    do {
        printHeader("🛠 ADMIN MENU");
        cout << "1. View All Bookings\n";
        cout << "2. Process Next Passenger\n";
        cout << "3. Search Booking\n";
        cout << "4. Sort Bookings\n";
        cout << "5. Transaction History\n";
        cout << "6. View Seat Map (by Trip)\n";
        cout << "0. Back\n👉 ";
        cin >> choice;
        switch (choice) {
            case 1: viewBookings();     break;
            case 2: servePassenger();   break;
            case 3: searchBooking();    break;
            case 4: sortBookings();     break;
            case 5: viewHistory();      break;
            case 6: adminViewSeatMap(); break;
        }
    } while (choice != 0);
}

void roleMenu() {
    int role;
    do {
        printHeader("🚢 SAILCHECK SYSTEM");
        cout << "1. Passenger\n";
        cout << "2. Admin\n";
        cout << "0. Exit\n👉 ";
        cin >> role;
        switch (role) {
            case 1: customerMenu(); break;
            case 2: if (adminLogin()) adminMenu(); break;
        }
    } while (role != 0);
}

// ===================== MAIN =====================
int main() {
    setlocale(LC_ALL, "");
    initTrips();

    cout << "\n=================================\n";
    cout << "  🚢 WELCOME TO SAILCHECK 🌊\n";
    cout << "    Online Booking System\n";
    cout << "=================================\n";
    cout << "Loading system...\n";

    for (int i = 0; i < 12; i++) {
        cout << " 🛥️";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    cout << "\n";
    spinnerLine("        ", 600);   
    cout << "\n✅ System ready!\n";
    cout << "👉 Please log in to continue.\n";

    roleMenu();
    return 0;
}
