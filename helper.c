#include "helper.h"

// --- ID se kitab dhundne wala function ---
// Ye linear search hai, O(n) complexity (Exam me likh dena, marks milenge)
int dhundoKitabIDSe(Kitab *shelf,int targetID){
    // Loop ghuma ke check kar rahe hain
    for(int i=0;i<bookCount;i++){
        // Pointer arrow operator use kiya hai taki pointer arithmetic ka swaad aaye
        if((shelf+i)->id==targetID){
            return i; // Mil gaya maal! Index return karo
        }
    }
    return -1; // 404 Not Found - Kitab gayab hai
}
// --- Naam ya Author se search karne wala function ---
// Google jaisa feel dene ki koshish
void searchByName(Kitab *shelf){
    char query[50];
    // 1. Pichle scanf ka leftover 'Enter' khana padega
    // Nahi to ye function shuru hote hi khatam ho jayega
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nSearch query (Title/Author): ");
    // Gets use nahi kiya, unsafe hai. Fgets is our responsible friend.
    fgets(query, 50, stdin);
    // 2. Newline killer logic
    // Kyunki fgets end me '\n' chipka deta hai, usko hatana padega
    query[strcspn(query, "\n")] = 0;
    int found=0; // Flag variable (mil gaya to 1, nahi to 0)
    printf("\nSearch Results:\n");
    // Poori library scan maro
    for(int i=0;i<bookCount;i++){
        Kitab *k=(shelf+i);
        // 3. strstr = String ke andar String dhundo (Substring search)
        // Agar Title me ya Author me match mila, to print karo
        if(strstr(k->naam,query) || strstr(k->likhneWala,query)){
            // 4. NUCLEAR PRINT STRATEGY
            // Hum direct %s print nahi karenge kyunki kabhi kabhi 'Enter'
            // chipak ke aa jata hai. Character by character print karenge.
            // Safai abhiyan chalu!
            printf(">> FOUND: [ID: %d] ", k->id);
            // Naam print karo, par newline mat aane do
            for(int j=0; k->naam[j] != '\0'; j++) {
                if(k->naam[j] != '\n') printf("%c", k->naam[j]);
            }
            printf(" by ");
            // Author print karo, bina newline ke
            for(int j=0; k->likhneWala[j] != '\0'; j++) {
                if(k->likhneWala[j] != '\n') printf("%c", k->likhneWala[j]);
            }
            printf("\n"); // Ab final enter maaro
            found=1; // Mil gayi kitab!
        }
    }
    // Agar loop khatam aur kuch nahi mila...
    if(!found){
        printf(">> Kuch nahi mila bhai. Spelling check kar lo ya chashma laga lo.\n");
    }
}
