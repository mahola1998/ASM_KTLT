# HỆ THỐNG QUẢN LÝ THƯ VIỆN C++ (LIBRARY MANAGEMENT SYSTEM)

Ứng dụng hỗ trợ đầy đủ các nghiệp vụ quản lý thư viện thực tế: quản lý danh mục sách, quản lý độc giả, lập phiếu mượn/trả sách, kiểm tra sách quá hạn, thống kê lượt mượn và lưu trữ dữ liệu bền vững dạng CSV.

## 1. Cấu Trúc Thư Mục & Tệp Tin

final-project/
├──README.md #Tài liệu hướn dẫn sữ dụng hệ thống
├──src/ #Thư mục chứa toàn bộ mã nguồn C++
│ ├──main.cpp #Điểm chạy chương trình
│ ├──menu.cpp #Chứa chức menu cho chương trình
│ ├──models.h #Định nghĩa các Object
│ ├──services.cpp #Thực hiện logic các hàm dịch vụ
│ └──services.h #Khai báo các hàm xử lý nghiệp vụ
├──data/ #Thư mục chứa dữ liệu
│ ├──Book.csv #chứa dữ liệu sách
│ ├──Reader.csv #Chứa dữ liệu đọc giả
│ └──RentalInfo.csv #Chứa dữ liệu lịch sử mượn trả
├── tests/ #Thư mục kiểm thử
│ └── test_cases.md #Chi tiết các kịch bản kiểm thử
└── .gitignore #File cấu hình

## 2. Chi Tiết Các File Trong Dự Án

models.h: Khai báo 4 cấu trúc nền tảng: Date, Book, Reader, BorrowRecord.
services.h: Khai báo toàn bộ danh mục hàm nghiệp vụ, giúp mã nguồn tuân thủ nguyên tắc Modular Programming.
services.cpp: Cài đặt thuật toán ngày tháng (mktime, difftime), các hàm CRUD Sách/Độc giả, kiểm tra tồn kho,
xử lý mượn/trả và đọc/ghi CSV.
menu.cpp: Console UIXây dựng Menu 14 lựa chọn linh hoạt, sub-menu tìm kiếm sách, tự động dọn dẹp bộ đệm std::cin.
main.cpp: Khởi tạo các std::vector lưu trữ, tự động nạp dữ liệu từ file khi mở và ghi lại xuống file khi kết thúc.

## 3. Danh Sách 14 Chức Năng Trên Menu Console

# Quản Lý Sách & Độc Giả

Thêm sách (addBook): Thêm cuốn sách mới (có kiểm tra trùng mã ID).
Cập nhật thông tin sách (updateBook): Thay đổi Tiêu đề, Tác giả, Thể loại, Số lượng.
Xóa sách (deleteBook): Xóa sách khỏi hệ thống (Có ràng buộc: Không cho xóa sách đang được mượn).
Tìm kiếm sách (searchBookMenu): Tìm kiếm theo Mã sách, Tên sách hoặc Tác giả.
Hiển thị danh sách sách (displayBooks): In toàn bộ kho sách dạng bảng gọn gàng.
Thêm độc giả (addReader): Đăng ký độc giả mới vào hệ thống.
Hiển thị danh sách độc giả (displayReaders): Xem toàn bộ danh sách độc giả.

# Quản Lý Mượn - Trả & Thống Kê

Mượn sách (borrowBook): Lập phiếu mượn, giảm tồn kho, tăng lượt mượn, tự động tính hạn trả (+14days).
Trả sách (returnBook): Hoàn sách về kho, ghi nhận ngày trả thực tế và cảnh báo số ngày trễ (nếu có).
Kiểm tra trạng thái sách (isBookAvailable): Tra cứu nhanh cuốn sách còn sẵn trong kho hay đã được mượn hết.
Lịch sử mượn/trả (displayBorrowHistory): Xem toàn bộ nhật ký giao dịch, số ngày đã mượn và trạng thái quá hạn.
Lưu dữ liệu vào file (saveData): Chủ động ghi dữ liệu hiện tại xuống các file CSV.
Danh sách sách quá hạn (displayOverdueBooks): Liệt kê danh sách các phiếu mượn trễ hạn so với ngày hệ thống.
Thống kê sách HOT (displayMostBorrowedBooks): Liệt kê toàn bộ các cuốn sách có lượt mượn cao nhất.

## 5. Hướng Dẫn Biên Dịch Và Khởi Chạy

Chạy chương trình bằng main.exe

## 6. Quy Định Cấu Trúc File CSV Dữ Liệu

Dữ liệu được lưu trữ trong thư mục ../data/ theo định dạng phân cách bằng dấu phẩy (,):

- book.csv: MaSach,TenSach,TacGia,TheLoai,SoLuong,SoLuotMuon
  Ví dụ: B001,Lap trinh C++,Nguyen Van A,CNTT,5,2
- reader.csv: MaDocGia,TenDocGia,SoDienThoai
  Ví dụ: R001,Tran Van B,0901234567
- rentalInfo.csv: MaDocGia,MaSach,NgayMuon,HanTra,NgayTraThucTe,TrangThai(1:DaTra/0:ChuaTra)
  Ví dụ: R001,B001,1/7/2026,15/7/2026,0/0/0,0
