#ifndef COMMON_H
#define COMMON_H

#define MAX_PRODUCTS 100
#define MAX_CATEGORIES 20
#include <stdlib.h>
#include <string.h>
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


struct Node{
    PhieuNhap* value;
    struct Node* next;

};



#endif