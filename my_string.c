#include "my_string.h"

int string_cmp(char a[], char b[], int n, int m){
    if(n != m) return 0;
    int i = 0;
    while(i < n){
        if(a[i] != b[i]) return 0;
        i++;
    }
    return 1;
}

int string_head_dup(char a[], char b[], int n){
    int i;
    for(i = 0; i < n; i++){
        if(b[i] != a[i]){
            return 0;
        }
    }
    return 1;
}

int string_len(char a[], int max_size){
    int n = 0;
    while(n < max_size && a[n] != '\0'){
        n++;
    }
    return n;
}
   