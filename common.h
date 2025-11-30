#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Bhai max books itni hi hongi, library choti hai
#define MAX_KITABS 100
// Structure for our book... I mean Kitab
typedef struct{
    int id;
    char naam[50];        // Book title
    char likhneWala[50];  // Author name
    int availableHai;     // 1 agar shelf pe hai, 0 agar kisi ne utha li
    char kiskePaasHai[50];// Student ka naam agar issue hui hai
}Kitab;
// Global counter taki pata rahe kitni books hain abhi
// Extern use kar rahe taki har jagah dikhe
extern int bookCount;
#endif
