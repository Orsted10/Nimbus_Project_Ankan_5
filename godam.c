#include "godam.h"
// ======================= NAYA STOCK ADD KARO =======================
// Ye function basically library me new entry create karta hai.
// Real life analogy: librarian register me new line likhta hai.
// Yaha hum user se details mangwa ke struct Kitab me bhar dete hain aur array me daal dete hain.
void nayiKitabDalo(Kitab shelf[]){
    // Sabse pehle safety check - capacity limit cross to nahi ho rahi
    if(bookCount>=MAX_KITABS){
        printf(">> Jagah nahi hai boss! Nayi almari khareedo pehle.\n");
        return;
    }
    Kitab k; // Local variable jisme pehle sab data fill karenge
    printf("\n--- Nayi Kitab Entry (Dhyan se bharna) ---\n");
    printf("ID batao (Unique honi chahiye): ");
    scanf("%d",&k.id);
    // scanf integer ke baad jo '\n' bachta hai, use clean karne ke liye ye loop
    int c; while((c=getchar())!='\n'&&c!=EOF);
    // Duplicate ID check - warna 2 kitabein same ID se ho jayengi, jo ki bahut bada confusion hai
    for(int i=0;i<bookCount;i++){
        if(shelf[i].id==k.id){
            printf(">> Oye! Ye ID %d pehle se exist karti hai. Cheating nahi.\n",k.id);
            return;
        }
    }
    // Ab safe hai, ID unique hai. Chalo actual text fields lete hain.
    printf("Kitab ka naam: ");
    fgets(k.naam,100,stdin);                        // fgets use kiya to spaces bhi aa sakte hain
    k.naam[strcspn(k.naam,"\n")]=0;                 // fgets by default '\n' bhi le aata hai, is line se hata diya
    printf("Lekhak (Author): ");
    fgets(k.lekhak,100,stdin);
    k.lekhak[strcspn(k.lekhak,"\n")]=0;
    printf("Genre (e.g. Horror/Code): ");
    fgets(k.genre,50,stdin);
    k.genre[strcspn(k.genre,"\n")]=0;
    printf("Keemat (Price in Rs): ");
    scanf("%d",&k.price);
    // Initial status: abhi abhi aayi hai, obvious si baat hai shelf pe available hogi
    k.availableHai=1;
    strcpy(k.studentName,"N/A"); // "Not Applicable" kyuki abhi kisi ke paas nahi
    strcpy(k.issueDate,"N/A");
    // Finally is ready-made Kitab struct ko hamare array me last index pe daaldo
    shelf[bookCount]=k;
    bookCount++; // Counter bhoolna nahi hai, warna data dikha hi nahi payega
    printf(">> Badhai ho! Kitab '%s' register ho gayi.\n",k.naam);
}
// ======================= SAARI KITABEIN DIKHAO ====================
// Basic listing function jo saari books ek table format me dikha deta hai.
// Viva me bol sakte ho "sir yaha formatted output ka use kiya hai (%-20s etc.)"
void sabDikhao(Kitab shelf[]){
    // Agar library me ek bhi kitab nahi hai to seedha message de do
    if(bookCount==0){
        printf(">> Library khali padi hai. Makkhi ud rahi hai.\n");
        return;
    }
    // Header line - nicely aligned columns
    printf("\n%-5s %-20s %-15s %-10s %-8s %-15s\n","ID","Title","Author","Genre","Status","Holder");
    printf("------------------------------------------------------------------------------\n");
    // Har kitab ek line me
    for(int i=0;i<bookCount;i++){
        printf("%-5d %-20s %-15s %-10s %-8s %-15s\n",
        shelf[i].id,
        shelf[i].naam,
        shelf[i].lekhak,
        shelf[i].genre,
        (shelf[i].availableHai==1)?"Avail":"ISSUED",      // Agar availableHai==1 to "Avail" warna "ISSUED"
        (shelf[i].availableHai==1)?"-":shelf[i].studentName); // Agar issued hai to naam dikhao
    }
    printf("------------------------------------------------------------------------------\n");
    printf(">> Total Kitabein: %d\n",bookCount);
}
// ======================= KITAB PERMANENT DELETE ===================
// Jab koi kitab itni purani ho jaye ki sirf raddi me kaam aaye, yaha se uda sakte hain.
// BUT: agar currently kisi student ke paas issued hai, to delete block kar denge.
void kitabHatao(Kitab shelf[]){
    int id,found=0;
    printf("\n--- Kitab Delete Panel (Soch samajh ke karna) ---\n");
    printf("Kaunsi ID udani hai: ");
    scanf("%d",&id);
    // Poore shelf me search karo
    for(int i=0;i<bookCount;i++){
        if(shelf[i].id==id){
            found=1;
            // Agar abhi kisi ke bag me pada hai to delete mat karne do
            if(shelf[i].availableHai==0){
                printf(">> Error: Ye kitab '%s' ke paas hai. Pehle wapas lo!\n",shelf[i].studentName);
                return;
            }
            // Array shifting: i-th index se aage sabko ek step left shift karna padega
            for(int j=i;j<bookCount-1;j++){
                shelf[j]=shelf[j+1];
            }
            bookCount--; // Total count 1 kam kar diya
            printf(">> Delete successful. Ab wo kitab itihas ban gayi.\n");
            break;
        }
    }
    if(!found) printf(">> Ye ID mili hi nahi. Hawa me teer mat chalao.\n");
}
// ======================= DATA ENTRY CORRECTION ====================
// kabhi-kabhi galti se spelling galat type ho jati hai, usse fix karne ke liye ye function hai.
void editKitab(Kitab shelf[]){
    int id;
    printf("\n--- Correction Window ---\n");
    printf("Kis ID me galti hui: ");
    scanf("%d",&id);
    // scanf ke baad buffer clean
    int c; while((c=getchar())!='\n'&&c!=EOF);
    // Jo ID mile, uska naam/author update karne ka option dete hain
    for(int i=0;i<bookCount;i++){
        if(shelf[i].id==id){
            printf("Purana Naam: %s\n",shelf[i].naam);
            printf("Naya Naam dalo: ");
            fgets(shelf[i].naam,100,stdin);
            shelf[i].naam[strcspn(shelf[i].naam,"\n")]=0;
            
            printf("Purana Author: %s\n",shelf[i].lekhak);
            printf("Naya Author: ");
            fgets(shelf[i].lekhak,100,stdin);
            shelf[i].lekhak[strcspn(shelf[i].lekhak,"\n")]=0;
            
            printf(">> Update ho gaya. Agli baar dhyan rakhna.\n");
            return;
        }
    }
    printf(">> ID not found boss.\n");
}
// ======================= SORTING (ID wise) ========================
// Simple bubble sort laga rahe hain. Sirf 200 books ke max case me bhi ye chill rahega.
// Logic: bar-bar adjacent elements compare kar ke galat order wale swap karna.
void sortKitabs(Kitab shelf[]){
    Kitab temp;
    int swapped;
    for(int i=0;i<bookCount-1;i++){
        swapped=0; // Optimization flag
        for(int j=0;j<bookCount-i-1;j++){
            if(shelf[j].id>shelf[j+1].id){
                // Typical 3-step swap
                temp=shelf[j];
                shelf[j]=shelf[j+1];
                shelf[j+1]=temp;
                swapped=1;
            }
        }
        // Agar poore inner loop me koi swap nahi hua,
        // iska matlab array already sorted hai, time bachane ke liye break kar do.
        if(swapped==0) break;
    }
    printf(">> Saari kitabein ID wise line me laga di hain.\n");
}