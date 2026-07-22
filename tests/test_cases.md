# TÀI LIỆU KỊCH BẢN KIỂM THỬ (TEST CASES)

## HỆ THỐNG QUẢN LÝ THƯ VIỆN (C++)

Tài liệu này chứa danh sách chi tiết 40 ca kiểm thử (Test Cases) từ TC01 đến TC41 dùng để nghiệm thu các chức năng trong hệ thống.

---

## 1. Nhóm Quản Lý Thời Gian (`Date`)

| Mã test  | Hàm kiểm thử            | Dữ liệu đầu vào                                 | Kết quả mong đợi                                   | Loại test   | Kết quả thực tế | Trạng thái        |
| :------- | :---------------------- | :---------------------------------------------- | :------------------------------------------------- | :---------- | :-------------- | :---------------- |
| **TC01** | `formatDate()`          | `Date={25,2,2026}`                              | `"25/2/2026"`                                      | Bình thường |                 | [x] Pass [ ] Fail |
| **TC02** | `parseDate()`           | `"15/8/2026"`                                   | `Date{day=15,month=8, year=2026}`                  | Bình thường |                 | [x] Pass [ ] Fail |
| **TC03** | `getCurrentDate()`      | Gọi hàm trực tiếp từ hệ thống                   | Trả về đúng ngày, tháng, năm hiện tại của máy tính | Hệ thống    |                 | [x] Pass [ ] Fail |
| **TC04** | `addDays()`             | `startDate={28,2,2026}`, `daysToAdd = 2`        | `{2, 3, 2026}`                                     | Logic biên  |                 | [x] Pass [ ] Fail |
| **TC05** | `getDifferenceInDays()` | `startDate={01,6,2026}`, `endDate={15,6, 2026}` | `14`                                               | Bình thường |                 | [x] Pass [ ] Fail |

---

## 2. Nhóm Kiểm Tra Nhập Liệu Console (`Input Validation`)

| Mã test  | Hàm kiểm thử         | Dữ liệu đầu vào   | Kết quả mong đợi                                    | Loại test   | Kết quả thực tế | Trạng thái        |
| :------- | :------------------- | :---------------- | :-------------------------------------------------- | :---------- | :-------------- | :---------------- |
| **TC06** | `checkIntInput()`    | `xyz`             | `"Phai nhap so nguyen. Nhap lai: "` và chờ nhập lại | Dữ liệu xấu |                 | [x] Pass [ ] Fail |
| **TC07** | `checkIntInput()`    | `-5`              | `"So phai >= 0. Nhap lai: "` và chờ nhập lại        | Dữ liệu xấu |                 | [x] Pass [ ] Fail |
| **TC08** | `checkIntInput()`    | `10`              | Hàm kết thúc thành công, trả về true                | Bình thường |                 | [x] Pass [ ] Fail |
| **TC09** | `checkStringInput()` | `null`            | `"Khong duoc de trong. Nhap lai: "` và chờ nhập lại | Dữ liệu xấu |                 | [x] Pass [ ] Fail |
| **TC10** | `checkStringInput()` | `"Lap trinh C++"` | Hàm kết thúc thành công, trả về true                | Bình thường |                 | [x] Pass [ ] Fail |

---

## 3. Nhóm Quản Lý Sách (`Book`)

