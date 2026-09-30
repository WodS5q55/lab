#include "Publication.h"
#include "Reader.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

Publication::Publication(int pub_id, string pub_title, string pub_author, int pub_year, int pub_pages) {
    if (pub_title.empty() || pub_author.empty()) {
        throw InvalidBookDataException("название или автор пустые");
    }

    if (pub_pages < 1 || pub_pages > 10000) {
        throw InvalidBookDataException("некорректное количество страниц");
    }

    id = pub_id;
    title = pub_title;
    author = pub_author;
    year = pub_year;
    pages = pub_pages;
    borrowed_by = nullptr;
}

Publication::~Publication() {
}

int Publication::get_id() const { return id; }
string Publication::get_title() const { return title; }
string Publication::get_author() const { return author; }
int Publication::get_year() const { return year; }
int Publication::get_pages() const { return pages; }
Reader* Publication::get_borrowed_by() const { return borrowed_by; }

bool Publication::is_available() const { return borrowed_by == nullptr; }
bool Publication::is_borrowed() const { return borrowed_by != nullptr; }

void Publication::borrow_book(Reader* reader) {
    if (is_borrowed()) {
        throw BookNotAvailableException();
    }
    borrowed_by = reader;
}

void Publication::return_book() {
    if (is_available()) {
        throw BookNotBorrowedException();
    }
    borrowed_by = nullptr;
}

ostream& operator<<(ostream& os, const Publication& pub) {
    os << "#" << pub.id << " \"" << pub.title << "\" - " << pub.author
        << " (" << pub.year << ", " << pub.pages << " стр.)";
    return os;
}

bool Publication::operator==(const Publication& other) const {
    return year == other.year;
}

bool Publication::operator!=(const Publication& other) const {
    return year != other.year;
}

bool Publication::operator<(const Publication& other) const {
    return pages < other.pages;
}

bool Publication::operator>(const Publication& other) const {
    return pages > other.pages;
}

bool Publication::operator<=(const Publication& other) const {
    return year <= other.year;
}

bool Publication::operator>=(const Publication& other) const {
    return year >= other.year;
}