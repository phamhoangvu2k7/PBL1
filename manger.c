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
        if (danh_sach_thu_muc[i].id == category_id) 
            return danh_sach_thu_muc[i].thue;
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
        printf("Ngay %02d/%02d/%04d: %.2f VNĐ\n", ngay_dang_xet.ngay, ngay_dang_xet.thang, ngay_dang_xet.nam, tong_tien_ngay);
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

