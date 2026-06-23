#include <stdio.h>
#include <stdlib.h>

#include "../library/manager.h"
#include "../library/common.h"
#include "../library/my_string.h"
#include "../library/utils.h"

ThuMuc ds_thu_muc[MAX_CATEGORIES];
int so_thu_muc = 0;

Node *danh_sach_hang = NULL;
Node *cuoi_danh_sach;
int so_hang = 0;

float thue_thu_muc(int id_thumuc){
  for (int i = 0; i < so_thu_muc; i++){
    if (ds_thu_muc[i].id == id_thumuc)
      return ds_thu_muc[i].thue;
  }
  return 0.0;
}

void tinh_thanh_tien(PhieuNhap *phieu){
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

void thong_ke_tong_tien(){
  if (so_hang == 0){
    printf("khong co hang de thong ke\n");
    return;
  }

  int thang_tk, nam_tk;
  nhap_thang_nam(&thang_tk, &nam_tk);

  // lay so ngay trong thang do
  int so_ngay = lay_so_ngay_trong_thang(thang_tk, nam_tk);

  printf("\n" BOLD CYAN "+------------+----------------------------------+" RESET "\n");
  printf(BOLD CYAN "|" RESET BOLD YELLOW " %-10s " RESET BOLD CYAN "|" RESET BOLD YELLOW " %-30s " RESET BOLD CYAN "|" RESET "\n", "Ngay", "Tong Tien (VND)");
  printf(BOLD CYAN "+------------+----------------------------------+" RESET "\n");

  float tong_tien_thang = 0;

  // lap qua tung ngay trong thang
  for (int ngay = 1; ngay <= so_ngay; ngay++){
    float tong_tien_ngay = 0;
    
    //tim mat hang co date trung khop
    Node *curNode = danh_sach_hang;
    while (curNode != NULL){
      NgayThang ngay_nhap = curNode->value->ngay_nhap;
      
      //neu khop thi cong don tien
      if (ngay_nhap.ngay == ngay && ngay_nhap.thang == thang_tk && ngay_nhap.nam == nam_tk){
        tong_tien_ngay += curNode->value->thanh_tien;
      }
      
      curNode = curNode->next;
    }

    tong_tien_thang += tong_tien_ngay;

    //in ra man hinh
    char ngay_str[20];
    sprintf(ngay_str, "%02d/%02d/%04d", ngay, thang_tk, nam_tk);
    
    if (tong_tien_ngay > 0){
      printf(BOLD CYAN "|" RESET " %-10s " BOLD CYAN "|" RESET GREEN " %30.2f " RESET BOLD CYAN "|" RESET "\n", ngay_str, tong_tien_ngay);
    }
    else{
      printf(BOLD CYAN "|" RESET " %-10s " BOLD CYAN "|" RESET " %30.2f " BOLD CYAN "|" RESET "\n", ngay_str, tong_tien_ngay);
    }
  }
  
  printf(BOLD CYAN "+------------+----------------------------------+" RESET "\n");
  printf(BOLD CYAN "|" RESET BOLD YELLOW " %-10s " RESET BOLD CYAN "|" RESET BOLD GREEN " %30.2f " RESET BOLD CYAN "|" RESET "\n", "TONG CONG", tong_tien_thang);
  printf(BOLD CYAN "+------------+----------------------------------+" RESET "\n");
}

void xoa_mat_hang(){

  if (so_hang == 0){
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
  if (f == NULL){
    printf("Khong the mo file '%s'!\n", duong_dan);
    return;
  }

  char input_don_vi[20];
  char input_ma_hang[20];

  int read_status = 0;
  if (fscanf(f, "%s", input_don_vi) != 1 || fscanf(f, "%s", input_ma_hang) != 1) {
    printf(RED "Loi: File xoa hang khong dung dinh dang hoac bi rong!" RESET "\n");
    read_status = 1;
  }
  fclose(f);

  if (read_status) {
    return;
  }

  printf(CYAN ">> Don vi  : " RESET "%s\n", input_don_vi);
  printf(CYAN ">> Ma hang : " RESET "%s\n", input_ma_hang);

  int so_luong_xoa = 0;
  Node *curNode = danh_sach_hang;
  Node *prev = NULL;

  while (curNode != NULL){
    PhieuNhap *p = curNode->value;

    if (string_cmp(p->don_vi, input_don_vi) &&
        string_head_dup(input_ma_hang, p->ma_hang)){

      Node *del_node = curNode;

      // can xoa node dau tien
      if (prev == NULL){
        danh_sach_hang = curNode->next;
        curNode = danh_sach_hang;
      }
      // xoa node o dua
      else{
        prev->next = curNode->next;
        curNode = prev->next;
      }
      // xoa node cuoi cung
      if (del_node == cuoi_danh_sach){
        cuoi_danh_sach = prev;
      }

      free(del_node->value);
      free(del_node);
      so_hang--;
      so_luong_xoa++;
    }
    else{
      prev = curNode;
      // xet tiep node tiep theo
      curNode = curNode->next;
    }
  }

  if (danh_sach_hang == NULL){
    cuoi_danh_sach = NULL;
  }

  printf("\n=> Da xoa %d mat hang co don vi '%s' va ma bat dau bang '%s'.\n",
         so_luong_xoa, input_don_vi, input_ma_hang);
}

void quan_ly_thue(){
  char ten_file[100];
  char duong_dan[200];
  int lua_chon_menu, id;
  float thue_nhap;
  char ten_thu_muc_nhap[50];

  do{
    printf("\n" BOLD CYAN "--- QUAN LY THUE THU MUC ---" RESET "\n");
    printf(YELLOW "1." RESET " Sua thue\n");
    printf(YELLOW "2." RESET " Xem thue\n");
    printf(YELLOW "3." RESET " Xoa thue\n");
    printf(YELLOW "4." RESET " Them thu muc moi\n");
    printf(RED "0." RESET " Quay lai\n");
    printf(BOLD "Chon chuc nang (0-4): " RESET);

    if (!nhap_so_nguyen(&lua_chon_menu)){
      printf(BOLD RED "Nhap sai! Vui long nhap so nguyen." RESET "\n");

      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
      continue;
    }

    if (lua_chon_menu == 0){
      break;
    }

    if (lua_chon_menu < 0 || lua_chon_menu > 4){
      printf(BOLD RED "Lua chon khong hop le! Vui long chon tu 0 den 4." RESET "\n");
      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
      continue;
    }

    // xem thue
    if (lua_chon_menu == 2){
      printf("\n" BOLD CYAN "+------+----------------------+------------+" RESET "\n");
      printf(CYAN "|" RESET BOLD " %-4s " RESET CYAN "|" RESET BOLD " %-20s " RESET CYAN "|" RESET BOLD " %-10s " RESET CYAN "|" RESET "\n", 
             "ID", "Ten Thu Muc", "Thue (%)");
      printf(CYAN "+------+----------------------+------------+" RESET "\n");
      for (int i = 0; i < so_thu_muc; i++){
        printf(CYAN "|" RESET " %-4d " CYAN "|" RESET " %-20s " CYAN "|" RESET " %9.2f%% " CYAN "|" RESET "\n", 
               ds_thu_muc[i].id, ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
      }
      printf(CYAN "+------+----------------------+------------+" RESET "\n\n");
      
      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
      continue;
    } 
    
    // sua thue/ xoa thue/ them thu muc moi
    if (lua_chon_menu == 1 || lua_chon_menu == 3 || lua_chon_menu == 4){
      if (lua_chon_menu == 4 && so_thu_muc >= MAX_CATEGORIES){
        printf(BOLD RED "Danh sach thu muc da day!" RESET "\n");
        printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
        system("pause > nul");
        continue;
      }

      printf("Nhap ten file du lieu (trong data/quan_ly_thue/): ");
      scanf(" %s", ten_file);

      sprintf(duong_dan, "data/quan_ly_thue/%s.txt", ten_file);
      FILE *f = fopen(duong_dan, "r");
      if (f == NULL){
        printf(BOLD RED "Khong the mo file '%s'!" RESET "\n", duong_dan);
        printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
        system("pause > nul");
        continue;
      }

      // xu ly truong hip nhap file ko dung dinh dang
      int format_err = 0;
      if (lua_chon_menu == 1){ 
        // bat buoc doc dung 2 so
        if (fscanf(f, "%d %f", &id, &thue_nhap) != 2){
          printf(BOLD RED "File khong dung dinh dang! (Yeu cau 2 so: ID va Thue moi)" RESET "\n");
          format_err = 1;
        }
      }

      else if (lua_chon_menu == 3){ 
        // bat buoc chi co 1 so
        float kiem_tra_du;
        int so_luong_doc_duoc = fscanf(f, "%d %f", &id, &kiem_tra_du);
        
        if (so_luong_doc_duoc > 1){
          printf(BOLD RED "File khong dung dinh dang! (Chuc nang xoa chi nhan file chua duy nhat 1 so ID)" RESET "\n");
          format_err = 1;
        }
        else if (so_luong_doc_duoc != 1){
          printf(BOLD RED "File khong dung dinh dang hoac file rong! (Yeu cau 1 so: ID)" RESET "\n");
          format_err = 1;
        }
      }
      
      else if (lua_chon_menu == 4){
        // Doc thong tin them thu muc moi: Ten thu muc va Thue (%)
        if (fscanf(f, " %[^\n]", ten_thu_muc_nhap) != 1){
          printf(BOLD RED "File khong dung dinh dang! (Yeu cau dong thu nhat la Ten thu muc)" RESET "\n");
          format_err = 1;
        }
        if (!format_err && fscanf(f, "%f", &thue_nhap) != 1){
          printf(BOLD RED "File khong dung dinh dang! (Yeu cau dong thu hai la Thue)" RESET "\n");
          format_err = 1;
        }
        
        if (!format_err){
          // Tu dong sinh ID = max_id + 1
          int max_id = 0;
          for (int i = 0; i < so_thu_muc; i++){
            if (ds_thu_muc[i].id > max_id){
              max_id = ds_thu_muc[i].id;
            }
          }
          id = max_id + 1;
        }
      }
      fclose(f);

      if (format_err){
        printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
        system("pause > nul");
        continue;
      }

      // in thong tin
      if (lua_chon_menu == 1){
        printf(CYAN ">> ID thu muc: " RESET "%d\n", id);
        printf(CYAN ">> Thue moi  : " RESET "%.0f%%\n", thue_nhap);
      } else if (lua_chon_menu == 3){
        printf(CYAN ">> ID thu muc: " RESET "%d\n", id);
      } else if (lua_chon_menu == 4){
        printf(CYAN ">> ID thu muc: " RESET "%d\n", id);
        printf(CYAN ">> Ten thu muc: " RESET "%s\n", ten_thu_muc_nhap);
        printf(CYAN ">> Thue       : " RESET "%.0f%%\n", thue_nhap);
      }

      // XU ly logic cap nhat/ xoa / them
      if (lua_chon_menu == 4){
        ds_thu_muc[so_thu_muc].id = id;
        string_copy(ds_thu_muc[so_thu_muc].ten_thu_muc, ten_thu_muc_nhap);
        
        ds_thu_muc[so_thu_muc].thue = thue_nhap / 100.0;
        so_thu_muc++;
        printf(BOLD GREEN "Da them thu muc moi thanh cong!" RESET "\n");
        
        printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
        system("pause > nul");
        continue;
      }

      int tim_thay = 0;
      for (int i = 0; i < so_thu_muc; i++){
        if (ds_thu_muc[i].id == id){
          tim_thay = 1;
          
          if (lua_chon_menu == 1){
            ds_thu_muc[i].thue = thue_nhap / 100.0;
            printf(BOLD GREEN "Da cap nhat thue thanh cong!" RESET "\n");
          } else{
            ds_thu_muc[i].thue = 0.0;
            printf(BOLD GREEN "Da xoa thue (Set = 0%%)!" RESET "\n");
          }

          // Duyệt danh sách liên kết để cập nhật lại thành tiền
          Node *curNode = danh_sach_hang;
          while (curNode != NULL){
            if (curNode->value->thu_muc_id == id){
              tinh_thanh_tien(curNode->value);
            }
            curNode = curNode->next;
          }
          break;
        }
      }

      if (!tim_thay){
        printf(BOLD RED "Khong tim thay ID thu muc nay!" RESET "\n");
      }
      
      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
    }
  } while (lua_chon_menu != 0);
}

void thong_ke_kho_hang(){
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
  while (p != NULL){
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

void tao_du_lieu_mau(){
  so_thu_muc = 0;
  danh_sach_hang = NULL;
  cuoi_danh_sach = NULL;
  so_hang = 0;

  // Doc danh sach thu muc
  FILE *f1 = fopen("data/data_mau/ds_thu_muc.txt", "r");
  if (f1 == NULL){
    printf("Khong the mo file data/data_mau/ds_thu_muc.txt de nap du lieu mau!\n");
    return;
  }
  int count_thu_muc = 0;
  if (fscanf(f1, "%d", &count_thu_muc) == 1){
    for (int i = 0; i < count_thu_muc && i < MAX_CATEGORIES; i++){

      if (fscanf(f1, "%d", &ds_thu_muc[i].id) != 1) break;
      if (fscanf(f1, " %[^\n]", ds_thu_muc[i].ten_thu_muc) != 1) break;
      if (fscanf(f1, "%f", &ds_thu_muc[i].thue) != 1) break;
      so_thu_muc++;
    }
  }
  fclose(f1);

  // Doc danh sach hang hoa
  FILE *f2 = fopen("data/data_mau/ds_hang.txt", "r");
  if (f2 == NULL){
    printf("Khong the mo file data/data_mau/ds_hang.txt de nap du lieu mau!\n");
    return;
  }
  int count_hang = 0;
  if (fscanf(f2, "%d", &count_hang) == 1){
    for (int i = 0; i < count_hang; i++){
      Node *newNode = (Node *)malloc(sizeof(Node));
      newNode->value = (PhieuNhap *)malloc(sizeof(PhieuNhap));
      
      //doc bi thieu thong tin thi lạp tuc dung doc
      if (fscanf(f2, "%s", newNode->value->ma_hang) != 1){
        free(newNode->value);
        free(newNode);
        break;
      }
      if (fscanf(f2, " %[^\n]", newNode->value->ten_hang) != 1){
        free(newNode->value);
        free(newNode);
        break;
      }
      if (fscanf(f2, "%d", &newNode->value->so_luong) != 1){
        free(newNode->value);
        free(newNode);
        break;
      }
      if (fscanf(f2, "%d %d %d", &newNode->value->ngay_nhap.ngay,
                                 &newNode->value->ngay_nhap.thang,
                                 &newNode->value->ngay_nhap.nam) != 3){
        free(newNode->value);
        free(newNode);
        break;
      }
      if (fscanf(f2, " %[^\n]", newNode->value->don_vi) != 1){
        free(newNode->value);
        free(newNode);
        break;
      }
      if (fscanf(f2, "%f", &newNode->value->don_gia) != 1){
        free(newNode->value);
        free(newNode);
        break;
      }
      if (fscanf(f2, "%d", &newNode->value->thu_muc_id) != 1){
        free(newNode->value);
        free(newNode);
        break;
      }
      
      tinh_thanh_tien(newNode->value);
      newNode->next = NULL;
      
      //them vao cuoi danh sach
      if (danh_sach_hang == NULL){
        danh_sach_hang = cuoi_danh_sach = newNode;
      }
      else{
        cuoi_danh_sach->next = newNode;
        cuoi_danh_sach = newNode;
      }
      so_hang++;
    }
  }
  fclose(f2);
}

void thong_ke_thu_muc(){
  printf("\n" BOLD YELLOW "----- THONG KE THU MUC -----" RESET "\n");
  printf(CYAN "+------+----------------------+------------+" RESET "\n");
  printf(CYAN "|" RESET BOLD " %-4s " RESET CYAN "|" RESET BOLD " %-20s " RESET CYAN "|" RESET BOLD " %-10s " RESET CYAN "|" RESET "\n", 
         "ID", "Ten Thu Muc", "Thue (%)");
  printf(CYAN "+------+----------------------+------------+" RESET "\n");
  for (int i = 0; i < so_thu_muc; i++){
    printf(CYAN "|" RESET " %-4d " CYAN "|" RESET " %-20s " CYAN "|" RESET " %9.2f%% " CYAN "|" RESET "\n", 
           ds_thu_muc[i].id, ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
  }
  printf(CYAN "+------+----------------------+------------+" RESET "\n\n");
}

void nhap_hang(){
  char ten_file[100];
  char duong_dan[200];
  printf("Nhap ten file du lieu (trong data/nhap_hang/): ");
  scanf(" %s", ten_file);

  sprintf(duong_dan, "data/nhap_hang/%s.txt", ten_file);
  FILE *f = fopen(duong_dan, "r");
  if (f == NULL){
    printf("Khong the mo file '%s'!\n", duong_dan);
    return;
  }

  Node *phieu_nhap_new = (Node *)malloc(sizeof(Node));
  phieu_nhap_new->value = (PhieuNhap *)malloc(sizeof(PhieuNhap));
  int err = 0;

  if (fscanf(f, "%s", phieu_nhap_new->value->ma_hang) != 1) {
    printf(RED "Loi: Khong doc duoc ma hang tu file!" RESET "\n");
    err = 1;
  }

  if (!err && fscanf(f, " %[^\n]", phieu_nhap_new->value->ten_hang) != 1) {
    printf(RED "Loi: Khong doc duoc ten hang tu file!" RESET "\n");
    err = 1;
  }

  if (!err && fscanf(f, "%d", &phieu_nhap_new->value->so_luong) != 1) {
    printf(RED "Loi: So luong trong file khong phai so nguyen!" RESET "\n");
    err = 1;
  }
  if (!err && phieu_nhap_new->value->so_luong < 0) {
    printf(RED "Loi logic: So luong trong file khong the am (%d)!" RESET "\n", phieu_nhap_new->value->so_luong);
    err = 1;
  }

  NgayThang date;
  if (!err && fscanf(f, "%d %d %d", &date.ngay, &date.thang, &date.nam) != 3) {
    printf(RED "Loi: Ngay nhap trong file khong dung dinh dang (ngay thang nam)!" RESET "\n");
    err = 1;
  }
  if (!err) {
    if (date.nam < 1 || date.thang < 1 || date.thang > 12) {
      printf(RED "Loi logic: Ngay nhap khong hop le (Nam phai > 0, Thang tu 1 den 12)!" RESET "\n");
      err = 1;
    } else {
      int max_ngay = lay_so_ngay_trong_thang(date.thang, date.nam);
      if (date.ngay < 1 || date.ngay > max_ngay) {
        printf(RED "Loi logic: Ngay %02d khong hop le trong thang %02d nam %04d!" RESET "\n", date.ngay, date.thang, date.nam);
        err = 1;
      }
    }
  }
  if (!err) {
    phieu_nhap_new->value->ngay_nhap = date;
  }

  if (!err && fscanf(f, " %[^\n]", phieu_nhap_new->value->don_vi) != 1) {
    printf(RED "Loi: Khong doc duoc don vi tu file!" RESET "\n");
    err = 1;
  }

  if (!err && fscanf(f, "%f", &phieu_nhap_new->value->don_gia) != 1) {
    printf(RED "Loi: Don gia trong file khong dung dinh dang!" RESET "\n");
    err = 1;
  }
  if (!err && phieu_nhap_new->value->don_gia < 0.0) {
    printf(RED "Loi logic: Don gia trong file khong the am (%.2f)!" RESET "\n", phieu_nhap_new->value->don_gia);
    err = 1;
  }

  if (!err && fscanf(f, "%d", &phieu_nhap_new->value->thu_muc_id) != 1) {
    printf(RED "Loi: ID Thu muc trong file khong dung dinh dang!" RESET "\n");
    err = 1;
  }


  if (!err && check_trung_maHang(phieu_nhap_new->value->ma_hang, danh_sach_hang)){
    printf(RED "Ma hang '%s' da ton tai!" RESET "\n", phieu_nhap_new->value->ma_hang);
    err = 1;
  }
  if (!err && (phieu_nhap_new->value->thu_muc_id > so_thu_muc || phieu_nhap_new->value->thu_muc_id <= 0)){
    printf(RED "Thu muc co id %d khong ton tai!" RESET "\n",  phieu_nhap_new->value->thu_muc_id);
    err = 1;
  }
  fclose(f);

  if(err){
    free(phieu_nhap_new->value);
    free(phieu_nhap_new);
    return;
  }

  printf(CYAN ">> Ma hang   : " RESET "%s\n", phieu_nhap_new->value->ma_hang);
  printf(CYAN ">> Ten hang  : " RESET "%s\n", phieu_nhap_new->value->ten_hang);
  printf(CYAN ">> So luong  : " RESET "%d\n", phieu_nhap_new->value->so_luong);
  printf(CYAN ">> Ngay nhap : " RESET "%02d/%02d/%04d\n", date.ngay, date.thang, date.nam);
  printf(CYAN ">> Don vi    : " RESET "%s\n", phieu_nhap_new->value->don_vi);
  printf(CYAN ">> Don gia   : " RESET "%.2f\n", phieu_nhap_new->value->don_gia);
  printf(CYAN ">> ID Thu muc: " RESET "%d\n", phieu_nhap_new->value->thu_muc_id);

  tinh_thanh_tien(phieu_nhap_new->value);

  phieu_nhap_new->next = NULL;

  if (danh_sach_hang == NULL){
    danh_sach_hang = cuoi_danh_sach = phieu_nhap_new;
  }
  else{
    cuoi_danh_sach->next = phieu_nhap_new;
    cuoi_danh_sach = phieu_nhap_new;
  }

  so_hang++;
  printf(GREEN "Da nhap hang thanh cong! Thanh tien: %.2f" RESET "\n",
         phieu_nhap_new->value->thanh_tien);
}

void tim_kiem_theo_ma_hang(){
  char ma_hang_tim[20];
  printf("\n--- TIM KIEM MAT HANG THEO MA ---\n");
  printf("Nhap ma hang can tim: ");
  scanf(" %s", ma_hang_tim);

  Node *p = danh_sach_hang;
  int tim_thay = 0;
  while (p != NULL){
    if (string_cmp(p->value->ma_hang, ma_hang_tim)){
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

  if (!tim_thay){
    printf("\nKhong tim thay mat hang nao boi ma '%s'.\n", ma_hang_tim);
  }
}

void sap_xep_danh_sach(){
  int lua_chon;
  do{
    printf("\n" BOLD CYAN "--- SAP XEP DANH SACH ---" RESET "\n");
    printf(YELLOW "1." RESET " Sap xep theo thanh tien\n");
    printf(YELLOW "2." RESET " Sap xep theo ngay thang nhap\n");
    printf(YELLOW "3." RESET " Sap xep theo thu tu chu cai cua ma hang\n");
    printf(RED "0." RESET " Quay lai\n");
    printf(BOLD "Chon loai sap xep (0-3): " RESET);

    if (!nhap_so_nguyen(&lua_chon)){
      printf(BOLD RED "Nhap sai! Vui long nhap so nguyen." RESET "\n");
      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
      continue;
    }

    if (lua_chon == 0){
      break;
    }

    if (lua_chon < 0 || lua_chon > 3){
      printf(BOLD RED "Lua chon khong hop le! Vui long chon tu 0 den 3." RESET "\n");
      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
      continue;
    }

    if (danh_sach_hang == NULL || danh_sach_hang->next == NULL){
      printf("\nDanh sach rong hoac chi co 1 mat hang, khong can sap xep.\n");
      if (danh_sach_hang != NULL)
        thong_ke_kho_hang();
      printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
      system("pause > nul");
      break;
    }

    Node *i, *j;
    for (i = danh_sach_hang; i->next != NULL; i = i->next){
      for (j = i->next; j != NULL; j = j->next){
        int swap = 0;
        if (lua_chon == 1){
          if (i->value->thanh_tien > j->value->thanh_tien)
            swap = 1;
        }
        
        else if (lua_chon == 2){
          if (so_sanh_ngay(i->value->ngay_nhap, j->value->ngay_nhap) > 0)
            swap = 1;
        }
        
        else if (lua_chon == 3){
          if (so_sanh_chu_cai(i->value->ma_hang, j->value->ma_hang) > 0)
            swap = 1;
        }

        if (swap){
          PhieuNhap *temp = i->value;
          i->value = j->value;
          j->value = temp;
        }
      }
    }

    printf("\nDa sap xep xong!\n");
    thong_ke_kho_hang();
    printf("\n" BOLD GREEN "Nhan phim bat ky de tiep tuc..." RESET "\n");
    system("pause > nul");
  } while (lua_chon != 0);
}

void hien_thi_thong_tin_du_an(){
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
