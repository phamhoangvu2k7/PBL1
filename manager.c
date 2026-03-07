#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "common.h"
#include "manager.h"
#include "utils.h"

ThuMuc ds_thu_muc[MAX_CATEGORIES];
int so_thu_muc = 0;

struct Node* danh_sach_hang = NULL;
struct Node* cuoi_danh_sach;
int so_hang = 0;

void createNode(char ma_hang[], char ten_hang[], char don_vi[], NgayThang ngay_nhap, int so_luong, float don_gia, int thu_muc_id, float thanh_tien, struct Node* newNode){
    newNode->value = (PhieuNhap*)malloc(sizeof(PhieuNhap));
    strcpy(newNode->value->ma_hang, ma_hang);
    strcpy(newNode->value->ten_hang, ten_hang);
    strcpy(newNode->value->don_vi, don_vi);
    newNode->value->ngay_nhap = ngay_nhap;
    newNode->value->so_luong = so_luong;
    newNode->value->don_gia = don_gia;
    newNode->value->thu_muc_id = thu_muc_id;
    newNode->value->thanh_tien = thanh_tien;

}
// Get tax of category
float thue_thu_muc(int category_id) {
    for (int i = 0; i < so_thu_muc; i++) {
        if (ds_thu_muc[i].id == category_id) 
            return ds_thu_muc[i].thue;
    }
    return 0.0;
}

void tinh_thanh_tien(PhieuNhap *phieu) {
    float ty_le_giam = 0.0;
    if (phieu->so_luong > 200) ty_le_giam = 0.15;
    else if (phieu->so_luong > 100) ty_le_giam = 0.1;

    float tien_goc = phieu->so_luong * phieu->don_gia;
    float tien_sau_giam = tien_goc * (1.0 - ty_le_giam);

    float thue = thue_thu_muc(phieu->thu_muc_id);
    phieu->thanh_tien = tien_sau_giam * (1.0 + thue);
}

void thong_ke_theo_ngay() {
    printf("\n--- THONG KE TONG TIEN THEO NGAY ---\n");

    int da_duyet[so_hang+1];
    for(int i = 0; i< so_hang; i++){
        da_duyet[i] = 0;
    }

    int i = 0;
    struct Node* curNodei = danh_sach_hang;
    while(i < so_hang){
        if(da_duyet[i]){
            i++;
            curNodei = curNodei->next;
            continue;
        }

        NgayThang ngay_dang_xet = curNodei->value->ngay_nhap;
        float tong_tien_ngay = 0;

        int j = i;
        struct Node* curNodej = curNodei;

        while(j < so_hang){
            if (cung_ngay(curNodei->value->ngay_nhap, curNodej->value->ngay_nhap)) {

                tong_tien_ngay += curNodej->value->thanh_tien;
                da_duyet[j] = 1; 
            }
            j++;

            curNodej = curNodej->next;
        }
        i++;
        curNodei = curNodei->next;

        printf("-----DATE: %d - %d - %d: ---- ", ngay_dang_xet.ngay, ngay_dang_xet.thang, ngay_dang_xet.nam);
        printf("Tong Tien:  %f \n", tong_tien_ngay);
    }
}

void xoa_mat_hang() {
    char input_don_vi[20];
    char input_ma_hang[20];

    printf("\n--- XOA MAT HANG ---\n");
    printf("Nhap don vi can xoa: ");
    scanf("%s", input_don_vi); 
    printf("Nhap ma hang can xoa: ");
    scanf("%s", input_ma_hang); 

    int so_luong_xoa = 0;
    struct Node *curNode = danh_sach_hang;
    struct Node *prev = NULL;

    while (curNode != NULL) {
        PhieuNhap *p = curNode->value;
        
        int n = string_len(p->don_vi, 20);
        int m = string_len(input_don_vi, 20);
        if (string_cmp(p->don_vi, input_don_vi, n, m) == 0 
            && string_head_dup(p->ma_hang, input_ma_hang, n)) {
            
            struct Node *temp = curNode; 
            
            // xoa curnode di
            if (prev == NULL) {
                danh_sach_hang = curNode->next;
                curNode = danh_sach_hang;
            }
            else{
                prev->next = curNode->next;
                //nhay qua thang tiep theo de tinh
                curNode = prev->next;
            }

            if (temp == cuoi_danh_sach) {
                cuoi_danh_sach = prev;
            }

            free(temp->value); 
            free(temp);
            so_hang--;
            so_luong_xoa++;
        }
        else{
            prev = curNode;
            //xet tiep node tiep theo
            curNode = curNode->next;
        }
    }

    printf("\n=> Da xoa %d mat hang co don vi '%s' va ma bat dau bang '%s'.\n", so_luong_xoa, input_don_vi, input_ma_hang);
}

