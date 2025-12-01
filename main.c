#include "common.h"
#include "godam.h"
#include "len_den.h"
#include "helper.h"
// ======================= GLOBAL VARIABLE DEFINITIONS ==============
// Declaration common.h me thi (extern ke saath), actual memory yaha allocate ho rahi hai.
int bookCount=0;
int txnCount=0;
int waitCount=0;
int totalFineCollected=0;
Transaction history[MAX_HISTORY];
Reservation waitlist[MAX_WAITLIST];
// ======================= MAIN FUNCTION ============================
// Ye hi hamara program ka entry point hai. Yahi se pura menu driven flow control hota hai.
int main(){
    // Array of structs, jaha har index ek kitab ka record hold karega
    Kitab libraryShelf[MAX_KITABS];
    int choice;
    int running=1; // Flag jis sai while loop control hoga
    // Step 1: Security check
    if(!loginSystem()){
        // Galat password dala, to direct exit. Data safe.
        return 0;
    }
    // Step 2: Pichli baar ka data agar exist karta hai to load karo
    loadSabKuch(libraryShelf);
    // Step 3: Infinite style loop, jab tak user "Save & Exit" nahi bolta
    while(running){
        printf("\n=== MAIN MENU ===\n");
        printf("1. Stock Dekho (List)\n");
        printf("2. Nayi Kitab Add Karo\n");
        printf("3. Kitab Issue Karo\n");
        printf("4. Kitab Return Karo\n");
        printf("5. Waitlist/Reservation\n");
        printf("6. Search (Khoj)\n");
        printf("7. Reports & Stats\n");
        printf("8. History Log (Audit)\n");
        printf("9. Edit/Sort/Delete (Admin Tools)\n");
        printf("10. Save & Exit (Tata Bye Bye)\n");
        printf("Choice batao: ");
        scanf("%d",&choice);
        // Switch-case: best pattern for menu driven programs, theory me bhi likh sakte ho
        switch(choice){
            case 1:
                sabDikhao(libraryShelf);
                break;
            case 2:
                nayiKitabDalo(libraryShelf);
                break;
            case 3:
                kitabUthao(libraryShelf);
                break;
            case 4:
                kitabWapasKaro(libraryShelf);
                break;
            case 5:{
                // Nested mini menu specifically waitlist ke liye
                printf("1. Reserve Karo\n2. List Dekho\nChoose: ");
                int r;
                scanf("%d",&r);
                if(r==1) reservationSystem(libraryShelf);
                else showWaitlist();
                break;
            }
            case 6:
                searchEngine(libraryShelf);
                break;
            case 7:
                reportCard(libraryShelf);
                break;
            case 8:
                showHistory();
                break;
            case 9:{
                // Admin tools ka chota menu
                printf("1. Edit\n2. Delete\n3. Sort\nChoose: ");
                int tool;
                scanf("%d",&tool);
                if(tool==1) editKitab(libraryShelf);
                else if(tool==2) kitabHatao(libraryShelf);
                else if(tool==3) sortKitabs(libraryShelf);
                break;
            }
            case 10:
                // Exit se pehle data safe karna bahut zaroori hai
                saveSabKuch(libraryShelf);
                printf(">> Program band ho raha hai. Padhai kar lena thodi.\n");
                running=0;
                break;
            default:
                printf(">> Galat button dabaya. 1 se 10 me se choose karo.\n");
        }
    }
    return 0;
}