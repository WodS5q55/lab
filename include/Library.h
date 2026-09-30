#ifndef LIBRARY_H
#define LIBRARY_H

#include "Publication.h"
#include "Reader.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Library {
private:
    vector<Publication*> publications;
    vector<Reader> readers;
    vector<time_t> borrow_dates;

    static const int MAX_BORROW_DAYS = 14;
    int next_pub_id;

    int find_pub_index(const Publication* pub) const;

public:
    Library();
    ~Library();

    Library& operator+=(Publication* pub);
    Library& operator-=(Publication* pub);
    Library& operator+=(const Reader& reader);
    Library& operator-=(const Reader& reader);

    void add_publication(Publication* pub);
    void add_reader(const Reader& reader);
    void remove_publication(Publication* pub);

    const vector<Publication*>& get_publications() const;
    const vector<Reader>& get_readers() const;
    vector<Reader>& get_readers_mutable();

    Publication* find_publication_by_title(const string& title);
    vector<Publication*> find_available_publications();
    vector<Publication*> find_borrowed_publications();
    Reader* find_reader_by_id(int id);

    void borrow_publication(Publication* pub, Reader* reader);
    void return_publication(Publication* pub);

    int get_days_left(const Publication* pub) const;
    bool is_overdue(const Publication* pub) const;

    void display_all_publications() const;
    void display_all_readers() const;
    void display_overdue_publications() const;
    void display_publication_info(Publication* pub);
    void display_reader_info(Reader* reader);
    void compare_two_publications() const;
    void compare_two_readers() const;
    void display_all_types_info() const;

    void change_reader_name(Reader* reader, string new_name);
    void change_reader_phone(Reader* reader, string new_phone);

    int get_publication_count() const;
    int get_reader_count() const;
};

#endif