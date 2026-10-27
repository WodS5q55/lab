#include "Utils.h"
#include "Library.h"
#include "../Exceptions/AllExceptions.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

bool is_blank(const string& str) {
    for (char c : str) if (!isspace(c)) return false;
    return true;
}

bool is_valid_date(const string& date) {
    if (date.length() != 10 || date[2] != '.' || date[5] != '.') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1452 || year > 2026) return false;
    return true;
}

void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int select_from_list(const vector<string>& items, const string& prompt) {
    if (items.empty()) { cout << "Список пуст." << endl; return -1; }
    cout << "\n" << prompt << endl;
    for (size_t i = 0; i < items.size(); ++i) cout << "  " << (i + 1) << ". " << items[i] << endl;
    cout << "  0. Отмена" << endl << "Выберите номер: ";
    int choice;
    cin >> choice;
    if (cin.fail()) { clear_input(); throw InvalidInputException("введено не число"); }
    if (choice == 0) return -1;
    if (choice < 1 || static_cast<size_t>(choice) > items.size()) {
        throw InvalidInputException("неверный номер из списка");
    }
    return choice - 1;
}

string input_non_empty_string(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    if (value.empty() || is_blank(value)) {
        throw InvalidInputException("поле не может быть пустым");
    }
    return value;
}

int input_int_in_range(const string& prompt, int min_val, int max_val) {
    int value;
    cout << prompt;
    cin >> value;
    if (cin.fail()) { clear_input(); throw InvalidInputException("введено не число"); }
    if (value < min_val || value > max_val) {
        throw InvalidInputException("значение должно быть от " + to_string(min_val) + " до " + to_string(max_val));
    }
    clear_input();
    return value;
}

Publication* select_publication(vector<Publication*>& candidates, const string& prompt) {
    vector<string> lines;
    for (auto* pub : candidates) lines.push_back(pub->short_line());
    int idx = select_from_list(lines, prompt);
    if (idx < 0) return nullptr;
    return candidates[idx];
}

Reader* select_reader(Library& library, const string& prompt) {
    vector<string> lines;
    const vector<Reader*>& readers = library.get_readers();
    for (const auto* reader : readers) {
        lines.push_back(reader->get_name() + " (ID: " + to_string(reader->get_id()) + ", тел.: " + reader->get_phone() + ")");
    }
    int idx = select_from_list(lines, prompt);
    if (idx < 0) return nullptr;
    return readers[idx];
}

Publication* select_any_publication(Library& library, const string& prompt) {
    vector<Publication*> all = library.get_publications();
    return select_publication(all, prompt);
}