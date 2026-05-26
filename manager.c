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
  printf("+------------+----------------------+\n");
  printf("| %-10s | %-20s |\n", "Ngay", "Tong Tien");
  printf("+------------+----------------------+\n");

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

    char ngay_str[20];
    sprintf(ngay_str, "%02d/%02d/%04d", ngay_dang_xet.ngay, ngay_dang_xet.thang,
            ngay_dang_xet.nam);
    printf("| %-10s | %20.2f |\n", ngay_str, tong_tien_ngay);
  }
  printf("+------------+----------------------+\n");
}

void thong_ke_theo_thang() {
  if (so_hang == 0) {
    printf("khong co hang de thong ke");
    return;
  }
  printf("\n--- THONG KE TONG TIEN THEO THANG ---\n");
  printf("+---------+----------------------+\n");
  printf("| %-7s | %-20s |\n", "Thang", "Tong Tien");
  printf("+---------+----------------------+\n");

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

    NgayThang thang_dang_xet = curNodei->value->ngay_nhap;
    float tong_tien_thang = 0;

    int j = i;
    Node *curNodej = curNodei;

    while (j < so_hang) {
      if (cung_thang(curNodei->value->ngay_nhap, curNodej->value->ngay_nhap)) {
        tong_tien_thang += curNodej->value->thanh_tien;
        da_duyet[j] = 1;
      }
      j++;

      curNodej = curNodej->next;
    }
    i++;
    curNodei = curNodei->next;

    char thang_str[20];
    sprintf(thang_str, "%02d/%04d", thang_dang_xet.thang, thang_dang_xet.nam);
    printf("| %-7s | %20.2f |\n", thang_str, tong_tien_thang);
  }
  printf("+---------+----------------------+\n");
}

