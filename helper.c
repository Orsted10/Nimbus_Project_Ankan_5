#include "helper.h"
int dhundoKitabIDSe(Kitab *shelf,int targetID){
    // Linear search standard tarike se
    for(int i=0;i<bookCount;i++){
        // Pointer arrow operator use kiya hai CO1 ke liye
        if((shelf+i)->id==targetID){
            return i; // Mil gaya, index return karo
        }
    }
    return -1; // Nahi mila, -1 return karo
}
// In helper.c

void searchByName(Kitab *shelf){
    char query[50];
    // 1. Clear buffer before asking for input (Safety first)
    // If the previous scanf left a newline, this might be needed depending on main.c
    // But if main.c handles it, just the fgets below is key.
    printf("\nSearch query (Title/Author): ");
    // 2. Use fgets to read input safely
    fgets(query, 50, stdin);
    // 3. NEWLINE KILLER: Remove the '\n' from the search query itself
    // This ensures we are searching for "Alchemist" and not "Alchemist\n"
    query[strcspn(query, "\n")] = 0;
    int found=0;
    printf("\nSearch Results:\n");
    for(int i=0;i<bookCount;i++){
        Kitab *k=(shelf+i);
        // Search Logic
        if(strstr(k->naam,query) || strstr(k->likhneWala,query)){
            // 4. Print Format Fix: Ensure everything is on one line
            // We print the ID, Title, and Author explicitly without extra newlines
            printf(">> FOUND: [ID: %d] %s by %s\n", k->id, k->naam, k->likhneWala);
            found=1;
        }
    }
    if(!found){
        printf(">> Kuch nahi mila bhai. Spelling check kar lo.\n");
    }
}
