#ifndef COMMON_H
#define COMMON_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
// ====================== GLOBAL SETTINGS ZONE ======================
// Yaha pe saari "constants" rakhi hain jo pura system control karti hain.
// Agar kal ko library badi ho jaye / fine badhana ho / waitlist limit badhani ho,
// bas yaha values change karni hain, poora code automatically adjust ho jayega.

#define MAX_KITABS 200       // Library godam me maximum itni hi kitabein rakh sakte hain abhi
#define MAX_HISTORY 500      // History log me maximum itne hi paap (transactions) yad rahenge
#define MAX_WAITLIST 50      // Ek kitab ke chakkar me kitni jaan line me khadi ho sakti hai
#define PASSWORD "admin123"  // Admin ka password - beta viva me bolo "sir hardcoded hai demo ke liye"
#define FINE_PER_DAY 10      // 15 din ke baad har extra din ka fine (Rs). Inflation OP.

// ====================== STRUCTS ZONE ==============================
// Yaha pe hum apna custom data type bana rahe hain (struct).
// Basically C me "Kitab" naam ka object create kar diya jiska khud ka ID, naam, author etc. hai.
// Ye hamara main hero hai - har book/kitab ka poora biodata yahi store hoga.
typedef struct{
    int id;                  // Unique ID: ye hi primary key hai pura system ki
    char naam[100];          // Book title, thoda lamba bhi aa jaye to tension nahi
    char lekhak[100];        // Author ka naam (jisne mehnat ki)
    char genre[50];          // Type: e.g. "CS", "Novel", "Horror", "Self-help"
    int price;               // Market price; agar kho jaye to itna jurmana lag sakta hai
    int availableHai;        // 1 == shelf pe maujood, 0 == kisi student ke bag me ghaas kha rahi
    char studentName[50];    // Agar issued hai to yaha jis bande ke paas hai uska naam aayega
    char issueDate[20];      // DD/MM/YYYY format me string, simple rakhne ke liye
}Kitab;
// Har bar jab koi kitab issue ya return hoti hai, uska record yaha aayega.
// Ye future me "audit" ya "who did what" ke liye mast kaam aa sakta hai.
typedef struct{
    int txnId;               // Serial number of transaction (1,2,3,...)
    int kitabId;             // Kis kitab pe ye transaction hua
    char studentName[50];    // Kaun banda involve tha (student ka naam)
    char type[10];           // "ISSUE" ya "RETURN" - clear tag
    char timestamp[30];      // Exact time stamp string (ctime se aata hai)
}Transaction;
// Reservation system (waitlist) ke entries.
// Jab koi kitab already kisi ke paas ho aur next banda wait karna chahe.
typedef struct{
    int kitabId;             // Kis kitab ke liye wait chal raha hai
    char studentName[50];    // Kaun wait kar raha hai
}Reservation;
// ====================== GLOBAL STATE VARIABLES ====================
// Ye variables pure project me "extern" ke through visible rahenge.
// Inka definition main.c me hoga, yaha sirf declaration hai.
// Total kitabein currently system me
extern int bookCount;
// Total transactions jitne bhi history me record kiye gaye
extern int txnCount;
// Waitlist me abhi tak kitni entries bhari gayi hain
extern int waitCount;
// Fine se ab tak kitna paisa kama liya (hypothetical)
extern int totalFineCollected;
// Global arrays jaha puri history aur waitlist ka data pada rahega
extern Transaction history[MAX_HISTORY];
extern Reservation waitlist[MAX_WAITLIST];

#endif