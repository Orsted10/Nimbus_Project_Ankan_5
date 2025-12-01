#ifndef LENDEN_H
#define LENDEN_H
#include "common.h"
#include "helper.h" // History ke liye addTransaction yaha se aata hai
// ================== LEN-DEN (TRANSACTION) FUNCTION DECLARATIONS ===============
// Ye part basically "counter wala bhaiya" ka kaam karta hai - issue, return, fine, reservation, etc.

void kitabUthao(Kitab shelf[]);        // Student ko kitab dena (issue karna)
void kitabWapasKaro(Kitab shelf[]);    // Student se kitab wapas lena + fine ka hisaab
void reservationSystem(Kitab shelf[]); // Agar kitab kisi ke paas hai to waitlist me naam daalna
void showWaitlist();                   // Abhi ka pura waiting list status dikha deta hai
#endif