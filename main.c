#include <stdio.h>
#include "manager.h" 

int main() {
    tao_du_lieu_mau();
    
    int chuc_nang;

    do {
        printf("\n====== HE THONG QUAN LY KHO ======\n");
        printf("1. Thong ke tong tien theo ngay\n");
        printf("2. Xoa mat hang theo dieu kien\n");
        printf("3. Quan ly thue thu muc (Xem, Sua, Xoa)\n");
        printf("4. Thong ke tat ca san pham\n");
        printf("0. Thoat chuong trinh\n");
        printf("====================================\n");
        printf("Chon chuc nang: ");
        scanf("%d", &chuc_nang);

        switch (chuc_nang) {
            case 1:
                thong_ke_theo_ngay();
                break; 
            case 2:
                xoa_mat_hang();
                break;
            case 3:
                quan_ly_thue();
                break;
            case 4: 
                thong_ke_tat_ca_san_pham();
                break;
            case 0:
                printf("He thong da dong. Chuc ban mot ngay tot lanh!\n");
                break;
            default: 
                printf("Lua chon khong hop le! Vui long chon tu 0 den 3.\n");
        }
    } while (chuc_nang != 0); 

    return 0; 
}