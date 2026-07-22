#include "services.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>

const string BOOK_FILE = "../data/book.csv";
const string READER_FILE = "../data/reader.csv";
const string BORROW_FILE = "../data/rentalInfo.csv";

using namespace std;

// Hàm chuyển đổi Date sang chuỗi (Dùng để in ra màn hình và ghi file)
string formatDate(const Date &d)
{
    if (d.day == 0 && d.month == 0 && d.year == 0)
        return "0/0/0";
    return to_string(d.day) + "/" + to_string(d.month) + "/" + to_string(d.year);
}

// Hàm chuyển đổi chuỗi sang Date (Dùng khi đọc từ file CSV)
Date parseDate(const string &dateStr)
{
    Date d = {0, 0, 0};
    if (dateStr.empty() || dateStr == "0/0/0")
        return d;

    stringstream ss(dateStr);
    string part;

    if (getline(ss, part, '/'))
        d.day = stoi(part);
    if (getline(ss, part, '/'))
        d.month = stoi(part);
    if (getline(ss, part, '/'))
        d.year = stoi(part);

    return d;
}

// 1. Lấy ngày hiện tại của hệ thống máy tính
Date getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    Date d;
    d.day = ltm->tm_mday;
    d.month = 1 + ltm->tm_mon;
    d.year = 1900 + ltm->tm_year;
    return d;
}

// Thêm hạn trả
Date addDays(Date startDate, int daysToAdd)
{
    tm timeinfo = {};
    timeinfo.tm_mday = startDate.day + daysToAdd;
    timeinfo.tm_mon = startDate.month - 1;
    timeinfo.tm_year = startDate.year - 1900;

    mktime(&timeinfo);

    Date result;
    result.day = timeinfo.tm_mday;
    result.month = timeinfo.tm_mon + 1;
    result.year = timeinfo.tm_year + 1900;
    return result;
}

// tính số ngày đã mượn
int getDifferenceInDays(Date startDate, Date endDate)
{
    tm time1 = {};
    time1.tm_mday = startDate.day;
    time1.tm_mon = startDate.month - 1;
    time1.tm_year = startDate.year - 1900;

    tm time2 = {};
    time2.tm_mday = endDate.day;
    time2.tm_mon = endDate.month - 1;
    time2.tm_year = endDate.year - 1900;

    time_t t1 = mktime(&time1);
    time_t t2 = mktime(&time2);

    double seconds = difftime(t2, t1);
    return static_cast<int>(seconds / 86400.0);
}

// kiểm tra int
void checkIntInput(int &number)
{
    while (true)
    {
        cin >> number;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Phai nhap so nguyen. Nhap lai: ";
            continue;
        }

        if (number < 0)
        {
            cout << "So phai >= 0. Nhap lai: ";
            continue;
        }
        cin.ignore(10000, '\n');
        break;
    }
}

// kiểm tra string
void checkStringInput(string &text)
{
    while (true)
    {
        getline(cin, text);

        if (text.find_first_not_of(' ') != string::npos)
            break;

        cout << "Khong duoc de trong. Nhap lai: ";
    }
}

// Thêm sách
void addBook(vector<Book> &books)
{
    Book newBook;
    cout << "\n--- THEM SACH MOI ---\n";
    cout << "Nhap Ma sach (ID): ";
    checkStringInput(newBook.id);

    if (findBookById(books, newBook.id) != nullptr)
    {
        cout << "Loi: Ma sach nay da ton tai trong he thong!\n";
        return;
    }

    cout << "Nhap Ten sach: ";
    checkStringInput(newBook.title);

    cout << "Nhap Ten tac gia: ";
    checkStringInput(newBook.author);

    cout << "Nhap The loai: ";
    checkStringInput(newBook.category);

    cout << "Nhap Tong so luong: ";
    checkIntInput(newBook.quantity);

    newBook.borrowedCount = 0;

    books.push_back(newBook);
    cout << "-> Them sach thanh cong!\n";
}

