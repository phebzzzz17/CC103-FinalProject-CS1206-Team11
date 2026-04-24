#include <iostream>
#include <string>
using namespace std;

#define MAX 5

struct Passenger {
    int ticketNo;
    string name;
    string trip;
};

struct Queue {
    Passenger data[MAX];
    int front, rear;
};

int nextTicket = 1001;

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

// ===================== BOOK TICKET =====================
void enqueue(Queue &q, string name, int choice) {

    if (isFull(q)) {
        cout << "\n❌ Booking failed: No available slots.\n";
        return;
    }

    Passenger p;
    p.ticketNo = nextTicket++;
    p.name = name;

    if (choice < 1 || choice > 3) {
        cout << "\n❌ Invalid trip selection.\n";
        return;
    }

    p.trip = trips[choice - 1];

    if (q.front == -1) q.front = 0;

    q.data[++q.rear] = p;

    cout << "\n✅ Booking Confirmed!\n";
    cout << "🎫 Ticket #: " << p.ticketNo << endl;
}

// ===================== SERVE (ADMIN USE ONLY) =====================
void dequeue(Queue &q) {

    if (isEmpty(q)) {
        cout << "\n📭 No pending bookings.\n";
        return;
    }

    cout << "\n🚢 Processing next booking...\n";
    cout << "🎫 Ticket #: " << q.data[q.front].ticketNo << endl;
    cout << "👤 Name    : " << q.data[q.front].name << endl;
    cout << "🛳 Trip    : " << q.data[q.front].trip << endl;

    q.front++;
}

// ===================== DISPLAY =====================
void displayQueue(Queue q) {

    if (isEmpty(q)) {
        cout << "\n📭 No bookings available.\n";
        return;
    }

    cout << "\n📋 Current Bookings:\n";

    for (int i = q.front; i <= q.rear; i++) {
        cout << "🎫 " << q.data[i].ticketNo
             << " | " << q.data[i].name
             << " | " << q.data[i].trip << endl;
    }
}