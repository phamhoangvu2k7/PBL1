#include "manager.h"

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "my_string.h"
#include "utils.h"

ThuMuc ds_thu_muc[MAX_CATEGORIES];
int so_thu_muc = 0;

Node *danh_sach_hang = NULL;
Node *cuoi_danh_sach;
int so_hang = 0;

void createNode(char ma_hang[], char ten_hang[], char don_vi[],
                NgayThang ngay_nhap, int so_luong, float don_gia,
                int thu_muc_id, float thanh_tien, Node *newNode) {
  newNode->value = (PhieuNhap *)malloc(sizeof(PhieuNhap));
  string_copy(newNode->value->ma_hang, ma_hang);
  string_copy(newNode->value->ten_hang, ten_hang);
  string_copy(newNode->value->don_vi, don_vi);
  newNode->value->ngay_nhap = ngay_nhap;
  newNode->value->so_luong = so_luong;
  newNode->value->don_gia = don_gia;
  newNode->value->thu_muc_id = thu_muc_id;
  newNode->value->thanh_tien = thanh_tien;

  newNode->next = NULL;
}

float thue_thu_muc(int id_thumuc) {
  for (int i = 0; i < so_thu_muc; i++) {
    if (ds_thu_muc[i].id == id_thumuc)
      return ds_thu_muc[i].thue;
  }
  return 0.0;
}

void tinh_thanh_tien(PhieuNhap *phieu) {
  float ty_le_giam = 0.0;
  if (phieu->so_luong > 200)
    ty_le_giam = 0.15;
  else if (phieu->so_luong > 100)
    ty_le_giam = 0.1;

  float tien_goc = phieu->so_luong * phieu->don_gia;
  float tien_sau_giam = tien_goc * (1.0 - ty_le_giam);

  float thue = thue_thu_muc(phieu->thu_muc_id);
  phieu->thanh_tien = tien_sau_giam * (1.0 + thue);
}

void thong_ke_theo_ngay() {
  if (so_hang == 0) {
    printf("khong co hang de thong ke");
    return;
  }
  printf("\n--- THONG KE TONG TIEN THEO NGAY ---\n");

  int da_duyet[so_hang];
  for (int i = 0; i < so_hang; i++) {
    da_duyet[i] = 0;
  }

  int i = 0;
  Node *curNodei = danh_sach_hang;
  while (i < so_hang) {
    if (da_duyet[i]) {
      i++;
      curNodei = curNodei->next;
      continue;
    }

    NgayThang ngay_dang_xet = curNodei->value->ngay_nhap;
    float tong_tien_ngay = 0;

    int j = i;
    Node *curNodej = curNodei;

    while (j < so_hang) {
      if (cung_ngay(curNodei->value->ngay_nhap, curNodej->value->ngay_nhap)) {
        tong_tien_ngay += curNodej->value->thanh_tien;
        da_duyet[j] = 1;
      }
      j++;

      curNodej = curNodej->next;
    }
    i++;
    curNodei = curNodei->next;

    printf("-----DATE: %d - %d - %d: ---- ", ngay_dang_xet.ngay,
           ngay_dang_xet.thang, ngay_dang_xet.nam);
    printf("Tong Tien:  %0.2f \n", tong_tien_ngay);
  }
}

