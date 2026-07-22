#include <iostream>
#include <vector>

#include "models.h"
#include "menu.cpp"
#include "services.h"

int main()
{

    std::vector<Book> books;
    std::vector<Reader> readers;
    std::vector<BorrowRecord> records;

    // Đọc dữ liệu từ file
    loadBooks(books);
    loadReaders(readers);
    loadBorrowRecords(records);

    // Hiển thị menu
    mainMenu(books, readers, records);

    // Lưu dữ liệu trước khi thoát
    saveBooks(books);
    saveReaders(readers);
    saveBorrowRecords(records);

    std::cout << "\nĐã thoát chương trình!\n";

    return 0;
}