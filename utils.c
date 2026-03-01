#include "utils.h"
#include <string.h>
#include <ctype.h>

bool start_with(const char *str, const char *key){
    for (int i = 0; i < strlen(key); i++) {
        if (tolower(str[i]) != tolower(key[i])) return false;
    }
    return true;
}

bool cung_ngay(NgayThang product1, NgayThang product2){
    if (product1.ngay == product2.ngay && product1.thang == product2.thang && product1.nam == product2.nam)
        return true;
    return false;
}