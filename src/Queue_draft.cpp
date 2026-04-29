#include <iostream>
#include <string>
using namespace std;

#define MAX 20

struct Passenger {
    int ticketNo;
    string name;
    string trip;
};

struct Queue {
    Passenger data[MAX];
    int front;
    int rear;
};

// ===================== INIT =====================
void initQueue(Queue &q) {
    q.front = -1;
    q.rear = -1;
}

bool isEmpty(Queue q) {
    return (q.front == -1 || q.front > q.rear);
}

bool isFull(Queue q) {
    return (q.rear == MAX - 1);
}

// ===================== TRIPS =====================
string trips[3] = {
    "Batangas → Mindoro | 08:00 AM",
    "Batangas → Mindoro | 12:00 PM",
    "Batangas → Mindoro | 04:00 PM"
};

int nextTicket = 1000; // Starting ticket number
// ===================== BOOK TICKET =====================
void enqueue(Queue &q, string name) {

    if (isFull(q)) {
        cout << "\n❌ Booking failed: No available slots.\n";
        return;
    }

    Passenger p;
    p.ticketNo = nextTicket++;
    p.name = name;

    if (q.front == -1) {
        q.front = 0; // First passenger
    }   
    q.data[++q.rear] = p;

    cout << "\n✅ Booking Confirmed!\n";
    cout << "🎫 Ticket #: " << p.ticketNo << endl;
}

// ===================== DISPLAY QUEUE =====================
void displayQueue(Queue q, string tripName) {

 cout << "\n📋 " << tripName << " Bookings:\n";

    if (isEmpty(q)) {
        cout << "\n📭 No bookings available.\n";
        return;
    }

    for (int i = q.front; i <= q.rear; i++) {
        cout << "🎫 " << q.data[i].ticketNo
             << " | " << q.data[i].name << endl;
           //  << " | " << q.data[i].trip << endl;
    }
}


// ===================== MAIN =====================
int main() {

    Queue q1, q2, q3;
    initQueue(q1);
    initQueue(q2);
    initQueue(q3);

    int choice;
    string name;
    int tripChoice;

    do {
        cout << "\n=============================\n";
        cout << "   🚢 MULTI-QUEUE SYSTEM\n";
        cout << "=============================\n";
        cout << "1. Book Ticket\n";
        cout << "2. View All Trips\n";
        cout << "0. Exit\n👉 ";
        cin >> choice;

        switch (choice) {

            case 1:
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);

                cout << "\nSelect Trip:\n";
                for (int i = 0; i < 3; i++) {
                    cout << i + 1 << ". " << trips[i] << endl;
                }

                cout << "Choice: ";
                cin >> tripChoice;

                if (tripChoice == 1)
                    enqueue(q1, name);
                else if (tripChoice == 2)
                    enqueue(q2, name);
                else if (tripChoice == 3)
                    enqueue(q3, name);
                else
                    cout << "❌ Invalid choice\n";

                break;

            case 2:
                displayQueue(q1, trips[0]);
                displayQueue(q2, trips[1]);
                displayQueue(q3, trips[2]);
                break;
        }

    } while (choice != 0);

    cout << "\n👋 Thank you!\n";
    return 0;
}