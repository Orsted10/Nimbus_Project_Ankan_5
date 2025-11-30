# **Desi Library Management System**

*"Because remembering who took which book is too mainstream."*

---

## **Project Objective**

*Target: 100/100 Marks (Zero negotiation).*

**Core Purpose:** The main purpose is to implement a Library Book Management System using C that handles cataloging, issuing, and returning books efficiently. The system is Desi style to interact with Indian Students more easily and friendly.

**Real-world Context:** Libraries are messy. Students forget to return books. Librarians lose their minds. We fixed it.

## **Key Tech Stack:**

*C Language:* The grandfather of all languages. Basically a language which helped the upbringing of many more languages and being the backbone of all infrastructures.

*Pointers:* Because we like living dangerously with memory addresses.

*Structs:* To keep our data organized (unlike our dorm rooms).

*Modular Programming:* 4 Source files + 4 Header files (Professional stuff). 

## **The "Dream Team" (Credits)**

Built with lots of caffeine ☕ and 💻 many late nights debugging by:

*Ankan* - Backend Logic & Pointer Wizardry

*Protistha* - Database Structure & Variables

*Shivansh* - Search Algorithms & Bug Hunting

*Aditya* - Documentation & Viva Defense Squad

## **How to Compile & Run (Don't mess this up)**

*Since we used Modular Programming (fancy, right?), you can't just hit "Run" on main.c. You have to link the object files.*

*Step 1: Open Terminal*

Go to the folder where you dumped our code.

*Step 2: Compile*

Type this magic spell into your terminal:

*gcc main.c godam.c len_den.c helper.c -o library_app*

*Step 3: Run*

Launch the beast:

*./library_app*

## **Output & Usage Guide**

**1. The Main Menu**

(Looks professional, works like a charm, with desi masala)

=== DESI LIBRARY MANAGEMENT ===
1. Kitab List Dekho         <-- See all books
2. Nayi Kitab Add Karo      <-- Add new stock
3. Kitab Issue Karo         <-- Give book to student
4. Kitab Return Karo        <-- Get book back
5. Search Karo              <-- Find book
6. Exit (Bhago)             <-- Run away
Enter choice: _

**2. Adding a Book (godam.c in action)**

We use gets() because we like living on the edge, but fflush(stdin) saves us.

--- Nayi Kitab Entry ---

ID batao: 105

Kitab ka naam kya hai: The Alchemist

Lekhak (Author) kaun hai: Paulo Coelho

>> Badhai ho! Kitab add ho gayi.

**3. Issuing a Book (len_den.c logic)**

Checks availability instantly. No fake promises.

Kaunsi kitab chahiye (ID batao): 105

Apna naam batao: Aditya

>> Le jao bhai, par time pe wapas kar dena.

**4. Search Feature (helper.c logic)**

Finds partial matches because students never remember full titles.

Search query (Title/Author): Alch

Search Results:

>> FOUND: [ID: 105] The Alchemist by Paulo Coelho
