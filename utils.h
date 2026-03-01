#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "common.h"

bool start_with(const char *str, const char *key);
bool cung_ngay(NgayThang product1, NgayThang product2);
int kiem_tra_thu_muc(ThuMuc product, ThuMuc ds_thu_muc[], int so_thu_muc);

#endif