// Cập nhật thông tin sách
void updateBook(vector<Book> &books)
{
    string id;
    cout << "\n--- CAP NHAT THONG TIN SACH ---\n";
    cout << "Nhap Ma sach can cap nhat: ";
    cin >> id;

    Book *bookToUpdate = findBookById(books, id);
    if (bookToUpdate == nullptr)
    {
        cout << "Loi: Khong tim thay sach co ma " << id << "!\n";
        return;
    }

    cout << "Nhap Ten sach moi (Ten hien tai: " << bookToUpdate->title << "): ";
    checkStringInput(bookToUpdate->title);

    cout << "Nhap Ten tac gia moi (Hien tai: " << bookToUpdate->author << "): ";
    checkStringInput(bookToUpdate->author);

    cout << "Nhap The loai moi (Hien tai: " << bookToUpdate->category << "): ";
    checkStringInput(bookToUpdate->category);

    cout << "Nhap Tong so luong moi (Hien tai: " << bookToUpdate->quantity << "): ";
    checkIntInput(bookToUpdate->quantity);

    cout << "-> Cap nhat thong tin sach thanh cong!\n";
}

// Xóa sách
void deleteBook(vector<Book> &books, const vector<BorrowRecord> &records)
{
    string id;
    cout << "\n--- XOA SACH ---\n";
    cout << "Nhap Ma sach can xoa: ";
    cin >> id;

    // Kiểm tra sách có đang được mượn không
    for (const auto &record : records)
    {
        if (record.bookId == id && !record.returned)
        {
            cout << "Loi: Sach dang duoc muon, khong the xoa!\n";
            return;
        }
    }

    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it->id == id)
        {
            books.erase(it);
            cout << "-> Xoa sach thanh cong!\n";
            return;
        }
    }

    cout << "Loi: Khong tim thay sach co ma " << id << " de xoa!\n";
}

// Tìm sách theo id
Book *findBookById(vector<Book> &books, const string &id)
{
    for (auto &book : books)
    {
        if (book.id == id)
        {
            return &book;
        }
    }
    return nullptr;
}

// Tìm sách theo tiêu đề
Book *findBookByTitle(vector<Book> &books, const string &title)
{

    for (auto &book : books)
    {
        if (book.title == title)
        {
            return &book;
        }
    }
    return nullptr;
}

// Tìm sách theo tác giả
vector<Book *> findBookByAuthor(vector<Book> &books, const string &author)
{
    vector<Book *> result;
    for (auto &book : books)
    {
        if (book.author == author)
        {
            result.push_back(&book);
        }
    }
    return result;
}

// hiển thị danh sách sách
void displayBooks(const vector<Book> &books)
{
    if (books.empty())
    {
        cout << "Thu vien hien chua co cuon sach nao.\n";
        return;
    }

    cout << "\n================ DANH SACH SACH ================\n";
    for (const auto &book : books)
    {
        displayBook(book);
    }
    cout << "================================================\n";
}

// hiện thị sách
void displayBook(const Book &book)
{
    cout << left << "ID: " << setw(4) << book.id
         << "| Ten: " << setw(30) << book.title
         << "| Tac gia: " << setw(15) << book.author
         << "| The loai: " << setw(10) << book.category
         << "| So luong: " << setw(1) << book.quantity
         << "| Luot muon: " << setw(2) << book.borrowedCount << "\n";
}

// xem sách có sẳn sàng cho mượn hay không
void isBookAvailable(vector<Book> &books)
{
    string bookId;

    cout << "\n--- KIEM TRA SACH CON HAY DA DUOC MUON ---\n";
    cout << "Nhap ma sach can kiem tra: ";
    cin >> bookId;

    Book *book = findBookById(books, bookId);

    if (book == nullptr)
    {
        cout << "Loi: Khong tim thay sach co ma "
             << bookId << "!\n";
        return;
    }

    cout << "\nThong tin sach:\n";
    displayBook(*book);

    if (book->quantity > 0)
    {
        cout << "Trang thai: SACH CON SAN DE MUON.\n";
        cout << "So luong con lai: "
             << book->quantity << " cuon.\n";
    }
    else
    {
        cout << "Trang thai: SACH DA DUOC MUON HET.\n";
        cout << "Hien tai khong con cuon nao de cho muon.\n";
    }
}

// thêm độc giả
void addReader(vector<Reader> &readers)
{
    Reader newReader;
    cout << "\n--- THEM DOC GIA MOI ---\n";
    cout << "Nhap Ma doc gia (ID): ";
    checkStringInput(newReader.id);

    if (findReaderById(readers, newReader.id) != nullptr)
    {
        cout << "Loi: Ma doc gia nay da ton tai trong he thong!\n";
        return;
    }

    cout << "Nhap Ten doc gia: ";
    checkStringInput(newReader.name);

    cout << "Nhap So dien thoai: ";
    checkStringInput(newReader.phone);

    readers.push_back(newReader);
    cout << "-> Them doc gia thanh cong!\n";
}

