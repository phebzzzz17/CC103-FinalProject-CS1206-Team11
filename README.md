# 🚢 SAILCHECK: Online Booking System




---

## 📌 Problem Overview

In real-world ferry terminals, passengers often experience disorganized queues, long waiting times, and lack of proper prioritization. Although trips are scheduled, most systems still follow a basic first-come, first-served approach.

This becomes inefficient when handling urgent passengers such as seniors, PWDs, pregnant individuals, and VIPs.

SAILCHECK addresses this by introducing a structured system that combines trip-based grouping and priority-based processing using appropriate data structures.

---

## &#x20;🧠 Data Structures Used  

 

🔹 Queue

FIFO structure used for regular passengers

→ Ensures fairness based on arrival time

🔹 Priority Queue

Heap-based structure for urgent passengers

→ Ensures VIP, senior, PWD, and pregnant passengers are served first

🔹 Stack

LIFO structure used for transaction history

→ Stores recent bookings and cancellations for tracking system activity

🔹 Map

Key-value structure (trip → passengers)

→ Organizes passengers per trip schedule for better system structure

🔹 Vector

Dynamic container for passenger storage

→ Used for searching, sorting, and iteration

🏗️ System Design

The system is built in a modular structure with functions handling booking, cancellation, serving, seat allocation, and trip management.

It simulates a real-world ferry system by combining scheduling, prioritization, and structured seat assignment.

⚙️ Key Features

* 🎫 Ticket Booking System
* 🛳 Trip Selection (Batangas → Mindoro schedules)
* ⭐ Priority Passenger Handling (VIP)
* 📋 View and Manage Bookings
* ❌ Cancel Reservations
* 🔍 Search Passenger by ID
* 🔃 Sort Bookings by Name
* 📜 Transaction History Tracking
* 🔐 Admin Login System

---

## 🧠 Data Structures Used

| Data Structure | Purpose                           |
| -------------- | --------------------------------- |
| Queue          | Handles regular passengers (FIFO) |
| Priority Queue | Handles VIP passengers            |
| Stack          | Stores transaction history        |
| Vector         | Stores all passenger records      |

---

## 🖥️ System Flow

1. User selects role (Customer/Admin)
2. Customer can book, view, or cancel tickets
3. Admin can manage passengers and system data
4. System prioritizes VIP passengers during serving

---

## 💻 How to Run the Program

### 1. Compile the code

```bash
g++ main.cpp -o sailcheck
```

### 2. Run the program

```bash
./sailcheck
```

---

## 🔐 Admin Access

* **Password:** `admin123`

---

## 📸 Sample Output

```
WELCOME TO SAILCHECK
Port Booking System

Loading system...
████████████████████ 100%

System ready!
```

---

## 🚀 Technologies Used

* C++
* Standard Template Library (STL)

  * queue
  * stack
  * priority_queue
  * vector

---

## 👨‍💻 Developers

* Charmaine Argona
* Phoebe Leonides Dolor
* Danielle Panopio

---

## &#x20;⏱️     Time Complexity Summary  

Operation	Complexity	Reason

Booking	O(1)	Direct insertion

Serve Passenger	O(log n)	Priority queue handling

Search	O(n)	Linear traversal

Cancel	O(n)	Search + removal

Sorting	O(n log n)	STL sort per trip

Seat Assignment	O(n)	Seat scanning

---

## 📌 Future Improvements

* Add graphical user interface (GUI)
* Connect to a database for persistent storage
* Online booking integration
* Mobile-friendly system

---

##