void xoa_mat_hang() {

  if (so_hang == 0) {
    printf("khong con hang de xoa\n");
    return;
  }

  char ten_file[100];
  char duong_dan[200];
  printf("\n--- XOA MAT HANG ---\n");
  printf("Nhap ten file du lieu (trong data/xoa_hang/): ");
  scanf(" %s", ten_file);

  sprintf(duong_dan, "data/xoa_hang/%s", ten_file);
  FILE *f = fopen(duong_dan, "r");
  if (f == NULL) {
    printf("Khong the mo file '%s'!\n", duong_dan);
    return;
  }

  char input_don_vi[40];
  char input_ma_hang[40];

  fscanf(f, "%s", input_don_vi);
  fscanf(f, "%s", input_ma_hang);
  fclose(f);

  printf("Doc tu file: don_vi='%s', ma_hang='%s'\n", input_don_vi, input_ma_hang);

  int so_luong_xoa = 0;
  Node *curNode = danh_sach_hang;
  Node *prev = NULL;

  while (curNode != NULL) {
    PhieuNhap *p = curNode->value;

    int n = string_len(p->don_vi, 40);
    int m = string_len(input_don_vi, 40);

    if (string_cmp(p->don_vi, input_don_vi, n, m) &&
        string_head_dup(input_ma_hang, p->ma_hang)) {

      Node *del_node = curNode;

      // can xoa node dau tien
      if (prev == NULL) {
        danh_sach_hang = curNode->next;
        curNode = danh_sach_hang;
      }
      // xoa node o dua
      else {
        prev->next = curNode->next;
        curNode = prev->next;
      }
      // xoa node cuoi cung
      if (del_node == cuoi_danh_sach) {
        cuoi_danh_sach = prev;
      }

      free(del_node->value);
      free(del_node);
      so_hang--;
      so_luong_xoa++;
    } else {
      prev = curNode;
      // xet tiep node tiep theo
      curNode = curNode->next;
    }
  }

  if (danh_sach_hang == NULL) {
    cuoi_danh_sach = NULL;
  }

  printf("\n=> Da xoa %d mat hang co don vi '%s' va ma bat dau bang '%s'.\n",
         so_luong_xoa, input_don_vi, input_ma_hang);
}

