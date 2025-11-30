#include "godam.h"
// Global variable yahan define hoga
int bookCount=0;
void setupLibrary(Kitab *shelf){
    // Thoda dummy data daal dete hain taki khali na lage
    // Pointer arithmetic use kar rahe bhai COs ke liye
    (shelf+0)->id=101;
    strcpy((shelf+0)->naam,"C Programming");
    strcpy((shelf+0)->likhneWala,"Dennis Ritchie");
    (shelf+0)->availableHai=1;
    strcpy((shelf+0)->kiskePaasHai,"Koi Nahi");
    bookCount++;

    (shelf+1)->id=102;
    strcpy((shelf+1)->naam,"Data Structures");
    strcpy((shelf+1)->likhneWala,"Tanenbaum");
    (shelf+1)->availableHai=1;
    strcpy((shelf+1)->kiskePaasHai,"Koi Nahi");
    bookCount++;
    // Do books kafi hain testing ke liye
}
void nayiKitabDalo(Kitab *shelf){
    if(bookCount>=MAX_KITABS){
        printf("\nArre bas kar bhai! Godam full hai (Array Overflow)\n");
        return;
    }
    Kitab *nayaMaal=(shelf+bookCount);
    printf("\n--- Nayi Kitab Entry ---\n");
    printf("ID batao: ");
    scanf("%d",&nayaMaal->id);
    // --- THE FIX IS HERE ---
    // scanf int padhta hai par 'Enter' chhod deta hai. 
    // Ye loop us 'Enter' ko kha jayega.
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    // -----------------------
    printf("Kitab ka naam kya hai: ");
    // Using gets is risky, but if you must:
    fgets(nayaMaal->naam,sizeof(nayaMaal->naam),stdin); 
    printf("Lekhak (Author) kaun hai: ");
    fgets(nayaMaal->likhneWala,sizeof(nayaMaal->likhneWala),stdin);
    nayaMaal->availableHai=1; 
    strcpy(nayaMaal->kiskePaasHai,"Koi Nahi");
    bookCount++;
    printf("\n>> Badhai ho! Kitab add ho gayi.\n");
}
void sabDikhao(Kitab *shelf){
    if(bookCount==0){
        printf("\nLibrary khali padi hai bhai makdi ke jaale hain bas.\n");
        return;
    }
    printf("\n%-5s %-20s %-20s %-15s\n","ID","Naam","Author","Status");
    printf("----------------------------------------------------------------\n");
    // Loop ghuma ke sab print marenge
    for(int i=0;i<bookCount;i++){
        Kitab *k=(shelf+i); // Pointer se access, efficiency pro max
        printf("%-5d %-20s %-20s %s\n",
               k->id,
               k->naam,
               k->likhneWala,
               (k->availableHai)?"Available":"Issued to Student");
    }
}

//Author - Made by Ankan (The Bengali) ;p
