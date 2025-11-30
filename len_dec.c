#include "len_den.h"
#include "helper.h" // Search function chahiye hoga
void kitabUthao(Kitab *shelf){
    int targetID;
    printf("\nKaunsi kitab chahiye (ID batao): ");
    scanf("%d",&targetID);
    // --- THE FIX IS HERE ---
    // Consume the newline left by scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // -----------------------
    int index=dhundoKitabIDSe(shelf,targetID);
    if(index==-1){
        printf(">> Bhai aisi koi kitab nahi hai apne paas.\n");
    }else{
        Kitab *ptr=(shelf+index);
        if(ptr->availableHai==0){
            printf(">> Sorry boss, ye book already %s le gaya hai.\n",ptr->kiskePaasHai);
        }else{
            printf("Apna naam batao: ");
            gets(ptr->kiskePaasHai); // Now this will actually wait for input!
            ptr->availableHai=0;
            printf(">> Le jao bhai, par time pe wapas kar dena.\n");
        }
    }
}
void kitabWapasKaro(Kitab *shelf){
    int targetID;
    printf("\nWapas karne wali kitab ka ID: ");
    scanf("%d",&targetID);
    int index=dhundoKitabIDSe(shelf,targetID);
    if(index==-1){
        printf(">> Galat ID. Ye hamari library ki book hi nahi lag rahi.\n");
    }else{
        Kitab *ptr=(shelf+index);
        if(ptr->availableHai==1){
            printf(">> Bhai ye book to already shelf pe hai, kyu mazaak kar raha hai?\n");
        }else{
            printf(">> Shukriya %s bhai, book wapas mil gayi.\n",ptr->kiskePaasHai);
            ptr->availableHai=1;
            strcpy(ptr->kiskePaasHai,"Koi Nahi");
        }
    }
}