void thong_ke_tong_tien() {
  int lua_chon;
  do {
    printf("\n" BOLD CYAN "--- THONG KE TONG TIEN ---" RESET "\n");
    printf(YELLOW "1." RESET " Thong ke theo ngay\n");
    printf(YELLOW "2." RESET " Thong ke theo thang\n");
    printf(RED "0." RESET " Quay lai\n");
    printf(BOLD "Chon loai thong ke: " RESET);
    if (scanf("%d", &lua_chon) != 1) {
      printf("Nhap sai! Vui long nhap so.\n");
      while (getchar() != '\n');
      continue;
    }

    switch (lua_chon) {
      case 1:
        thong_ke_theo_ngay();
        break;
      case 2:
        thong_ke_theo_thang();
        break;
      case 0:
        break;
      default:
        printf("Lua chon khong hop le!\n");
    }
  } while (lua_chon != 0);
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

  sprintf(duong_dan, "data/xoa_hang/%s.txt", ten_file);
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

  printf(CYAN ">> Don vi  : " RESET "%s\n", input_don_vi);
  printf(CYAN ">> Ma hang : " RESET "%s\n", input_ma_hang);

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
  int lua_chon_menu, id;
  float thue_nhap;
  char ten_thu_muc_nhap[50];

  printf("\n--- QUAN LY THUE THU MUC ---\n");
  printf("1. Sua thue\n");
  printf("2. Xem thue\n");
  printf("3. Xoa thue\n");
  printf("4. Them thu muc moi\n");
  printf("Chon chuc nang (1-4): ");
  if (scanf("%d", &lua_chon_menu) != 1) {
    printf("Nhap sai! Vui long nhap so.\n");
    while (getchar() != '\n');
    return;
  }

  // xem thue
  if (lua_chon_menu == 2) {
    printf("\n" BOLD CYAN "+------+----------------------+------------+" RESET "\n");
    printf(CYAN "|" RESET BOLD " %-4s " RESET CYAN "|" RESET BOLD " %-20s " RESET CYAN "|" RESET BOLD " %-10s " RESET CYAN "|" RESET "\n", 
           "ID", "Ten Thu Muc", "Thue (%)");
    printf(CYAN "+------+----------------------+------------+" RESET "\n");
    for (int i = 0; i < so_thu_muc; i++) {
      printf(CYAN "|" RESET " %-4d " CYAN "|" RESET " %-20s " CYAN "|" RESET " %9.2f%% " CYAN "|" RESET "\n", 
             ds_thu_muc[i].id, ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
    }
    printf(CYAN "+------+----------------------+------------+" RESET "\n\n");
    return;
  } 
  
  // sua thue/ xoa thue/ them thu muc moi
  else if (lua_chon_menu == 1 || lua_chon_menu == 3 || lua_chon_menu == 4) {
    if (lua_chon_menu == 4 && so_thu_muc >= MAX_CATEGORIES) {
      printf("Danh sach thu muc da day!\n");
      return;
    }

    printf("Nhap ten file du lieu (trong data/quan_ly_thue/): ");
    scanf(" %s", ten_file);

    sprintf(duong_dan, "data/quan_ly_thue/%s.txt", ten_file);
    FILE *f = fopen(duong_dan, "r");
    if (f == NULL) {
      printf("Khong the mo file '%s'!\n", duong_dan);
      return;
    }

    if (lua_chon_menu == 1) { 
      // Bắt buộc đọc được đúng 2 số
      if (fscanf(f, "%d %f", &id, &thue_nhap) != 2) {
        printf("File khong dung dinh dang! (Yeu cau 2 so: ID va Thue moi)\n");
        fclose(f);
        return;
      }
    } else if (lua_chon_menu == 3) { 
      // bat buoc chi co 1 so
      float kiem_tra_du;
      int so_luong_doc_duoc = fscanf(f, "%d %f", &id, &kiem_tra_du);
      
      if (so_luong_doc_duoc > 1) {
        printf("File khong dung dinh dang! (Chuc nang xoa chi nhan file chua duy nhat 1 so ID)\n");
        fclose(f);
        return;
      } else if (so_luong_doc_duoc != 1) {
        printf("File khong dung dinh dang hoac file rong! (Yeu cau 1 so: ID)\n");
        fclose(f);
        return;
      }
    } else if (lua_chon_menu == 4) {
      // Doc thong tin them thu muc moi: Ten thu muc va Thue (%)
      if (fscanf(f, " %[^\n]", ten_thu_muc_nhap) != 1) {
        printf("File khong dung dinh dang! (Yeu cau dong thu nhat la Ten thu muc)\n");
        fclose(f);
        return;
      }
      if (fscanf(f, "%f", &thue_nhap) != 1) {
        printf("File khong dung dinh dang! (Yeu cau dong thu hai la Thue)\n");
        fclose(f);
        return;
      }
      
      // Tu dong sinh ID = max_id + 1
      int max_id = 0;
      for (int i = 0; i < so_thu_muc; i++) {
        if (ds_thu_muc[i].id > max_id) {
          max_id = ds_thu_muc[i].id;
        }
      }
      id = max_id + 1;
    }
    fclose(f);

    // In thông tin đã đọc
    if (lua_chon_menu == 1) {
      printf(CYAN ">> ID thu muc: " RESET "%d\n", id);
      printf(CYAN ">> Thue moi  : " RESET "%.0f%%\n", thue_nhap);
    } else if (lua_chon_menu == 3) {
      printf(CYAN ">> ID thu muc: " RESET "%d\n", id);
    } else if (lua_chon_menu == 4) {
      printf(CYAN ">> ID thu muc: " RESET "%d\n", id);
      printf(CYAN ">> Ten thu muc: " RESET "%s\n", ten_thu_muc_nhap);
      printf(CYAN ">> Thue       : " RESET "%.0f%%\n", thue_nhap);
    }

    // Xử lý logic Cập nhật/Xóa/Thêm
    if (lua_chon_menu == 4) {
      ds_thu_muc[so_thu_muc].id = id;
      string_copy(ds_thu_muc[so_thu_muc].ten_thu_muc, ten_thu_muc_nhap);
      ds_thu_muc[so_thu_muc].thue = thue_nhap / 100.0;
      so_thu_muc++;
      printf("Da them thu muc moi thanh cong!\n");
      return;
    }

    int tim_thay = 0;
    for (int i = 0; i < so_thu_muc; i++) {
      if (ds_thu_muc[i].id == id) {
        tim_thay = 1;
        
        if (lua_chon_menu == 1) {
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
    printf("Lua chon khong hop le!\n");
  }
}

void thong_ke_kho_hang() {
  Node *p = danh_sach_hang;
  printf("\n" BOLD YELLOW "----- THONG KE KHO HANG -----" RESET "\n");
  printf(CYAN "+----------+--------------------------+------------+------------"
              "+----------+--------------+------------+------------+-----------------+-----------------+" RESET
              "\n");
  printf(CYAN
         "|" RESET BOLD " %-8s " RESET CYAN "|" RESET BOLD " %-24s " RESET CYAN
         "|" RESET BOLD " %-10s " RESET CYAN "|" RESET BOLD " %-10s " RESET CYAN
         "|" RESET BOLD " %-8s " RESET CYAN "|" RESET BOLD " %-12s " RESET CYAN
         "|" RESET BOLD " %-10s " RESET CYAN "|" RESET BOLD " %-10s " RESET CYAN
         "|" RESET BOLD " %-15s " RESET CYAN "|" RESET BOLD " %-15s " RESET CYAN
         "|" RESET "\n",
         "Ma Hang", "Ten Hang", "Don Vi", "Ngay Nhap", "So Luong", "Don Gia",
         "ID Thu Muc", "Thue (%)", "Tien Thue", "Thanh Tien");
  printf(CYAN "+----------+--------------------------+------------+------------"
              "+----------+--------------+------------+------------+-----------------+-----------------+" RESET
              "\n");
  while (p != NULL) {
    char ngay_nhap[20];
    sprintf(ngay_nhap, "%02d/%02d/%04d", p->value->ngay_nhap.ngay,
            p->value->ngay_nhap.thang, p->value->ngay_nhap.nam);
    float thue_ap_dung = thue_thu_muc(p->value->thu_muc_id);
    float tien_thue = (p->value->thanh_tien / (1.0 + thue_ap_dung)) * thue_ap_dung;

    printf(CYAN "|" RESET " %-8s " CYAN "|" RESET " %-24s " CYAN "|" RESET
                " %-10s " CYAN "|" RESET " %-10s " CYAN "|" RESET " %8d " CYAN
                "|" RESET " %12.3f " CYAN "|" RESET " %10d " CYAN "|" RESET " %9.2f%% " CYAN "|" RESET
                " %15.2f " CYAN "|" RESET " %15.2f " CYAN "|" RESET "\n",
           p->value->ma_hang, p->value->ten_hang, p->value->don_vi, ngay_nhap,
           p->value->so_luong, p->value->don_gia, p->value->thu_muc_id,
           thue_ap_dung * 100, tien_thue, p->value->thanh_tien);
    p = p->next;
  }
  printf(CYAN "+----------+--------------------------+------------+------------"
              "+----------+--------------+------------+------------+-----------------+-----------------+" RESET
              "\n");
}

void tao_du_lieu_mau() {
  ds_thu_muc[0] = (ThuMuc){1, "Cong nghe", 0.10};
  ds_thu_muc[1] = (ThuMuc){2, "Gia dung", 0.05};

  ds_thu_muc[2] = (ThuMuc){3, "Thoi trang", 0.15};
  ds_thu_muc[3] = (ThuMuc){4, "Phu kien", 0.08};

  ds_thu_muc[4] = (ThuMuc){5, "Thuc pham", 0.02};
  ds_thu_muc[5] = (ThuMuc){6, "Suc khoe", 0.12};

  ds_thu_muc[6] = (ThuMuc){7, "Noi that", 0.05};
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
  printf("\n" BOLD YELLOW "----- THONG KE THU MUC -----" RESET "\n");
  printf(CYAN "+------+----------------------+------------+" RESET "\n");
  printf(CYAN "|" RESET BOLD " %-4s " RESET CYAN "|" RESET BOLD " %-20s " RESET CYAN "|" RESET BOLD " %-10s " RESET CYAN "|" RESET "\n", 
         "ID", "Ten Thu Muc", "Thue (%)");
  printf(CYAN "+------+----------------------+------------+" RESET "\n");
  for (int i = 0; i < so_thu_muc; i++) {
    printf(CYAN "|" RESET " %-4d " CYAN "|" RESET " %-20s " CYAN "|" RESET " %9.2f%% " CYAN "|" RESET "\n", 
           ds_thu_muc[i].id, ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
  }
  printf(CYAN "+------+----------------------+------------+" RESET "\n\n");
}

void nhap_hang() {
  char ten_file[100];
  char duong_dan[200];
  printf("Nhap ten file du lieu (trong data/nhap_hang/): ");
  scanf(" %s", ten_file);

  sprintf(duong_dan, "data/nhap_hang/%s.txt", ten_file);
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

  printf(CYAN ">> Ma hang   : " RESET "%s\n", phieu_nhap_new->value->ma_hang);
  printf(CYAN ">> Ten hang  : " RESET "%s\n", phieu_nhap_new->value->ten_hang);
  printf(CYAN ">> So luong  : " RESET "%d\n", phieu_nhap_new->value->so_luong);
  printf(CYAN ">> Ngay nhap : " RESET "%02d/%02d/%04d\n", date.ngay, date.thang, date.nam);
  printf(CYAN ">> Don vi    : " RESET "%s\n", phieu_nhap_new->value->don_vi);
  printf(CYAN ">> Don gia   : " RESET "%.0f\n", phieu_nhap_new->value->don_gia);
  printf(CYAN ">> ID Thu muc: " RESET "%d\n", phieu_nhap_new->value->thu_muc_id);

  tinh_thanh_tien(phieu_nhap_new->value);

  phieu_nhap_new->next = NULL;

  if (danh_sach_hang == NULL) {
    danh_sach_hang = cuoi_danh_sach = phieu_nhap_new;
  } else {
    cuoi_danh_sach->next = phieu_nhap_new;
    cuoi_danh_sach = phieu_nhap_new;
  }

  so_hang++;
  printf(GREEN "Da nhap hang thanh cong! Thanh tien: %.2f" RESET "\n",
         phieu_nhap_new->value->thanh_tien);
}

void tim_kiem_theo_ma_hang() {
  char ma_hang_tim[40];
  printf("\n--- TIM KIEM MAT HANG THEO MA ---\n");
  printf("Nhap ma hang can tim: ");
  scanf(" %s", ma_hang_tim);

  Node *p = danh_sach_hang;
  int tim_thay = 0;
  while (p != NULL) {
    if (string_cmp(p->value->ma_hang, ma_hang_tim,
                   string_len(p->value->ma_hang, 40),
                   string_len(ma_hang_tim, 40))) {
      printf("\nDa tim thay mat hang:\n");
      printf("+----------+--------------------------+------------+------------+"
             "----------+--------------+------------+------------+-----------------+-----------------+\n");
      printf(
          "| %-8s | %-24s | %-10s | %-10s | %-8s | %-12s | %-10s | %-10s | %-15s | %-15s |\n",
          "Ma Hang", "Ten Hang", "Don Vi", "Ngay Nhap", "So Luong", "Don Gia",
          "ID Thu Muc", "Thue (%)", "Tien Thue", "Thanh Tien");
      printf("+----------+--------------------------+------------+------------+"
             "----------+--------------+------------+------------+-----------------+-----------------+\n");
      char ngay_nhap[20];
      sprintf(ngay_nhap, "%02d/%02d/%04d", p->value->ngay_nhap.ngay,
              p->value->ngay_nhap.thang, p->value->ngay_nhap.nam);
      float thue_ap_dung = thue_thu_muc(p->value->thu_muc_id);
      float tien_thue = (p->value->thanh_tien / (1.0 + thue_ap_dung)) * thue_ap_dung;

      printf(
          "| %-8s | %-24s | %-10s | %-10s | %8d | %12.3f | %10d | %9.2f%% | %15.2f | %15.2f |\n",
          p->value->ma_hang, p->value->ten_hang, p->value->don_vi, ngay_nhap,
          p->value->so_luong, p->value->don_gia, p->value->thu_muc_id,
          thue_ap_dung * 100, tien_thue, p->value->thanh_tien);
      printf("+----------+--------------------------+------------+------------+"
             "----------+--------------+------------+------------+-----------------+-----------------+\n");
      tim_thay = 1;
      break;
    }
    p = p->next;
  }

  if (!tim_thay) {
    printf("\nKhong tim thay mat hang nao boi ma '%s'.\n", ma_hang_tim);
  }
}

void sap_xep_danh_sach() {
  if (danh_sach_hang == NULL || danh_sach_hang->next == NULL) {
    printf("\nDanh sach rong hoac chi co 1 mat hang, khong can sap xep.\n");
    if (danh_sach_hang != NULL)
      thong_ke_kho_hang();
    return;
  }

  int lua_chon;
  printf("\n" BOLD CYAN "--- SAP XEP DANH SACH ---" RESET "\n");
  printf(YELLOW "1." RESET " Sap xep theo thanh tien\n");
  printf(YELLOW "2." RESET " Sap xep theo ngay thang nhap\n");
  printf(YELLOW "3." RESET " Sap xep theo thu tu chu cai cua ma hang\n");
  printf(BOLD "Chon loai sap xep: " RESET);
  if (scanf("%d", &lua_chon) != 1) {
    printf(RED "Nhap sai! Vui long nhap so." RESET "\n");
    while (getchar() != '\n');
    return;
  }

  if (lua_chon < 1 || lua_chon > 3) {
    printf(RED "Lua chon khong hop le!" RESET "\n");
    return;
  }

  Node *i, *j;
  for (i = danh_sach_hang; i->next != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      int should_swap = 0;
      if (lua_chon == 1) {
        if (i->value->thanh_tien > j->value->thanh_tien)
          should_swap = 1;
      } else if (lua_chon == 2) {
        if (so_sanh_ngay(i->value->ngay_nhap, j->value->ngay_nhap) > 0)
          should_swap = 1;
      } else if (lua_chon == 3) {
        if (so_sanh_chu_cai(i->value->ma_hang, j->value->ma_hang) > 0)
          should_swap = 1;
      }

      if (should_swap) {
        PhieuNhap *temp = i->value;
        i->value = j->value;
        j->value = temp;
      }
    }
  }

  printf("\nDa sap xep xong!\n");
  thong_ke_kho_hang();
}

// clang-format off
void hien_thi_thong_tin_du_an() {
  const int width = 75;
  printf(BLUE "+---------------------------------------------------------------------------+" RESET "\n");
  printf(BLUE "|" RESET "%*s" BOLD CYAN "%s" RESET "%*s" BLUE "|" RESET "\n", 16, "", "TRUONG DAI HOC BACH KHOA - DAI HOC DA NANG", 17, "");
  printf(BLUE "|" RESET "%*s" BOLD "%s" RESET "%*s" BLUE "|" RESET "\n", 25, "", "KHOA CONG NGHE THONG TIN", 26, "");
  printf(BLUE "|" RESET "%*s" BOLD "%s" RESET "%*s" BLUE "|" RESET "\n", 32, "", "DU AN PBL 1", 32, "");
  printf(BLUE "|" RESET "%*s" BLUE "|" RESET "\n", width, "");
  printf(BLUE "|" RESET "%*s" BLUE "|" RESET "\n", width, "");
  printf(BLUE "|" RESET "%*s" YELLOW BOLD "!!!   QUAN LY HANG NHAP TRONG 1 THANG   !!!" RESET "%*s" BLUE "|" RESET "\n", 16, "", 16, "");
  printf(BLUE "|" RESET "%*s" BLUE "|" RESET "\n", width, "");
  printf(BLUE "|" RESET "    " YELLOW BOLD "Giao vien huong dan : " RESET BOLD "Do Thi Tuyet Hoa" RESET "%*s" BLUE "|" RESET "\n", 33, "");
  printf(BLUE "|" RESET "    " CYAN "** NHOM 7 **" RESET "%*s" BLUE "|" RESET "\n", 59, "");
  printf(BLUE "|" RESET "            1. " BOLD "PHAM HOANG VU" RESET " - 25T_DT1%*s" BLUE "|" RESET "\n", 37, "");
  printf(BLUE "|" RESET "            2. " BOLD "LE MINH DANH" RESET "  - 25T_DT4%*s" BLUE "|" RESET "\n", 37, "");
  printf(BLUE "+---------------------------------------------------------------------------+" RESET "\n");
}
// clang-format on
