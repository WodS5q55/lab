#ifndef BOOK_H
#define BOOK_H

#include "Publication.h"

class Book : public Publication {
private:
    string type;

public:
    Book();
    Book(int book_id, string book_title, string book_author, int pub_year, int book_pages, string book_type);

    string get_book_type() const;
    void set_book_type(string new_type);

    bool is_for_students() const;
    bool is_too_old_for_study() const;
    int get_difficulty_level() const;

    string get_type() const override;
    string short_line() const override;
    void display_info() const override;
    double calculate_price() const override;
    string get_field() const override;
    string get_field_name() const override;
};

#endif