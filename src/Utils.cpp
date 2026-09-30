#include "Utils.h"
#include "Library.h"
#include "Exceptions.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

bool is_blank(const string& str) {
    for (char c : str) {
        if (!isspace(c)) return false;
    }
    return true;
}

bool is_valid_date(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '.' || date[5] != '.') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 1452 || year > 2026) return false;

    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        days_in_month[1] = 29;
    }

    if (day > days_in_month[month - 1]) return false;

    return true;
}

void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int select_from_list(const vector<string>& items, const string& prompt) {
    if (items.empty()) {
        cout << "Список пуст." << endl;
        return -1;
    }
    cout << "\n" << prompt << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << "  " << (i + 1) << ". " << items[i] << endl;
    }
    cout << "  0. Отмена" << endl;
    cout << "Выберите номер: ";

    int choice;
    cin >> choice;
    if (cin.fail()) {
        clear_input();
        cout << "[ОШИБКА] Введите число." << endl;
        return -1;
    }
    if (choice == 0) {
        cout << "Отменено." << endl;
        return -1;
    }
    if (choice < 1 || static_cast<size_t>(choice) > items.size()) {
        cout << "[ОШИБКА] Неверный номер." << endl;
        return -1;
    }
    return choice - 1;
}

string input_non_empty_string(const string& prompt) {
    string value;
    do {
        cout << prompt;
        getline(cin, value);
        if (value.empty() || is_blank(value)) {
            cout << "[ОШИБКА] Поле не может быть пустым!" << endl;
        }
    } while (value.empty() || is_blank(value));
    return value;
}

int input_int_in_range(const string& prompt, int min_val, int max_val) {
    int value;
    do {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            clear_input();
            cout << "[ОШИБКА] Введите число!" << endl;
            continue;
        }
        if (value < min_val || value > max_val) {
            cout << "[ОШИБКА] Значение должно быть от "
                << min_val << " до " << max_val << "!" << endl;
        }
    } while (value < min_val || value > max_val);
    clear_input();
    return value;
}

Publication* select_publication(vector<Publication*>& candidates, const string& prompt) {
    vector<string> lines;
    for (auto* pub : candidates) {
        lines.push_back(pub->short_line());
    }
    int idx = select_from_list(lines, prompt);
    if (idx < 0) return nullptr;
    return candidates[static_cast<size_t>(idx)];
}

Reader* select_reader(Library& library, const string& prompt) {
    vector<string> lines;
    vector<Reader>& readers = library.get_readers_mutable();
    for (const auto& reader : readers) {
        lines.push_back(reader.get_name() + " (ID: " + to_string(reader.get_id())
            + ", тел.: " + reader.get_phone() + ")");
    }
    int idx = select_from_list(lines, prompt);
    if (idx < 0) return nullptr;
    return &readers[static_cast<size_t>(idx)];
}

Publication* select_any_publication(Library& library, const string& prompt) {
    vector<Publication*> all = library.get_publications();
    return select_publication(all, prompt);
}