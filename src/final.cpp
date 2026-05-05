#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <chrono>
#include <map>

using namespace std;

// ===================== PASSENGER STRUCT =====================
struct Passenger {
    int id;
    string name;
    string trip;
    bool isPriority;
    int age;
    string category;

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

// ===================== INIT =====================
void initTrips() {
    tripBookings["1"] = {};
    tripBookings["2"] = {};
    tripBookings["3"] = {};

    tripSeats["1"] = 2;
    tripSeats["2"] = 2;
    tripSeats["3"] = 2;
}

// ===================== UI =====================
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
        return;
    }

    if (tripBookings[choice].size() >= tripSeats[choice]) {
        
         cout << "\n❌ TRIP FULLY BOOKED\n";
        cout << "🚫 This schedule is no longer available.\n";
        
        return;
    }

    // ================= PRIORITY LOGIC =================
    if (p.age >= 60) {
        p.isPriority = true;
        p.category = "Senior";
        cout << "👴 Senior detected → Auto Priority\n";
    } else {
        int type;
        cout << "\nSelect Passenger Type:\n";
        cout << "1. Regular\n";
        cout << "2. Pregnant\n";
        cout << "3. PWD\n";
        cout << "4. VIP\n👉 ";
        cin >> type;

        if (type == 1) {
            p.isPriority = false;
            p.category = "Regular";
        }
        else if (type == 2) {
            p.isPriority = true;
            p.category = "PWD";
        }
        else if (type == 3) {
            p.isPriority = true;
            p.category = "VIP";
        }
    }

    if (choice == "1") p.trip = "08:00 AM";
    else if (choice == "2") p.trip = "12:00 PM";
    else if (choice == "3") p.trip = "04:00 PM";

    tripBookings[choice].push_back(p);
    allBookings.push_back(p);

    if (p.isPriority)
        priorityQueue.push(p);
    else
        regularQueue.push(p);

    transactionStack.push("Booked ID: " + to_string(p.id));

    cout << "\n✅ BOOKING RECEIVED\n";
    cout << "Booking ID: " << p.id << endl;
}

// ===================== FARE =====================
double computeFare(Passenger p) {
    if (p.age < 3) return 0;
    if (p.age >= 60) return baseFare * 0.8;
    return baseFare;
}

// ===================== ADMIN PROCESS =====================
void servePassenger() {

    cout << "\n🔄 PROCESSING...\n";

    Passenger p;

    if (!priorityQueue.empty()) {
        p = priorityQueue.top();
        priorityQueue.pop();
        cout << "🚢 PRIORITY SERVED\n";
    }
    else if (!regularQueue.empty()) {
        p = regularQueue.front();
        regularQueue.pop();
        cout << "🚢 REGULAR SERVED\n";
    }
    else {
        cout << "⚠ No passengers.\n";
        return;
    }

    confirmedPassengers.push_back(p);

    double fare = computeFare(p);

    // 🎟 TICKET
    cout << "\n🎟 ===== TICKET =====\n";
    cout << "Booking ID: " << p.id << endl;
    cout << "Name: " << p.name << endl;
    cout << "Age: " << p.age << endl;
    cout << "Category: " << p.category << endl;
    cout << "Trip: " << p.trip << endl;
    cout << "Base Fare: ₱" << baseFare << endl;

    if (p.age >= 60)
        cout << "Discount: 20% (Senior)\n";
    else if (p.age < 3)
        cout << "Discount: FREE (Infant)\n";
    else
        cout << "Discount: None\n";

    cout << "TOTAL: ₱" << fare << endl;
    cout << "====================\n";
}

// ===================== VIEW BOOKINGS =====================
void viewBookings() {

    if (allBookings.empty()) {
        cout << "\n📭 No bookings.\n";
        return;
    }

    cout << "\n📋 ALL BOOKINGS (BY TRIP):\n";

    for (auto &pair : tripBookings) {

        if (pair.second.empty()) continue;

        cout << "\n📍 TRIP " << pair.first << ":\n";

        for (auto &p : pair.second) {
            cout << "ID: " << p.id
                 << " | Name: " << p.name
                 << " | Priority: " << (p.isPriority ? "Yes" : "No")
                 << endl;
        }
    }
}

