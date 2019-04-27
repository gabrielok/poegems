#include <stdio.h>
#include <stdlib.h>

void swap(int *xp, int *yp) { 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void bubbleSort(int arr[], int n) { 
   int i, j, swapped; 
   for (i = 0; i < n-1; i++) { 
    swapped = 0; 
    for (j = 0; j < n-i-1; j++) { 
        if (arr[j] < arr[j+1]) { 
           swap(&arr[j], &arr[j+1]); 
           swapped = 1; 
        } 
     } 
     
     if (swapped == 0) 
        break; 
   }
}

void copyArray(int arr1[], int arr2[], int arrlen) {
    // Copies array 1 into array 2
    for (int i = 0; i < arrlen; i++) {
        arr2[i] = arr1[i];
    }
}

void printArray(int arr[], int arrlen) {
    // Prints the numbers in the array
    for (int i=0; i < arrlen; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int again = 1;
int gems [20];
int num, bestSum, bestLen;
int bestComb [20];

void gemAdd(int i, int sum, int len, int comb [20]) {
    if (i == num || bestSum == 40) {
        return;
    }
    // dont add itself, go to next gem
    gemAdd(i+1,sum,len,comb);
    
    // add itself
    if (bestSum == 40) {
        return;
    }
    sum += gems[i];
    comb[len] = gems[i];
    len++;
    // check if it's a better combination
    if (abs(sum-40) <= abs(bestSum-40)) {
        if (abs(sum-40) == abs(bestSum-40) && sum < 40) {
            // nothing -- keep the > 40 combination
        } else {
            copyArray(comb,bestComb,len);
            bestSum = sum;
            bestLen = len;
        }
    }
    gemAdd(i+1,sum,len,comb);
}

int main()
{
    char temp [90];
    char * s;
    
    while (again == 1) {
        // reset global variables
        num = 0;
        bestSum = 0;
        bestLen = 0;
        for (int i = 0; i < 20; i++) {
            gems[i] = 0;
            bestComb[i] = 0;
        }
        
        // get the number of gems
        printf("Input number of gems: ");
        fgets(temp, 90, stdin);
        num = atoi(temp);
        
        // get their quality values
        printf("Input quality values: ");
        fgets(temp, 90, stdin);
        
        // transform the string into an int array
        for (int i = 0; i < num; i++) {
            s = temp + i*3;
            gems[i] = atoi(s);
        }
        
        // sort gems from highest to lowest quality
        bubbleSort(gems,num);
        
        // find the best combination recursively
        gemAdd(0,0,0,bestComb);
        
        printf("\n-----Results-----\n");
        if (bestSum < 40) {
            printf("Not enough quality. Total: %d\n", bestSum);
        } else if (bestSum == 40) {
            printf("Perfect! Combination: ");
            printArray(bestComb,bestLen);
        } else if (bestSum < 45) {
            printf("A little too much! Total: %d Combination: ", bestSum);
            printArray(bestComb,bestLen);
        } else {
            printf("Too much! Total: %d Combination: ", bestSum);
            printArray(bestComb,bestLen);
        }
        
        printf("\nAgain? ");
        fgets(temp, 90, stdin);
        again = atoi(temp);
    }
}
