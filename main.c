#include "manager.h"
#include <stdio.h>

int main() {
  tao_du_lieu_mau();

  int chuc_nang;

  do {
    printf("\n====== HE THONG QUAN LY KHO ======\n");
    printf("1. Tao phieu nhap kho \n");
    printf("2. Thong ke tong tien theo ngay\n");
    printf("3. Xoa mat hang theo dieu kien\n");
    printf("4. Quan ly thue thu muc (Xem, Sua, Xoa)\n");
    printf("5. Hien thi tat ca mat hang\n");
    printf("6. Tim kiem mat hang theo ma\n");
    printf("7. Sap xep danh sach mat hang\n");
    printf("0. Thoat chuong trinh\n");
    printf("====================================\n");
    printf("Chon chuc nang: ");

    if (scanf("%d", &chuc_nang) != 1) {
      printf("Nhap sai! Vui long nhap so.\n");

      while (getchar() != '\n')
        ;

      continue;
    }

    switch (chuc_nang) {
    case 1:
      nhap_hang();
      break;
    case 2:
      thong_ke_theo_ngay();
      break;
    case 3:
      xoa_mat_hang();
      break;
    case 4:
      quan_ly_thue();
      break;
    case 5:
      thong_ke_kho_hang();
      break;
    case 6:
      tim_kiem_theo_ma_hang();
      break;
    case 7:
      sap_xep_danh_sach();
      break;
    case 0:
      printf("He thong da dong.\n");
      break;
    default:
      printf("Lua chon khong hop le! Vui long chon tu 0 den 6.\n");
    }

  } while (chuc_nang != 0);

  return 0;
}