// ===================== CANCEL =====================
void cancelTicket() {

    int id;
    cout << "Enter Booking ID: ";
    cin >> id;

    for (auto it = allBookings.begin(); it != allBookings.end(); ++it) {

        if (it->id == id) {

            for (auto &t : tripBookings) {
                auto &vec = t.second;
                vec.erase(remove_if(vec.begin(), vec.end(),
                    [&](Passenger &p) { return p.id == id; }), vec.end());
            }

            allBookings.erase(it);

            transactionStack.push("Cancelled Ticket ID: " + to_string(id));

            cout << "✅ Cancelled Booking ID " << id << endl;
            return;
        }
    }

    cout << "❌ Booking not found.\n";
}

// ===================== SEARCH =====================
void searchBooking() {

    int id;
    cout << "Enter Booking ID: ";
    cin >> id;

    for (auto &p : allBookings) {
        if (p.id == id) {
            cout << "\n🔍 FOUND:\n";
            cout << "ID: " << p.id << endl;
            cout << "Name: " << p.name << endl;
            cout << "Trip: " << p.trip << endl;
            cout << "Priority: " << (p.isPriority ? "YES" : "NO") << endl;
            return;
        }
    }

    cout << "❌ Not found.\n";
}

// ===================== SORT =====================
void sortBookings() {

    cout << "\n📋 SORTED BY TRIP + PRIORITY:\n";

    for (auto &pair : tripBookings) {

        cout << "\n📍 TRIP " << pair.first << ":\n";

        vector<Passenger> temp = pair.second;

        sort(temp.begin(), temp.end(),
            [](const Passenger &a, const Passenger &b) {
                return a.isPriority > b.isPriority;
            }
        );

        for (auto &p : temp) {
            cout << "ID: " << p.id
                 << " | Name: " << p.name
                 << " | Priority: " << (p.isPriority ? "Yes" : "No")
                 << endl;
        }
    }
}

// ===================== HISTORY =====================
void viewHistory() {

    stack<string> temp = transactionStack;

    cout << "\n📜 TRANSACTION HISTORY:\n";

    while (!temp.empty()) {
        cout << temp.top() << endl;
        temp.pop();
    }
}

// ===================== LOGIN =====================
bool adminLogin() {

    string password;
    int attempts = 3;

    while (attempts--) {

        cout << "Enter password: ";
        cin >> password;

        if (password == "admin123") {
            cout << "✅ Login success\n";
            return true;
        }

        cout << "❌ Wrong. Attempts left: " << attempts << endl;
    }

    return false;
}

// ===================== MENUS =====================
void customerMenu() {

    int choice;

    do {
        printHeader("👤 PASSANGER MENU");

        cout << "1. Book Trip\n";
        cout << "2. View Trips\n";
        cout << "3. Cancel Booking\n";
        cout << "4. View Bookings\n";
        cout << "0. Back\n👉 ";

        cin >> choice;

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: showTrips(); break;
            case 3: cancelTicket(); break;
            case 4: viewBookings(); break;
        }

    } while (choice != 0);
}

void adminMenu() {

    int choice;

    do {
        printHeader("🛠 ADMIN MENU");

        cout << "1. View Bookings\n";
        cout << "2. Process Bookings\n";
        cout << "3. Search\n";
        cout << "4. Sort\n";
        cout << "5. History\n";
        cout << "0. Back\n👉 ";

        cin >> choice;

        switch (choice) {
            case 1: viewBookings(); break;
            case 2: servePassenger(); break;
            case 3: searchBooking(); break;
            case 4: sortBookings(); break;
            case 5: viewHistory(); break;
        }

    } while (choice != 0);
}

void roleMenu() {

    int role;

    do {
        printHeader("🚢 SAILCHECK SYSTEM");

        cout << "1. Passanger\n";
        cout << "2. Admin\n";
        cout << "0. Exit\n👉 ";

        cin >> role;

        switch (role) {
            case 1: customerMenu(); break;
            case 2:
                if (adminLogin()) adminMenu();
                break;
        }

    } while (role != 0);
}

// ===================== MAIN =====================
int main() {

    initTrips();

    cout << "\n=================================\n";
    cout << "   🚢 WELCOME TO SAILCHECK🌊\n";
    cout << "       Port Booking System\n";
    cout << "=================================\n";

    cout << "Loading system...\n";

    for (int i = 0; i < 12; i++) {
        cout << "🛥️ ";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    cout << "\n\n✅ System ready!\n";
    cout << "👉 Please log in to continue.\n";

    roleMenu();

    return 0;
}