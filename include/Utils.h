#ifndef UTILS_H
#define UTILS_H

#include "Book.h"
#include "Reader.h"
#include <vector>
#include <string>

using namespace std;

class Library;

void clear_input();
bool is_blank(const string& str);
int select_from_list(const vector<string>& items, const string& prompt);
Book* select_book(vector<Book*>& candidates, const string& prompt);
Reader* select_reader(Library& library, const string& prompt);
Book* select_any_book(Library& library, const string& prompt);

void validate_book_fields(string title, string author, int year, string type);
void validate_reader_fields(string name, string phone);

#endif