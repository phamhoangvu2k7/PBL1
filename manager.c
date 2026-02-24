#include <stdio.h>
#include <string.h>
#include "manager.h"
#include "utils.h"

ThuMuc ds_thu_muc[MAX_CATEGORIES];
int so_thu_muc = 0;

PhieuNhap danh_sach_hang[MAX_PRODUCTS];
int so_hang = 0;

// Get tax of category
float thue_thu_muc(int category_id) {
    for (int i = 0; i < so_thu_muc; i++) {
        if (ds_thu_muc[i].id == category_id) 
            return ds_thu_muc[i].thue;
    }
    return 0.0;
}

void tinh_thanh_tien(PhieuNhap *phieu) {
    float ty_le_giam = 0.0;
    if (phieu->so_luong > 200) ty_le_giam = 0.15;
    else if (phieu->so_luong > 100) ty_le_giam = 0.1;

    float tien_goc = phieu->so_luong * phieu->don_gia;
    float tien_sau_giam = tien_goc * (1.0 - ty_le_giam);

    float thue = thue_thu_muc(phieu->thu_muc_id);
    phieu->thanh_tien = tien_sau_giam * (1.0 + thue);
}

void thong_ke_theo_ngay() {
    printf("\n--- THONG KE TONG TIEN THEO NGAY ---\n");
    
    bool da_duyet[MAX_PRODUCTS] = {false};

    for (int i = 0; i < so_hang; i++) {
        if (da_duyet[i]) continue; 

        NgayThang ngay_dang_xet = danh_sach_hang[i].ngay_nhap;
        float tong_tien_ngay = 0;

        for (int j = i; j < so_hang; j++) {
            if (cung_ngay(danh_sach_hang[j].ngay_nhap, ngay_dang_xet)) {
                tong_tien_ngay += danh_sach_hang[j].thanh_tien;
                da_duyet[j] = true; 
            }
        }
        printf("Ngay %02d/%02d/%04d: %.2f VND\n", ngay_dang_xet.ngay, ngay_dang_xet.thang, ngay_dang_xet.nam, tong_tien_ngay);
    }
}

void xoa_mat_hang() {
    char input_don_vi[20];
    char input_ma_hang[20];

    printf("\n--- XOA MAT HANG ---\n");
    
    printf("Nhap don vi can xoa: ");
    scanf("%s", input_don_vi); 

    printf("Nhap ma hang can xoa: ");
    scanf("%s", input_ma_hang); 

    int i = 0; 
    int so_luong_xoa = 0;

    while(i < so_hang) {
        if (strcmp(danh_sach_hang[i].don_vi, input_don_vi) == 0 && start_with(danh_sach_hang[i].ma_hang, input_ma_hang)) {
            for (int j = i; j < so_hang - 1; j++) {
                danh_sach_hang[j] = danh_sach_hang[j + 1];
            }
            so_hang--;
            so_luong_xoa++;
        } else {
            ++i;
        }
    }

    printf("\n=> Da xoa %d mat hang co don vi '%s' va ma bat dau bang '%s'.\n", so_luong_xoa, input_don_vi, input_ma_hang);
}

void quan_ly_thue() {
    int lua_chon, id;
    float thue_nhap;

    printf("\n--- QUAN LY THUE THU MUC ---\n");
    printf("1. Xem danh sach thue\n");
    printf("2. Sua thue\n");
    printf("3. Xoa thue (Set ve 0%%)\n");
    printf("Chon chuc nang: ");
    scanf("%d", &lua_chon);

    if (lua_chon == 1) {
        printf("\n%-5s | %-20s | %-10s\n", "ID", "Ten Thu Muc", "Thue (%)");
        printf("-------------------------------------------\n");
        for (int i = 0; i < so_thu_muc; i++) {
            printf("%-5d | %-20s | %.2f%%\n", ds_thu_muc[i].id, ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
        }
        printf("\n");
    }

    else if (lua_chon == 2 || lua_chon == 3) {
        printf("Nhap ID thu muc can thao tac: ");
        scanf("%d", &id);
        
        for (int i = 0; i < so_thu_muc; i++) {
            if (ds_thu_muc[i].id == id) {
                
                if (lua_chon == 2) {
                    printf("Nhap muc thue moi (Nhap %% - vi du nhap 10 tuong ung 10%%): ");
                    scanf("%f", &thue_nhap);
                    
                    ds_thu_muc[i].thue = thue_nhap / 100.0;
                    printf("Da cap nhat thue thanh cong!\n");
                } 
                else {
                    ds_thu_muc[i].thue = 0.0; // Xóa nghĩa là set thuế về 0
                    printf("Da xoa thue (Set = 0%%)!\n");
                }
                
                for(int j = 0; j < so_hang; j++) {
                    if(danh_sach_hang[j].thu_muc_id == id) {
                        tinh_thanh_tien(&danh_sach_hang[j]); 
                    }
                }
                return; 
            }
        }
        printf("Khong tim thay ID thu muc nay!\n");
    }
}

void tao_du_lieu_mau() {
    ds_thu_muc[0] = (ThuMuc){1, "Cong nghe", 0.10}; 
    ds_thu_muc[1] = (ThuMuc){2, "Gia dung", 0.05};  
    so_thu_muc = 2;

    danh_sach_hang[0] = (PhieuNhap){"mh102", "Dien thoai", "cai", {15, 10, 2026}, 150, 1000, 1, 0}; 
    danh_sach_hang[1] = (PhieuNhap){"mh105", "Tai nghe", "hop", {15, 10, 2026}, 50, 200, 1, 0}; 
    danh_sach_hang[2] = (PhieuNhap){"mh200", "Noi com dien", "cai", {16, 10, 2026}, 250, 500, 2, 0}; 
    so_hang = 3;

    for (int i = 0; i < so_hang; i++) {
        tinh_thanh_tien(&danh_sach_hang[i]);
    }
}