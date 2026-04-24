#ifndef STACK_BOX_H
#define STACK_BOX_H

#include <iostream>
using namespace std;

#define MAX 10  // maximum history records

// This stores ONE transaction (booking/cancel)
struct Transaction {
    string message;  // e.g. "Booked ID 1001"
};

// Manual stack (no STL stack used)
class Stack {

private:
    Transaction arr[MAX];
    int top;

public:
    // Constructor
    Stack() {
        top = -1;
    }

    // Check if empty
    bool isEmpty() {
        return top == -1;
    }

    // Check if full
    bool isFull() {
        return top == MAX - 1;
    }

    // PUSH (add transaction)
    void push(Transaction t) {
        if (isFull()) {
            cout << "Transaction history is full!\n";
            return;
        }

        top++;
        arr[top] = t;

        cout << "Logged: " << t.message << endl;
    }

    // POP (remove last transaction)
    Transaction pop() {
        if (isEmpty()) {
            cout << "No transaction to undo.\n";
            return {"NULL"};
        }

        Transaction t = arr[top];
        top--;
        return t;
    }

    // PEEK (see last transaction)
    Transaction peek() {
        if (isEmpty()) {
            return {"NULL"};
        }
        return arr[top];
    }

    // DISPLAY all history
    void display() {
        if (isEmpty()) {
            cout << "No transaction history.\n";
            return;
        }

        cout << "\n===== TRANSACTION HISTORY =====\n";

        for (int i = top; i >= 0; i--) {
            cout << arr[i].message << endl;
        }

        cout << "==============================\n";
    }
};
#endif