// Tìm độc giả theo id
Reader *findReaderById(vector<Reader> &readers, const string &id)
{
    for (auto &reader : readers)
    {
        if (reader.id == id)
        {
            return &reader;
        }
    }
    return nullptr;
}

//  In danh sách toàn bộ độc giả
void displayReaders(const vector<Reader> &readers)
{
    if (readers.empty())
    {
        cout << "He thong chua co doc gia nao.\n";
        return;
    }

    cout << "\n================ DANH SACH DOC GIA ================\n";
    for (const auto &reader : readers)
    {
        displayReader(reader);
    }
    cout << "===================================================\n";
}

//  In thông tin 1 độc giả
void displayReader(const Reader &reader)
{
    cout << left << "ID: " << setw(4) << reader.id
         << " | Ten: " << setw(25) << reader.name
         << " | SDT: " << setw(15) << reader.phone << "\n";
}

//===================== MƯỢN - TRẢ =====================//
// Mượn sách
void borrowBook(vector<Book> &books,
                vector<Reader> &readers,
                vector<BorrowRecord> &records)
{
    string readerId;
    string bookId;

    cout << "\n--- MUON SACH ---\n";
    cout << "Nhap ma doc gia: ";
    cin >> readerId;

    Reader *reader = findReaderById(readers, readerId);
    if (reader == nullptr)
    {
        cout << "Loi: Khong tim thay doc gia co ma " << readerId << "!\n";
        return;
    }

    cout << "Nhap ma sach: ";
    cin >> bookId;

    Book *book = findBookById(books, bookId);
    if (book == nullptr)
    {
        cout << "Loi: Khong tim thay sach co ma " << bookId << "!\n";
        return;
    }

    if (book->quantity <= 0)
    {
        cout << "Loi: Sach hien da het, khong the cho muon!\n";
        return;
    }

    for (const auto &record : records)
    {
        if (record.readerId == readerId &&
            record.bookId == bookId &&
            !record.returned)
        {
            cout << "Loi: Doc gia dang muon sach nay va chua tra!\n";
            return;
        }
    }

    BorrowRecord newRecord;
    newRecord.readerId = readerId;
    newRecord.bookId = bookId;
    newRecord.borrowDate = getCurrentDate();
    newRecord.returnDate = addDays(newRecord.borrowDate, 14);
    newRecord.returned = false;

    records.push_back(newRecord);
    book->quantity--;
    book->borrowedCount++;

    cout << "-> Muon sach thanh cong!\n";
    cout << "Doc gia: " << reader->name << "\n";
    cout << "Sach: " << book->title << "\n";
    cout << "Ngay muon: " << formatDate(newRecord.borrowDate) << "\n";
    cout << "Han tra: " << formatDate(newRecord.returnDate) << "\n";
}

// trả sách
void returnBook(vector<Book> &books,
                vector<BorrowRecord> &records)
{
    string readerId;
    string bookId;

    cout << "\n--- TRA SACH ---\n";
    cout << "Nhap ma doc gia: ";
    cin >> readerId;
    cout << "Nhap ma sach: ";
    cin >> bookId;

    BorrowRecord *recordToReturn = nullptr;

    for (auto it = records.rbegin(); it != records.rend(); ++it)
    {
        if (it->readerId == readerId &&
            it->bookId == bookId &&
            !it->returned)
        {
            recordToReturn = &(*it);
            break;
        }
    }

    if (recordToReturn == nullptr)
    {
        cout << "Loi: Khong tim thay phieu muon chua tra phu hop!\n";
        return;
    }

    Book *book = findBookById(books, bookId);
    if (book == nullptr)
    {
        cout << "Loi: Sach khong con ton tai trong danh sach!\n";
        return;
    }

    Date currentDate = getCurrentDate();
    int daysLate = getDifferenceInDays(recordToReturn->returnDate, currentDate);

    recordToReturn->returned = true;
    book->quantity++;

    cout << "-> Tra sach thanh cong!\n";
    cout << "Sach: " << book->title << "\n";
    cout << "Ngay tra: " << formatDate(currentDate) << "\n";

    if (daysLate > 0)
        cout << "Canh bao: Sach duoc tra tre " << daysLate << " ngay.\n";
    else
        cout << "Trang thai: Tra dung han.\n";
}

