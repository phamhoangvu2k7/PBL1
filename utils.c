#include "utils.h"
#include <string.h>

bool start_with(const char *str, const char *key){
    return strncmp(str, key, strlen(key)) == 0;
}

bool cung_ngay(NgayThang product1, NgayThang product2){
    if (product1.ngay == product2.ngay && product1.thang == product2.thang && product1.nam == product2.nam)
        return true;
    return false;
}