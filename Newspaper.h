#ifndef NEWSPAPER_H
#define NEWSPAPER_H

#include "Publication.h"

class Newspaper : public Publication {
private:
    string publication_date;

public:
    Newspaper();
    Newspaper(int np_id, string np_title, string np_author, int pub_year, int np_pages, string date);

    string get_publication_date() const;
    void set_publication_date(string new_date);

    string get_type() const override;
    string short_line() const override;
    void display_info() const override;
    int get_specific_value() const override;
    string get_specific_field() const override;
    string get_specific_field_name() const override;
};

#endif