void quan_ly_thue() {
  char ten_file[100];
  char duong_dan[200];
  int lua_chon, id;
  float thue_nhap;

  printf("\n--- QUAN LY THUE THU MUC ---\n");
  printf("Nhap ten file du lieu (trong data/quan_ly_thue/): ");
  scanf(" %s", ten_file);

  sprintf(duong_dan, "data/quan_ly_thue/%s", ten_file);
  FILE *f = fopen(duong_dan, "r");
  if (f == NULL) {
    printf("Khong the mo file '%s'!\n", duong_dan);
    return;
  }

  fscanf(f, "%d", &lua_chon);
  printf("Doc tu file: lua_chon=%d\n", lua_chon);

  if (lua_chon == 1) {
    fclose(f);
    printf("\n%-5s | %-20s | %-10s\n", "ID", "Ten Thu Muc", "Thue (%)");
    printf("-------------------------------------------\n");
    for (int i = 0; i < so_thu_muc; i++) {
      printf("%-5d | %-20s | %.2f%%\n", ds_thu_muc[i].id,
             ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
    }
    printf("\n");
  } else if (lua_chon == 2 || lua_chon == 3) {
    fscanf(f, "%d", &id);
    if (lua_chon == 2) {
      fscanf(f, "%f", &thue_nhap);
    }
    fclose(f);

    printf("Doc tu file: ID=%d\n", id);
    if (lua_chon == 2) {
      printf("Doc tu file: thue_moi=%.0f%%\n", thue_nhap);
    }

    int tim_thay = 0;
    for (int i = 0; i < so_thu_muc; i++) {
      if (ds_thu_muc[i].id == id) {
        tim_thay = 1;
        if (lua_chon == 2) {
          ds_thu_muc[i].thue = thue_nhap / 100.0;
          printf("Da cap nhat thue thanh cong!\n");
        } else {
          ds_thu_muc[i].thue = 0.0;
          printf("Da xoa thue (Set = 0%%)!\n");
        }

        // Duyệt danh sách liên kết để cập nhật lại thành tiền
        Node *curNode = danh_sach_hang;
        while (curNode != NULL) {
          if (curNode->value->thu_muc_id == id) {
            tinh_thanh_tien(curNode->value);
          }
          curNode = curNode->next;
        }
        break;
      }
    }

    if (!tim_thay) {
      printf("Khong tim thay ID thu muc nay!\n");
    }
  } else {
    fclose(f);
    printf("Lua chon khong hop le trong file!\n");
  }
}

void thong_ke_kho_hang() {
  Node *p = danh_sach_hang;
  printf("-----THONG KE MAT HANG -----\n\n");
  while (p != NULL) {
    printf("Ma Hang: %s \n", p->value->ma_hang);
    printf("Ten Hang: %s \n", p->value->ten_hang);
    printf("Don Vi: %s \n", p->value->don_vi);
    printf("Ngay / Thang / Nam : %d / %d / %d \n", p->value->ngay_nhap.ngay,
           p->value->ngay_nhap.thang, p->value->ngay_nhap.nam);
    printf("So Luong: %d \n", p->value->so_luong);
    printf("Don Gia: %0.3f\n", p->value->don_gia);
    printf("Id thu muc: %d", p->value->thu_muc_id);
    p = p->next;

    printf("\n\n");
  }
}

void tao_du_lieu_mau() {
  ds_thu_muc[0] = (ThuMuc){1, "Cong nghe", 0.10};
  ds_thu_muc[1] = (ThuMuc){2, "Gia dung", 0.05};

  ds_thu_muc[2] = (ThuMuc){3, "Thoi trang", 0.15};
  ds_thu_muc[3] = (ThuMuc){4, "Phu kien", 0.08};

  ds_thu_muc[4] = (ThuMuc){5, "Thuc pham", 0.02};
  ds_thu_muc[5] = (ThuMuc){6, "Suc khoe", 0.12};

  ds_thu_muc[6] = (ThuMuc){7, "Sach & Van phong pham", 0.05};
  ds_thu_muc[7] = (ThuMuc){8, "Do choi", 0.10};

  ds_thu_muc[8] = (ThuMuc){9, "Lam dep", 0.20};
  ds_thu_muc[9] = (ThuMuc){10, "The thao", 0.07};
  so_thu_muc = 10;

  Node *newNode1 = (Node *)malloc(sizeof(Node));
  createNode("mh102", "Dien thoai", "cai", (NgayThang){15, 10, 2026}, 150, 1000,
             1, 0, newNode1);
  tinh_thanh_tien(newNode1->value);
  danh_sach_hang = newNode1;

  Node *newNode2 = (Node *)malloc(sizeof(Node));
  createNode("mh105", "Tai nghe", "hop", (NgayThang){15, 10, 2026}, 50, 200, 1,
             0, newNode2);
  tinh_thanh_tien(newNode2->value);
  newNode1->next = newNode2;

  Node *newNode3 = (Node *)malloc(sizeof(Node));
  createNode("mh200", "Noi com dien", "cai", (NgayThang){16, 10, 2026}, 250,
             500, 2, 0, newNode3);
  tinh_thanh_tien(newNode3->value);
  newNode2->next = newNode3;

  Node *newNode4 = (Node *)malloc(sizeof(Node));
  createNode("mh300", "Binh nong lanh", "cai", (NgayThang){16, 10, 2026}, 300,
             300, 2, 0, newNode4);
  tinh_thanh_tien(newNode4->value);
  newNode3->next = newNode4;

  cuoi_danh_sach = newNode4;
  so_hang = 4;
  newNode4->next = NULL;
}

void thong_ke_thu_muc() {
  printf("-----THONG KE THU MUC -----\n\n");
  printf("\n%-5s | %-20s | %-10s\n", "ID", "Ten Thu Muc", "Thue (%)");
  printf("-------------------------------------------\n");
  for (int i = 0; i < so_thu_muc; i++) {
    printf("%-5d | %-20s | %.2f%%\n", ds_thu_muc[i].id,
           ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
  }
  printf("\n");
}

void nhap_hang() {
  char ten_file[100];
  char duong_dan[200];
  printf("Nhap ten file du lieu (trong data/nhap_hang/): ");
  scanf(" %s", ten_file);

  sprintf(duong_dan, "data/nhap_hang/%s", ten_file);
  FILE *f = fopen(duong_dan, "r");
  if (f == NULL) {
    printf("Khong the mo file '%s'!\n", duong_dan);
    return;
  }

  Node *phieu_nhap_new = (Node *)malloc(sizeof(Node));
  phieu_nhap_new->value = (PhieuNhap *)malloc(sizeof(PhieuNhap));

  fscanf(f, "%s", phieu_nhap_new->value->ma_hang);

  if (check_trung_maHang(phieu_nhap_new->value->ma_hang, danh_sach_hang)) {
    printf("Ma hang '%s' da ton tai!\n", phieu_nhap_new->value->ma_hang);
    free(phieu_nhap_new->value);
    free(phieu_nhap_new);
    fclose(f);
    return;
  }

  fscanf(f, " %[^\n]", phieu_nhap_new->value->ten_hang);
  fscanf(f, "%d", &phieu_nhap_new->value->so_luong);

  NgayThang date;
  fscanf(f, "%d %d %d", &date.ngay, &date.thang, &date.nam);
  phieu_nhap_new->value->ngay_nhap = date;

  fscanf(f, " %[^\n]", phieu_nhap_new->value->don_vi);
  fscanf(f, "%f", &phieu_nhap_new->value->don_gia);
  fscanf(f, "%d", &phieu_nhap_new->value->thu_muc_id);
  fclose(f);

  printf("Doc tu file: ma='%s', ten='%s', sl=%d, ngay=%d/%d/%d, dv='%s', gia=%.0f, tm_id=%d\n",
         phieu_nhap_new->value->ma_hang,
         phieu_nhap_new->value->ten_hang,
         phieu_nhap_new->value->so_luong,
         date.ngay, date.thang, date.nam,
         phieu_nhap_new->value->don_vi,
         phieu_nhap_new->value->don_gia,
         phieu_nhap_new->value->thu_muc_id);

  tinh_thanh_tien(phieu_nhap_new->value);

  phieu_nhap_new->next = NULL;

  if (danh_sach_hang == NULL) {
    danh_sach_hang = cuoi_danh_sach = phieu_nhap_new;
  } else {
    cuoi_danh_sach->next = phieu_nhap_new;
    cuoi_danh_sach = phieu_nhap_new;
  }

  so_hang++;
  printf("Da nhap hang thanh cong! Thanh tien: %.2f\n", phieu_nhap_new->value->thanh_tien);
}

void tim_kiem_theo_ma_hang() {
  char ma_hang_tim[40];
  printf("\n--- TIM KIEM MAT HANG THEO MA ---\n");
  printf("Nhap ma hang can tim: ");
  scanf(" %s", ma_hang_tim);

  Node *p = danh_sach_hang;
  int tim_thay = 0;
  while (p != NULL) {
    if (string_cmp(p->value->ma_hang, ma_hang_tim, string_len(p->value->ma_hang, 40), string_len(ma_hang_tim, 40))) {
      printf("\nDa tim thay mat hang:\n");
      printf("Ma Hang: %s \n", p->value->ma_hang);
      printf("Ten Hang: %s \n", p->value->ten_hang);
      printf("Don Vi: %s \n", p->value->don_vi);
      printf("Ngay / Thang / Nam : %d / %d / %d \n", p->value->ngay_nhap.ngay,
             p->value->ngay_nhap.thang, p->value->ngay_nhap.nam);
      printf("So Luong: %d \n", p->value->so_luong);
      printf("Don Gia: %0.3f\n", p->value->don_gia);
      printf("Id thu muc: %d\n", p->value->thu_muc_id);
      printf("Thanh tien: %0.2f\n", p->value->thanh_tien);
      tim_thay = 1;
      break; 
    }
    p = p->next;
  }
  
  if (!tim_thay) {
    printf("\nKhong tim thay mat hang nao boi ma '%s'.\n", ma_hang_tim);
  }
}