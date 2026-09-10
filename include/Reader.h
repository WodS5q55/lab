#ifndef READER_H
#define READER_H

#include <string>

using namespace std;

class Reader {
private:
    string full_name;
    string phone;
    int reader_id;
    static int next_id;

public:
    Reader(string name, string phone_num);

    string get_name() const;
    string get_phone() const;
    int get_id() const;

    void set_phone(string new_phone);
    void display_info() const;
};

#endif#pragma once
