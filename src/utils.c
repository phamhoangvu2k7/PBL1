#include "../library/utils.h"
#include "../library/my_string.h"

int so_sanh_ngay(NgayThang n1, NgayThang n2) {
    if (n1.nam != n2.nam) return n1.nam - n2.nam;
    if (n1.thang != n2.thang) return n1.thang - n2.thang;
    return n1.ngay - n2.ngay;
}

int so_sanh_chu_cai(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1; // a < b
        if (a[i] > b[i]) return 1; // a > b
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0; // a = b
    if (a[i] == '\0') return -1; // a < b
    return 1;
}

int check_trung_maHang(char maHang[], Node* danh_sach_hang){
    Node *cur = danh_sach_hang;
    
    while(cur != NULL){

        if(string_cmp(cur->value->ma_hang, maHang)){
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

int lay_so_ngay_trong_thang(int thang, int nam) {
    switch (thang) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            // nam  nhuan
            if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) {
                return 29;
            }
            return 28;
        default:
            return 31;
    }
}

int nhap_so_nguyen(int *val) {
    char extra;
    int res = scanf("%d%c", val, &extra);
    
    if (res == 2) {

        //chap nhan space va tap
        while (extra == ' ' || extra == '\t') {
            extra = getchar();
        }
        //EOF = end of file (ket thuc file) 
        //'\n' ket thuc nhap tu ban phim
        if (extra == '\n' || extra == EOF) {
            return 1;
        }

        while (extra != '\n' && extra != EOF) {
            extra = getchar();
        }
        return 0;
    }
    else {
        // Clear buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
}

void nhap_thang_nam(int *thang, int *nam){
  int thang_ip, nam_ip;

  while (1){
    printf(BOLD "Nhap thang can thong ke (1-12): " RESET);
    if (nhap_so_nguyen(&thang_ip)){

      if (thang_ip >= 1 && thang_ip <= 12){
        *thang = thang_ip;
        break;
      }
      else{
        printf(BOLD RED "Loi logic: Thang phai nam trong khoang tu 1 den 12!\n\n" RESET);
      }
    }
    
    else{
      printf(BOLD RED "Loi dinh dang: Thang khong hop le (phai la so nguyen)!\n\n" RESET);
    }
  }

  while (1){
    printf(BOLD "Nhap nam can thong ke (1000 - 9999): " RESET);
    
    if (nhap_so_nguyen(&nam_ip)){
      if (nam_ip >= 1000 && nam_ip <= 9999){
        *nam = nam_ip;
        break;
      }
      else{
        printf(BOLD RED "Loi logic: Nam phai nam trong khoang tu 1000 den 9999!\n\n" RESET);
      }
    }
    
    else{
      printf(BOLD RED "Loi dinh dang: Nam khong hop le (phai la so nguyen)!\n\n" RESET);
    }
  }
}