| Mã test  | Hàm kiểm thử         | Dữ liệu đầu vào                                           | Kết quả mong đợi                                                        | Loại test           | Kết quả thực tế | Trạng thái        |
| :------- | :------------------- | :-------------------------------------------------------- | :---------------------------------------------------------------------- | :------------------ | :-------------- | :---------------- |
| **TC11** | `addBook()`          | `B001`                                                    | `"Loi: Ma sach nay da ton tai trong he thong!"`                         | Trùng mã            |                 | [x] Pass [ ] Fail |
| **TC12** | `addBook()`          | `B010, Sach nau an, Nguyen van A, nau an`                 | Thêm sách mới vào vector books, đặt borrowedCount = 0 và báo thành công | Bình thường         |                 | [x] Pass [ ] Fail |
| **TC13** | `updateBook()`       | `B0022`                                                   | `"Loi: Khong tim thay sach co ma...!"`                                  | Dữ liệu xấu         |                 | [x] Pass [ ] Fail |
| **TC14** | `updateBook()`       | `B001`                                                    | Cập nhật thành công các thông tin title, author, category, quantity mới | Bình thường         |                 | [x] Pass [ ] Fail |
| **TC15** | `deleteBook()`       | Xóa mã sách đang có bản ghi chưa trả (`returned = false`) | In thông báo `"Loi: Sach dang duoc muon, khong the xoa!"`               | Nghiệp vụ ràng buộc |                 | [x] Pass [ ] Fail |
| **TC16** | `deleteBook()`       | Xóa mã sách không tồn tại hoặc đã được trả hết            | Xóa thành công cuốn sách khỏi danh sách hệ thống                        | Bình thường         |                 | [x] Pass [ ] Fail |
| **TC17** | `findBookById()`     | `B001`                                                    | `Book(id=”B001”)`                                                       | Bình thường         |                 | [x] Pass [ ] Fail |
| **TC18** | `findBookByTitle()`  | `Lap trinh C++ co ban`                                    | `Book(title=”Lap trinh C++ co ban”)`                                    | Hợp lệ              |                 | [x] Pass [ ] Fail |
| **TC19** | `findBookByAuthor()` | `Nguyen Van A`                                            | `Book(author=”Nguyen Van A”)`                                           | Hợp lệ              |                 | [x] Pass [ ] Fail |
| **TC21** | `isBookAvailable()`  | `quantity = 0`                                            | `false`                                                                 | Điều kiện biên      |                 | [x] Pass [ ] Fail |

---

## 4. Nhóm Quản Lý Độc Giả (`Reader`)

| Mã test  | Hàm kiểm thử       | Dữ liệu đầu vào    | Kết quả mong đợi                                   | Loại test      | Kết quả thực tế | Trạng thái        |
| :------- | :----------------- | :----------------- | :------------------------------------------------- | :------------- | :-------------- | :---------------- |
| **TC22** | `addReader()`      | `A001`             | `"Loi: Ma doc gia nay da ton tai trong he thong!"` | Dữ liệu xấu    |                 | [x] Pass [ ] Fail |
| **TC23** | `addReader()`      | `A010, Tran Thi B` | Thêm thành công, trả về true                       | Bình thường    |                 | [x] Pass [ ] Fail |
| **TC24** | `findReaderById()` | `A01`              | Trả về giá trị con trỏ `nullptr`                   | Không tìm thấy |                 | [x] Pass [ ] Fail |

---

## 5. Nhóm Nghiệp Vụ Mượn - Trả Sách (`Borrow & Return`)

| Mã test  | Hàm kiểm thử   | Dữ liệu đầu vào                                   | Kết quả mong đợi                                                                               | Loại test             | Kết quả thực tế | Trạng thái        |
| :------- | :------------- | :------------------------------------------------ | :--------------------------------------------------------------------------------------------- | :-------------------- | :-------------- | :---------------- |
| **TC25** | `borrowBook()` | Nhập sai mã độc giả hoặc mã sách                  | Báo lỗi tương ứng và ngừng thực hiện giao dịch                                                 | Dữ liệu xấu           |                 | [x] Pass [ ] Fail |
| **TC26** | `borrowBook()` | Sách yêu cầu mượn có `quantity = 0`               | `"Loi: Sach hien da het, khong the cho muon!"`                                                 | Điều kiện biên        |                 | [x] Pass [ ] Fail |
| **TC27** | `borrowBook()` | Độc giả cũ đang mượn đúng cuốn sách này chưa trả  | Báo lỗi trùng lặp và không cho phép mượn tiếp                                                  | Quy định nghiệp vụ    |                 | [x] Pass [ ] Fail |
| **TC28** | `borrowBook()` | Mọi thông tin hợp lệ và đủ điều kiện              | Tạo bản ghi mượn mới (`returned = false`), giảm quantity sách đi 1, tăng borrowedCount lên 1.  | Bình thường           |                 | [x] Pass [ ] Fail |
| **TC29** | `returnBook()` | Nhập cặp mã (Độc giả, Sách) không có bản ghi mượn | `"Loi: Khong tim thay phieu muon chua tra phu hop!"`                                           | Dữ liệu xấu           |                 | [x] Pass [ ] Fail |
| **TC30** | `returnBook()` | Trả sách trước hoặc đúng hạn trả mượn             | Cập nhật `returned = true`, tăng quantity sách lên 1, in ra dòng `"Trang thai: Tra dung han."` | Bình thường           |                 | [x] Pass [ ] Fail |
| **TC31** | `returnBook()` | Ngày hiện tại vượt quá ngày hạn trả của phiếu     | Thực hiện trả sách, in cảnh báo `"Canh bao: Sach duoc tra tre... ngay."`                       | Xử lý logic thời gian |                 | [x] Pass [ ] Fail |

