#include "services.h"
#include "services.cpp"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Hàm bổ trợ để nhập số an toàn, chống treo vòng lặp
void handleInputError()
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void searchBookMenu(std::vector<Book> &books)
{
    int choice;
    std::string keyword;

    do
    {
        std::cout << "\n========== TIM KIEM SACH ==========\n";
        std::cout << "1. Theo ma sach\n";
        std::cout << "2. Theo ten sach\n";
        std::cout << "3. Theo tac gia\n";
        std::cout << "0. Quay lai\n";
        std::cout << "===================================\n";
        std::cout << "Nhap lua chon: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            choice = -1;
        }
        handleInputError();

        switch (choice)
        {
        case 1:
        {
            std::cout << "Nhap ma sach: ";
            std::getline(std::cin, keyword);

            Book *book = findBookById(books, keyword);

            if (book != nullptr)
                displayBook(*book);
            else
                std::cout << "Khong tim thay sach!\n";

            break;
        }

        case 2:
        {
            std::cout << "Nhap ten sach: ";
            std::getline(std::cin, keyword);

            Book *book = findBookByTitle(books, keyword);

            if (book != nullptr)
                displayBook(*book);
            else
                std::cout << "Khong tim thay sach!\n";

            break;
        }

        case 3:
        {
            std::cout << "Nhap ten tac gia: ";
            std::getline(std::cin, keyword);

            std::vector<Book *> result = findBookByAuthor(books, keyword);

            if (result.empty())
            {
                std::cout << "Khong tim thay sach!\n";
            }
            else
            {
                for (Book *book : result)
                    displayBook(*book);
            }

            break;
        }

        case 0:
            break;

        default:
            std::cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}

void mainMenu(std::vector<Book> &books,
              std::vector<Reader> &readers,
              std::vector<BorrowRecord> &records)
{
    int choice;

    do
    {
        std::cout << "\n========== QUAN LY THU VIEN ==========\n";
        std::cout << "1. Them sach\n";
        std::cout << "2. Cap nhat thong tin sach\n";
        std::cout << "3. Xoa sach\n";
        std::cout << "4. Tim kiem sach\n";
        std::cout << "5. Hien thi danh sach sach\n";
        std::cout << "6. Them doc gia\n";
        std::cout << "7. Hien thi danh sach doc gia\n";
        std::cout << "8. Muon sach\n";
        std::cout << "9. Tra sach\n";
        std::cout << "10. Kiem tra sach con hay da muon\n";
        std::cout << "11. Lich su muon/tra\n";
        std::cout << "12. Luu du lieu vao file\n";
        std::cout << "13. Danh sach sach qua han\n";
        std::cout << "14. Thong ke sach duoc muon nhieu nhat\n";
        std::cout << "0. Thoat\n";
        std::cout << "======================================\n";
        std::cout << "Nhap lua chon: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            choice = -1;
        }
        handleInputError();

        switch (choice)
        {
        case 1:
            addBook(books);
            break;

        case 2:
            updateBook(books);
            break;

        case 3:
            deleteBook(books, records);
            break;

        case 4:
            searchBookMenu(books);
            break;

        case 5:
            displayBooks(books);
            break;

        case 6:
            addReader(readers);
            break;

        case 7:
            displayReaders(readers);
            break;

        case 8:
            borrowBook(books, readers, records);
            break;

        case 9:
            returnBook(books, records);
            break;

        case 10:
            isBookAvailable(books);
            break;

        case 11:
            displayBorrowHistory(records);
            break;

        case 12:
            saveBooks(books);
            saveReaders(readers);
            saveBorrowRecords(records);
            std::cout << "Luu du lieu thanh cong!\n";
            break;

        case 13:
            displayOverdueBooks(records);
            break;

        case 14:
            displayMostBorrowedBooks(books);
            break;

        case 0:
            std::cout << "Cam on ban da su dung chuong trinh!\n";
            break;

        default:
            std::cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}