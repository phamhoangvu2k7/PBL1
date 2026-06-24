#include "../library/manager.h"
#include "../library/utils.h"
#include <stdio.h>

int main() {
  hien_thi_thong_tin_du_an();
  tao_du_lieu_mau();

  int chuc_nang;

  do {

    printf("\n" BOLD BLUE "==============================================" RESET "\n");
    printf(BOLD CYAN "         HE THONG QUAN LY KHO HANG" RESET "\n");
    printf(BOLD BLUE "==============================================" RESET "\n");
    printf(YELLOW " 1." RESET " Tao phieu nhap kho\n");
    printf(YELLOW " 2." RESET " Thong ke tong tien\n");
    printf(YELLOW " 3." RESET " Xoa mat hang theo dieu kien\n");
    printf(YELLOW " 4." RESET " Quan ly thue thu muc (Xem, Sua, Xoa, Them)\n");
    printf(YELLOW " 5." RESET " Hien thi tat ca mat hang\n");
    printf(YELLOW " 6." RESET " Tim kiem mat hang theo ma\n");
    printf(YELLOW " 7." RESET " Sap xep danh sach mat hang\n");
    printf(RED " 0." RESET " Thoat chuong trinh\n");
    printf(BOLD BLUE "----------------------------------------------" RESET "\n");
    printf(BOLD "Chon chuc nang: " RESET);

    if (!nhap_so_nguyen(&chuc_nang)) {
      printf("Nhap sai! Vui long nhap so nguyen.\n");

      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
      continue;
    }

    switch (chuc_nang) {
    case 1:
      nhap_hang();
      break;
    case 2:
      thong_ke_tong_tien();
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
      cap_nhat_du_lieu_mau();
      printf("He thong da dong.\n");
      break;
    default:
      printf("Lua chon khong hop le! Vui long chon tu 0 den 6.\n");
    }

    if (chuc_nang != 0 && chuc_nang != 4 && chuc_nang != 7) {
      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
    }

  } while (chuc_nang != 0);

  return 0;
}