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

    bool is_latest_issue(int current_issue) const;
    bool is_recent() const;

    string get_type() const override;
    string short_line() const override;
    void display_info() const override;
    double calculate_specific_value() const override;
    string get_specific_field() const override;
    string get_specific_field_name() const override;
};

#endif