// hiện lịch sử mượn - trả
void displayBorrowHistory(const vector<BorrowRecord> &records)
{
    if (records.empty())
    {
        cout << "He thong chua co lich su muon sach.\n";
        return;
    }

    cout << "\n================ LICH SU MUON - TRA ================\n";

    for (const auto &record : records)
    {
        cout << left << "Doc gia: " << setw(4) << record.readerId
             << " | Sach: " << setw(30) << record.bookId
             << " | Ngay muon: " << setw(4) << formatDate(record.borrowDate)
             << " | Han tra: " << setw(4) << formatDate(record.returnDate)
             << " | Trang thai: " << setw(4) << (record.returned ? "DA TRA" : "CHUA TRA");

        if (!record.returned)
        {
            int days = getDifferenceInDays(record.borrowDate, getCurrentDate());
            if (days < 0)
                days = 0;
            cout << " | Da muon: " << days << " ngay";

            int daysLate = getDifferenceInDays(record.returnDate, getCurrentDate());
            if (daysLate > 0)
                cout << " | QUA HAN " << daysLate << " ngay";
        }

        cout << "\n";
    }

    cout << "====================================================\n";
}

//===================== FILE =====================//
// đọc file sách
void loadBooks(vector<Book> &books)
{
    books.clear();
    ifstream inputFile(BOOK_FILE);

    if (!inputFile.is_open())
    {
        cout << "Khong mo duoc file " << BOOK_FILE << ". Danh sach sach duoc khoi tao rong.\n";
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        vector<string> fields;
        string field;

        while (getline(ss, field, ','))
        {
            if (!field.empty() && field.back() == '\r')
                field.pop_back();
            fields.push_back(field);
        }

        try
        {
            Book book;

            if (fields.size() == 5)
            {
                book.id = fields[0];
                book.title = fields[1];
                book.author = fields[2];
                book.category = "Chua phan loai";
                book.quantity = stoi(fields[3]);
                book.borrowedCount = stoi(fields[4]);
            }
            else if (fields.size() >= 6)
            {
                book.id = fields[0];
                book.title = fields[1];
                book.author = fields[2];
                book.category = fields[3];
                book.quantity = stoi(fields[4]);
                book.borrowedCount = stoi(fields[5]);
            }
            else
            {
                continue;
            }

            books.push_back(book);
        }
        catch (const exception &)
        {
            cout << "Bo qua dong sach khong hop le: " << line << "\n";
        }
    }

    inputFile.close();
}

// Lưu sách
void saveBooks(const vector<Book> &books)
{
    ofstream outputFile(BOOK_FILE);

    if (!outputFile.is_open())
    {
        cout << "Loi: Khong the ghi file " << BOOK_FILE << "!\n";
        return;
    }

    for (const auto &book : books)
    {
        outputFile << book.id << ","
                   << book.title << ","
                   << book.author << ","
                   << book.category << ","
                   << book.quantity << ","
                   << book.borrowedCount << "\n";
    }

    outputFile.close();
}

// đọc file đọc giả
void loadReaders(vector<Reader> &readers)
{
    readers.clear();
    ifstream inputFile(READER_FILE);

    if (!inputFile.is_open())
    {
        cout << "Khong mo duoc file " << READER_FILE << ". Danh sach doc gia duoc khoi tao rong.\n";
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        Reader reader;

        if (!getline(ss, reader.id, ','))
            continue;
        if (!getline(ss, reader.name, ','))
            continue;

        if (!getline(ss, reader.phone))
            reader.phone = "";

        if (!reader.name.empty() && reader.name.back() == '\r')
            reader.name.pop_back();
        if (!reader.phone.empty() && reader.phone.back() == '\r')
            reader.phone.pop_back();

        readers.push_back(reader);
    }

    inputFile.close();
}

// lưu dọc giả
void saveReaders(const vector<Reader> &readers)
{
    ofstream outputFile(READER_FILE);

    if (!outputFile.is_open())
    {
        cout << "Loi: Khong the ghi file " << READER_FILE << "!\n";
        return;
    }

    for (const auto &reader : readers)
    {
        outputFile << reader.id << ","
                   << reader.name << ","
                   << reader.phone << "\n";
    }

    outputFile.close();
}

