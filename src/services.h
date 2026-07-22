#ifndef SERVICES_H
#define SERVICES_H

#include "models.h"
#include <vector>
#include <string>

using namespace std;

//=================== QUẢN LÝ THỜI GIAN ===================//

string formatDate(const Date &d);
Date parseDate(const string &dateStr);
Date getCurrentDate();
Date addDays(Date startDate, int daysToAdd);
int getDifferenceInDays(Date startDate, Date endDate);

//===================== QUẢN LÝ SÁCH =====================//

void checkIntInput(int &number);
void checkStringInput(string &text);
void addBook(vector<Book> &books);
void updateBook(vector<Book> &books);
void deleteBook(vector<Book> &books, const vector<BorrowRecord> &records);

Book *findBookById(vector<Book> &books, const string &id);
Book *findBookByTitle(vector<Book> &books, const string &title);
vector<Book *> findBookByAuthor(vector<Book> &books, const string &author);

void displayBooks(const vector<Book> &books);
void displayBook(const Book &book);

void isBookAvailable(vector<Book> &books);

//===================== QUẢN LÝ ĐỘC GIẢ =====================//

void addReader(vector<Reader> &readers);

Reader *findReaderById(vector<Reader> &readers, const string &id);

void displayReaders(const vector<Reader> &readers);
void displayReader(const Reader &reader);

//===================== MƯỢN - TRẢ =====================//

void borrowBook(vector<Book> &books,
                vector<Reader> &readers,
                vector<BorrowRecord> &records);

void returnBook(vector<Book> &books,
                vector<BorrowRecord> &records);

void displayBorrowHistory(const vector<BorrowRecord> &records);

//===================== FILE =====================//

void loadBooks(vector<Book> &books);
void saveBooks(const vector<Book> &books);

void loadReaders(vector<Reader> &readers);
void saveReaders(const vector<Reader> &readers);

void loadBorrowRecords(vector<BorrowRecord> &records);
void saveBorrowRecords(const vector<BorrowRecord> &records);

//===================== THỐNG KÊ =====================//

int calculateBorrowDays(const BorrowRecord &record);

bool isOverdue(const BorrowRecord &record);

void displayOverdueBooks(const vector<BorrowRecord> &records);

void displayMostBorrowedBooks(const vector<Book> &books);

#endif