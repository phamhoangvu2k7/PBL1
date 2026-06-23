#ifndef UTILS_H
#define UTILS_H

#include "common.h"

int so_sanh_ngay(NgayThang n1, NgayThang n2);
int so_sanh_chu_cai(char a[], char b[]);
int check_trung_maHang(char maHang[], Node* danh_sach_hang);
int lay_so_ngay_trong_thang(int thang, int nam) ;
int nhap_so_nguyen(int *val);
void nhap_thang_nam(int *thang, int *nam);

#endif