// đọc file lịch sử mượn
void loadBorrowRecords(vector<BorrowRecord> &records)
{
    records.clear();
    ifstream inputFile(BORROW_FILE);

    if (!inputFile.is_open())
    {
        cout << "Khong mo duoc file " << BORROW_FILE << ". Lich su muon duoc khoi tao rong.\n";
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        if (line.empty())
            continue;
        if (line.back() == '\r')
            line.pop_back();

        stringstream ss(line);
        string part;
        BorrowRecord record;

        try
        {
            if (getline(ss, record.readerId, ',') &&
                getline(ss, record.bookId, ','))
            {
                if (getline(ss, part, ','))
                    record.borrowDate = parseDate(part);
                if (getline(ss, part, ','))
                    record.returnDate = parseDate(part);
                if (getline(ss, part, ','))
                    record.actualReturnDate = parseDate(part);

                if (getline(ss, part))
                {
                    record.returned = (part == "1" || part == "true" || part == "TRUE");
                }
                records.push_back(record);
            }
        }
        catch (const exception &)
        {
            cout << "Bo qua dong muon sach khong hop le: " << line << "\n";
        }
    }
    inputFile.close();
}

// Lưu lịch sử mượn
void saveBorrowRecords(const vector<BorrowRecord> &records)
{
    ofstream outputFile(BORROW_FILE);

    if (!outputFile.is_open())
    {
        cout << "Loi: Khong the ghi file " << BORROW_FILE << "!\n";
        return;
    }

    for (const auto &record : records)
    {
        outputFile << record.readerId << ","
                   << record.bookId << ","
                   << formatDate(record.borrowDate) << ","
                   << formatDate(record.returnDate) << ","
                   << formatDate(record.actualReturnDate) << ","
                   << (record.returned ? 1 : 0) << "\n";
    }

    outputFile.close();
}

//===================== THỐNG KÊ =====================//

int calculateBorrowDays(const BorrowRecord &record)
{
    Date endDate = record.returned ? record.actualReturnDate : getCurrentDate();
    return getDifferenceInDays(record.borrowDate, endDate);
}

bool isOverdue(const BorrowRecord &record)
{
    if (record.returned)
    {
        return getDifferenceInDays(record.returnDate, record.actualReturnDate) > 0;
    }
    else
    {
        return getDifferenceInDays(record.returnDate, getCurrentDate()) > 0;
    }
}

void displayOverdueBooks(const vector<BorrowRecord> &records)
{
    cout << "\n================ SACH QUA HAN ================\n";
    bool hasOverdue = false;

    for (const auto &rec : records)
    {
        if (isOverdue(rec))
        {
            hasOverdue = true;
            cout << left << "Doc gia: " << setw(4) << rec.readerId
                 << " | Sach: " << setw(30) << rec.bookId
                 << " | Ngay muon: " << setw(10) << formatDate(rec.borrowDate)
                 << " | Han tra: " << setw(10) << formatDate(rec.returnDate);

            if (!rec.returned)
            {
                int daysLate = getDifferenceInDays(rec.returnDate, getCurrentDate());
                cout << " | Trang thai: CHUA TRA (Tre " << daysLate << " ngay)\n";
            }
            else
            {
                int daysLate = getDifferenceInDays(rec.returnDate, rec.actualReturnDate);
                cout << " | Trang thai: DA TRA (Nhung tra tre " << daysLate << " ngay)\n";
            }
        }
    }
    if (!hasOverdue)
    {
        cout << "Khong co sach qua han.\n";
    }

    cout << "==============================================\n";
}

// Sách được đọc nhiều nhất
void displayMostBorrowedBooks(const vector<Book> &books)
{
    if (books.empty())
    {
        cout << "Khong co du lieu sach de thong ke.\n";
        return;
    }

    int maxBorrowedCount = books[0].borrowedCount;

    for (const auto &book : books)
    {
        if (book.borrowedCount > maxBorrowedCount)
            maxBorrowedCount = book.borrowedCount;
    }

    cout << "\n================ SACH DUOC MUON NHIEU NHAT ================\n";
    cout << "So luot muon cao nhat: " << maxBorrowedCount << "\n";

    for (const auto &book : books)
    {
        if (book.borrowedCount == maxBorrowedCount)
            displayBook(book);
    }

    cout << "===========================================================\n";
}