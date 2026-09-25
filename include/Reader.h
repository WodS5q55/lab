#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>

using namespace std;

class Reader {
private:
    string full_name;
    string phone;
    int reader_id;
    static int next_id;

public:
    Reader();
    Reader(string name, string phone_num);

    string get_name() const;
    string get_phone() const;
    int get_id() const;

    void set_name(string new_name);
    void set_phone(string new_phone);

    void display_info() const;


    bool operator<(const Reader& other) const;  
    bool operator>(const Reader& other) const;   

    bool operator==(const Reader& other) const; 
    bool operator!=(const Reader& other) const;  
    bool operator<=(const Reader& other) const;   
    bool operator>=(const Reader& other) const;  

    friend ostream& operator<<(ostream& os, const Reader& reader);
    friend istream& operator>>(istream& is, Reader& reader);
};

#endif