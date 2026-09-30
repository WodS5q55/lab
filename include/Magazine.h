#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Publication.h"

class Magazine : public Publication {
private:
    int issue_number;

public:
    Magazine();
    Magazine(int mag_id, string mag_title, string mag_author, int pub_year, int mag_pages, int issue);

    int get_issue_number() const;
    void set_issue_number(int new_issue);

    string get_type() const override;
    string short_line() const override;
    void display_info() const override;
    int get_specific_value() const override;
    string get_specific_field() const override;
    string get_specific_field_name() const override;
};

#endif