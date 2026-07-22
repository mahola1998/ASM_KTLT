#ifndef MODEL_H
#define MODEL_H

#include <string>

struct Date
{
    int day;
    int month;
    int year;
};

struct Book
{
    std::string id;
    std::string title;
    std::string author;
    std::string category;
    int quantity;
    int borrowedCount;
};

struct Reader
{
    std::string id;
    std::string name;
    std::string phone;
};

struct BorrowRecord
{
    std::string readerId;
    std::string bookId;
    Date borrowDate;
    Date returnDate;
    // Date expectedReturnDate;
    Date actualReturnDate;
    bool returned;
};

#endif