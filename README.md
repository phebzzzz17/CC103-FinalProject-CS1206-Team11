# 🚢 SAILCHECK: Port Booking System

![C++](https://img.shields.io/badge/Language-C++-blue)
![Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)

---

## 📌 Project Overview

**SAILCHECK** is a console-based port booking system developed in C++.
It allows passengers to book ferry tickets, manage reservations, and prioritize VIP passengers using efficient data structures.

The system simulates a real-world port booking process with queue handling, transaction tracking, and admin controls.

---

## 🎯 Objectives

* To simulate a real-life ticket booking system
* To apply fundamental data structures in a practical scenario
* To create an organized and user-friendly console application

---

## ⚙️ Key Features

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

* **Password:** `********`

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
* Phoebe Leonides M. Dolor
* Danielle Panopio

---

## 📚 Learnings

* Implementation of real-world queue systems
* Understanding FIFO, LIFO, and priority-based processing
* Improving problem-solving and system design skills

---

## 📌 Future Improvements

* Add graphical user interface (GUI)
* Connect to a database for persistent storage
* Online booking integration
* Mobile-friendly system

---

## ⭐ Conclusion

SAILCHECK demonstrates how data structures can be applied in real-world systems like transportation booking. It provides an efficient and organized way to manage passengers and prioritize services.

---

