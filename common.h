#ifndef COMMON_H
#define COMMON_H

#define MAX_PRODUCTS 100
#define MAX_CATEGORIES 20

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
    float dien_tich;
} PhieuNhap;

extern ThuMuc danh_sach_thu_muc[MAX_CATEGORIES];
extern int so_thu_muc;

extern PhieuNhap danh_sach_hang[MAX_PRODUCTS];
extern int so_hang;

extern float dien_tich_kho;

#endif