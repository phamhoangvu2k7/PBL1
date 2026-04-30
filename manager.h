#ifndef MANAGER_H
#define MANAGER_H

#include "common.h"

void tinh_thanh_tien(PhieuNhap *phieu);
void thong_ke_theo_ngay();
void thong_ke_theo_thang();
void thong_ke_tong_tien();
void xoa_mat_hang();
void quan_ly_thue();
void thong_ke_kho_hang();
void tim_kiem_theo_ma_hang();
void sap_xep_danh_sach();
void hien_thi_thong_tin_du_an();

void createNode(char ma_hang[], char ten_hang[], char don_vi[], NgayThang ngay_nhap, int so_luong, float don_gia, int thu_muc_id, float thanh_tien, struct Node* newNode);
void nhap_hang();
void tao_du_lieu_mau();

#endif