---

## 6. Nhóm Lưu Trữ Đọc/Ghi Tập Tin (`File I/O`)

| Mã test  | Hàm kiểm thử          | Dữ liệu đầu vào                           | Kết quả mong đợi                                           | Loại test              | Kết quả thực tế | Trạng thái        |
| :------- | :-------------------- | :---------------------------------------- | :--------------------------------------------------------- | :--------------------- | :-------------- | :---------------- |
| **TC32** | `loadBooks()`         | File `book.csv` không tồn tại ở đường dẫn | `"Khong mo duoc file book.csv"`, `"Du lieu khoi tao rong"` | Xử lý ngoại lệ file    |                 | [x] Pass [ ] Fail |
| **TC33** | `loadBooks()`         | File chứa dòng dữ liệu lỗi định dạng      | Bỏ qua dữ liệu lỗi                                         | Kiểm tra tính bền vững |                 | [x] Pass [ ] Fail |
| **TC34** | `saveBooks()`         | Danh sách đang chứa dữ liệu sách          | Ghi file thành công                                        | Tương tác dữ liệu      |                 | [x] Pass [ ] Fail |
| **TC36** | `loadBorrowRecords()` | Dòng dữ liệu mượn hợp lệ                  | Đọc chính xác các thông tin ngày tháng năm                 | Chuyển đổi dữ liệu     |                 | [x] Pass [ ] Fail |
| **TC37** | `saveBorrowRecords()` | Danh sách đang chứa các bản ghi mượn trả  | Ghi file thành công                                        | Tương tác dữ liệu      |                 | [x] Pass [ ] Fail |

---

## 7. Nhóm Thống Kê Báo Cáo (`Statistics`)

| Mã test  | Hàm kiểm thử                 | Dữ liệu đầu vào                                   | Kết quả mong đợi                                                                 | Loại test            | Kết quả thực tế | Trạng thái        |
| :------- | :--------------------------- | :------------------------------------------------ | :------------------------------------------------------------------------------- | :------------------- | :-------------- | :---------------- |
| **TC38** | `calculateBorrowDays()`      | Bản ghi đã trả sách                               | Tính số ngày chênh lệch từ ngày mượn đến ngày trả thực tế (`actualReturnDate`)   | Thuật toán tính toán |                 | [x] Pass [ ] Fail |
| **TC39** | `isOverdue()`                | Bản ghi chưa trả sách, hạn trả trước ngày hôm nay | Hàm trả về giá trị logic `true`                                                  | Logic điều kiện      |                 | [x] Pass [ ] Fail |
| **TC40** | `displayOverdueBooks()`      | Hệ thống không có ai mượn quá hạn                 | In ra dòng chữ thông báo `"Khong co sach qua han."`                              | Điều kiện biên       |                 | [x] Pass [ ] Fail |
| **TC41** | `displayMostBorrowedBooks()` | Có nhiều cuốn sách cùng đạt số lượt mượn cao nhất | Liệt kê toàn bộ thông tin chi tiết của tất cả các cuốn sách đạt mốc cao nhất đó. | Logic thống kê       |                 | [x] Pass [ ] Fail |