void quan_ly_thue() {
    int lua_chon, id;
    float thue_nhap;

    printf("\n--- QUAN LY THUE THU MUC ---\n");
    printf("1. Xem danh sach thue\n");
    printf("2. Sua thue\n");
    printf("3. Xoa thue (Set ve 0%%)\n");
    printf("Chon chuc nang: ");
    scanf("%d", &lua_chon);

    if (lua_chon == 1) {
        printf("\n%-5s | %-20s | %-10s\n", "ID", "Ten Thu Muc", "Thue (%)");
        printf("-------------------------------------------\n");
        for (int i = 0; i < so_thu_muc; i++) {
            printf("%-5d | %-20s | %.2f%%\n", ds_thu_muc[i].id, ds_thu_muc[i].ten_thu_muc, ds_thu_muc[i].thue * 100);
        }
        printf("\n");
    } 
    else if (lua_chon == 2 || lua_chon == 3) {
        printf("Nhap ID thu muc can thao tac: ");
        scanf("%d", &id);
        
        int tim_thay = 0;
        for (int i = 0; i < so_thu_muc; i++) {
            if (ds_thu_muc[i].id == id) {
                tim_thay = 1;
                if (lua_chon == 2) {
                    printf("Nhap muc thue moi (Vi du nhap 10 cho 10%%): ");
                    scanf("%f", &thue_nhap);
                    ds_thu_muc[i].thue = thue_nhap / 100.0;
                    printf("Da cap nhat thue thanh cong!\n");
                } else {
                    ds_thu_muc[i].thue = 0.0;
                    printf("Da xoa thue (Set = 0%%)!\n");
                }
                
                // Duyệt danh sách liên kết để cập nhật lại thành tiền
                struct Node *curr = danh_sach_hang;
                while (curr != NULL) {
                    if (curr->value->thu_muc_id == id) {
                        tinh_thanh_tien(curr->value); 
                    }
                    curr = curr->next;
                }
                break; 
            }
        }
        
        if (!tim_thay) {
            printf("Khong tim thay ID thu muc nay!\n");
        }
    }
}

void tao_du_lieu_mau() {
    ds_thu_muc[0] = (ThuMuc){1, "Cong nghe", 0.10}; 
    ds_thu_muc[1] = (ThuMuc){2, "Gia dung", 0.05};  
    so_thu_muc = 2;

    struct Node* newNode1 = (struct Node*)malloc(sizeof(struct Node));
    createNode("mh102", "Dien thoai", "cai", (NgayThang){15, 10, 2026}, 150, 1000, 1, 0, newNode1);
    tinh_thanh_tien(newNode1->value);
    danh_sach_hang = newNode1;

    struct Node* newNode2 = (struct Node*)malloc(sizeof(struct Node));
    createNode("mh105", "Tai nghe", "hop", (NgayThang){15, 10, 2026}, 50, 200, 1, 0, newNode2);
    tinh_thanh_tien(newNode2->value);
    newNode1->next = newNode2;

    struct Node* newNode3 = (struct Node*)malloc(sizeof(struct Node));
    createNode("mh200", "Noi com dien", "cai", (NgayThang){16, 10, 2026}, 250, 500, 2, 0, newNode3);
    tinh_thanh_tien(newNode3->value);
    newNode2->next = newNode3;

    struct Node* newNode4 = (struct Node*)malloc(sizeof(struct Node));
    createNode("mh300", "Binh nong lanh", "cai", (NgayThang){16, 10, 2026}, 300, 300, 2, 0, newNode4);
    tinh_thanh_tien(newNode4->value);
    newNode3->next = newNode4;

    cuoi_danh_sach = newNode4;
    so_hang = 4;
    newNode4->next = NULL;


}

void nhap_hang(){
    struct Node *phieu_nhap_new = (struct Node*)malloc(sizeof(struct Node));
    phieu_nhap_new->value = (PhieuNhap*)malloc(sizeof(PhieuNhap));

    printf("Nhap Ma Hang: \n");
    scanf("%s", phieu_nhap_new->value->ma_hang);

    printf("Nhap Ten Hang: \n");
    scanf("%s", phieu_nhap_new->value->ten_hang);

    printf("Nhap So Luong: \n");
    scanf("%d", &phieu_nhap_new->value->so_luong);

    printf("Nhap Ngay Nhap : ngay - thang -nam: \n");
    NgayThang date;
    scanf("%d %d %d", &date.ngay, &date.thang, &date.nam);
    phieu_nhap_new->value->ngay_nhap = date;

    printf("Nhap Don Vi: \n");
    scanf("%s", phieu_nhap_new->value->don_vi);

    printf("Nhap Don Gia: \n");
    scanf("%f", &phieu_nhap_new->value->don_gia);

    printf("Nhap ID Thu Muc: "); scanf("%d", &phieu_nhap_new->value->thu_muc_id);

    tinh_thanh_tien(phieu_nhap_new->value);

    phieu_nhap_new->next = NULL;

    if(danh_sach_hang == NULL){
        danh_sach_hang = cuoi_danh_sach =  phieu_nhap_new;
    }
    else{
        cuoi_danh_sach->next = phieu_nhap_new;
        cuoi_danh_sach = phieu_nhap_new;
    }

    so_hang++;
}