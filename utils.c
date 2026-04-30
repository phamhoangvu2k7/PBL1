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

int cung_thang(NgayThang n1, NgayThang n2) {
    if (n1.thang == n2.thang && n1.nam == n2.nam)
        return 1;
    return 0;
}

int so_sanh_ngay(NgayThang n1, NgayThang n2) {
    if (n1.nam != n2.nam) return n1.nam - n2.nam;
    if (n1.thang != n2.thang) return n1.thang - n2.thang;
    return n1.ngay - n2.ngay;
}

int so_sanh_chu_cai(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
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