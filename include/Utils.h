#ifndef UTILS_H
#define UTILS_H

#include "Publication.h"
#include "Reader.h"
#include <vector>
#include <string>

using namespace std;

class Library;

void clear_input();
bool is_blank(const string& str);
bool is_valid_date(const string& date);
int select_from_list(const vector<string>& items, const string& prompt);
Publication* select_publication(vector<Publication*>& candidates, const string& prompt);
Reader* select_reader(Library& library, const string& prompt);
Publication* select_any_publication(Library& library, const string& prompt);

#endif