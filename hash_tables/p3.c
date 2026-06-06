/*
    Idea: (problem where one-off errors runs rampant)
        observe the following
                xef
               /
        abcdxx
        ------ \
         |      ef
         LCP (longest common prefix) mismatch happen at index p

         abcdx 
               \
                 xxef
               / ----
          abcd   |
                 LCS (longest common suffix) mismatch happens at (N - 1) - s
                 where s is the length of longest common suffix
                 and N is the length of the first string
*/

#include "../utils.h"

// returns the index from the left where first mismatch occurs
// after comparing strings from the left 
int upper_bound(char *a, char *b, int Nb) {
    int i = 0;
    while (i < Nb && a[i] == b[i]) {
        i++;
    }
    return i;
}

// returns the index from the left where first mismatch occurs
// after comparing strings from the right
int lower_bound(char *a, char *b, int Na) {
    int i = Na - 1;
    while(i > 0 && a[i] == b[i - 1]) {
        i--;
    }
    return i;
}


int main() {
    char s1[] = "axxb";
    char s2[] = "axb";
    int Na = strlen(s1);
    int Nb = strlen(s2);
    int a = lower_bound(s1, s2, Na);
    int b = upper_bound(s1, s2, Nb);

    if (b < a || a == b) {
        printf("0");
    }
    for (int i = a; i <= b; i++) {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}