#ifndef HELPER_H
#define HELPER_H
#include "common.h"
// ===================== HELPER / UTILITY FUNCTION DECLARATIONS =================
// Ye sab "side heroes" hain jo main kahani ko smooth banate hain: login, file save/load, search, reports, etc.
int loginSystem();                      // Simple password based login, taaki random banda data na bigaad de
void saveSabKuch(Kitab shelf[]);        // Saari current state ko file me dump kar deta hai (persistent storage)
void loadSabKuch(Kitab shelf[]);        // Program start hone pe file se data wapas laata hai
void searchEngine(Kitab shelf[]);       // Title/Author/Genre based search (partial match supported)
void reportCard(Kitab shelf[]);         // Overall stats / analytics viva ke liye
void addTransaction(int bid,char *sname,char *type); // History me naya record add karta hai
void showHistory();                     // Poora transaction log print karta hai
#endif