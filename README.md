Start project:
gcc main.c utils.c manager.c my_string.c -o QuanLyKho
.\QuanLyKho

***Trong tính năng nhập phiếu hàng thì khi đến tính năng nhập tên thư mục cần 1 hàm check các trường hợp sau:***
check tên thư mục có trong kho chưa: Nếu có thì lưu, nếu chưa thì tạo
check mã hàng (mã hàng là primary key nên mỗi hàng chỉ có 1 mã hàng duy nhất) nếu trùng thì bắt nhập lại
