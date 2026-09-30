#ifndef UTILS_H
#define UTILS_H

#include "Publication.h"
#include "Reader.h"
#include <vector>
#include <string>

using namespace std;

class Library;

string input_non_empty_string(const string& prompt);
int input_int_in_range(const string& prompt, int min_val, int max_val);
void clear_input();
bool is_blank(const string& str);
bool is_valid_date(const string& date);
int select_from_list(const vector<string>& items, const string& prompt);
Publication* select_publication(vector<Publication*>& candidates, const string& prompt);
Reader* select_reader(Library& library, const string& prompt);
Publication* select_any_publication(Library& library, const string& prompt);

#endif