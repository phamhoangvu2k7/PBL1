Start project:
gcc main.c utils.c manager.c -o QuanLyKho
.\QuanLyKho


**Sửa tính năng nhập ID thư mục trong phần nhập phiếu hàng thành nhập tên thư mục**
Khi nhập phiếu hàng ở tính năng nhập tên thư mục *show 1 menu hiện thị toàn bộ thư mục có trong kho* ta có 2 trường hợp:
- TH1: Nếu user nhập tên thư mục có sẵn trong kho --> Lưu
- TH2: Nếu user nhập tên thư mục khác --> Tạo 1 thư mục mới. Đồng thời bắt user phải nhập thuế cho thư mục mới 