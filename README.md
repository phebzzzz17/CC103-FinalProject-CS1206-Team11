# 🚢 SAILCHECK: Port Booking System

![C++](https://img.shields.io/badge/Language-C++-blue)
![Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)

---

👨‍💻 Team Members
Name	Role
Member 1	Booking System & Queue Handling
Member 2	Seat Management & Trip Organization
Member 3	Priority Logic & Sorting System
📌 Problem Overview

In real-world ferry terminals, passengers often experience disorganized queues, long waiting times, and lack of proper prioritization. Although trips are scheduled, most systems still follow a basic first-come, first-served approach.

This becomes inefficient when handling urgent passengers such as seniors, PWDs, pregnant individuals, and VIPs.

SAILCHECK addresses this by introducing a structured system that combines trip-based grouping and priority-based processing using appropriate data structures.

🧠 Data Structures Used
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

🔒 Core Components
regularQueue → Regular passengers
priorityQueue → Priority passengers
transactionStack → Booking history
allBookings → Master passenger list
tripBookings → Groups passengers per trip
tripSeats → Tracks available seats per trip
tripNormalOrder / tripPriorityOrder → Seat allocation system
🔄 System Process Flow
1. Booking Process
Passenger enters details (name, age, trip)
System assigns ticket ID
Passenger is categorized based on age or type
Seat is assigned dynamically
Stored in trip-based and global structures
Added to appropriate queue system
2. Trip Organization

Passengers are grouped using:

map<string, vector<Passenger>>

Each trip acts as a separate container:

Trip 1 → 08:00 AM
Trip 2 → 12:00 PM
Trip 3 → 04:00 PM

This improves clarity and structured management.

3. Priority Sorting

Inside each trip, passengers are sorted using:

return a.isPriority > b.isPriority;
💡 Meaning:
Priority passengers are displayed first
Regular passengers follow after

This is a custom comparator-based sorting method

4. Serving Process
Priority queue is checked first
If not empty → serve priority passenger
Otherwise → serve regular passenger
Served data is stored in transaction history stack
5. Seat System
Each trip has a structured seat layout
Seats are assigned dynamically based on availability
Separate logic for normal and priority allocation
Seats are freed when bookings are cancelled
⏱️ Time Complexity Summary
Operation	Complexity	Reason
Booking	O(1)	Direct insertion
Serve Passenger	O(log n)	Priority queue handling
Search	O(n)	Linear traversal
Cancel	O(n)	Search + removal
Sorting	O(n log n)	STL sort per trip
Seat Assignment	O(n)	Seat scanning
🔁 Key System Concepts
Concept	Implementation
Trip Organization	Map-based grouping
Priority Handling	Priority queue + comparator
Regular Flow	FIFO queue
History Tracking	Stack structure
