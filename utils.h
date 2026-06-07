#ifndef UTILS_H
#define UTILS_H

// #include <stdbool.h>
#include "common.h"

// bool start_with(const char *str, const char *key);
int cung_ngay(NgayThang product1, NgayThang product2);
int cung_thang(NgayThang n1, NgayThang n2);
int so_sanh_ngay(NgayThang n1, NgayThang n2);
int so_sanh_chu_cai(char a[], char b[]);
int check_trung_maHang(char maHang[], Node* danh_sach_hang);
int lay_so_ngay_trong_thang(int thang, int nam) ;

#endif