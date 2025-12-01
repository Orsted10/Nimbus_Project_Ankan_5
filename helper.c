#include "helper.h"
// ======================= LOGIN / SECURITY =========================
// Basic password check: taaki koi bhi random banda program chala ke data na bigaad de.
// Real projects me obviously hashed password, role based auth hota, but yaha viva-level demo ke liye enough hai.
int loginSystem(){
    char pass[20];
    printf("\n========================================\n");
    printf("   DESI LIBRARY MANAGEMENT SYSTEM   \n");
    printf("========================================\n");
    printf("Security Check required.\n");
    printf("Password dalo (Hint: admin123): ");
    scanf("%s",pass);
    // strcmp 0 deta hai jab strings equal hoti hain
    if(strcmp(pass,PASSWORD)==0){
        printf(">> Access Granted. Welcome Boss!\n");
        return 1;
    }else{
        printf(">> GALAT PASSWORD. Security alert baja dunga!\n");
        return 0;
    }
}
// ======================= SAVE TO FILE =============================
// Ye function pura in-memory data (books + history) ko ek text file me dump karta hai.
// Taaki program band karne ke baad bhi data bacha rahe (persistent storage).
void saveSabKuch(Kitab shelf[]){
    FILE *f=fopen("library_data.txt","w");
    if(f==NULL){
        printf(">> Error: File create nahi ho pa rahi. Disk full hai kya?\n");
        return;
    }
    // Pehle top level counters likh rahe hain, jisse load karte time
    // hume pata rahe kitni entries aage padhni hain.
    fprintf(f,"%d\n%d\n%d\n",bookCount,totalFineCollected,txnCount);
    // Ab har kitab ek block me likhte hain
    for(int i=0;i<bookCount;i++){
        // Har field alag line pe, taaki fscanf/fgets se easily parse ho jaye
        fprintf(f,"%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n",
        shelf[i].id, shelf[i].price, shelf[i].availableHai,
        shelf[i].naam, shelf[i].lekhak, shelf[i].genre,
        shelf[i].studentName, shelf[i].issueDate);
    }
    // Transaction history bhi dump kar dete hain (audit trail)
    for(int i=0;i<txnCount;i++){
        fprintf(f,"%d\n%d\n%s\n%s\n%s\n",
        history[i].txnId, history[i].kitabId, history[i].studentName,
        history[i].type, history[i].timestamp);
    }
    fclose(f);
    printf(">> Data saved successfully. Bijli gayi to bhi tension nahi.\n");
}
// ======================= LOAD FROM FILE ===========================
// Program start hotee hi ye function check karta hai ki purana "library_data.txt" hai ya nahi.
// Agar hai to usse sari kitabein + history wapas memory me load kar leta hai.
void loadSabKuch(Kitab shelf[]){
    FILE *f=fopen("library_data.txt","r");
    if(f==NULL){
        // Pehla run ya file delete ho gayi, to simply empty start
        printf(">> Welcome New User! Koi purana data nahi mila.\n");
        return;
    }
    // Pehle 3 master values read karo
    fscanf(f,"%d",&bookCount);
    fscanf(f,"%d",&totalFineCollected);
    fscanf(f,"%d",&txnCount);
    
    // Last fscanf ke baad ek newline bacha hoga, use consume karne ke liye fgetc
    fgetc(f);
    // Ab sequentially books read kar rahe hain, same format jaisa save time pe likha tha
    for(int i=0;i<bookCount;i++){
        fscanf(f,"%d",&shelf[i].id);
        fscanf(f,"%d",&shelf[i].price);
        fscanf(f,"%d",&shelf[i].availableHai);
        fgetc(f); // newline eater
        fgets(shelf[i].naam,100,f);      shelf[i].naam[strcspn(shelf[i].naam,"\n")]=0;
        fgets(shelf[i].lekhak,100,f);    shelf[i].lekhak[strcspn(shelf[i].lekhak,"\n")]=0;
        fgets(shelf[i].genre,50,f);      shelf[i].genre[strcspn(shelf[i].genre,"\n")]=0;
        fgets(shelf[i].studentName,50,f);shelf[i].studentName[strcspn(shelf[i].studentName,"\n")]=0;
        fgets(shelf[i].issueDate,20,f);  shelf[i].issueDate[strcspn(shelf[i].issueDate,"\n")]=0;
    }
    // Ab utni hi history entries read karo jitni txnCount hai
    for(int i=0;i<txnCount;i++){
        fscanf(f,"%d",&history[i].txnId);
        fscanf(f,"%d",&history[i].kitabId);
        fgetc(f);
        fgets(history[i].studentName,50,f); history[i].studentName[strcspn(history[i].studentName,"\n")]=0;
        fgets(history[i].type,10,f);        history[i].type[strcspn(history[i].type,"\n")]=0;
        fgets(history[i].timestamp,30,f);   history[i].timestamp[strcspn(history[i].timestamp,"\n")]=0;
    }
    fclose(f);
    printf(">> Purana data load ho gaya. Total %d kitabein hain.\n",bookCount);
}
// ======================= SEARCH ENGINE ============================
// Sasta Google: user jo string dega usko title, author aur genre me partial match ki tarah dhundenge.
// E.g. "Har" search karega "Harry Potter", "Harper Lee", "Horror" sab me.
void searchEngine(Kitab shelf[]){
    char query[50];
    int found=0;
    printf("\n--- Google (Sasta wala) ---\n");
    printf("Search (Title/Author/Genre): ");
    // Pehle input buffer clean
    int c; while((c=getchar())!='\n'&&c!=EOF);
    fgets(query,50,stdin);
    query[strcspn(query,"\n")]=0; // trailing '\n' hata diya
    printf("Results:\n");
    for(int i=0;i<bookCount;i++){
        // strstr substring dhoondta hai; NULL nahi mila matlab match hua.
        if(strstr(shelf[i].naam,query)||strstr(shelf[i].lekhak,query)||strstr(shelf[i].genre,query)){
            printf(">> FOUND: [ID: %d] %s by %s (%s)\n",
            shelf[i].id,shelf[i].naam,shelf[i].lekhak,shelf[i].genre);
            found=1;
        }
    }
    if(!found) printf(">> Kuch nahi mila bhai. Spelling check karo.\n");
}
// ======================= REPORT / ANALYTICS =======================
// Ye function high-level stats print karta hai jo viva me dikhane ke liye mast hai:
// kitni books, kitni issued, kitna fine, kitni transactions, etc.
void reportCard(Kitab shelf[]){
    int issued=0;
    
    for(int i=0;i<bookCount;i++){
        if(shelf[i].availableHai==0) issued++;
    }
    printf("\n--- LIBRARY ANALYTICS (Viva stats) ---\n");
    printf("Total Books:     %d\n",bookCount);
    printf("Books Issued:    %d (Padaku log)\n",issued);
    printf("Books in Godam:  %d\n",bookCount-issued);
    printf("Total Fine:      Rs %d (Chai-sutta budget)\n",totalFineCollected);
    printf("Total Txns:      %d\n",txnCount);
    printf("--------------------------------------\n");
}
// ======================= ADD TO HISTORY LOG =======================
// Ye helper har ISSUE/RETURN ke waqt ek new Transaction entry banata hai.
// Yahi se hum later poora "who did what when" ka record dikha sakte hain.
void addTransaction(int bid,char *sname,char *type){
    if(txnCount>=MAX_HISTORY){
        // Simple guard: agar history array full ho gaya to new entries skip kar denge
        return;
    }
    history[txnCount].txnId=txnCount+1;
    history[txnCount].kitabId=bid;
    strcpy(history[txnCount].studentName,sname);
    strcpy(history[txnCount].type,type);
    // Current system time stash karne ka standard C ka jugad (time + ctime)
    time_t t;
    time(&t);
    strcpy(history[txnCount].timestamp,ctime(&t));
    history[txnCount].timestamp[strcspn(history[txnCount].timestamp,"\n")]=0; // ctime ka '\n' hata diya
    txnCount++;
}
// ======================= HISTORY DISPLAY ==========================
// Simple for loop jo har transaction print kar deta hai readable format me.
// Ye pura "audit log" hai jo viva ke time sir ko impress karega.
void showHistory(){
    printf("\n--- LOG BOOK (Kaun kab kya le gaya) ---\n");
    if(txnCount==0){
        printf(">> Abhi tak koi transaction hi nahi hua. System bilkul naya hai.\n");
        return;
    }
    for(int i=0;i<txnCount;i++){
        printf("[%s] ID:%d | User:%s | Action:%s | Time:%s\n",
        history[i].timestamp, history[i].kitabId,
        history[i].studentName, history[i].type, history[i].timestamp);
    }
}