#ifndef MANAGER_H
#define MANAGER_H

#include "common.h"

void tinh_thanh_tien(PhieuNhap *phieu);
void thong_ke_theo_ngay();
void xoa_mat_hang();
void quan_ly_thue();
void createNode(char ma_hang[], char ten_hang[], char don_vi[], NgayThang ngay_nhap, int so_luong, float don_gia, int thu_muc_id, float thanh_tien, struct Node* newNode);
void tao_du_lieu_mau();

#endif