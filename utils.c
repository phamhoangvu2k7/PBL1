#include "utils.h"
#include "my_string.h"
// bool start_with(const char *str, const char *key){
//     return strncmp(str, key, strlen(key)) == 0;
// }

int cung_ngay(NgayThang product1, NgayThang product2){
    if (product1.ngay == product2.ngay && product1.thang == product2.thang && product1.nam == product2.nam)
        return 1;
    return 0;
}

int check_trung_maHang(char maHang[], Node* danh_sach_hang){
    Node *cur = danh_sach_hang;
    
    while(cur != NULL){
        int n = string_len(cur->value->ma_hang, 40);
        int m = string_len(maHang, 40);

        if(string_cmp(cur->value->ma_hang, maHang, n, m)){
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}