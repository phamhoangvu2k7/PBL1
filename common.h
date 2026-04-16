#ifndef COMMON_H
#define COMMON_H

#define MAX_CATEGORIES 50

#include <stdlib.h>

typedef struct {
    int ngay;
    int thang;
    int nam;
} NgayThang;

typedef struct {
    int id;
    char ten_thu_muc[50];
    float thue;
} ThuMuc;

typedef struct {
    char ma_hang[20];
    char ten_hang[50];
    char don_vi[20];
    NgayThang ngay_nhap;
    int so_luong;
    float don_gia;

    int thu_muc_id;
    float thanh_tien;
} PhieuNhap;


typedef struct Node{
    PhieuNhap* value;
    struct Node* next;

} Node;



#endif