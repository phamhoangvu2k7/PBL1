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

int kiem_tra_thu_muc(ThuMuc product, ThuMuc danh_sach_thu_muc[], int so_thu_muc) {
    for (int i = 0; i < so_thu_muc; i++)
        if (strlen(product.ten_thu_muc) == strlen(danh_sach_thu_muc[i].ten_thu_muc) && start_with(product.ten_thu_muc, danh_sach_thu_muc[i].ten_thu_muc)) 
            return danh_sach_thu_muc[i].id;
    return 0;

}