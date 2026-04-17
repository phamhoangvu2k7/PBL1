# BÁO CÁO CHI TIẾT DỰ ÁN QUẢN LÝ KHO (PBL1)

## 1. Tổng quan dự án
- **Tên dự án**: Hệ thống Quản lý Kho hàng (QuanLyKho).
- **Ngôn ngữ lập trình**: C.
- **Mục tiêu**: Xây dựng một ứng dụng console cho phép quản lý các mặt hàng nhập kho, tính toán thành tiền dựa trên số lượng và thuế suất, thực hiện các thống kê và xóa dữ liệu theo điều kiện.

## 2. Kiến trúc hệ thống
Hệ thống được tổ chức theo từng module chức năng, giúp dễ dàng bảo trì và mở rộng.

### 2.1. Cấu trúc thư mục và tệp tin
- `main.c`: Đầu vào của chương trình, chứa menu điều hướng người dùng.
- `manager.c` & `manager.h`: Chứa logic xử lý nghiệp vụ chính như nhập hàng, thống kê, xóa hàng và quản lý thuế.
- `common.h`: Chứa các định nghĩa hằng số và cấu trúc dữ liệu (struct) dùng chung toàn hệ thống.
- `my_string.c` & `my_string.h`: Thư viện xử lý chuỗi tự xây dựng (thay thế cho `string.h`).
- `utils.c` & `utils.h`: Các hàm tiện ích bổ trợ như xử lý ngày tháng, kiểm tra tính hợp lệ của dữ liệu.
- `data/`: Thư mục chứa các tệp tin dữ liệu đầu vào dạng văn bản (.txt).

## 3. Cấu trúc dữ liệu
Dự án sử dụng kết hợp giữa mảng tĩnh (đối với danh mục) và danh sách liên kết đơn (đối với hàng hóa) để tối ưu hóa việc quản lý bộ nhớ.

### 3.1. Cấu trúc chính
1. **`NgayThang`**: Lưu trữ thông tin ngày, tháng, năm.
2. **`ThuMuc`**: Lưu trữ ID danh mục, tên danh mục và thuế suất tương ứng.
3. **`PhieuNhap`**: Lưu trữ chi tiết một phiếu nhập hàng (mã hàng, tên, đơn vị, ngày nhập, số lượng, đơn giá, ID danh mục, thành tiền).
4. **`Node`**: Cấu trúc nút trong danh sách liên kết đơn để lưu trữ `PhieuNhap`.

## 4. Các tính năng chính của hệ thống

### 4.1. Nhập phiếu hàng (File-based)
- Đọc thông tin hàng hóa từ các file trong thư mục `data/nhap_hang/`.
- **Ràng buộc**: Kiểm tra mã hàng. Nếu mã hàng đã tồn tại trong hệ thống, chương trình sẽ thông báo lỗi và từ chối nhập.
- Tự động tính toán **Thanh tiền** ngay khi nhập.

### 4.2. Quản lý thuế danh mục
- Cho phép xem danh sách các danh mục hàng hóa (Công nghệ, Gia dụng, Thời trang,...).
- Hỗ trợ cập nhật thuế suất cho từng danh mục thông qua tệp tin trong `data/quan_ly_thue/`.
- **Tính năng đặc biệt**: Khi thuế suất của một danh mục thay đổi, hệ thống sẽ tự động duyệt lại toàn bộ danh sách mặt hàng để cập nhật lại `thanh_tien` cho các mặt hàng thuộc danh mục đó.

### 4.3. Xóa mặt hàng theo điều kiện
- Đọc điều kiện xóa từ file trong `data/xoa_hang/`.
- Điều kiện xóa bao gồm: Tên đơn vị tính và tiền tố mã hàng (ví dụ: xóa tất cả hàng có đơn vị 'hộp' và mã bắt đầu bằng 'mh1').

### 4.4. Thống kê dữ liệu
- **Thống kê theo ngày**: Tính tổng giá trị hàng hóa nhập kho theo từng ngày cụ thể.
- **Thống kê kho hàng**: Hiển thị toàn bộ danh sách mặt hàng hiện có với đầy đủ chi tiết.

### 4.5. Tìm kiếm mặt hàng theo mã hàng
- Cho phép người dùng tìm nhanh thông tin của một mặt hàng bằng cách nhập chính xác mã hàng.
- Nếu tìm thấy, hệ thống hiển thị đầy đủ thông tin: Tên, đơn vị, ngày nhập, số lượng, đơn giá, ID danh mục và thành tiền.
- Nếu không thấy, hệ thống đưa ra thông báo lỗi phù hợp.

## 5. Quy tắc nghiệp vụ (Business Rules)
Hệ thống áp dụng các quy tắc tính toán sau:
- **Chính sách giảm giá**:
    - Số lượng > 200: Giảm **15%** trên giá gốc.
    - Số lượng > 100: Giảm **10%** trên giá gốc.
- **Công thức tính thành tiền**:
    - `Giá sau giảm = Đơn giá * Số lượng * (1 - Tỷ lệ giảm)`
    - `Thành tiền = Giá sau giảm * (1 + Thuế suất danh mục)`

## 6. Hướng dẫn kỹ thuật
### Biên dịch chương trình
Sử dụng trình biên dịch GCC:
```bash
gcc main.c utils.c manager.c my_string.c -o QuanLyKho
```

### Cách thức hoạt động với file
Khi chọn các tính năng 1, 3, 4, người dùng cần cung cấp tên file (ví dụ: `input.txt`). Chương trình sẽ tìm file tương ứng trong các thư mục con của `data/` để xử lý. Các tính năng 2, 5, 6 hoạt động trực tiếp trên dữ liệu đang lưu trong bộ nhớ (RAM).

---