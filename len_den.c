#include "len_den.h"
// ======================= ISSUE COUNTER LOGIC ======================
// Ye function real life me "librarian counter" ka kaam karta hai:
// student ID deta hai, naam batata hai, date batata hai, aur system me entry ho jati hai.
void kitabUthao(Kitab shelf[]){
    int id,found=0;
    printf("\n--- ISSUE COUNTER ---\n");
    printf("Kaunsi Kitab (ID): ");
    scanf("%d",&id);
    // scanf ke baad jo newline bachta hai, use ignore karne ke liye
    int c; while((c=getchar())!='\n'&&c!=EOF);
    // Poore shelf me ghoom ke dekhte hain
    for(int i=0;i<bookCount;i++){
        if(shelf[i].id==id){
            found=1;   
            // Agar already kisi ke paas hai to direct mana
            if(shelf[i].availableHai==0){
                printf(">> Sorry boss, ye abhi '%s' le gaya hai.\n",shelf[i].studentName);
                printf(">> Tip: Reservation system use kar lo.\n");
            }else{
                // Yahi pe issue process start hota hai
                printf("Student ka naam: ");
                fgets(shelf[i].studentName,50,stdin);
                shelf[i].studentName[strcspn(shelf[i].studentName,"\n")]=0;
                printf("Aaj ki Date (DD/MM/YYYY): ");
                fgets(shelf[i].issueDate,20,stdin);
                shelf[i].issueDate[strcspn(shelf[i].issueDate,"\n")]=0;
                shelf[i].availableHai=0; // Ab ye book officially "bahar" hai
                // History log me bhi entry karo
                addTransaction(shelf[i].id,shelf[i].studentName,"ISSUE");
                printf(">> Issued! %s, isko phadna mat please.\n",shelf[i].studentName);
            }
            break;
        }
    }
    if(!found) printf(">> Wrong ID. Pehle list check kar lo.\n");
}
// ======================= RETURN + FINE LOGIC ======================
// Jab student kitab wapas laata hai, yaha se:
// 1) Check karte hain sach me issued thi ya nahi,
// 2) Fine calculate karte hain agar late hai,
// 3) History me RETURN entry likhte hain,
// 4) Status fir se available kar dete hain.
void kitabWapasKaro(Kitab shelf[]){
    int id,found=0;
    printf("\n--- RETURN & FINE COUNTER ---\n");
    printf("Kitab ID wapas aayi: ");
    scanf("%d",&id);
    for(int i=0;i<bookCount;i++){
        if(shelf[i].id==id){
            found=1;
            // Agar already system ke hisab se ye book shelf pe hai,
            // to student ki memory pe question uthta hai :)
            if(shelf[i].availableHai==1){
                printf(">> Ye kitab to library me hi hai. Kisko wapas kar rahe ho?\n");
            }else{
                int days;
                printf("Kitne din rakhi thi (Sach bolna): ");
                scanf("%d",&days);
                // Simple rule: 15 din tak free, uske baad har din fine lagega
                if(days>15){
                    int extra=days-15;
                    int fine=extra*FINE_PER_DAY;
                    printf(">> LATE ENTRY! 15 din allowed the.\n");
                    printf(">> %d din late ho. Total Fine: Rs %d\n",extra,fine);
                    printf(">> Fine diya? (1=Haan/0=Nahi): ");
                    int paid;
                    scanf("%d",&paid);
                    if(paid==1){
                        totalFineCollected+=fine;
                    }else{
                        printf(">> Udhaar khata me likh raha hu fir.\n");
                    }
                }else{
                    printf(">> Time pe wapas karne ke liye shukriya.\n");
                }
                // History log me RETURN tag ke saath entry
                addTransaction(shelf[i].id,shelf[i].studentName,"RETURN");
                // Ab ye kitab fir se freely available hai
                shelf[i].availableHai=1;
                printf(">> Kitab wapas shelf pe rakh di gayi hai.\n");
                // Bonus: Agar koi waitlist me is kitab ke liye tha, usko notify kar sakte hain
                for(int w=0;w<waitCount;w++){
                    if(waitlist[w].kitabId==id){
                        printf(">> NOTIFICATION: %s is kitab ka wait kar raha tha!\n",waitlist[w].studentName);
                        // Chaho to yaha waitlist se remove bhi kar sakte ho
                    }
                }
            }
            break;
        }
    }
    if(!found) printf(">> Database me aisi koi ID nahi hai.\n");
}
// ======================= RESERVATION / WAITLIST ===================
// Jab student kisi aisi kitab ka demand kare jo already kisi ke paas hai,
// to uska naam ek choti si list me daal dete hain taaki wapas aane pe usko priority mile.
void reservationSystem(Kitab shelf[]){
    if(waitCount>=MAX_WAITLIST){
        printf(">> Waiting list full hai. Kal aana.\n");
        return;
    }
    int id;
    printf("\n--- Reservation Desk ---\n");
    printf("Kis ID ke liye wait karna hai: ");
    scanf("%d",&id);
    // Again buffer clear, warna fgets niche skip ho jayega
    int c; while((c=getchar())!='\n'&&c!=EOF);
    int exists=0;
    for(int i=0;i<bookCount;i++){
        if(shelf[i].id==id) exists=1;
    }
    if(exists){
        waitlist[waitCount].kitabId=id;
        printf("Apna naam batao: ");
        fgets(waitlist[waitCount].studentName,50,stdin);
        waitlist[waitCount].studentName[strcspn(waitlist[waitCount].studentName,"\n")]=0;
        waitCount++;
        printf(">> Naam likh liya hai. Jab kitab aayegi bata denge.\n");
    }else{
        printf(">> Aisi kitab hi nahi hai, wait kiska karoge?\n");
    }
}
// ======================= WAITLIST DISPLAY =========================
// Just info panel: currently kaun kaun kis kitab ke liye wait kar raha hai.
void showWaitlist(){
    printf("\n--- Waiting List ---\n");
    if(waitCount==0){
        printf(">> Koi line me nahi hai.\n");
        return;
    }
    for(int i=0;i<waitCount;i++){
        printf("%d. %s is waiting for Book ID %d\n",i+1,waitlist[i].studentName,waitlist[i].kitabId);
    }
}