#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include <iostream>

using namespace std;

class Reader;

class Publication {
protected:
    int id;
    string title;
    string author;
    int year;
    int pages;
    Reader* borrowed_by;

public:
    Publication(int pub_id, string pub_title, string pub_author, int pub_year, int pub_pages);
    virtual ~Publication();

    int get_id() const;
    string get_title() const;
    string get_author() const;
    int get_year() const;
    int get_pages() const;
    Reader* get_borrowed_by() const;

    bool is_available() const;
    bool is_borrowed() const;

    void borrow_book(Reader* reader);
    void return_book();

    virtual string get_type() const = 0;
    virtual string short_line() const = 0;
    virtual void display_info() const = 0;
    virtual double calculate_price() const = 0;
    virtual string get_specific_field() const = 0;
    virtual string get_specific_field_name() const = 0;

    friend ostream& operator<<(ostream& os, const Publication& pub);

    bool operator==(const Publication& other) const;
    bool operator!=(const Publication& other) const;
    bool operator<(const Publication& other) const;
    bool operator>(const Publication& other) const;
    bool operator<=(const Publication& other) const;
    bool operator>=(const Publication& other) const;
};

#endif