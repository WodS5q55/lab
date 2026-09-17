#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Reader.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Library {
private:
    vector<Book> books;
    vector<Reader> readers;

    vector<time_t> borrow_dates;

    static const int MAX_BORROW_DAYS = 14;

    int find_book_index(const Book* book) const;
    void print_book_line(const Book& book, bool with_author) const;

public:
    Library();

    void add_book(const Book& book);
    void add_reader(const Reader& reader);
    void remove_book(Book* book);

    const vector<Book>& get_books() const;
    const vector<Reader>& get_readers() const;
    vector<Book>& get_books_mutable();

    Book* find_book_by_title(const string& title);
    vector<Book*> find_available_books();
    vector<Book*> find_borrowed_books();
    Reader* find_reader_by_id(int id);

    void borrow_book(Book* book, Reader* reader);
    void return_book(Book* book);

    int get_days_left(const Book* book) const; 
    bool is_overdue(const Book* book) const;     
    time_t get_borrow_date(const Book* book) const;

    void display_all_books() const;
    void display_all_readers() const;
    void display_overdue_books() const;
    void display_book_info(Book* book);
    void display_reader_info(Reader* reader);

    void change_reader_name(Reader* reader, string new_name);
    void change_reader_phone(Reader* reader, string new_phone);

    int get_book_count() const;
    int get_reader_count() const;
};

#endif