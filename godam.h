#ifndef GODAM_H
#define GODAM_H
#include "common.h"
// ================== GODAM (INVENTORY) FUNCTION DECLARATIONS ==================
// Ye functions basically physical library ke "store room" wala kaam karte hain:
// nayi kitab lana, purani dikhana, galti se register hui ho to edit/delete karna, etc.
void nayiKitabDalo(Kitab shelf[]);  // Library me nayi kitab ko officially register karta hai
void sabDikhao(Kitab shelf[]);      // Saari currently registered kitabein console pe print karta hai
void kitabHatao(Kitab shelf[]);     // Safe delete: agar book issued hai to delete nahi karega
void editKitab(Kitab shelf[]);      // Data entry wali typos sudharne ka option
void sortKitabs(Kitab shelf[]);     // ID wise sorting (bubble sort, simple but enough for 200 books)
#endif