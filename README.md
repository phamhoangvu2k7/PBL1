Start project:
gcc main.c utils.c manager.c my_string.c -o QuanLyKho
.\QuanLyKho

***Trong tính năng nhập phiếu hàng thì khi đến tính năng nhập tên thư mục cần 1 hàm check các trường hợp sau:***
check tên thư mục có trong kho chưa: Nếu có thì lưu, nếu chưa thì tạo
check mã hàng (mã hàng là primary key nên mỗi hàng chỉ có 1 mã hàng duy nhất) nếu trùng thì bắt nhập lại


**Sửa tính năng nhập ID thư mục trong phần nhập phiếu hàng thành nhập tên thư mục**
Khi nhập phiếu hàng ở tính năng nhập tên thư mục *show 1 menu hiện thị toàn bộ thư mục có trong kho* ta có 2 trường hợp:
- TH1: Nếu user nhập tên thư mục có sẵn trong kho --> Lưu
- TH2: Nếu user nhập tên thư mục khác --> Tạo 1 thư mục mới. Đồng thời bắt user phải nhập thuế cho thư mục mới 

_Danh
    +my_string
    +Xoa_mat_hang
    +Thong_Ke_Tong_tien
    +tinh thanh tien

_Vu
    +Quan_Ly_Thue
    +tim kiem theo ma hang
    +sap sep danh sach
    +thong ke kho hang

_Chung
    +Nhap_Hang
    +Tao du lieu mau
    +common.h
    +main.c
    +utils